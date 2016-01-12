#pragma config(Sensor, S1,     cam,                 sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: NXTCAM-test2.c 46 2011-01-16 16:56:49Z xander $
 */

/**
 * NXTCAM-driver.h provides an API for the Mindsensors NXTCam.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Gordon Wyeth for writing the original driver and cam_display program
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 28 November 2009
 * version 0.2
 */

#include "drivers/NXTCAM-driver.h"

// int xscale(int x) - Scales x values from camera coordinates to screen coordinates.
int xscale(int x) {
  return ((x - 12) * 99) / 87;
}

// int yscale(int y) - Scales y values from camera coordinates to screen coordinates.
int yscale(int y) {
  return ((143 - y) * 63) / 143;
}

/*
 Main task
 */
task main () {
  blob_array _blobs;
  memset(_blobs, 0, sizeof(blob_array));

  // combine all colliding blobs into one
  bool _condensed = true;

  //blob_array _blobs;
  int _l, _t, _r, _b;
  int _x, _y;
  int _nblobs;
  eraseDisplay();

  // Initialise the camera
  NXTCAMinit(cam);
  while(true) {
    eraseDisplay();
    // Fetch all the blobs, have the driver combine all
    // the colliding blobs.
    _nblobs = NXTCAMgetBlobs(cam, _blobs, _condensed);
    for (int i = 0; i < _nblobs; i++) {
      // Draw the scaled blobs
      _l = xscale(_blobs[i].x1);
      _t = yscale(_blobs[i].y1);
      _r = xscale(_blobs[i].x2);
      _b = yscale(_blobs[i].y2);
      nxtDrawRect(_l, _t, _r, _b);

    }
    NXTCAMgetAverageCenter(_blobs, 3, 0, _x, _y);
    _x = xscale(_x);
    _y = yscale(_y);
    nxtEraseRect(_x-4, _y-4, _x+4, _y+4);
    nxtDrawLine(_x, _y+2, _x, _y-2);
    nxtDrawLine(_x+2, _y, _x-2, _y);
    nxtDisplayTextLine(1, "%d", _nblobs);
    wait1Msec(100);
  }
}

/*
 * $Id: NXTCAM-test2.c 46 2011-01-16 16:56:49Z xander $
 */
