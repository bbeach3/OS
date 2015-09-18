#include "./mpx_spring15/include/core/io.h"
#include "./mpx_spring15/include/core/serial.h"
#include "./mpx_spring15/include/string.h"
//Modify build paths so that they only go as far as mpx_spring15

#include "mpx_supt.c"
/** \file
 *Contains the functions allowing the control of time and date settings in the MPX system
 *Contains the functions allowing us to set the systems time and      date, as well as allowing us to retrieve the time and date
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
	const char *month = inb(0x71);
	unsigned int finalmonth = (((month & 0b11110000) >> 4) * 10) + (month * 0b00001111);

	date = finalmonth;
	if(finalmonth < 10)
	{
		serial_println("0" + date + "-");
	}
	else
	{
		serial_println(date + "-");
	}

	outb(0x70, 0x07); //Day
	const char *day = inb(0x71);
	unsigned int finalday = (((day & 0b11110000) >> 4) * 10) + (day * 0b00001111);
	
	date = finalday;
	if(finalday < 10)
	{
		serial_println("0" + date + "-");
	}
	else
	{
		serial_println(date + "-");
	}

	outb(0x70, 0x09); //Year
	const char *year = inb(0x71);
	unsigned int finalyear = (((year & 0b11110000) >> 4) * 10) + (year * 0b00001111);
	
	date = finalyear;
	if(finalyear < 10)
	{
		serial_println("0" + date);
	}
	else
	{
		serial_println(date);
	}

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
	const char *hour = inb(0x71);

	unsigned int finalhour = (((hour & 0b11110000) >> 4) * 10) + (hour * 0b00001111);
	
	time = finalhour;
	if(finalhour < 10)
	{
		serial_println("0" + time + ":");
	}
	else
	{
		serial_println(time + ":");
	}

	outb(0x70, 0x02); //Minutes
	const char *minute = inb(0x71);

	unsigned int finalminute = (((minute & 0b11110000) >> 4) * 10) + (minute * 0b00001111);
	
	time = finalminute;
	if(finalminute < 10)
	{
		serial_println("0" + time + ":");
	}
	else
	{
		serial_println(time + ":");
	}

	outb(0x07, 0x00); //Seconds
	const char *second = inb(0x71);

	unsigned int finalsecond = (((second & 0b11110000) >> 4) * 10) + (second * 0b00001111);
	
	time = finalsecond;
	if(finalsecond < 10)
	{
		serial_println("0" + time);
	}
	else
	{
		serial_println(time);
	}
}

/**
\Function: setDate
\Description: Sets the date on the system
\Parameters: datestring[] - A string specifying the date
\Returns: none
*/
void setdate(char datestring[])
{
	//Will require a specified format - In this case, 'month-day-year' (MM-DD-YY)
	cli();
	//We need to ensure that we transform the parameter into BCD and set it equal to entry!
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
		for(int i = 0; i < strlen(parsedate), i++)
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
			
			if(j == 0)
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
\Parameters: timestring - A string specifying the time
\Returns: none
*/
void settime(char* timestring)
{
	//Will require a specified format - In this case, 'hour:minute:second' (HH:MM:SS)[Military Time]
	cli();
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
		for(int i = 0; i < strlen(parsetime), i++)
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
			
			if(j == 0)
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
