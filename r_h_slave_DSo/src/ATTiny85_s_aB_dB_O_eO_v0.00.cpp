/***
   *
   *  possible output pins
   *  3 // digital/analog
   *  5 // digital/analog
   *  1 // digital/pwm
   *  4 // digital/analog/pwm // used by analog button row 0
   *
   *  possible analog button row pins
   *  A2 // digital pin 4 // 1023 PWM
   *  A0 // digital pin 5
   *  A3 // digital pin 3 // 1.5k pullup
   * !A1 // digital pin 2 cannot be used b/c i2c
   *
   */

#include <Arduino.h>
#include <SmallSetup.h>
#include <TinyWire.h>
#include <EasyButton.h>
#include <Ticker.h>



/***
   *     ######  ######## ########    ####  #######   ######        ###    ########  ########  ########
   *    ##    ## ##          ##        ##  ##     ## ##    ##      ## ##   ##     ## ##     ## ##     ##
   *    ##       ##          ##        ##         ## ##           ##   ##  ##     ## ##     ## ##     ##
   *     ######  ######      ##        ##   #######  ##          ##     ## ##     ## ##     ## ########
   *          ## ##          ##        ##  ##        ##          ######### ##     ## ##     ## ##   ##
   *    ##    ## ##          ##        ##  ##        ##    ##    ##     ## ##     ## ##     ## ##    ##
   *     ######  ########    ##       #### #########  ######     ##     ## ########  ########  ##     ##
   *
   *
   *  reserved addresses:
   *    0      0b0000000 0  0x00       general call
   *    1      0b0000000 1  0x01       start byte
   *  2-3      0b0000001 x  0x02-0x03  cbus addresses
   *  4-5      0b0000010 x  0x04-0x05  different bus format
   *  6-7      0b0000011 x  0x06-0x07  future purposes
   *  8-15     0b00001xx x  0x08-0x0F  hs-mode master code
   *  249-255  0b11111xx 1  0xF9-0xFF  device id
   *  240-247  0b11110xx x  0xF0-0xF7  10-bit slave addressing
   *
   *  pseudo reserved addresses:
   *   1    0b0001   0x01  Digital receivers, SMBus
   *   2    0b0010   0x02  TV video line decoders, IPMB
   *   3    0b0011   0x03  AV codecs
   *   4    0b0100   0x04  Video encoders, GPIO expanders
   *   5    0b0101   0x05  ACCESS bus, PMBus
   *   6    0b0110   0x06  VESA DDC, PMBus
   *   7    0b0111   0x07  Display controller
   *   8    0b1000   0x08  TV signal processing, audio processing, SMBus
   *   9    0b1001   0x09  AV switching, ADCs and DACs, IPMB, SMBus
   *  10    0b1010   0x0A  Storage memory, real-time clock
   *  11    0b1011   0x0B  AV processors
   *  12    0b1100   0x0C  PLLs and tuners, modulators and demodulators, SMBus
   *  13    0b1101   0x0D  AV processors and decoders, audio power amplifiers, SMBus
   *  14    0b1110   0x0E  AV colour space converters
   */

// set own master & slave addresses
const byte ownMaddr = 030; // 032,034,036,038,...
const byte ownSaddr = 031; // 033,035,037,039,...

// include relative master's (server/subserver) slave address '021' too!
const byte slaveSaddr[] =
   { 021, 031/*, 033, 035, 037, 039,...*/ }
;



/***
   *
   *  set i2c registers
   *
   *    0   0x00  analog   0  // 0-254
   *    1   0x01  analog   1  // 0-254
   *    2   0x02  analog   2  // 0-254
   *  ...
   *   16   0x0F  analog   15 // 0-254
   *
   *   17   0x10  digital  0  // 0/1
   *   18   0x11  digital  1  // 0/1
   *   19   0x12  digital  2  // 0/1
   *  ...
   *   30   0x1F  digital  15 // 0/1
   *
   *  ...
   *  250   0xFA  aux
   *  251   0xFB  id
   *  252   0xFC  mode register
   *  253   0xFD  configuratiom register
   *  254   0xFE  status register
   *  255   0xFF  // probably reserved for sth
   *
   */


const byte slaveRegs[ 256 ];

const byte sthsth // TODO



/***
   *     #######  ########      ##         ##
   *    ##     ## ##     ##     ##       ####
   *    ##     ## ##     ##     ##         ##
   *    ##     ## ########      ##         ##
   *    ##     ## ##            ##         ##
   *    ##     ## ##            ##         ##
   *     #######  ##            ######## ######
   */

