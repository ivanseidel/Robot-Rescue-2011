/*
 * $Id: README.txt 57 2011-05-30 19:49:26Z xander $
 */


-= Note =-
These drivers are for RobotC 2.00 and higher and are part of the
version 2.0b2 of the 3rd Party RobotC Drivers suite.

* common.h: substituted functions with macros: min2, min3, max2, max3, clip to save memory, replaces all instances of previous functions in drivers.
* Added driver for MicroInfinity CruizCore XG1300L
* Fixed MSDISTsendCmd()
* Added example MSMMUX-test2.c to show how to use MMUX with a daisy chained sensor (DIST-nx)

-= Previous changes=- (2.0b1)

* Removed unnecessary common.h includes from examples
* Changed arrays from structs to just typedefs, all drivers have been adjusted
* motor mux stuff split off from common.h
* All SMUX supported drivers now use new SMUX mechanism
* Modified common.h to separate SMUX functions from rest using defines
* removed ubyteToInt from all drivers and common.h
* test programs have had their sensor types reconfigured, you will need ROBOTC 2.26
* HTSMUX-driver.h newly added, has all the new SMUX functions split from common.h
* MMUX-common.h newly added, contains all the MMUX functions split from common.h
* added min/max functions for floats
* light-common.h: newly added, adds RGBtoHSV conversion
* HTCS-driver.h/HTCS2-driver.h: added functions for HSV values
* HTMC-driver.h: Improved relative heading algorithm 
* added DGPSreadTravHeading() to DGPS-driver.h and fixed commands
* Removed single axis functions from HTAC-driver.h
* Removed functions for single signal strength in HTIRS and HTIRS2.
* Removed No Wait functions from EOPD driver
* Removed HTIRL-NG, is now named HTIRL
* Changed arguments from byte to ubyte in MSLL-driver.h
* All applicable Mindsensors sensors now have an optional "address" argument that can be ommitted if using the default


-= API Documentation =-
The complete API documentation can be found in the html folder.
Just point your browser at the index.html file.


-= Downloads and support =-
These drivers can also be downloaded from:
http://sourceforge.net/projects/rdpartyrobotcdr/

The documentation is hosted here:
http://rdpartyrobotcdr.sourceforge.net/documentation/index.html

For support questions, please use the RobotC 3rd party sensors forum:
http://www.robotc.net/forums/viewforum.php?f=41

Thanks,
Xander Soldaat (mightor@gmail.com)

/*
 * $Id: README.txt 57 2011-05-30 19:49:26Z xander $
 */