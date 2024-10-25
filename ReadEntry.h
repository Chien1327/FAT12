#ifndef __READENTRY_H__
#define __READENTRY_H__
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FILENAME_LENGTH 8
#define EXTENSION_LENGTH 3
#define RESERVED_LENGTH 10 

/*******************************************************************************
 * Struct Definitions
 ******************************************************************************/
typedef struct DirectoryEntry{
    char filename[FILENAME_LENGTH];
    char extension[EXTENSION_LENGTH];
    uint8_t attributes;
    uint8_t reserved[RESERVED_LENGTH];
    uint16_t time;
    uint16_t date;
    uint16_t startingCluster;
    uint32_t fileSize;
} __attribute__((packed)) DirectoryEntry;

typedef struct Node {
	DirectoryEntry entry;
	uint8_t index_entry;
	struct Node *pNext;
} NodeEntry_t;

typedef struct CollectionEntry {
	CollectionEntry *Children;
	uint8_t num;
} CollectionEntry_t;

typedef enum StatusReadDirectory {
	READ_END,
	READROOTDIRECTORY_SUCCESS, 
	READROOTDIRECTORY_FAIL,
	READ_NAME,
	READ_EXTENSION,
	READ_ATTRIBUTE,
	READ_RESERVER,
	READ_TIMECREATE,
	READ_DATECREATE,
	READ_STARTCLUSTER,
	READ_SIZE
} StatusReadDirectory_t;

StatusReadDirectory_t readDirectoryEntry(DirectoryEntry **dirEntries, uint32_t rootBlockStartOffset);
#endif 