/*!@addtogroup Lego
 * @{
 * @defgroup legots Touch Sensor
 * Touch Sensor
 * @{
 */

/*
 * $Id: LEGOTS-driver.h 47 2011-01-17 19:47:22Z xander $
 */

#ifndef __LEGOTS_H__
#define __LEGOTS_H__
/** \file LEGOTS-driver.h
 * \brief Lego Touch Sensor driver
 *
 * LEGOTS-driver.h provides an API for the Lego Touch Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 08 December 2009
 * \version 0.1
 * \example LEGOTS-test1.c
 * \example LEGOTS-SMUX-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

// Function prototypes
bool TSreadState(tSensors link);

#ifdef __HTSMUX_SUPPORT__
bool TSreadState(tMUXSensor muxsensor);
#endif


/**
 * Read the state of the touch sensor
 * @param link the Touch Sensor port number
 * @return true if the sensor is pressed, false if it's not
 */
bool TSreadState(tSensors link) {
  if ((SensorType(link) !=  sensorTouch) && SensorMode(link) != modeBoolean) {
    SetSensorType(link, sensorTouch);
    SetSensorMode(link, modeBoolean);
    wait1Msec(10);
  }

  return (SensorRaw[link] < 500) ? true : false;
}


/**
 * Read the state of the touch sensor
 * @param muxsensor the SMUX sensor port number
 * @return true if the sensor is pressed, false if it's not
 */
#ifdef __HTSMUX_SUPPORT__
bool TSreadState(tMUXSensor muxsensor) {
  return (HTSMUXreadAnalogue(muxsensor) < 500) ? true : false;
}
#endif


#endif // __LEGOTS_H__

/*
 * $Id: LEGOTS-driver.h 47 2011-01-17 19:47:22Z xander $
 */
/* @} */
/* @} */
