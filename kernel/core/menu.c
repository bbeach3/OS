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
#include "modules/mod2/pcb.h"
#include "modules/mod2/queue.h"

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
serial_println("7. PCB options");
serial_println("8. Shutdown");

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
 //PCB menu
 serial_println("What PCB-related command would you like?");
 serial_println("1. Suspend");
 serial_println("2. Resume");
 serial_println("3. Set Priority");
 serial_println("4. Show PCB");
 serial_println("5. Show all Processes");
 serial_println("6. Show Ready Processes");
 serial_println("7. Show Blocked Processes");
 serial_println("8. Temporary Commands");
 serial_println("9. Go Back");
 
 takeInput(*input,size);
 input2 = input[0];
 inputInt = atoi(input2);
 switch(inputInt)
  {
  case 1:
  //serial_println("Suspend goes here");
  serial_println("What do you want to suspend?");
  takeInput(*input,size);
  pcb *suspendedPCB = findPCB(*input);
  suspendedPCB->suspension=0;
  break;

  case 2:
  serial_println("Resume goes here");
  serial_println("What do you want to resume?");
  takeInput(*input,size);
  pcb *resumedPCB = findPCB(*input);
  resumedPCB->suspension =1;
  break;

  case 3:
  serial_println("Set Priority goes here");
  break;

  case 4:
  serial_println("Give name to find. This is temporary text");
  takeInput(*input, size);
  displayPCB(findPCB(*input));
  break;

  case 5:
  serial_println("Show all Processes goes here");
  
  break;

  case 6:
  serial_println("Show Ready Processes goes here");
  /**struct pcb *temp = readyQueue->head;
  while(temp != NULL){
  	displayPCB(temp);
  	temp = temp->next;
  } */
  break;

  case 7:
  serial_println("Show Blocked Processes goes here");
  break;
  
  case 8:
  	serial_println("What temporary PCB-related command would you like?");
 	serial_println("1. Create PCB");
 	serial_println("2. Delete PCB");
 	serial_println("3. Block");
 	serial_println("4. Unblock");
 	serial_println("5. Go Back");
 
 	takeInput(*input,size);
 	input2 = input[0];
 	inputInt = atoi(input2);
 	switch(inputInt)
 	 {
 	 case 1:
 	 serial_println("Give priority");
 	 //using input here is temporary probably
 	 takeInput(*input, size);
 	 input2 = input[0];
 	 serial_println("give name");
 	 takeInput(*input, size);
 	 insertPCB(setupPCB(*input,1,*input2));
 	 break;
	
 	 case 2:
 	 serial_println("Give name.");
 	 takeInput(*input, size);
 	 removePCB(findPCB(*input));
 	 break;
	
	 case 3:
	 //serial_println("Block goes here");
	 
	 serial_println("What do you want to block?");
	 takeInput(*input,size);
	 removePCB(findPCB(*input));
	 pcb *changePCB = findPCB(*input);
	 changePCB->state=0;
	 insertBlocked(findPCB(*input));
	 	 
	 break;
	
	 case 4:
  	// serial_println("Unblock goes here");

	 serial_println("What do you want to unblock?");
	 takeInput(*input,size);
	 removePCB(findPCB(*input));
	 pcb *changedPCB = findPCB(*input);
	 changedPCB->state = 1;
	 insertReady(findPCB(*input));
 	 break;

	//if this part of the menu wasn't temporary, I'd fix this so it only went back one step.
  	 case 5:
  	 break;
  	}
  break;

  case 9:
  break;
  }
 break;
 
 case 8:
 serial_println("Are you sure you want to shut down? Use y/n.");
 takeInput(*input,size);
 char input3 = *input[0];
 if(input3=='y')
 x=0;
 break;
 }
}
}
