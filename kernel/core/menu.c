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
#include "include/core/serial.h"
#include "include/core/keyboardInput.h"
#include "include/core/shutdown.h"
#include "include/core/version.h"
#include "include/core/help.h"
#include "modules/time.h"
#include "modules/mod2/pcb.h"
#include "modules/mod2/queue.h"
#include "modules/mod34/call.h"
#include "modules/mod34/procsr3.h"
#include "include/core/interrupts.h"

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
 serial_println("7. PCB Commands");
 serial_println("8. Go back");
 
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
   serial_println("What PCB-related command would you like help with?");
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
	case 1: suspend_help();
	break;
	
	case 2: resume_help();
	break;

	case 3: setpriority_help();
	break;

	case 4: pcbprint_help();
	break;

	case 5: processdisplay_help();
	break;

	case 6: readydisplay_help();
	break;

	case 7: blockdisplay_help();
	break;

	case 8:
	  serial_println("What temporary PCB-related command would you like help with?");
 	  serial_println("1. Create PCB");
 	  serial_println("2. Delete PCB");
 	  serial_println("3. Block");
 	  serial_println("4. Unblock");
	  serial_println("5. Yield (Manual Interrupt)");
	  serial_println("6. Load r3 Processes");
 	  serial_println("7. Go Back");
  
 	  takeInput(*input,size);
 	  input2 = input[0];
 	  inputInt = atoi(input2);
 	  switch(inputInt)
	  {
		case 1: createpcb_help();
		break;

		case 2: deletepcb_help();
		break;

		case 3: block_help();
		break;

		case 4: unblock_help();
		break;

		case 5: yield_help();
		break;

		case 6: loadr3_help();
		break;

		case 7:
		break;
	  }
	break;

	case 9:
	break;
   }
  break;

  case 8:
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
  if(suspendedPCB == NULL){
    serial_println("Could not find that PCB");
    break;
  }
  suspendedPCB->suspension=0;
  //reinserting into queue
  removePCB(suspendedPCB);
  insertPCB(suspendedPCB);
  break;

  case 2:
  //serial_println("Resume goes here");
  serial_println("What do you want to resume?");
  takeInput(*input,size);
  pcb *resumedPCB = findPCB(*input);
  if(resumedPCB == NULL){
    serial_println("Could not find that PCB");
    break;
  }
  resumedPCB->suspension =1;
  //reinserting into queue
  removePCB(resumedPCB);
  insertPCB(resumedPCB);
  break;

  case 3:
  //serial_println("Set Priority goes here");
  serial_println("What do you want to change the priority of?");
  takeInput(*input,size);
  pcb *priorityPCB = findPCB(*input);
  if(priorityPCB == NULL){
    serial_println("Could not find that PCB");
    break;
  }
  serial_println("What do you want to change the priority to?");
  takeInput(*input,size);
  input2 = input[0];
  inputInt = atoi(input2);
  if(inputInt<0||inputInt>9)
  serial_println("Error, this must be between 0 and 9");
  else
  {
  priorityPCB->priority=inputInt;
  //putting in proper place in queue
  removePCB(priorityPCB);
  insertPCB(priorityPCB);
  }
  break;

  case 4:
  serial_println("Please input name of wanted PCB.");
  takeInput(*input, size);
  displayPCB(findPCB(*input));
  break;

  case 5: //show all processes
  displayReady();
  displayBlocked();
  break;

  case 6: //show ready processes
  displayReady();

  break;

  case 7: //show blocked processes
  displayBlocked();
  break;
  
  case 8:
  	serial_println("What temporary PCB-related command would you like?");
 	serial_println("1. Create PCB");
 	serial_println("2. Delete PCB");
 	serial_println("3. Block");
 	serial_println("4. Unblock");
	serial_println("5. Yield (Manual Interrupt)");
	serial_println("6. Load r3 Processes");
 	serial_println("7. Go Back");
 
 	takeInput(*input,size);
 	input2 = input[0];
 	inputInt = atoi(input2);
 	switch(inputInt)
 	 {
 	 case 1:
 	 serial_println("Give priority");
 	 takeInput(*input, size);
 	 input2 = input[0];
	 inputInt = atoi(input2);
	 if(inputInt<0||inputInt>9) {
	 serial_println("Error, this must be between 0 and 9");
	 break;
	 }
	 int stateVal;
	 serial_println("Give type. 1 = App. 0 = System.");
	 takeInput(*input, size);
	 input2 = input[0];
	 stateVal = atoi(input2);
	 if(stateVal < 0 || stateVal > 1){
	 serial_println("Not a valid state");
	 break;
	 }
 	 serial_println("Give name");
 	 takeInput(*input, size);
	 struct pcb *temp = setupPCB(*input,stateVal,inputInt);
	 if(temp == NULL){
	 serial_println("Invalid name - please use a unique name under 8 characters.");
	 } else {
	 insertPCB(temp);
	 }
 	 break;
	
 	 case 2:
 	 serial_println("Give name.");
 	 takeInput(*input, size);
 	 pcb *toDelete = findPCB(*input);
	 if((removePCB(toDelete)) == 0){
	 serial_println("PCB not deleted - could not be found");
	 }
	 freePCB(toDelete);
 	 break;
	
	 case 3:
	 //Block
	 
	 serial_println("What do you want to block?");
	 takeInput(*input,size);
	 pcb *toBlockPCB = findPCB(*input);
    if(toBlockPCB == NULL){
    serial_println("Could not find that PCB");
    break;
    }
	 removePCB(toBlockPCB);
	 toBlockPCB->state=0;
	 //remove links to old queue
	 toBlockPCB->prev = NULL;
	 toBlockPCB->next = NULL;
	 insertPCB(toBlockPCB);
	 	 
	 break;
	
	 case 4:
  	// Unblock
	 serial_println("What do you want to unblock?");
	 takeInput(*input,size);
	 pcb *toUnblockPCB = findPCB(*input);
    if(toUnblockPCB == NULL){
    serial_println("Could not find that PCB");
    break;
    }
	 removePCB(toUnblockPCB);
	 toUnblockPCB->state=1;
	 toUnblockPCB->prev = NULL;
	 toUnblockPCB->next = NULL;
	 insertPCB(toUnblockPCB);
	 	 
	 break;

	//if this part of the menu wasn't temporary, I'd fix this so it only went back one step.
	case 5: 
	//Mod 3 only - Defunct!
	//asm volatile ("int $60");
	break;

	case 6: //loadr3
	//we never used the pcb* proc1 et al, which threw warnings
	//'temporarily' removed
	//serial_println("Start");
	insertPCB(loadr3("Process1"));
	//serial_println("1");
	insertPCB(loadr3("Process2"));
	//serial_println("2");
	insertPCB(loadr3("Process3"));
	//serial_println("3");
	insertPCB(loadr3("Process4"));
	//serial_println("4");
	insertPCB(loadr3("Process5"));
	//serial_println("5");	
	break;

	case 7:
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
 {
 serial_println("Starting system shutdown procedure...");
 serial_println("Shutdown complete. You may now turn off the machine. (QEMU: C-a x)");
 hlt();
 x=0;
 }
 break;
 }
sys_req(IDLE); //let things dispatch
}
}
