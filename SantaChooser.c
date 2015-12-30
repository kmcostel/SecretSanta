/* @Author Kevin Costello
 * Goal: Program will write combinations of
 * secret santa pairings to a file named pairings
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

/*Assuming names under 20 characters */
#define MAX_NAME 20
#define NUM_PEOPLE 11
#define false 0
#define true 1


char **names;
/* Number of names; number at start of inputted file */
int numNames;

/* Get index of a person who has no gifter
 * and who isn't me
 */
int getOpenGiftee(int me, int available[]) {
   int option;
   time_t time;

   /* Intializes random number generator */
   srand((uint) &time);
   
   /* May be infinite, should set a timer */
   option = me;
   while (option == me) {
      /* [0, NUM_PEOPLE) */
      option = rand() % numNames;
      
      /* If the chosen option (person) is unavailable
       * AKA already has a secret santa assigned to
       * themselves, then re-run loop */
      if (available[option] == false) {
         option = me;
      }
   }

   /* Set chosen option to false (unavailable) */
   available[option] = false;
   
   return option;

}

void makePairings(FILE *list) {
   int i, open;
   char buffer[MAX_NAME];
   int available[numNames];

   for (i = 0; i < numNames; i++) {
      available[i] = true;
   }

   /* Continue making the program work with a variable
    * file name, with list of names. Need to make a list of names,
    * each name will need to be malloc-ed"
    */
   
   /* Get pairing for each person */
   for (i = 0; i < numNames; i++) {
      open = getOpenGiftee(i, available);
      sprintf(buffer, "%s %s\n", names[i], names[open]);
      
      /* Write to list (FILE*) */
      fwrite(buffer, strlen(buffer), 1, list);
   }

}

void freeNames() {
   int i;

   for (i = 0; i < numNames; i++) {
      free(*(names+i));
   }
}

void initNames() {
   names = (char **)malloc(numNames * sizeof(char *));
}

/* Test if list was created correctly */
void printNameList() {
   int i;

   for (i = 0; i < numNames; i++) {
      puts(*(names + i));
   }
}

int main (int argc, char **argv) {
   
   FILE *santasList, *namesList;
   int i;
   char buffer[MAX_NAME];
   char *namesFile;
   

   if (argc == 1) {
      printf("Usage: ./SantaChooser names\n");
      printf("\"names\" is a file starting with a number,"
	      " followed by that number of names, "
	      "on seperate lines.\n");
      puts("\nDefaulting to \"names.txt\"\n");
      namesFile = "names.txt";
   }
   else {
      namesFile = argv[1];
   }

   /* Create a blank file called "SecretList.txt"
    * for the pairings of people */
   santasList = fopen("SecretList.txt", "w");
   if (santasList == NULL) {
      fprintf(stderr, "Couldn't make Santa's list =(\n");
      exit(1);
   }

   namesList = fopen("names.txt", "r");
   if (namesList == NULL) {
      printf("Invalid file name, try again\n");
      exit(1);
   }

   /* Read number at beginning of file */
   fscanf(namesList, "%d", &numNames);
   
   initNames();

   i = 0;
   /* While names are still being read in */
   while (fscanf(namesList, "%s", buffer) == 1) {
      *(names + i) = malloc(strlen(buffer));
      strcpy(*(names + i), buffer);
      ++i;
   }

   makePairings(santasList);

   puts("Done, pairings listed in \"SecretList.txt\"\n");
   return 0;
}

