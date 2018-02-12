#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
// hello world in C
#define MAX_BUF 160
#define MAX_TOKS 100
int main(void) {
         char *pos;
         char *tok;
         char s[MAX_BUF];
         char *toks[MAX_TOKS];
        int flag=1;
        while(flag==1){
               
                char exit[]="exit";
                printf("msh>");
                //grabbing user input
                 char *input = fgets(s, MAX_BUF-1, stdin);
               
                //checking if the user entered "exit"
                if(strcmp(input,"exit\n")==0)
                {
                        flag=2;
                }
                //detecting the ctrl+d
                else if(feof(stdin))
                {       printf("\n");
                        flag=2;
                }else if(strcmp(input,"today\n")==0){

                    time_t timer;
                    char buffer[26];
                    struct tm* tm_info;
                
                    time(&timer);
                    tm_info = localtime(&timer);
                
                    strftime(buffer, 26, "%B %d, %Y", tm_info);
                    puts(buffer);

                }


                else if(strcmp(input,"help\n")==0){
                        printf("please enter Linux command or 'exit' to exit\n");
                }
                else if(strcmp(input,"cat\n")==0){
                        printf("please enter a file name with 'cat' \n");
                }
                //printing out input
                else
                {       //making child process
                        int rc=fork();
                        if(rc<0){
                        fprintf(stderr, "fork failed");
                                flag=2;
                        }
                        else if(rc==0)
                        {
                          char *args[64];
                         char **next = args;
                         //breaking user input into tokens
                         tok= strtok(input, " \n");
                        while (tok != NULL)
                        {
                            *next++ = tok;
                            //printf("%s\n", temp);
                            tok = strtok(NULL, " \n");
                        }
                        *next = NULL;
                        execvp(args[0], args);
                           }
                          
                        else{
                                int wc=wait(NULL);
                        }
                        
                }
        }
return 0;

}