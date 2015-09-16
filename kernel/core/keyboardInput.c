#include <core/serial.h>

void takeInput() {
	//size of input array, since it comes up again in the default below
	int inputSize = 100;
	//make array for the input
	char inputLine[inputSize];
	//make equally-long array to print to clear line
	char clearLine[inputSize];
	int i;
	for(i = 0; i < 100; i++){
		clearLine[i] = '\0';
	//for tracking cursor
	int curChar = 0;
	//Taking input until we're broken out.
	while(1){
		if(inb(COM1+5)&1) {
			char x = inb(COM1);
			//First task: what do we have here?
			switch(x) {
			/* Possibilities and ASCII Values:
			Backspace: 127
			Delete: 27, 91, 51, 126
			Arrow Keys: 27, 91, X
				X: Up = 65, Down = 66, Right = 67, Left = 68
			Carriage Return: 13
			New Line: 10 
			Everything else is DEFAULT.*/
				case 10: //New line aka run command
				case 13: //Carriage Return
					/* NOTE: Whoever is handling commands
					This is where you'll put the call to however
					we're handling commands. It'll be something like
					command_handler(inputLine);
					
					NOTE: Everyone
					Should there be a difference?
					*/
					serial_print(clearLine);
					serial_println(inputLine);
					break;
				case 27: //switch between delete and arrow keys
				/* Del and arrow keys have additional characters come in
				at the same time, so we'll ID them with those. */
					//need to track whether we hit the end or not
					int special = 1;
					while(special){
						if (inb(COM1+5)&1) {
							x = inb(COM1);
							switch(x){
								case 51: //Just filler as far as we care
								case 91: //Ditto
									continue; //since they don't end a special
								case 65: //Up Arrow
								case 66: //Down Arrow
								/*NOTE: Everyone
								If we're using a menu, do these have a job?
								*/
									special = 0;
									break; //since it's the end of a special
								case 67: //Right Arrow
									if (curChar < inputSize-1) {
										curChar++;
									}
									special = 0;
									break;
								case 68: //Left Arrow
									if (curChar > 0) {
										curChar--;
									}
									special = 0;
									break;
								case 126: //Delete
									/*NOTE: me
									Write this tomorrow.
									Copy everything from curChar+2 to curChar+1
									*/
									special = 0;
									break;
							}
						}	
					}
					break;
				case 127: //Backspace
					/* NOTE: me
					Rewrite this to move later chars forward if cursor
					had been moved away from the end.
					Could be as easy as copying everything that comes after
					to one space earlier.
					*/
					inputLine[curChar] = '\0';
					curChar--; 
					serial_print(clearLine);
					serial_print(inputLine);
					break;
				default: //In general, just text
					/*NOTE: Everyone
					If cursor isn't at end, should we overwrite or insert?
					If insert, note on Backspace gives a possible solution.
					*/
					if(curChar < inputSize-1) {
						inputLine[curChar] = x;
						curChar++;
						inputLine[curChar] = '\0'
						serial_print(clearLine);
						serial_print(inputLine);
					}
					break;
			}
		}
	}
}
