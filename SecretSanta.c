/* @Author: Kevin Costello */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *greet = "What's your name?";
static char *confused = "Sorry can't find you";

int prefix (const char *pre, const char *str) {
   return strncmp(pre, str, strlen(pre)) == 0;
}

int main(int argc, char **argv) {
   FILE *list;
   char buffer[20];
   char *line;
   char name[10];
   int found;

   list = fopen("SecretList.txt", "r");
   if (list == NULL) {
      printf("Couldn't find SecretList.txt!\n");
      exit(1);
   }

   puts(greet);
   scanf("%s", name);

   found = 0;
   while (!found && fgets(buffer, 20, list) != NULL) {
      if (prefix(name, buffer)) {
	  found = 1;
        
	  line = strtok(buffer, "\n");
          printf("You're the secret santa of %s! HAVE FUN\n", line + strlen(name) + 1);
      }
   }

   if (!found) {
      puts(confused);
      exit(1);
   }


   return 0;
}
