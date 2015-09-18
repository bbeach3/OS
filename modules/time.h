#ifndef _TIME_H
#define _TIME_H

#include "core/io.h"
#include "core/serial.h"
#include "string.h"

/*
  Procedure..: getdate
  Description..: Retrieves the current date.
*/
void getdate();

/*
  Procedure..: gettime
  Description..: Retrieves the current time.
*/
void gettime();

/*
  Procedure..: setdate
  Description..: Modifies the stored date to the user's input.
  Params..: datestring-The date the time should become.
*/
void setdate(char datestring[]);

/*
  Procedure..: settime
  Description..: Modifies the stored time to the user's input.
  Params..: timestring-The time the time should become.
*/
void settime(char timestring[]);

#endif
