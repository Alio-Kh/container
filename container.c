#define _GNU_SOURCE 
#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mount.h>


int child(void *args)
{
    char hostname[20] = "KHYATTI&ELGHAZI";
    printf("child pid inside: %d.\n", getpid());
    printf("parent pid inside: %d.\n", getppid());
    sleep(1);
    printf ("running container ... \n");
    char cwd[255];
    if(getcwd(cwd, sizeof(cwd))!= NULL){
        sethostname(hostname,sizeof(hostname));
        printf ("processing");
       /* for (int i = 0 ; i<4 ; i++) {
            printf (".");
            sleep(2);
            if (i==3) printf (".\n");
        }*/
        printf ("pwd = %s \n", cwd);
        chroot(cwd);
        chdir("/");
        mount("proc", "/proc", "proc", 0, NULL);
        sleep(1);
        printf ("configuring network ... \n");
        system("ip link");
        sleep(1);
        printf("executing new bash ...\n");
        sleep(1);
        printf("container started. \n");
        //system("bash");
        execlp("/bin/bash", "/bin/bash" , NULL);
    }else{
        perror("getcwd() error");
        return 1;
    }   
}

int main()
{
    // Flags Description :
    // CLONE_NEWUTS : creer un nv processus au sein d'un nv ns uts namespace isolu
    // porte les memes identificateurs du systeme (hostname + NIS domain name)
    // CLONE_NEWPID : creer un nv processus au sein d'un nv ns pid ( diffrents processus dans differents nv peut avoir le meme pid)
    // CLONE_NEWIPC : creer un nv processus au sein d'un nv ns IPC ( isoler l'inter process communication )
    // CLONE_NEWNS : creer un nv processus au sein d'un nv ns ( mount space )
    // CLONE_NEWNET : creer un nv processus au sein d'un nv ns ( isolution du reseau)
    int namespaces = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    char cmd[200];
    
    pid_t pid = clone(child, malloc(4096) + 4096, SIGCHLD|namespaces, NULL);
    if (pid == -1) {
        perror("clone");
        exit(1);
    }
    printf("child pid outside: %d.\n", pid);
    
    system(" cgcreate -g memory:KHGH_shell");
    
    system(" echo 50M > /sys/fs/cgroup/memory/KHGH_shell/memory.limit_in_bytes");
    sprintf(cmd,"sudo echo %d  > /sys/fs/cgroup/memory/KHGH_shell/cgroup.procs",pid);
     
    system(cmd);
    
    waitpid(pid, NULL, 0);
    return 0;
}
