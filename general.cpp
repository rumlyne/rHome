// set relative masters' addresses
// byte masterMaddr = 000 ; // relative master address // don't set - he will call YOU!
byte masterSaddr = 001 ; // relative slave address

// set own master & slave addresses
byte ownMaddr = 010 ; // 020,030,040,050,...
byte ownSaddr = 011 ; // 021,031,041,051,...

// set relative/fellow slave addresses // here none because this is an aio unit
// byte slave1Saddr = 031 ; // 041,051,061,071,081,...
// byte slave2Saddr = 041 ; // 051,061,071,081,091,...



/***
 *     ######  ######## ########   ########  ##     ## ######## ########  #######  ##    ##  ######
 *    ##    ## ##          ##      ##     ## ##     ##    ##       ##    ##     ## ###   ## ##    ##
 *    ##       ##          ##      ##     ## ##     ##    ##       ##    ##     ## ####  ## ##
 *     ######  ######      ##      ########  ##     ##    ##       ##    ##     ## ## ## ##  ######
 *          ## ##          ##      ##     ## ##     ##    ##       ##    ##     ## ##  ####       ##
 *    ##    ## ##          ##      ##     ## ##     ##    ##       ##    ##     ## ##   ### ##    ##
 *     ######  ########    ##      ########   #######     ##       ##     #######  ##    ##  ######
 */



/*
// set digital buttons
EasyButton li_1( ab00 ) ;
EasyButton li_0( ab01 ) ;
EasyButton ro_1( ab02 ) ;
EasyButton ro_0( ab03 ) ;
*/



void setup() {
    // config easybuttons
    // button.begin() ;
}
