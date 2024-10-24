#ifndef __DISPLAYDATA_C__
#define __DISPLAYDATA_C__ 

#include "DisplayData.h"
#include "ParseData.h"

extern FILE * fileptr;

void DisplayData (uint32_t first_cluster) {
	
	uint32_t cluster_flag = 0; 
	
	do
	{
		cluster_flag = getNextCluster(first_cluster);
		fseek(fileptr, NextIndexDataofCluster(first_cluster), SEEK_SET);
		for (int i = 0; i < 512; i++) {
			printf("%c", fgetc(fileptr));
		}
		if (cluster_flag == 0xFF7) {
			first_cluster = first_cluster + 0x01;
		} 
		else {
			first_cluster = cluster_flag;
		}
	} while (cluster_flag <= 0xFF8 && cluster_flag >= 0x02 && cluster_flag <= 0xFF6);
}

#endif 