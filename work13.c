#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};
/*
read entire csv and its size and put it into a char array and separate by \n then comma
*/

/*
1. reads contents of csv and stores as struct pop_entry
2. creates and writes structs into a new data file
guessing that within each read, you write that struct into a new file
use a loop and read only the amount of bytes per line each time??
*/
void read_csv() {
}

/*
1. reads new data file into an array of struct pop_entry, allocated based on fiel size
*/
void read_data() {
}

void display_data(){
}

void add+
