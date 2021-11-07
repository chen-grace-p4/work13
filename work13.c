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

struct pop_entry * make_entry(int year, int pop, char * boro) {
   struct pop_entry *n;
   //n = malloc(sizeof(struct pop_entry));
   n = malloc(10000);

   n->year = year;
   n->population = pop;
   strncpy(n->boro, boro, 100);
   //n->boro = malloc(sizeof(boro));

   return n;
}

void print_entry(struct pop_entry * p) {
   printf("{year: %d\tpopulation: %d\tborough:%s\n}", p->year, p->population, p->boro);
}

// void print_entry() {
//
// }
/*
read entire csv and its size and put it into a char array and separate by \n then comma
*/

/*
1. reads contents of csv and stores as struct pop_entry
2. creates and writes structs into a new data file
guessing that within each read, you write that struct into a new file
use a loop and read only the amount of bytes per line each time??
new file can be .data
*/
char * read_all_data(char * all) {
   int in = open("nyc_pop.csv", O_RDONLY);
	if (in == -1) {
		printf("There is an error with open:\n");
		printf("%s\n", strerror(errno));
		return 0;
	}

   //gets size of file
   struct stat sb;
   stat("nyc_pop.csv", &sb);
   int sizeOfcsv = sb.st_size;
   //printf("%d", sizeOfcsv);
   //reads entire file into all
	read(in, all, sizeOfcsv);
	return all;
}

struct pop_entry ** make_datalist(int lines) {
   struct pop_entry ** datalist;
   //datalist = calloc(lines, sizeof(struct pop_entry *));
   //datalist = calloc(lines, 1000);
   datalist = calloc(10000, 10000);
   return datalist;
}

struct pop_entry ** add_data(struct pop_entry **datalist, int year ,int pop, char * boro, int i) {
   struct pop_entry *n = make_entry(year, pop, boro);
   datalist[i] = n;
   //printf("year is %d\tpop is %d\tboro is %s\n", datalist[i]->year, datalist[i]->population, datalist[i]->boro);
   return datalist;
}

void ** print_list(struct pop_entry ** list) {
   int i;
   for (i = 0; i < sizeof(list);  i++) {
      print_entry(list[i]);
   }
}

struct pop_entry ** read_csv(char * all) {
   struct pop_entry ** datalist;

   int i = 0;
   int lineCount = 0;
   while (all[i]) {
      if (all[i] == '\n') lineCount++;
      i++;
   }
   //-1 since it doesn't include the first line
   datalist = make_datalist(lineCount-1);

   //debug
   printf("num of lines: %d\n", lineCount);

   //resets i to beginning of all
   i = 0;

   //moves i to after the first line
   while (all[i] != '\n') {
      i++;
   }
   //printf("i is %d\n", i);

   //moves i down one to next line
   i ++;

   printf("current char is %c\n", all[i]);
   //index for datalist
   int dataIndex = 0;

   int line;
   for (line = 0; line < lineCount-1; line++) {
      //finds number of char in each line
      // int charInLine = 0;
      // printf("check\n");
      // while(all[i] != '\n') {
      //    charInLine++;
      // }
      //printf("check\n");
      int col;

      //data for pop_entry
      int year;
      int pop;
      char boro[100];
      //goes through each col on each line
      for (col = 0; col < 6; col++) {
         //printf("check\n");
         char info[100] = "";
         while(all[i] != ',' && all[i] != '\n') {
            //printf("check\n");
            //appending char all[i] to char * info
            char c[2];
            c[1] = '\0';
            c[0] = all[i];
            //printf("check: %s\n", c);
            //if (all[i+1] == ',') printf("comma next");
            strcat(info, c);
            //strcat(info, (char[2]){all[i], 0});
            i++;
         }
         //printf("info is: %s\n", info);
         //sets year
         if (col == 0) {
            year = atoi(info);
            //printf("year is: %d\n", year);
         }
         //adds data to datalist
         else {
            if (col == 1) strcpy(boro, "Manhattan");
            if (col == 2) strcpy(boro, "Brooklyn");
            if (col == 3) strcpy(boro, "Queens");
            if (col == 4) strcpy(boro, "Bronx");
            if (col == 5) strcpy(boro, "Staten Island");
            pop = atoi(info);
            datalist = add_data(datalist, year, pop, boro, dataIndex);
            //printf("dataindex is: %d\n", dataIndex);
            dataIndex++;
         }
         //moves index from comma to next
         i++;
      }
   }
}

/*
void read_csv() {
}

/*
1. reads new data file into an array of struct pop_entry, allocated based on fiel size
*/
/*
void read_data() {
}

void display_data(){
}
*/

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

   char all[951];
   strcpy(all, read_all_data(all));
   printf("%s \n", all);

   //printf("%c \n", *all);
   struct pop_entry ** datalist = make_datalist(100);
   datalist = read_csv(all);
   //printf("check\n");
   //WHY IS THERE SEGMENTATION FAULT HERE????
   print_entry(datalist[0]);

   //print_list(datalist);
}
