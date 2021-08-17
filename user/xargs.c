#include "kernel/types.h"
#include "user/user.h"

#define MAXARGS 32
#define MAXLEN 128

void usage() 
{
    printf("Usage: xargs <default command ...>\n");
}

int main(int argc, char *argv[])
{
    // Get <default command> from argv and split into 
    // an array that will be used to build a new cmd
    
    if (argc < 2)
        usage();

    char *cmd[MAXARGS];

    for (int i = 1; i < argc; i++)
    {
        cmd[i-1] = argv[i];
    }
    printf("%s\n", cmd[0]);

    // Now begin reading from stdin until 
    // a \n is reached and then fork / exec 
    char buff[1024];
    while(gets(buff, MAXLEN))
    {
        // Now need to split buff at each empty space
        printf("%s\n", buff);
    }
    
    exit(0);
    
}