#define _GNU_SOURCE 
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mount.h>

char *hostname;
int child(void *args)
{
    // char hostname[20] = "KHYATTI&ELGHAZI";

    printf("child pid inside: %d.\n", getpid());
    printf("parent pid inside: %d.\n", getppid());
    sleep(1);
    printf ("running container ... \n");
    char cwd[255];
    if(getcwd(cwd, sizeof(cwd))!= NULL){
        sethostname(hostname,sizeof(hostname));
        printf ("processing...");
        printf ("cwd = %s \n\n", cwd);
        chroot(cwd);
        chdir("/");
        mount("proc", "/proc", "proc", 0, NULL);
        sleep(1);

        printf ("Child (new) network Namespace ... \n");
        system("ip link");
        sleep(1);

        printf("\n\n\nexecuting new bash ...\n");
        execlp("/bin/bash", "/bin/bash" , NULL);
        sleep(1);
        printf("\ncontainer started. \n\n");
    }else{
        perror("getcwd() error");
        return 1;
    }   
}

int main(int argc, char const *argv[])
{
    // Flags Description :
    // CLONE_NEWUTS : Creer un nouveu processus au sein d'un nouveu uts namespace isolu
    // porte les memes identificateurs du systeme (hostname + NIS domain name)
    // CLONE_NEWPID : Creer un nouveu processus au sein d'un nouveu pid namespace ( diffrents processus dans differents nv peut avoir le meme pid)
    // CLONE_NEWIPC : Creer un nouveu processus au sein d'un nouveu IPC namespace ( isoler l'inter process communication )
    // CLONE_NEWNS : Creer un nouveu processus au sein d'un nouveu namespace ( mount space )
    // CLONE_NEWNET : Creer un nouveu processus au sein d'un nouveu Network namespace ( isolution du reseau)
    // SIGCHLD
    int flags = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    char cmd[200];

    hostname = malloc(30*sizeof(hostname));
    strcpy(hostname, argv[1]);
    
     printf("Original (parent) Network Namespace:\n");
     system("ip link");
     printf("\n\n");
    
    
    pid_t pid = clone(child, malloc(4096) + 4096, SIGCHLD|flags, NULL);
    if (pid == -1) {
        perror("clone");
        exit(1);
    }
    
    printf("\nChild pid outside: %d.\n\n", pid);
    
    system(" cgcreate -g memory:KH_GH_shell");
    
    system(" echo 50M > /sys/fs/cgroup/memory/KH_GH_shell/memory.limit_in_bytes");
    sprintf(cmd,"sudo echo %d  > /sys/fs/cgroup/memory/KH_GH_shell/cgroup.procs",pid);
     
    system(cmd);
    
    waitpid(pid, NULL, 0);
    return 0;
}
