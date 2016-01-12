#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTPB-exp1.c 49 2011-04-27 13:00:05Z xander $
 */

/**
 * HTPB-driver.h provides an API for the HiTechnic Protoboard.  This is program 1
 * for the HTPB experimenter's kit.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 14 February 2011
 * version 0.2
 */

#include "drivers/HTPB-driver.h"

task main() {
  // Local variables
  int inputdata;

  // The data to be written: 0x3F = 111111 binary,
  // makes all digital ports outputs.
  HTPBsetupIO(HTPB, 0x3F);

  while(true) {
    // Read a 10bit wide analogue value from A0
    inputdata = HTPBreadADC(HTPB, 0, 10);
    eraseDisplay();
    nxtDisplayTextLine(1, "%d", inputdata);

    // If A0 is less than 50% of the max value
    // turn off the LED, otherwise switch it on
    if(inputdata < 512)
      HTPBwriteIO(HTPB, 0x00);
    else
      HTPBwriteIO(HTPB, 0x01);

    wait1Msec(50);
  }
}

/*
 * $Id: HTPB-exp1.c 49 2011-04-27 13:00:05Z xander $
 */
