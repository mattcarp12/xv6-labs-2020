#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int ping[2], pong[2];
    pipe(ping);
    pipe(pong);
    int child_pid = fork();
    if (child_pid == 0) {
        // in child process

        // first close file we wont be needing
        close(ping[1]);
        close(pong[0]);

        // receive byte from parent
        char buffer;
        read(ping[0], &buffer, 1);

        // report the ping from parent
        printf("%d: received ping\n", getpid());

        // now write pong to parent
        write(pong[1], " ", 1);
        close(pong[1]);

        exit(0);

    } else {
        //in parent process

        // need to send a byte to child 
        // using the pipe fds

        // first close files we wont be needing
        close(ping[0]);
        close(pong[1]);
        
        // now write ping to the child
        write(ping[1], " ", 1);
        close(ping[1]);

        // now read from child
        char buffer;
        read(pong[0], &buffer, 1);

        // report the ping has been ponged
        printf("%d: received pong\n", getpid());
        
        exit(0);
    }
}