#include "time.h"

/** \file
 *Contains the functions allowing the control of time and date settings in the MPX system
 *Contains the functions allowing us to set the systems time and date, as well as allowing us to retrieve the time and date
*/

//BCD - A right-to-left binary system that stores each digit of a value in 4 binary digits
//Ex. 603 = 011000000011 = 0110 0000 0011

/**
\Function: getDate
\Description: prints out the date
\Parameters: none
\Returns: none
*/
void getdate()
{
	const char *date;

	outb(0x70, 0x08); //Month
	const char month = inb(0x71);

	date = &month;

	serial_println(date);
	/*unsigned int finalmonth = ((((int)month & (int)0b11110000) >> 4) * 10) + ((int)month & (int)0b00001111);

	const char inputmonth = (char)finalmonth;
	date = &inputmonth;
	serial_println(date);*/
/*
	char *finalmonth = ((((int)month & (int)0b11110000) >> 4) + '0');

	serial_print(finalmonth);

	*finalmonth = (((int)month & (int)0b00001111)) + '0');

	serial_println(finalmonth + "-");

	date = *finalmonth;
	if(finalmonth < 10)
	{
		
		serial_print("0" + finalmonth); 
		serial_print("-");
	}
	else
	{
		serial_print(finalmonth + "-");
	}
*/
	outb(0x70, 0x07); //Day
	const char day = inb(0x71);

	date = &day;

	serial_println(date);
/*	unsigned int finalday = ((((int)day & (int)0b11110000) >> 4) * 10) + ((int)day & (int)0b00001111);
	
	//date = finalday;
	if(finalday < 10)
	{
		serial_print("0" + finalday);
		serial_print("-");	
	}
	else
	{
		serial_print(finalday + "-");
	}
*/
	outb(0x70, 0x09); //Year
	const char year = inb(0x71);

	date = &year;

	serial_println(date);
/*	unsigned int finalyear = ((((int)year & (int)0b11110000) >> 4) * 10) + ((int)year * (int)0b00001111);
	
	//date = finalyear;
	if(finalyear < 10)
	{
		serial_println("0" + finalyear);
	}
	else
	{
		serial_println(finalyear);
	}
*/
}

/**
\Function: getTime
\Description: Prints out the time
\Parameters: none
\Returns: none
*/
void gettime()
{
	const char* time;

	outb(0x70, 0x04); //Hours
	const char hour = inb(0x71);

	time = &hour;

	serial_println(time);
/*
	unsigned int finalhour = ((((int)hour & (int)0b11110000) >> 4) * 10) + ((int)hour * (int)0b00001111);
	
	//time = finalhour;
	if(finalhour < 10)
	{
		serial_print("0" + finalhour);
		serial_print(":");
	}
	else
	{
		serial_print(finalhour + ":");
	}
*/
	outb(0x70, 0x02); //Minutes
	const char minute = inb(0x71);
	
	time = &minute;	

	serial_println(time);
/*
	unsigned int finalminute = ((((int)minute & (int)0b11110000) >> 4) * 10) + ((int)minute * (int)0b00001111);
	
	//time = finalminute;
	if(finalminute < 10)
	{
		serial_print("0" + finalminute);
		serial_print(":");
	}
	else
	{
		serial_print(finalminute + ":");
	}
*/
	outb(0x07, 0x00); //Seconds
	const char second = inb(0x71);
	
	time = &second;

	serial_println(time);
/*
	unsigned int finalsecond = ((((int)second & (int)0b11110000) >> 4) * 10) + ((int)second * (int)0b00001111);
	
	//time = finalsecond;
	if(finalsecond < 10)
	{
		serial_println("0" + finalsecond);
	}
	else
	{
		serial_println(finalsecond);
	}
*/
}

