
void menu()
{
serial_println("Welcome to the MPX Project for group 0. What do you want to do?");
serial_println("1. Help");
serial_println("2. Display version number");
serial_println("3. Get time");
serial_println("4. Set time");
serial_println("5. Get date");
serial_println("6. Set date");
serial_println("7. Shutdown");

char input = takeInput():
int inputInt = atoi(input);
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
 char input2 = takeInput();
 int inpputInt2 = atoi(input2);
 switch(inputInt2)
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
  }
 
 break;

 case 2:
 version();
 break;

 case 3:
 //getTime();
 break;

 case 4:
 //setTime();
 break;

 case 5:
 //getDate();
 break;

 case 6:
 //setDate();
 break;
 
 case 7:
 shutdown();
 break;
 }
}
