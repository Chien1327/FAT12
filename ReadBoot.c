#ifndef __READBOOT_C__
#define __READBOOT_C__ 

#include "ReadBoot.h"
extern FILE * fileptr;


// Funtion 

StatusReadBoot_t ReadBoot(BootBlock_t *bootBlock) {
	
	BootBlockReader bootBlockReader;
	StatusReadBoot_t status = READBOOT_SUCCESS;
	
	if (fileptr != NULL) {
		status = (fread(&bootBlockReader, sizeof(BootBlockReader), 1, fileptr) != 1) ? READBOOT_FAIL : READBOOT_SUCCESS;
		
		if (status == READBOOT_SUCCESS) {
			memcpy(bootBlock->bootstrap, bootBlockReader.bootstrap, BOOTSTRAP_SIZE);
	        memcpy(bootBlock->manufacturer_desc, bootBlockReader.manufacturer_desc, MANUFACTURER_DESC_SIZE);
	        memcpy(bootBlock->volume_serial_number, bootBlockReader.volume_serial_number, SERIAL_NUMBER_SIZE);
	        memcpy(bootBlock->volume_label, bootBlockReader.volume_label, VOLUME_LABEL_SIZE);
	        memcpy(bootBlock->filesystem_identifier, bootBlockReader.filesystem_identifier, FILESYSTEM_IDENTIFIER_SIZE);
	        memcpy(bootBlock->bootstrap_remainder, bootBlockReader.bootstrap_remainder, BOOTSTRAP_REMAINDER_SIZE);
	
	        /*Combine 2*uint8 to uint16*/ 
	        bootBlock->bytes_per_block = (bootBlockReader.bytes_per_block1 | (bootBlockReader.bytes_per_block2 << 8));
	        bootBlock->num_root_dir_entries = (bootBlockReader.root_dir_entries1 | (bootBlockReader.root_dir_entries2 << 8));
	        bootBlock->total_blocks = (bootBlockReader.total_blocks1 | (bootBlockReader.total_blocks2 << 8));
	        bootBlock->boot_signature = (bootBlockReader.boot_signature1 | (bootBlockReader.boot_signature2 << 8));
	
	        bootBlock->blocks_per_allocation_unit = bootBlockReader.blocks_per_allocation_unit;
	        bootBlock->reserved_blocks = bootBlockReader.reserved_blocks;
	        bootBlock->num_fat = bootBlockReader.num_fat;
	        bootBlock->media_descriptor = bootBlockReader.media_descriptor;
	        bootBlock->blocks_per_fat = bootBlockReader.blocks_per_fat;
	        bootBlock->blocks_per_track = bootBlockReader.blocks_per_track;
	        bootBlock->num_heads = bootBlockReader.num_heads;
	        bootBlock->hidden_blocks = bootBlockReader.hidden_blocks;
	        bootBlock->total_blocks_per_entry = bootBlockReader.total_blocks_per_entry;
	        bootBlock->physical_drive_number = bootBlockReader.physical_drive_number;
	        bootBlock->extended_boot_record_signature = bootBlockReader.extended_boot_record_signature;
		} else {
			// None
		}
	} else {
		status = READBOOT_FAIL;
	}
	
	return status;
}


void printBootBlock(const BootBlock_t *bootBlock) {
    if (bootBlock == NULL) {
        printf("BootBlock is NULL\n");
        return;
    }

    printf("BootBlock Contents (in Hexadecimal):\n");
    
    /*Print bootstrap*/ 
    printf("Bootstrap: ");
    for (size_t i = 0; i < BOOTSTRAP_SIZE; i++) {
        printf("%02X ", bootBlock->bootstrap[i]);
    }
    printf("\n");

   /*Print manufacturer description*/
    printf("Manufacturer Description: ");
    for (size_t i = 0; i < MANUFACTURER_DESC_SIZE; i++) {
        printf("%02X ", bootBlock->manufacturer_desc[i]);
    }
    printf("\n");

    /*Print other fields*/
    printf("Bytes Per Block: 0x%04X\n", bootBlock->bytes_per_block);
    printf("Blocks Per Allocation Unit: 0x%02X\n", bootBlock->blocks_per_allocation_unit);
    printf("Reserved Blocks: 0x%04X\n", bootBlock->reserved_blocks);
    printf("Number of FAT: 0x%02X\n", bootBlock->num_fat);
    printf("Number of Root Directory Entries: 0x%04X\n", bootBlock->num_root_dir_entries);
    printf("Total Blocks: 0x%04X\n", bootBlock->total_blocks);
    printf("Media Descriptor: 0x%02X\n", bootBlock->media_descriptor);
    printf("Blocks Per FAT: 0x%04X\n", bootBlock->blocks_per_fat);
    printf("Blocks Per Track: 0x%04X\n", bootBlock->blocks_per_track);
    printf("Number of Heads: 0x%04X\n", bootBlock->num_heads);
    printf("Hidden Blocks: 0x%08X\n", bootBlock->hidden_blocks);
    printf("Total Blocks Per Entry: 0x%08X\n", bootBlock->total_blocks_per_entry);
    printf("Physical Drive Number: 0x%04X\n", bootBlock->physical_drive_number);
    printf("Extended Boot Record Signature: 0x%02X\n", bootBlock->extended_boot_record_signature);

    /*Print volume serial number*/
    printf("Volume Serial Number: ");
    for (size_t i = 0; i < SERIAL_NUMBER_SIZE; i++) {
        printf("%02X ", bootBlock->volume_serial_number[i]);
    }
    printf("\n");

    /*Print volume label*/
    printf("Volume Label: ");
    for (size_t i = 0; i < VOLUME_LABEL_SIZE; i++) {
        printf("%02X ", bootBlock->volume_label[i]);
    }
    printf("\n");

    /*Print filesystem identifier*/
    printf("Filesystem Identifier: ");
    for (size_t i = 0; i < FILESYSTEM_IDENTIFIER_SIZE; i++) {
        printf("%02X ", bootBlock->filesystem_identifier[i]);
    }
    printf("\n");

    /*Print bootstrap remainder*/
    printf("Bootstrap Remainder: ");
    for (size_t i = 0; i < BOOTSTRAP_REMAINDER_SIZE; i++) {
        printf("%02X ", bootBlock->bootstrap_remainder[i]);
    }
    printf("\n");

    /*Print boot signature*/
    printf("Boot Signature: 0x%04X\n", bootBlock->boot_signature);
}

#endif 