/**
\Function: setDate
\Description: Sets the date on the system
\Parameters: datestring[] - A string specifying the date, datelength - The length of datestring
\Returns: none
*/
void setdate(char datestring[], int datelength)
{
	//Will require a specified format - In this case, 'month-day-year' (MM-DD-YY)
	cli();
	//We need to ensure that we transform the parameter into BCD and set it equal to entry!
	if(datelength != 9)
	{
		serial_println("Invalid format - Input dates as 'MM-DD-YY'");
		return;
	}

	int ele = 0;

	for(ele = 0; ele < datelength; ele++)
	{
		if((ele != 2 && ele != 5 && ele != 8) && (datestring[ele] < 48 || datestring[ele] > 57))
		{
			serial_println("Invalid format - Input dates as 'MM-DD-YY'");
			return;
		}
		
		if((ele == 2 || ele == 5) && datestring[ele] != '-')
		{
			serial_println("Invalid format - Input dates as 'MM-DD-YY'");
			return;
		}
	}

	char *parsedate = strtok(datestring, "-");

	unsigned char entry;
	int curr = 0;
	
	while(parsedate != NULL)
	{
		entry = 0;
		//Determining which value to write to
		switch (curr)
		{
			case 0:
				outb(0x70, 0x08); //Month
				break;
			case 1:
				outb(0x70, 0x07); //Day
				break;
			case 2:
				outb(0x70, 0x06); //Year
				break;
		}
		//Creating the BCD values
		int i;
		for(i = 0; i < strlen(parsedate); i++)
		{
			switch (parsedate[i])
			{
				case 0:
					entry = entry | 0b00000000;
					break;
				case 1:
					entry = entry | 0b00000001;
					break;
				case 2:
					entry = entry | 0b00000010;
					break;
				case 3:
					entry = entry | 0b00000011;
					break;
				case 4:
					entry = entry | 0b00000100;
					break;
				case 5:
					entry = entry | 0b00000101;
					break;
				case 6:
					entry = entry | 0b00000110;
					break;
				case 7:
					entry = entry | 0b00000111;
					break;
				case 8:
					entry = entry | 0b00001000;
					break;
				case 9:
					entry = entry | 0b00001001;
					break;
			}

			if(i == 0)
			{
				entry = entry << 4;
			}	
		}
		//Writing the BCD value
		outb(0x71, entry);

		parsedate = strtok(NULL, "-");

		curr++;
	}
	sti();
}

/**
\Function: setTime
\Description: Sets the time on the system
\Parameters: timestring[] - A string specifying the time, timelength - The length of timestring
\Returns: none
*/
void settime(char timestring[], int timelength)
{
	//Will require a specified format - In this case, 'hour:minute:second' (HH:MM:SS)[Military Time]
	cli();
	if(timelength != 9)
	{
		serial_println("Invalid format - Input times as 'HH:MM:SS' [Military Time]");
		return;
	}

	int ele = 0;
	for(ele = 0; ele < timelength; ele++)
	{
		if((ele != 2 && ele != 5 && ele != 8) && (timestring[ele] < 48 || timestring[ele] > 57))
		{
			serial_println("Invalid format - Input times as 'HH:MM:SS' [Military Time]");
			return;
		}
		
		if((ele == 2 || ele == 5) && timestring[ele] != ':')
		{
			serial_println("Invalid format - Input times as 'HH:MM:SS' [Military Time]");
			return;
		}
	}

	char *parsetime = strtok(timestring, ":");

	unsigned char entry;
	int curr = 0;
	
	//Determining which value we're modifying
	while(parsetime != NULL)
	{
		entry = 0;
		switch (curr)
		{
			case 0:
				outb(0x70, 0x04); //Hour
				break;
			case 1:
				outb(0x70, 0x02); //Minutes
				break;
			case 2:
				outb(0x70, 0x00); //Seconds
				break;
		}

		//Setting the BCD values
		int i;
		for(i = 0; i < strlen(parsetime); i++)
		{
			switch (parsetime[i])
			{
				case 0:
					entry = entry | 0b00000000;
					break;
				case 1:
					entry = entry | 0b00000001;
					break;
				case 2:
					entry = entry | 0b00000010;
					break;
				case 3:
					entry = entry | 0b00000011;
					break;
				case 4:
					entry = entry | 0b00000100;
					break;
				case 5:
					entry = entry | 0b00000101;
					break;
				case 6:
					entry = entry | 0b00000110;
					break;
				case 7:
					entry = entry | 0b00000111;
					break;
				case 8:
					entry = entry | 0b00001000;
					break;
				case 9:
					entry = entry | 0b00001001;
					break;
			}
			
			if(i == 0)
			{
				entry = entry << 4;
			}	
		}
		//Writing completed BCD value
		outb(0x71, entry);

		parsetime = strtok(NULL, ":");

		curr++;
	}
	sti();
}
