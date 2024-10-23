#include <stdio.h>
#include <stdint.h> 
#include <string.h>

#define BOOTSTRAP_SIZE 3
#define MANUFACTURER_DESC_SIZE 8
#define VOLUME_LABEL_SIZE 11
#define SERIAL_NUMBER_SIZE 4
#define FILESYSTEM_IDENTIFIER_SIZE 8
#define BOOTSTRAP_REMAINDER_SIZE 448

FILE *fileptr = NULL;

typedef struct BootBlock {
	
	uint8_t bootstrap[BOOTSTRAP_SIZE];
    uint8_t manufacturer_desc[MANUFACTURER_DESC_SIZE];
    uint16_t bytes_per_block;
    uint8_t blocks_per_allocation_unit; 
    uint16_t reserved_blocks;
    uint8_t num_fat;
    uint16_t num_root_dir_entries;
    uint16_t total_blocks;
    uint8_t media_descriptor;
    uint16_t blocks_per_fat;
    uint16_t blocks_per_track;
    uint16_t num_heads;  
    uint32_t hidden_blocks;
    uint32_t total_blocks_per_entry;
    uint16_t physical_drive_number;
    uint8_t extended_boot_record_signature;
    uint8_t volume_serial_number[SERIAL_NUMBER_SIZE];    
    uint8_t volume_label[VOLUME_LABEL_SIZE];
    uint8_t filesystem_identifier[FILESYSTEM_IDENTIFIER_SIZE];
    uint8_t bootstrap_remainder[BOOTSTRAP_REMAINDER_SIZE];
    uint16_t boot_signature;
    
} BootBlock_t;

BootBlock_t bootBlock;

typedef enum StatusReadBoot {
	READBOOT_SUCCESS, 
	READBOOT_FAIL
} StatusReadBoot_t;

StatusReadBoot_t ReadBoot();

typedef enum OpenFileFatStatus {
	OPEN_SUCCESS,
	OPEN_FAIL
} OpenFileFatStatus_t;

OpenFileFatStatus_t OpenFileFat(); 
OpenFileFatStatus_t CloseFileFat(); 

int main() {
	//fileptr = fopen("floppy.img", "r");
	
	OpenFileFatStatus_t OpenFileStatus; 
	OpenFileStatus = OpenFileFat(); 
	switch (OpenFileStatus) {
		case OPEN_SUCCESS: 
			
			//Read Root Block
			ReadBoot();
			// Print Root Directory 
			/* 
				While - choice
			*/
			
			
			// CloseFileFat();
			break;
		case OPEN_FAIL:
			printf("OPEN FAIL \n");
			break;
	}
	
	return 0;
}

StatusReadBoot_t ReadBoot() {
	StatusReadBoot_t status = READBOOT_SUCCESS;
	
	if (fileptr == NULL) {
		status = READBOOT_FAIL;
	}
	else {	
		fread(&bootBlock, sizeof(BootBlock_t), 1, fileptr);
		    /*Print bootstrap*/ 
	    printf("Bootstrap: ");
	    for (size_t i = 0; i < BOOTSTRAP_SIZE; i++) {
	        printf("%02X ", bootBlock.bootstrap[i]);
	    }
	    printf("\n");
	    /*Print manufacturer description*/
	    printf("Manufacturer Description: ");
	    for (size_t i = 0; i < MANUFACTURER_DESC_SIZE; i++) {
	        printf("%02X ", bootBlock.manufacturer_desc[i]);
	    }
	    printf("Bytes Per Block: 0x%04X\n", bootBlock.bytes_per_block);
	    printf("Blocks Per Allocation Unit: 0x%02X\n", bootBlock.blocks_per_allocation_unit);
	    printf("Reserved Blocks: 0x%04X\n", bootBlock.reserved_blocks);
	    printf("Number of FAT: 0x%02X\n", bootBlock.num_fat);
	    printf("Number of Root Directory Entries: 0x%04X\n", bootBlock.num_root_dir_entries);
	    printf("Total Blocks: 0x%04X\n", bootBlock.total_blocks);
//	    printf("Media Descriptor: 0x%02X\n", bootBlock->media_descriptor);
//	    printf("Blocks Per FAT: 0x%04X\n", bootBlock->blocks_per_fat);
//	    printf("Blocks Per Track: 0x%04X\n", bootBlock->blocks_per_track);
//	    printf("Number of Heads: 0x%04X\n", bootBlock->num_heads);
//	    printf("Hidden Blocks: 0x%08X\n", bootBlock->hidden_blocks);
//	    printf("Total Blocks Per Entry: 0x%08X\n", bootBlock->total_blocks_per_entry);
//	    printf("Physical Drive Number: 0x%04X\n", bootBlock->physical_drive_number);
//	    printf("Extended Boot Record Signature: 0x%02X\n", bootBlock->extended_boot_record_signature);
	    
	    printf("\n");
	}
	
}




OpenFileFatStatus_t OpenFileFat() {
	OpenFileFatStatus_t status = OPEN_SUCCESS;
	fileptr = fopen("floppy.img", "r + b");
	if (fileptr != NULL) {
		
		//None
	}		
	else {
		status = OPEN_FAIL;
	} 
	
	return status;
}


OpenFileFatStatus_t CloseFileFat() {
	OpenFileFatStatus_t status = OPEN_SUCCESS;
	fclose(fileptr);
	if (fileptr == NULL) {
		status = OPEN_FAIL;
	}
	else {
		// None
	}
	
	return status;
}