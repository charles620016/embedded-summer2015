#include <string.h>
#include <stdio.h>

char * strtok_reentrant (char *s, const char *delim, char **rest)
{
    char *token;

    if (s == NULL){
        s = *rest;
    }

    s += strspn (s, delim);
    if (*s == '\0'){
        *rest = s;
        return NULL;
    }

    token = s;
    s = strpbrk (token, delim);
    if (s == NULL){
        *rest = strchr (token, '\0');
    }
    else{
        *s = '\0';
        *rest = s + 1;
    }
    return token;
}

int main(){
    char str[80] = "Summer embedded (2015) - NCKU";
    const char delim[5] = " -()";
    char *token, *rest;
    rest = str;

    /* get the first token */
    token = strtok_reentrant(str, delim, &rest);

    /* walk through other tokens */
    while( token != NULL ) {
        printf( "%s\n", token );
        token = strtok_reentrant(NULL, delim, &rest);
    }

    return 0;
}