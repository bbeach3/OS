#ifndef _FAT_H
#define _FAT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct bootsector bootsector;

struct bootsector{
	char nobytes[2]; //Byte 11
	char clustercount; //Byte 13
	char reserved[2]; //Byte 14, value is 1
	char fatcopies; //Byte 16, value is 2
	char maxroots[2]; //Byte 17
	char sectorcount[2]; //Byte 19, value is 2880
	char fatsectors[3]; //Byte 22, value is 9
	char trackcount[2]; //Byte 24
	char noheads[2]; //Byte 26
	char totalsectors[4]; //Byte 32
	char bootsig; //Byte 38, value is 0x29
	char volumeid[4]; //Byte 39
	char volumelabel[11]; //Byte 43
	char systemtype[8]; //Byte 54, value is 'FAT12'
};

typedef struct entry entry;

struct entry{
	char name[8]; //Byte 0
	char extension[3]; //Byte 8
	char attr; //Byte 11
	char reserve[2]; //Byte 12
	char createtime[2]; //Byte 14
	char createdate[2]; //Byte 16
	char lastaccess[2]; //Byte 18
	char lastwritetime[2]; //Byte 22
	char lastwritedate[2]; //Byte 24
	char firstcluster[2]; //Byte 26
	char size[4]; //Byte 28
};

//The boot sector and the entries that make up the root directory - Thomas mentioned that data structures would be important in Module 6, but are there any other parts of the FAT system that would benefit from a data structure?

void sectorinfo();

void printroot();

void changecurr(char newfile[]);

void listcurr();

void listspec(char file[]);

void printfile(char file[]);

void renamefile(char oldname[], char newname[]);
#endif
