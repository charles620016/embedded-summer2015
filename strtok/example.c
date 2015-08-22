#include <string.h>
#include <stdio.h>

int main(){
   char str[80] = "Summer embedded (2015) - NCKU";
   const char delim[5] = " -()";
   char *token;
   
   /* get the first token */
   token = strtok(str, delim);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( "%s\n", token );
      token = strtok(NULL, delim);
   }
   
   return 0;
}