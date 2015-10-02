/** \file
 *Contains the source code for the menu
 *Contains the source code for the menu and functions related to executing the command from the menu
*/

/**
\Function: menu
\Description: Prints out the menu, and allows users to enter their input and have the system 
\Parameters: none
\Returns: none
*/
#include "kernel/core/keyboardInput.c"
#include "include/core/shutdown.c"
#include "include/core/version.c"
#include "include/core/help.c"
#include "modules/time.c"
void menu()
{
int x=1;
while(x==1)
{
serial_println("Welcome to the MPX Project for group 0. What do you want to do?");
serial_println("1. Help");
serial_println("2. Display version number");
serial_println("3. Get time");
serial_println("4. Set time");
serial_println("5. Get date");
serial_println("6. Set date");
serial_println("7. Shutdown");

int size=20;
char *input[size];
takeInput(*input,size);
char *input2 = input[0];
int inputInt = atoi(input2);
switch(inputInt)
 {
 case 1:
 serial_println("What command would you like help with?");
 serial_println("1. Display version number");
 serial_println("2. Get time");
 serial_println("3. Set time");
 serial_println("4. Get date");
 serial_println("5. Set date");
 serial_println("6. Shutdown");
 serial_println("7. Go back");
 
 takeInput(*input,size);
 input2 = input[0];
 inputInt = atoi(input2);
 switch(inputInt)
  {
  case 1: version_help();
  break;

  case 2: gettime_help();
  break;

  case 3: settime_help();
  break;

  case 4: getdate_help();
  break;

  case 5: setdate_help();
  break;

  case 6: shutdown_help();
  break;

  case 7:
  break;
  }
 
 break;

 case 2:
 version();
 break;

 case 3:
 gettime();
 break;

 case 4:
 //settime();
 break;

 case 5:
 getdate();
 break;

 case 6:
 //setdate();
 break;
 
 case 7:
// shutdown();
x=0;
 break;
 }
}
}
