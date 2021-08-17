#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define TRUE 1
#define FALSE 0
typedef uchar bool;

// for each file in the specified directory (argv[1]),
// check if a file or dir.
//      if file then check if matches name
//      if dir then recurse

void usage()
{
    printf("Usage: find [dir] <string>\n");
}

bool check_dir(char *dir)
{
    struct stat st;
    if (stat(dir, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", dir);
        return FALSE;
    }
    if (st.type == T_DIR)
        return TRUE;
    return FALSE;
}

void find(char *dir, char *match_str)
{
    char buf[512];
    struct dirent de;
    struct stat st;

    int dir_fd = open(dir, 0);

    while (read(dir_fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0)
            continue;
        // printf("%s\n", de.name);
        if (stat(de.name, &st) < 0)
        {
            printf("ls: cannot stat %s\n", buf);
            continue;
        }
        if (st.type == T_DIR)
        {
            // recurse
            if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
                continue;

            char path[1024], *p;
            strcpy(path, dir);
            p = path + strlen(path);
            *p++ = '/';
            strcpy(p, de.name);
            find(path, match_str);
        }
        else if (st.type == T_FILE)
        {
            // print out if file name is a match
            int cmp = strcmp(de.name, match_str);
            // printf("Current file: %s\tMatch string: %s\t Match: %d\n", de.name, match_str, cmp);
            if (cmp == 0)
            {
                printf("%s/%s\n", dir, de.name);
            }
        }
    }
    close(dir_fd);
}

int main(int argc, char *argv[])
{
    char *pwd;
    char *match_str;
    if (argc != 2 && argc != 3)
    {
        usage();
        exit(1);
    }
    else if (argc == 2)
    {
        pwd = ".";
        match_str = argv[1];
    }
    else if (argc == 3)
    {
        pwd = argv[1];
        match_str = argv[2];
    }

    if (!check_dir(pwd))
        exit(1);
    find(pwd, match_str);
    exit(0);
}