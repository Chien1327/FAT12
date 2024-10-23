#ifndef __READBOOT_C__
#define __READBOOT_C__ 

#include "ReadBoot.h"
extern FILE * fileptr;



void Read_BootBlock() {
	
	if (fileptr == NULL) {
		printf("OPEN");
	}
	
	else {
		printf("NOT OPEN");
	}
	
	
}

#endif 

