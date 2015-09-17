#include <core/serial.h>

/*NOTE: everyone
After reading through my code again, I figured it would be better
to have the method just take an established array and size as params.
Passing a reference just makes more sense than passing the whole array
for every command. You make a call to takeInput() and it'll update the
array you pass in, leaving it nice and ready for use.
*/
void takeInput(char *inputLine, int inputSize) {
	//make equally-long array to print to clear line
	//also preps the inputLine (i.e. wipes it)
	char blankLine[inputSize];
	int i;
	for(i = 0; i < inputSize; i++){
		clearLine[i] = '\0';
		inputLine[i] = '\0';
	}
	int curChar = 0; //for tracking cursor
	int curEnd = 0; //for tracking current end of string
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
					serial_print(clearLine);
					serial_println(inputLine);
					return; //since we're done getting the input
				case 13: //Carriage Return
					//as it was explained to me, a CR just needs to go to line start
					curChar = 0;
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
									continue; //since they don't end a special code
								case 65: //Up Arrow
								case 66: //Down Arrow
								//will implement when needed
									special = 0;
									break; 
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
									//sets every char from curChar to the right to the next char
									for(int toRemove = curChar; toRemove < inputSize-1; toRemove++){
										inputLine[toRemove] = inputLine[toRemove+1];
									}
									special = 0;
									serial_print(clearLine);
									serial_print(inputLine);
									curEnd--;
									break;
							}
						}	
					}
					break;
				case 127: //Backspace
					//sets every character from curChar-1 to the right to the next character.
					for(int toRemove = curChar-1; toRemove < inputSize-1' toRemove++) {
						inputLine[toRemove] = inputLine[toRemove+1];
					}
					curChar--; 
					curEnd--;
					serial_print(clearLine);
					serial_print(inputLine);
					break;
				default: //In general, just text
					/*If the input array isn't already full, inserts the new character.
					Since the cursor may not be at the end, it does this by bumping everything
					from the cursor onwards one place to the right, and then overwriting the
					value at the cursor. 
					*/
					if(curEnd < inputSize-2) { //ensures space for the /0 at the end.
						int toMove = curChar;
						//since we have room, move each character from curChar right up one slot
						for( int location = curEnd+1; location > curChar; location--) {
							inputLine[location] = inputLine[location-1];
						}
						inputLine[curChar] = x; //insert new input
						curChar++;
						curEnd++;
						serial_print(clearLine);
						serial_print(inputLine);
					}
					break;
			}
		}
	}
}