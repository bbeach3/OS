#include "fat12.h"

//Printing boot sector info
//1. Print out the value of the boot sector's variables - simple.

//Printing root directory
//The root directory will have a list consisting of entries, files and directories alike - We print the name (And extension for file) for each

//Change directory
//We'll have a pointer directing towards the current directory - This will find the directory requested, and return it

//List directory
//If the parameter is null, then we serial_println the appropriate information (file name, extension, logical size of file, starting logical cluster string) for each file. If If a specific filename is listed, then we just check the contents of the directory (Both name and extension) against the given parameter. If just an extension with a wildcard filename is given, then we do the same as above - just with the extension, not the name.

//Type
//Given an appropriate file (.txt, .bat, .c), the file is searched out (Directory entry) and we progress through the ->data area->FAT table-> cycle, tracking how many characters we print - After a set amount (~25 lines worth, preferrably at a space) we have to pause for the user to input any character.

//Rename
//Given the old filename, we simply modify the entry's name/extension variables - Unless a file path is given, we will search only the current directory

//MOD 6 IS INDEPENDENT - Envoked from command line, uses 1 or 2 commands - Will be using gcc directly

bootsector *boot;
entry maindirectory[224];//Already known for FAT12
char fat1[];//fat1 and fat2 are both character (8 each) arrays that hold the bits that make up the 12-bit data entries, but I'm still not sure how many elements each one will have - fat2 is identical to fat1, but how many is fat1 allowed? 
char fat2[];

int main()
{
	//Before we get started, we should get the boot sector intialized, variable values and all
	int x = 1;
	while(x == 1)
	{
		int input;
		char onefile[13];//This is assuming an 8 character filename, a period, a 3 character extensions, and a terminating character - Probably adjust this and just cut filenames short as necessary
		char twofile[13];//Same as onefile
		printf("Select an option (Number):\n");
		printf("1. Print boot sector info\n");
		printf("2. Print Root Directory\n");
		printf("3. Change Current Directory\n");
		printf("4. List Directory Information\n");
		printf("5. Print File\n");
		printf("6. Rename File\n");
		printf("7. Exit\n");

		input = getchar();

		//putchar(input);
		//printf("\n");

		switch(input)
		{
			case '1': printf("Enter the first file:\n");
				  scanf("%s", onefile);
				  printf("%s\n", onefile);
				  printf("Enter the second file:\n");
				  scanf("%s", twofile);
				  printf("%s\n", twofile);
				  //Then we can put them both into whatever function we want - Repeat this with one or both files when needed (Not this one, actually - Printing sector information requires no extrenal info)
			break;
			
			case '2': printf("Choice 2\n");
			break;

			case '3': printf("Choice 3\n");
			break;

			case '4': printf("Choice 4\n");
			break;

			case '5': printf("Choice 5\n");
			break;

			case '6': printf("Choice 6\n");
			break;

			case '7': printf("EXIT\n");
			x = 0;
			break;

			
		}
	}

	return 0;
}

void sectorinfo()
{
		
}

void printroot()
{

}

void changecurr(char newfile[])//Should we strtok the filename strings into the name and extension before we use it in methods, or after in the method itself?
{
	
}

void listcurr()
{

}

void listcurr(char file[])//List directory can be called with or without a file - We'll handle the wildcard case here as well
{

}

void printfile(char file[])
{

}

void renamefile(char oldname[], char newfile[])
{
	
}
