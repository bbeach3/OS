#include <core/serial.h>
#include <core/io.h>

/** \file
 *Contains the source code for the function that prints out the version number
 *Contains the source code for the function that prints out the version number
*/

/**
\Function: version
\Description: prints out the current version number
\Parameters: none
\Returns: none
*/
void version()
{
serial_println("This is version 5 of MPX");
}
