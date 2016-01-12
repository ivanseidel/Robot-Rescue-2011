/*!@addtogroup Lego
 * @{
 * @defgroup legols Light Sensor
 * Light Sensor
 * @{
 */

/*
 * $Id: LEGOLS-driver.h 47 2011-01-17 19:47:22Z xander $
 */

#ifndef __LEGOLS_H__
#define __LEGOLS_H__
/** \file LEGOLS-driver.h
 * \brief Lego Light Sensor driver
 *
 * LEGOLS-driver.h provides an API for the Lego Light Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Make use of new calls for analogue SMUX sensors in common.h
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 25 November 2009
 * \version 0.2
 * \example LEGOLS-test1.c
 * \example LEGOLS-test2.c
 * \example LEGOLS-SMUX-test1.c
 * \example LEGOLS-SMUX-test2.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

#define LEGOLSDAT "legols.dat"    /*!< Datafile for Light Sensor calibration info */

// Globals
int lslow = 0;                    /*!< Low calibration value */
int lshigh = 1023;                /*!< High calibration value */
bool legols_calibrated = false;   /*!< Has the sensor been calibrated yet */

// Function prototypes
int LSvalRaw(tSensors link);
int LSvalNorm(tSensors link);
void LScalLow(tSensors link);
void LScalLow(int lowval);
void LScalHigh(tSensors link);
void LScalHigh(int highval);
void LSsetActive(tSensors link);
void LSsetInactive(tSensors link);

#ifdef __HTSMUX_SUPPORT__
int LSvalNorm(tMUXSensor muxsensor);
void LScalLow(tMUXSensor muxsensor);
int LSvalRaw(tMUXSensor muxsensor);
void LScalHigh(tMUXSensor muxsensor);
void LSsetActive(tMUXSensor muxsensor);
void LSsetInactive(tMUXSensor muxsensor);
#endif // __HTSMUX_SUPPORT__

void _LScheckSensor(tSensors link);
void _LSwriteCalVals(int lowval, int highval);
void _LSreadCalVals(int &lowval, int &highval);


/**
 * Read the raw value of the Light Sensor.
 * @param link the Light Sensor port number
 * @return the raw value of the Light Sensor
 */
int LSvalRaw(tSensors link) {
  _LScheckSensor(link);

  return SensorRaw[link];
}


/**
 * Read the raw value of the Light Sensor.
 * @param muxsensor the SMUX sensor port number
 * @return the raw value of the Light Sensor
 */
#ifdef __HTSMUX_SUPPORT__
int LSvalRaw(tMUXSensor muxsensor) {
  return 1023 - HTSMUXreadAnalogue(muxsensor);
}
#endif // __HTSMUX_SUPPORT__

/**
 * Read the normalised value of the Light Sensor, based on the low and high values.
 * @param link the Light Sensor port number
 * @return the normalised value
 */
int LSvalNorm(tSensors link) {
  long currval = 0;

  _LScheckSensor(link);

  if (!legols_calibrated) {
    _LSreadCalVals(lslow, lshigh);
  }

  currval = LSvalRaw(link);

  if (currval <= lslow)
    return 0;
  else if (currval >= lshigh)
    return 100;

  return ((currval - lslow) * 100) / (lshigh - lslow);
}


/**
 * Read the normalised value of the Light Sensor, based on the low and high values.
 * @param muxsensor the SMUX sensor port number
 * @return the normalised value
 */
 #ifdef __HTSMUX_SUPPORT__
int LSvalNorm(tMUXSensor muxsensor) {
  long currval = 0;

  if (!legols_calibrated) {
    _LSreadCalVals(lslow, lshigh);
  }

  currval = LSvalRaw(muxsensor);

  if (currval <= lslow)
    return 0;
  else if (currval >= lshigh)
    return 100;

  return ((currval - lslow) * 100) / (lshigh - lslow);
}
#endif // __HTSMUX_SUPPORT__

/**
 * Calibrate the Light Sensor's low calibration value with the current raw sensor reading.
 * @param link the Light Sensor port number
 */
void LScalLow(tSensors link) {
  _LScheckSensor(link);

  lslow = SensorRaw[link];
  _LSwriteCalVals(lslow, lshigh);
}


/**
 * Calibrate the Light Sensor's low calibration value with the current raw sensor reading.
 * @param muxsensor the SMUX sensor port number
 */
#ifdef __HTSMUX_SUPPORT__
void LScalLow(tMUXSensor muxsensor) {
  lslow = LSvalRaw(muxsensor);
  _LSwriteCalVals(lslow, lshigh);
}
#endif // __HTSMUX_SUPPORT__


/**
 * Calibrate the Light Sensor's low calibration value with the supplied value.
 * @param lowval the sensor's low calibration value
 */
void LScalLow(int lowval) {
  lslow = lowval;
  _LSwriteCalVals(lslow, lshigh);
}


/**
 * Calibrate the Light Sensor's high calibration value with the current raw sensor reading.
 * @param link the Light Sensor port number
 */
