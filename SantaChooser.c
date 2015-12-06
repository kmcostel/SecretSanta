/* @Author Kevin Costello
 * Goal: Program will write combinations
 * of secret santa pairings to a file named
 * pairings
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#define NUM_PEOPLE 11
#define false 0
#define true 1

int available[NUM_PEOPLE];
static char* names[NUM_PEOPLE] = {
    "Kevin", "Ashley",
    "Beth", "Davis", "Nick",
    "Charissa", "Marisa",
    "Emi", "Kyle", "Cara",
    "Sierra"
};

/* Get index of a person who has no gifter
 * and who isn't me
 */
int getOpenGiftee(int me) {
   int option;
   time_t time;

   /* Intializes random number generator */
   srand((uint) &time);
   
   /* May be infinite, should set a timer */
   option = me;
   while (option == me) {
      /* [0, NUM_PEOPLE) */
      option = rand() % NUM_PEOPLE;
      
      if (available[option] == false) {
         option = me;
      }
   }

   available[option] = false;
   
   return option;

}

void makePairings(FILE *list) {
   int i, open;
   char buffer[20];


   /* Get pairing for each person */
   for (i = 0; i < NUM_PEOPLE; i++) {
      open = getOpenGiftee(i);
      sprintf(buffer, "%s %s\n", names[i], names[open]);
      
      /* Write to list(FILE*) */
      fwrite(buffer, strlen(buffer), 1, list);
   }

}


int main (int argc, char **argv) {
   
   FILE *santasList;
   int i;

   santasList = fopen("SecretList.txt", "w");
   
   if (santasList == NULL) {
      fprintf(stderr, "Couldn't make Santa's list =(\n");
      exit(1);
   }

   for (i = 0; i < NUM_PEOPLE; i++) {
      available[i] = true;
   }

   makePairings(santasList);

   return 0;
}

