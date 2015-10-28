/** \file
 *Contains source code for help functions
 *Contains source code for functions printing out help messages for menu options
*/

/**
\Function: version_help
\Description: prints out help message for the version option
\Parameters: none
\Returns: none
*/
void version_help()
{
serial_println("This command displays the current version of MPX that we are currently on.");
}


/**
\Function: shutdown_help
\Description: prints out help for the shutdown option
\Parameters: none
\Returns: none
*/
void shutdown_help()
{
serial_println("This command shuts down the MPX project. It asks for confirmation before doing so.");
}


/**
\Function: getdate_help
\Description: prints out help for the getdate option
\Parameters: none
\Returns: none
*/
void getdate_help()
{
serial_println("This command displays the current date.");
}


/**
\Function: setdate_help
\Description: prints out help for the setdate option
\Parameters: none
\Returns: none
*/
void setdate_help()
{
serial_println("This command allows you to set the date.");
}


/**
\Function: gettime_help
\Description: prints out help for the gettime option
\Parameters: none
\Returns: none
*/
void gettime_help()
{
serial_println("This command displays the current time.");
}

/**
\Function: settime_help
\Description: prints out help for the helptime option
\Parameters: none
\Returns: none
*/
void settime_help()
{
serial_println("This command allows you to set the time.");
}

/**
\Function: suspend_help
\Description: prints out help for the suspend option
\Parameters: none
\Returns: none
*/
void suspend_help()
{
serial_println("This command allows you to place a PCB in a suspended state.");
}

/**
\Function: resume_help
\Description: prints out help for the resume option
\Parameters: none
\Returns: none
*/
void resume_help()
{
serial_println("This command allows you to place a PCB in an unsuspended state.");
}

/**
\Function: setpriority_help
\Description: prints out help for the 'Set priority' option
\Parameters: none
\Returns: none
*/
void setpriority_help()
{
serial_println("This command allows you to set a PCB's priority.");
}

/**
\Function: pcbprint_help
\Description: prints out help for the 'Show PCD' option
\Parameters: none
\Returns: none
*/
void pcbprint_help()
{
serial_println("This command allows you to display a specified PCB and its details.");
}

/**
\Function: processdisplay_help
\Description: prints out help for the 'Display all processes' option
\Parameters: none
\Returns: none
*/
void processdisplay_help()
{
serial_println("This command allows you to show all the processes that currently exist.");
}

/**
\Function: readydisplay_help
\Description: prints out help for the 'Display ready processes' option
\Parameters: none
\Returns: none
*/
void readydisplay_help()
{
serial_println("This command allows you to show all the ready processes that currently exist.");
}

/**
\Function: blockdisplay_help
\Description: prints out help for the 'Display blocked processes' option
\Parameters: none
\Returns: none
*/
void blockdisplay_help()
{
serial_println("This command allows you to show all the blocked processes that currently exist.");
}

/**
\Function: createpcb_help
\Description: prints out help for the 'Create PCB' option
\Parameters: none
\Returns: none
*/
void createpcb_help()
{
serial_println("This command allows you to create a new PCB.");
}

/**
\Function: deletepcb_help
\Description: prints out help for the 'Delete PCB' option
\Parameters: none
\Returns: none
*/
void deletepcb_help()
{
serial_println("This command allows you to delete a PCB.");
}

/**
\Function: block_help
\Description: prints out help for the 'Block' option
\Parameters: none
\Returns: none
*/
void block_help()
{
serial_println("This command allows you to set a PCB to the blocked state.");
}

/**
\Function: unblock_help
\Description: prints out help for the 'Unblock' option
\Parameters: none
\Returns: none
*/
void unblock_help()
{
serial_println("This command allows you to set a PCB to the unblocked state.");
}

/**
\Function: yield_help
\Description: prints out help for the 'Yield' option
\Parameters: none
\Returns: none
*/
void yield_help()
{
serial_println("This command causes commhand to yield so that other processes may run.");
}

/**
\Function: loadr3_help
\Description: prints out help for the 'loadr3' option
\Parameters: none
\Returns: none
*/
void loadr3_help()
{
serial_println("This command loads all the r3 processes into memory.");
}