// set relative/fellow slave addresses to use as external outputs
const byte eOutput[] = {
   // registeradresses
   /*identifier of external output slave-register array TODO*/
};
// set pin array // onboard a/d output options // max 4 (with i2c enabled)
const byte aOutput[] = {
   // output pins: d/a, d/a, d/p, d/a/p
   3/*a*//*, 1d, 5?, 4?*/
};
const byte dOutput[] = {
   1/*d*/ /*, 3?, 5?, 4?*/
};



/***
   *    #### ########      ##         ##
   *     ##  ##     ##     ##       ####
   *     ##  ##     ##     ##         ##
   *     ##  ########      ##         ##
   *     ##  ##            ##         ##
   *     ##  ##            ##         ##
   *    #### ##            ######## ######
   */

// set analog button config
const byte aInputs[] = {
   /*A*/2/*, /*A0, /*A3 */
};


const byte aB[ sizeof ( aInputs ) /*/ sizeof( byte )*/ ] = {
   // corresponding analog measurem for each attached button OR
   // virtual button (2 pressed at the same time)
   // --divide by 4 to fit in one byte // see excel
   244, 234, 223, 210, 199, 180, 164, 152, 140, 128
   /*, 116, 104, 92, 81, 71, 61, 49, 39, 28, 18, 10,...k*/
};

// set digital button config
const byte dInputs[] = {
// digital input pins
   /*5, 3, 1, 4*/
};

const byte dB[] = {
   /*debounced buttons TODO*/
};



/***
   *    #### ########      ##        #######
   *     ##  ##     ##     ##       ##     ##
   *     ##  ##     ##     ##              ##
   *     ##  ########      ##        #######
   *     ##  ##            ##       ##
   *     ##  ##            ##       ##
   *    #### ##            ######## #########
   */

// set total button array
byte tB[ 2 ][
   (sizeof( aInputs ) /*/ sizeof( byte )*/) *
   (sizeof( aB ) /*/ sizeof( byte )*/) +
   (sizeof( dB ) /*/ sizeof( byte )*/) ] = {
      {  },
      // state
      { /*0*/ }
}




/***
   *     ######  ######## ########    ##     ##    ###    ##       ##     ## ########  ######
   *    ##    ## ##          ##       ##     ##   ## ##   ##       ##     ## ##       ##    ##
   *    ##       ##          ##       ##     ##  ##   ##  ##       ##     ## ##       ##
   *     ######  ######      ##       ##     ## ##     ## ##       ##     ## ######    ######
   *          ## ##          ##        ##   ##  ######### ##       ##     ## ##             ##
   *    ##    ## ##          ##         ## ##   ##     ## ##       ##     ## ##       ##    ##
   *     ######  ########    ##          ###    ##     ## ########  #######  ########  ######
   */

// MAYBE NOT SET VALUES

// set whole analog button state && old state
byte valaBs = 0;
byte valaBso = 0;

// set relay/dimmer variables
bool valRe0 = 0;
// bool valRe1 = 0;
byte valDi0 = 0;
// int valDi1 = 0;

// set ticker to replayce delay()
const unsigned long manDeb = 33
// set manual debounce/delay time
const unsigned long manDel = 330


int i, ii, iii;
int j, jj, jjj;
int k/*, kk*/;
int /*l, */ll, lll;
// int m;
// int n;
// int o;



/***
   *    ##     ##     ######  ######## ######## ##     ## ########
   *    ##     ##    ##    ## ##          ##    ##     ## ##     ##
   *    ##     ##    ##       ##          ##    ##     ## ##     ##
   *    ##     ##     ######  ######      ##    ##     ## ########
   *     ##   ##           ## ##          ##    ##     ## ##
   *      ## ##      ##    ## ##          ##    ##     ## ##
   *       ###        ######  ########    ##     #######  ##
   */

