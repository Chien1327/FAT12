#ifndef __READENTRY_C__
#define __READENTRY_C__

#include "ReadEntry.h"
extern FILE * fileptr;

StatusReadDirectory_t readDirectoryEntry(DirectoryEntry **dirEntries, uint32_t rootBlockStartOffset) {
	
	StatusReadDirectory_t status = READROOTDIRECTORY_SUCCESS;
	if (*dirEntries == NULL) {
		*dirEntries = (DirectoryEntry *)malloc(sizeof(DirectoryEntry) * 224);
	}
	else {
		// None
	}
	
	if (fileptr != NULL) {
		
		fseek(fileptr, rootBlockStartOffset, SEEK_SET);
		while (status != READ_END) {
			
		}
	}	
}

#endif 