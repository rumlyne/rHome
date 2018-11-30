4 button multiswitch

LIGHT
2 buttons report on/off (short press) or more/less (hold) to master
cycle through colors with

ROLLER BLINDS
2 bottons report on(shut)/off(open) (short press) or down/up (hold) to master


BOARD
digispark-tiny (Attiny85)


Überdash for diagram
‾


short press / hold / ! double hold !
 _____________________________________________________
|                 |                 |                 |
|  light on/more  |  light change+  |  roller off/up  |
|       li_1      |       lc_1      |       ro_0      |
|        1k       |       10k       |       82k       |
|                 |     ! 83k !     |                 |
|-----------------|-----------------|-----------------|
|                 |                 |                 |
|  light off/less |  light change-  |  roller on/down |
|       li_0      |       12k       |       ro_1      |
|        3k       |     ! 69k !     |       68k       |
|                 |                 |                 |
 ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾


VCC------------------------------------------------------------
          |           |           |           |               |
         1k          3k          10k         12k          13=<n=<100k
          |           |           |           |               |
        button      button      button      button         button n
          |           |           |           |               |
analogpin------------------------------------------------------
          |
   100k pulldown

see excel for further information
