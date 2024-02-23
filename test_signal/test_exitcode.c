#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execve_handler(const char *file_path, char *const argv[], char *const envp[]) {
    if (execve(file_path, argv, envp) < 0) {
        perror("execve error");
        exit(EXIT_FAILURE); // Dies setzt den Exit-Code auf EXIT_FAILURE, was in der Regel 1 ist
    }
}

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    int status1, status2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        char *argv[] = {"/bin/ls", "-l", NULL};
        execve_handler("/bin/ls", argv, NULL);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        char *argv[] = {"/bin/grep", "iiiiiiiiiii", NULL};
        execve_handler("/bin/grep", argv, NULL);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    // Warte auf Beendigung von Kindprozess 1 und hole den Exit-Code
    waitpid(pid1, &status1, 0);
    if (WIFEXITED(status1)) {
        printf("Exit-Code von /bin/ls: %d\n", WEXITSTATUS(status1));
    }

    // Warte auf Beendigung von Kindprozess 2 und hole den Exit-Code
    waitpid(pid2, &status2, 0);
    if (WIFEXITED(status2)) {
        printf("Exit-Code von /bin/grep: %d\n", WEXITSTATUS(status2));
    }

    return 0;
}