/*inline */void setup() {

   // config TinyWire library for I2C slave functionality
   TinyWire.begin( ownSaddr );
   // set slave receive callback
   TinyWire.onReceive( i2cReceive );



   /***
      *     #######  ########      ##        #######
      *    ##     ## ##     ##     ##       ##     ##
      *    ##     ## ##     ##     ##              ##
      *    ##     ## ########      ##        #######
      *    ##     ## ##            ##       ##
      *    ##     ## ##            ##       ##
      *     #######  ##            ######## #########
      */

   // generate 2d total output array from smaller individual output arrays
   byte tOutput[ 2 ][
      (sizeof( eOutput ) /*/ sizeof( byte )*/) +
      (sizeof( aOutput ) /*/ sizeof( byte )*/) +
      (sizeof( dOutput ) /*/ sizeof( byte )*/) ];


// DOES THIS WORK!? TODO CHECK
   for (
      int i = 0;
      i < ( sizeof( eOutput ) + sizeof( aOutput ) + sizeof( dOutput ) );
      i++ ) {
         if (
            i < sizeof( eOutput ) {
               tOutput[ 0 ][ i ] = eOutput[ i ]
         }
         else if (
            sizeof( eOutput )
            < i <
            (sizeof( eOutput ) + sizeof( aOutput )) ) {
               tOutput[ 0 ][ i ] = aOutput[ i - sizeof( eOutput ) ]
         }
         else if (
            (sizeof( eOutput ) + sizeof( aOutput ))
            < i <
            (sizeof( eOutput ) + sizeof( aOutput ) + sizeof( dOutput )) ) {
               tOutput[ 0 ][ i ] = dOutput[ i - sizeof( eOutput ) - sizeof( aOutput ) ]
         }/* else {
            //TODO send error maybe?
         } */
   };

tOutput[ 0 ][ i ] = eOutput[ i ]
// TODO end

   // END OP L2



   // enable all outputs after external outputs
   for(
      i = sizeof( eOutput );
      i < sizeof( tOutput );
      i++ ) {
         pinMode( tOutputs[ 0 ][ i ], OUTPUT );
   };

   // need not set pinmode on digispark-tiny
   /*
   // enable all inputs
   for( j = 0; j < sizeof( dInputs ) - 1; j++ ) {
      pinMode( dInputs[ j ], INPUT );
   };
   */

}



/***
   *    ##     ##    ##        #######   #######  ########
   *    ##     ##    ##       ##     ## ##     ## ##     ##
   *    ##     ##    ##       ##     ## ##     ## ##     ##
   *    ##     ##    ##       ##     ## ##     ## ########
   *     ##   ##     ##       ##     ## ##     ## ##
   *      ## ##      ##       ##     ## ##     ## ##
   *       ###       ########  #######   #######  ##
   */

/*inline */void loop() {


   // switch part

   // read state of buttons
   for(
      k = 0;
      k < (sizeof( aInputs ) / sizeof( byte ));
      k++ ) {
         // write highest reading input to valaB // TODO
         analogRead( aInputs[ k ] ),
         TODO;
   }

   /*
   // read state of digital buttons
   for(
      kk = 0;
      kk < sizeof( dB );
      kk++ ) {
         digitalRead( dB[ kk ] ),
         TODO write to tB;
   };
   */


   // check if any button was pressed
   if ( valaB != ) {

      // check if a button changed // TODO
      if ( valaB != valaBo ) {

         // check if a button was held // TODO
         if ( valaB0 == valaBo ) {
         }

      }

   };



   for(
      l = 0;
      l < sizeof( tOutput );
      l++ ) {
         if (
            ((sizeof( tOutput ) - sizeof( aOutput ) - sizeof( dOutput ))
            < l <
            (sizeof( eOutput ) - sizeof( dOutput )) ) {
               analogWrite( tOutputs[ 0 ][ l ], tOutputs[ 1 ][ l ] );
         };
         if (
            (sizeof( tOutput ) - sizeof( dOutput ))
            < l <
            sizeof( eOutput ) ) {
               if ( tOutputs[ 1 ][ l ] == 1 ) {
                  digitalWrite( tOutputs[ 0 ][ l ], HIGH );
               } else if ( tOutputs[ 1 ][ l ] == 0 ) {
                  digitalWrite( tOutputs[ 0 ][ l ], LOW );
               }/* else {
                  //TODO send error maybe?
               } */
            }
   };

   // last tasks in loop part

   // save current value of button rows to compare to next time
   byte valaBo = valaB;
   // debounce // disable?
   tick ( manDeb );

}



/***
   *    ##     ##    ####  #######   ######          ########
   *    ##     ##     ##  ##     ## ##    ##         ##     ##
   *    ##     ##     ##         ## ##               ##     ##
   *    ##     ##     ##   #######  ##               ########
   *     ##   ##      ##  ##        ##               ##   ##
   *      ## ##       ##  ##        ##    ##         ##    ##
   *       ###       #### #########  ######  ####### ##     ##
   */

void i2cReceive( int TODO ) {
   // loops, until all received bytes are read
   while(TinyWire.available() >0 ){

      // switches on relay, when an 'TODO Re1 on' is received
      if( TinyWire.read() == 'TODO valRe0 state' ) {
         digitalWrite( Re0 , HIGH ); // TODO
         valRe0 = ( TinyWire.read() == 'TODO valRe0 state' )
         tick( manDeb );
      }

      // controls dimmer, when an 'TODO Di0 valDi0' is received
      if( TinyWire.read() == 'TODO valDi1_0-254' ) {
         analogWrite( Di0 , valDi0 ); // TODO
         valDi0 = ( TinyWire.read() == 'TODO valDi1_0-254' ) // TODO
         tick( manDeb );
      }


      // write values to output pins

      // relay/dimmer/some active component part

   }

   tick( manDel );
}



// #include <SmallSetup.h>
