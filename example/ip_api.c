#include "ip.h"
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "ip_api.h"

static int main_entry_point2(int argc, const char*argv[]);

int main_entry_point2(int argc, const char*argv[])
{
   return main_entry_point(argc, (char**)argv);   
}

#define SIZEOF(X) (sizeof(X)/sizeof(char*))
#define MAX_LEN   1024

/*
 * @para: argc - number of command
 * @para: argv - array of command
 * @para: buffer - buffer provided by the user
 * @para: buffer_size - size of the buffer 
 */
int main_entry_point3(int argc, const char* argv[], char* buffer, size_t buffer_size)
{
   int code_rtn = 0;

   int saved_stdout = dup(STDOUT_FILENO);
   int pipefd[2];

   do
   {
      if(pipe(pipefd) == -1)
      {
         perror("pipe error");
         code_rtn = -1;
         break;
      }

      int code = dup2(pipefd[1], STDOUT_FILENO); 
      close(pipefd[1]);
      
      if (code == -1)
      {
         perror("dup2 error");
         code_rtn = -2;
         break;
      }

      int code_main = main_entry_point2(argc, argv);   
      if (code_main)
      {
         perror("iproute2 core error");
         code_rtn = code_main;
         break;
      }
  
      read(pipefd[0], buffer, buffer_size);
      dup2(saved_stdout, STDOUT_FILENO);
   }while(0);

   close(pipefd[0]);
   close(pipefd[1]);
   
   return code_rtn;
}
