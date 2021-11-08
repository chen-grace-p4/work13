#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "work13.h"

int main(int argc, char *argv[]) {
	char flag[100];

	if (argc > 1) {
		strcpy(flag, argv[1]);
	} else {
		printf("Please enter a flag: ");
		fgets(flag, sizeof(flag)-1, stdin);
		flag[strlen(flag)-1] = 0;
		printf("\n");
	}

   //testing if inputting flag works
   //printf("flag is: %s\n", flag);
   //yes it works

   //testing linecounter
   //printf("LINES:%d\n", lineCounter());
   //yes it works

   //read_csv(-1);
   //read_csv(53);
   //read_data();
   if(strcmp(flag, "-update_data") == 0) {
      read_data();
      update_data();
      //debug
      //read_data();
   }
   else if (strcmp(flag, "-add_data") == 0) {
      add_data();
      //debug
      //read_data();
   }
   else if (strcmp(flag, "-read_data") == 0) {
      read_data();
   }
   else if (strcmp(flag, "-read_csv") == 0) {
      read_csv();
   }
}
