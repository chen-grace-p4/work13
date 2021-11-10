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

void print_entry(struct pop_entry * p) {
   printf("{year: %d\tpopulation: %d\tborough:%s}\n", p->year, p->population, p->boro);
}

int lineCounter() {
   int in = open("nyc_pop.csv", O_RDONLY);
   char c;
   int lines = 0;
   while (read(in, &c ,1) != '\0'){
      if (c == '\n'){
         lines++;
      }
   }
   close(in);
   return lines;
}

long file_size(char *f) {
   struct stat b;
   stat(f,  &b);
   return b.st_size;
}

void read_csv() {
   int in = open("nyc_pop.csv", O_RDONLY);
   int newfile = open("entries.data", O_CREAT | O_WRONLY | O_TRUNC, 0644);
   int numOfEntries = 0;
   //int n;
   //stores line
   char buff[100];
   //stores char
   char c[2];
   c[1] = '\0';
   //data
   int year;
   int line;
   int totalLines = lineCounter();
   for(line = 0; line < totalLines; line++) {
      //so that read reads into c at first char
      c[0] = '\0';

      //reads through line
      int i;
      for(i = 0; c[0] != '\n'; i++) {
         int n;
         n = read(in, c, 1);
         //end of file
         if (n == '\0') break;
         //sets char of buff to the read in char
         buff[i] = c[0];
      }
      //terminates string
      buff[i] = '\0';

      //array of pop_entry, 5 for 5 col in each line
      struct pop_entry list[5];
      //puts buff information into appropriate variables
      //skips first line since that's just boroughs
      if (line != 0) {
         sscanf(buff, "%d,%d,%d,%d,%d,%d\n", &year, &list[0].population, &list[1].population, &list[2].population, &list[3].population, &list[4].population);
         //printf("%d\n", list[0].population);
         int a;
         for(a = 0; a < 5; a++) {
            list[a].year = year;
            numOfEntries++;
         }
         strcpy(list[0].boro, "Manhattan");
         strcpy(list[1].boro, "Brooklyn");
         strcpy(list[2].boro, "Queens");
         strcpy(list[3].boro, "Bronx");
         strcpy(list[4].boro, "Staten Island");

         write(newfile, list, sizeof(list));
      }
   }//end of loop through all lines
   //printf("number of entries: %d\n", numOfEntries);
   close(in);
   close(newfile);
}

void read_data() {
   int in = open("entries.data", O_RDONLY);

   int size = file_size("entries.data");
   int entries = size / sizeof(struct pop_entry);
   struct pop_entry *list = calloc(entries, sizeof(struct pop_entry));

   int err = read(in, list, size);
   if(err==-1){
      printf("error reading file:%s\n", strerror(errno));
   }

   int i;
   for(i = 0;i < entries;i++){
      printf("%d: ", i);
      print_entry(&(list[i]));
   }
   free(list);
}

void add_data() {
   struct pop_entry ent;

   int newYear = 0;
   int newPop = 0;
   char newBorough[100] = "";

   //year
   char nyear[100];
   printf("Please enter new year as an integer: ");
   fgets(nyear, sizeof(nyear)-1, stdin);
   nyear[strlen(nyear)-1] = 0;
   sscanf(nyear, "%d", &newYear);

   //population
   char npop[100];
   printf("Please enter new population as an integer: ");
   fgets(npop, sizeof(npop)-1, stdin);
   npop[strlen(npop)-1] = 0;
   sscanf(npop, "%d", &newPop);

   //borough
   printf("Please enter new borough as a string: ");
   fgets(newBorough, sizeof(newBorough)-1, stdin);
   newBorough[strlen(newBorough)-1] = 0;

   ent.year = newYear;
   ent.population = newPop;
   strcpy(ent.boro, newBorough);

   int in = open("entries.data", O_WRONLY | O_APPEND);

   write(in, &ent, sizeof(ent));

   printf("File is updated.\n");
   close(in);
}

void update_data() {
   int entry = 0;
   char e[100];
   printf("Enter the entry number you want to change: ");
   fgets(e, sizeof(e)-1, stdin);
   e[strlen(e)-1] = 0;
   sscanf(e, "%d", &entry);

   int in = open("entries.data", O_WRONLY);
   struct pop_entry ent;

   int newYear = 0;
   int newPop = 0;
   char newBorough[100] = "";

   //year
   char nyear[100];
   printf("Please enter new year as an integer: ");
   fgets(nyear, sizeof(nyear)-1, stdin);
   nyear[strlen(nyear)-1] = 0;
   sscanf(nyear, "%d", &newYear);

   //population
   char npop[100];
   printf("Please enter new population as an integer: ");
   fgets(npop, sizeof(npop)-1, stdin);
   npop[strlen(npop)-1] = 0;
   //printf("\n");
   sscanf(npop, "%d", &newPop);

   //borough
   printf("Please enter new borough as a string: ");
   fgets(newBorough, sizeof(newBorough)-1, stdin);
   newBorough[strlen(newBorough)-1] = 0;

   ent.year = newYear;
   ent.population = newPop;
   strcpy(ent.boro, newBorough);

   lseek(in, entry*sizeof(struct pop_entry), 0);
   write(in, &ent, sizeof(ent));

   printf("File is updated.\n");
   close(in);
}
