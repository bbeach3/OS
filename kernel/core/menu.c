
void menu()
{
int x =1;
while(x==1);
{
serial_println("Welcome to the MPX Project for group 0. What do you want to do?");
serial_println("1. Help");
serial_println("2. Display version number");
serial_println("3. Get time");
serial_println("4. Set time");
serial_println("5. Get date");
serial_println("6. Set date");
serial_println("7. Shutdown");

int size=50;
char *input[size];
takeInput(*input,size);
char input2 = *input[0];
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
 input2 = *input[0];
 inpputInt = atoi(input2);
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

  case 7: //I don't know how to go back
  break;
  }
 
 break;

 case 2:
 version();
 //need to display menu and take in input again
 break;

 case 3:
 //getTime();
 //need to display menu and take in input again
 break;

 case 4:
 //setTime();
 break;

 case 5:
 //getDate();
 //nned to display menu and take in input again
 break;

 case 6:
 //setDate();
 break;
 
 case 7:
 shutdown();
 break;
 }
}
}