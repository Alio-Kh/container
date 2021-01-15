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

//The new hostname 
char *hostname;

int child(void *args)
{
    printf("Child pid inside: %d.\n", getpid());
    printf("Parent pid inside: %d.\n", getppid());
    sleep(1);
    printf ("running container ... \n");
    char cwd[255];
    if(getcwd(cwd, sizeof(cwd))!= NULL){
        //Create a new hostname
        sethostname(hostname,sizeof(hostname));
        printf ("processing...");
        // The Current Working Directory
        printf ("cwd = %s \n\n", cwd);
        
        // Change the root directory of the container (child process) to the current working directory
        chroot(cwd);
	chdir("/");
	// Attach the (kernel) /proc file system to proc directory of new container, with proc as filesystem type 
	mount("proc", "/proc", "proc", 0, NULL);
	sleep(1);

	// Shows the network device configuration of the child process
	printf ("Child (new) network Namespace ... \n");
	system("ip link");
	sleep(1);

	printf("\n\n\n executing new bash ...\n");
	// Execute a new bash for  the container 
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
    // To create a child process in a new namespace and isolated resources we need to use one or more of the following flags :
    // CLONE_NEWUTS : Create a new process in a new isolated uts namespace
    // has the same system identifiers (hostname + NIS domain name)
    // CLONE_NEWPID : Create a new process in a new pid namespace (different processes in different new can have the same pid)
    // CLONE_NEWIPC : Create a new process in a new IPC namespace (isolate inter process communication)
    // CLONE_NEWNS : Create a new process within a new namespace (mount space)
    // CLONE_NEWNET : Create a new process within a new Network namespace (network isolution)
    // SIGCHLD : To send a signal to wakeup the parent process when a children is died 
    int flags = CLONE_NEWUTS|CLONE_NEWPID|CLONE_NEWIPC|CLONE_NEWNS|CLONE_NEWNET;
    char cmd[200];

    hostname = malloc(30*sizeof(hostname));
    strcpy(hostname, argv[1]);
    
    // Shows the network device configuration of the parent process
    printf("\n\n");
    printf("Original (parent) Network Namespace:\n");
    system("ip link");
    printf("\n\n");
    
    // Create a (new) child process that have his own view in the system 
    pid_t pid = clone(child, malloc(4096) + 4096, SIGCHLD|flags, NULL);
    if (pid == -1) {
        perror("clone");
        exit(1);
    }
    
    printf("\nChild pid outside: %d.\n\n", pid);
    
    // Ctreate a new Cgroupe in "/sys/fs/cgroup/memory/" called KH_GH_shell
    system(" cgcreate -g memory:KH_GH_shell");
    
    // Limmit the momory of the new Cgroup KH_GH_shell 
    // NB: you should check if the swap is 0 in /sys/fs/cgroup/memory/KH_GH_shell/memory.swappiness
    system(" echo 50M > /sys/fs/cgroup/memory/KH_GH_shell/memory.limit_in_bytes");
    
    // Attache the new child process to the new KH_GH_shell Cgroup 
    sprintf(cmd,"sudo echo %d  > /sys/fs/cgroup/memory/KH_GH_shell/cgroup.procs",pid);
    system(cmd);
    
    // The parent process waits for the child process until it ends
    waitpid(pid, NULL, 0);
    return 0;
}
