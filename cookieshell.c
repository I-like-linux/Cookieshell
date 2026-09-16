#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    printf("\e[2J\e[H");

    bool running = true;

    while (running) {
        char MainInput[1024]; // allocates 256 bytes to MainInput 
        char Pointer[] = ">"; // pointer, deafault is ">"
        char ArgPointer[] = "↳"; // pointer for arguments in 
        char PreCursor[1024]; // current file path
        char User[] = "user"; // the user
        char UserSeperator = '@'; // the symbol between the username and the PreCursor when printed in the main promt, default is "@"

	// detect the current path and use it as the PreCursor
	getcwd(PreCursor, sizeof(PreCursor));

        printf("\e[38;2;130;200;200m%s\e[38;2;150;255;150m%c\e[38;2;0;150;150m%s\e[0m%s ", User, UserSeperator, PreCursor, Pointer); // 130;200;200 . 150;255;255 . 0;150;150 . 255;255;255
	fgets(MainInput, sizeof(MainInput), stdin);
        
        if (strcmp(MainInput, "exit\n") == 0) {
	    running = false;
        }
        if (strcmp(MainInput, "clear\n") == 0) {
            printf("\e[2J\e[H");
        }

	if (strcmp(MainInput, "list\n") == 0) {
            DIR *d = opendir(".");
            struct dirent *entry = readdir(d);
	    while ((entry = readdir(d)) != NULL) {
	        printf("%s | ", entry->d_name);
	    }
	    closedir(d);
	    printf("\n");
	}
        if (strcmp(MainInput, "alist\n") == 0) {
            DIR *d = opendir(".");
            struct dirent *entry = readdir(d);
	    while ((entry = readdir(d)) != NULL) {
	        printf("%s\n", entry->d_name);
	    }
	}

	if (strcmp(MainInput, "chdir\n") == 0) {
            char ChdirInput[1024];
	    printf(" %s ", ArgPointer);
	    fgets(ChdirInput, sizeof(ChdirInput), stdin);
	    ChdirInput[strcspn(ChdirInput, "\n")] = 0;
	    chdir(ChdirInput);
	}

	if (strcmp(MainInput, "del\n") == 0) {
	    char DelInput[1024];
	    printf(" %s ", ArgPointer);
	    fgets(DelInput, sizeof(DelInput), stdin);
	    DelInput[strcspn(DelInput, "\n")] = 0;
	    remove(DelInput);
	}
	if (strcmp(MainInput, "deldir\n") == 0) {
            char DeldirInput[1024];
	    printf(" %s ", ArgPointer);
	    fgets(DeldirInput, sizeof(DeldirInput), stdin);
	    DeldirInput[strcspn(DeldirInput, "\n")] = 0;
	    rmdir(DeldirInput);
	}
	if (strcmp(MainInput, "mkfle\n") == 0) {
            char MkfleInput[1024];
	    printf(" %s ", ArgPointer);
	    fgets(MkfleInput, sizeof(MkfleInput), stdin);
	    MkfleInput[strcspn(MkfleInput, "\n")] = 0;
	    int fd = open(MkfleInput, O_CREAT | O_EXCL | O_WRONLY, 0644);
	}
	if (strcmp(MainInput, "repeat\n") == 0) {
	    char RepeatInput[2048]; // doubble the usual 1024 so larger entries can fit in repeat
	    printf(" %s ", ArgPointer);
            fgets(RepeatInput, sizeof(RepeatInput), stdin);
	    RepeatInput[strcspn(RepeatInput, "\n")] = 0;
	    printf("%s\n", RepeatInput);
	}
	if (strcmp(MainInput, "exec:\n") == 0) {
            char ExecPathInput[2048];
	    printf(" %s ", ArgPointer);
	    fgets(ExecPathInput, sizeof(ExecPathInput), stdin);
	    char ExecPath[2048];
	    ExecPathInput[strcspn(ExecPathInput, "\n")] = 0;
	    snprintf(ExecPath, sizeof(ExecPath), "/bin/%s", ExecPathInput);
	    printf("%s%s\n", "attempting to excute file: ", ExecPath);
	    pid_t pid = fork();
            if (pid == 0) {
                execl(ExecPath, ExecPath, NULL);
		perror("exec failed");
		_exit(1);
	    } else {
                waitpid(pid, NULL, 0);
	    }
	}
    }
    return 0;
}