void LScalHigh(tSensors link) {
  _LScheckSensor(link);

  lshigh = SensorRaw[link];
  _LSwriteCalVals(lslow, lshigh);
}


/**
 * Calibrate the Light Sensor's high calibration value with the current raw sensor reading.
 * @param muxsensor the SMUX sensor port number
 */
#ifdef __HTSMUX_SUPPORT__
void LScalHigh(tMUXSensor muxsensor) {
  lshigh = LSvalRaw(muxsensor);
  _LSwriteCalVals(lslow, lshigh);
}
#endif // __HTSMUX_SUPPORT__


/**
 * Calibrate the Light Sensor's high calibration value with the supplied value.
 * @param highval the sensor's high calibration value
 */
void LScalHigh(int highval) {
  lshigh = highval;
  _LSwriteCalVals(lslow, lshigh);
}


/**
 * Configure the sensor as a LightActive sensor
 * @param link the Light Sensor port number
 */
void LSsetActive(tSensors link) {
  SensorType[link] = sensorLightActive;
  SensorMode[link] = modeRaw;
  wait1Msec(5);
}


/**
 * Configure the sensor as a LightActive sensor
 * @param muxsensor the SMUX sensor port number
 */
#ifdef __HTSMUX_SUPPORT__
void LSsetActive(tMUXSensor muxsensor) {
  HTSMUXsetAnalogueActive(muxsensor);
}
#endif // __HTSMUX_SUPPORT__


/**
 * Configure the sensor as a LightInactive sensor
 * @param link the Light Sensor port number
 */
void LSsetInactive(tSensors link) {
  SensorType[link] = sensorLightInactive;
  SensorMode[link] = modeRaw;
  wait1Msec(5);
}


/**
 * Configure the sensor as a LightInactive sensor
 * @param muxsensor the SMUX sensor port number
 */
#ifdef __HTSMUX_SUPPORT__
void LSsetInactive(tMUXSensor muxsensor) {
  HTSMUXsetAnalogueInactive(muxsensor);
}
#endif // __HTSMUX_SUPPORT__


/**
 * Check if the sensor is set to raw and that it's been configured as a
 * LightActive or Inactive sensor.  If not, set the default to sensorLightInActive.
 *
 * Note: this is an internal function and should not be called directly
 * @param link the Light Sensor port number
 */
void _LScheckSensor(tSensors link) {
  if (SensorMode[link] != modeRaw &&
    ((SensorType[link] != sensorLightActive) ||
     (SensorType[link] != sensorLightInactive))) {
      LSsetInactive(link);
    }
}


/**
 * Write the low and high calibration values to a data file.
 *
 * Note: this is an internal function and should not be called directly
 * @param lowval the low calibration value
 * @param highval the high calibration value
 */
void _LSwriteCalVals(int lowval, int highval) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize = 4;

  // Delete the old data file and open a new one for writing
  Delete(LEGOLSDAT, nIoResult);
  OpenWrite(hFileHandle, nIoResult, LEGOLSDAT, nFileSize);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    eraseDisplay();
    nxtDisplayTextLine(3, "W:can't cal file");
    PlaySound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    StopAllTasks();
  }

  // Write the low calibration value
  WriteShort(hFileHandle, nIoResult, lowval);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "can't write lowval");
    PlaySound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    StopAllTasks();
  }

  // Write the high calibration value
  WriteShort(hFileHandle, nIoResult, highval);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "can't write highval");
    PlaySound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    StopAllTasks();
  }

  // Close the file
  Close(hFileHandle, nIoResult);
  if (nIoResult != ioRsltSuccess) {
    eraseDisplay();
    nxtDisplayTextLine(3, "Can't close");
    PlaySound(soundException);
    while(bSoundActive);
    wait1Msec(5000);
    StopAllTasks();
  }
}

/**
 * Read the low and high calibration values from a data file.
 *
 * Note: this is an internal function and should not be called directly
 * @param lowval the low calibration value
 * @param highval the high calibration value
 */
void _LSreadCalVals(int &lowval, int &highval) {
  TFileHandle hFileHandle;
  TFileIOResult nIoResult;
  short nFileSize;

  short lv = 0;
  short hv = 0;

  // Open the data file for reading
  legols_calibrated = true;
  OpenRead(hFileHandle, nIoResult, LEGOLSDAT, nFileSize);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the low calibration value
  ReadShort(hFileHandle, nIoResult, lv);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Read the high calibration value
  ReadShort(hFileHandle, nIoResult, hv);
  if (nIoResult != ioRsltSuccess) {
    Close(hFileHandle, nIoResult);
    return;
  }

  // Assign values and close file
  lowval = lv;
  highval = hv;
  Close(hFileHandle, nIoResult);
}

#endif // __LEGOLS_H__

/*
 * $Id: LEGOLS-driver.h 47 2011-01-17 19:47:22Z xander $
 */
/* @} */
/* @} */
