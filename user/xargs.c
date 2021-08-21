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

    int new_argc = 0;
    char *cmd[MAXARGS];
    char *path = argv[1]; // same as cmd[0]

    for (; new_argc < argc - 1; new_argc++)
    {
        cmd[new_argc] = argv[new_argc + 1];
    }
    // printf("This is the first cmd:\t%s\n", cmd[0]);

    // Now begin reading from stdin until
    // a \n is reached and then fork / exec
    char buff[1024];
    while (1)
    {
        gets(buff, MAXLEN);
        int line_len = strlen(buff);
        if (line_len < 1)
            break;

        // Now need to split buff at each empty space
        // printf("Successfully read string from stdin:\t%s\n", buff);

        int last_space = 0;
        for (int i = 0; i < line_len; i++)
        {
            if (buff[i] == ' ' || i == line_len - 1)
            {
                int new_arg_len = i - last_space + 1;
                char *new_arg = malloc(new_arg_len);
                memmove(new_arg, buff + last_space, new_arg_len);
                // printf("Contents of new_arg: %s\t len: %d\n", new_arg, new_arg_len);
                cmd[new_argc++] = new_arg;
                last_space = i;
            }
        }
        cmd[new_argc] = '\0';

        int pid = fork();
        if (pid == 0)
        {
            // in child
            // printf("Running cmd %s in child process (pid: %d) \n", path, pid);
            for (int i = 0; i < new_argc; i++)
            {
                // printf("%s\t", cmd[i]);
            }
            exec(path, cmd);
        }
        else
        {
            // in parent
            pid = wait((int *)0);
        }
    }

    exit(0);
}