/** \file
 *Contains the source code for the function to shut down the system
 *Contains the source code for the function to shut down the system
*/


/**
\Function: shutdown
\Description: Asks the user if they wish to shutdown the system, and if "yes" shuts it down
\Parameters: none
\Returns: none
*/
shutdown()
{
serial_println("Are you sure you want to shut down?");
int size = 3;
char *input[size];
takeInput(*input,size);
if(*input[0]=='y')
//return to kmain()

}
