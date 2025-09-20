#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void parse(char *line, char **argv)
{
    while (*line != '\0') {       /* if not the end of line ....... */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';       /* replace white spaces with 0    */
        if (*line != '\0')
            *argv++ = line;       /* save the argument position     */
        while (*line != '\0' && *line != ' ' && 
               *line != '\t' && *line != '\n') 
            line++;               /* skip the argument until ...    */
    }
    *argv = NULL;                 /* mark the end of argument list  */
}

void  execute(char **argv) //write your code here
{
//HINT you need to introduce the following functions: fork, execvp, waitpid
//Advanced HINT: pipe, dup2, close, open

     pid_t  pid;
     int    status;
}

/**
 * Print the entire content of the line array (first 100 chars) for debugging.
 * Does not stop at the \0' character; 
 *
 * @param line Pointer to the character array to print
 */
void print_line(char *line) {
    printf("\n-------------\n");
    printf("Current line:\n");
    for (int i = 0; i < 100; i++) {
        if (line[i] == '\n') {
            printf("\\n");
        } else if (line[i] == '\t') {
            printf("\\t");
        } else if (line[i] == '\0') {
            printf("\\0");
        } else {
            putchar(line[i]);
        }
    }
    printf("\n-------------\n");
}

int main(void)
{
    char line[1024];             /* the input line                 */
    char *argv[64];              /* the command line argument      */

    while (1) {                   /* repeat until done ....         */
        fputs("Shell -> ", stdout);     /*   display a prompt             */
        fgets(line, 1024, stdin);              /*   read in the command line     */
        print_line(line);
        fputs("\n", stdout);
        parse(line, argv);       /*   parse the line               */
        if (argv[0] && strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
            exit(0);            /*   exit if it is                */

        // print the current argv for debugging
        printf("Current argv:\n");
        for (int i = 0; argv[i] != NULL; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
        print_line(line);

        execute(argv);           /* otherwise, execute the command */
    }
    return 0;
}