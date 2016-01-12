/*
 * $Id: Driver Template.h 20 2009-12-08 22:59:13Z xander $
 */

/** \file <template>.h
 * \brief RobotC <device> Driver
 *
 * <filename>.h provides an API for the <device>.
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date <date>
 * \version <version>
 */

#pragma systemFile            

#define <DEVICE>_I2C_ADDR 0x02      /*!< <device> I2C device address */
#define <DEVICE>_A0_U     0x42      /*!< some register */

/*! Some define. */
#define DEF_SOMETHING   32

/*! arbStruct struct, <short explanation. */
typedef struct {
	int size;                 /*!< Number of bytes used */
	int arr[DEF_SOMETHING];   /*!< Array containing data */
} arbStruct;

/*
<function prototypes>
*/

/**
 * This function does something
 * @param foo a param to allow baz
 * @return some value
 */
byte arbFunc(byte foo) {
  return foo;
}

/*
 * $Id: Driver Template.h 20 2009-12-08 22:59:13Z xander $
 */
