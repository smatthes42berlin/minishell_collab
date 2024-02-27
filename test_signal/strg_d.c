#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int main() {
    const char *str = "/snap/bin/gimp";
    char ch = 'l';

    // Suche das letzte Vorkommen von 'e' im String
    char *ptr = strrchr(str, ch);

    if (ptr) {
        printf("Im String \n|%s|\nKommt das letzte Vorkommen von '%c' ist an Position: %ld\n", ptr + 1,  ch, ptr - str);
    } if(ptr == NULL) {
        printf("Zeichen '%c' nicht gefunden.\n", ch);
    }

    return 0;
}

// void handle_sigusr1(int sig) {
//     printf("SIGUSR1 empfangen, beende Kindprozess.\n");
//     exit(EXIT_SUCCESS); // Beendet den Kindprozess
// }

// int main(void) {
//     pid_t pid = fork();

//     if (pid == -1) {
//         perror("Fehler bei fork()");
//         exit(EXIT_FAILURE);
//     }

//     if (pid > 0) {
//         // Elternprozess
//         printf("Elternprozess: Warte auf CTRL+D...\n");

//         char c;
//         while (read(STDIN_FILENO, &c, 1) > 0) {
//             if (c == 0x04) { // CTRL+D erkannt
//                 printf("\nCTRL+D erkannt. Sende SIGUSR1 an Kindprozess %d.\n", pid);
//                 kill(pid, SIGUSR1);
//                 wait(NULL); // Warte auf die Beendigung des Kindprozesses
//                 break;
//             }
//         }
//     } else {
//         // Kindprozess
//         if (signal(SIGUSR1, handle_sigusr1) == SIG_ERR) {
//             perror("signal() fehlgeschlagen");
//             exit(EXIT_FAILURE);
//         }

//         printf("Kindprozess: PID %d. Bereit, Eingaben zu verarbeiten.\n", getpid());

//         while (1) {
//             char *input = readline("cli> ");
//             if (input == NULL) {
//                 printf("Keine Eingabe erkannt. Normalerweise durch CTRL+D.\n");
//                 continue;
//             }

//             if (*input) {
//                 add_history(input);
//                 printf("Eingabe: '%s'\n", input);
//             }

//             free(input);
//         }
//     }

//     return 0;
// }


//------------------------------------------------------------------------------------


// int main(void) {
//     int pipefd[2];
//     pid_t pid;

//     // Erstelle eine Pipe
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork();
//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid > 0) {
//         // Elternprozess
//         close(pipefd[0]); // Schließe Leseende der Pipe im Elternprozess

//         char c;
//         ssize_t readBytes;
//         while ((readBytes = read(STDIN_FILENO, &c, 1)) > 0) {
//             write(pipefd[1], &c, 1); // Schreibe das Zeichen in die Pipe
//         }

//         // `CTRL+D` wurde gedrückt oder `read()` ist auf einen Fehler gestoßen
//         if (readBytes == 0) {
//             printf("\nCTRL+D erkannt oder Ende der Eingabe. Beende Kindprozess.\n");
//         } else {
//             perror("Fehler beim Lesen von STDIN");
//         }

//         close(pipefd[1]); // Signalisiere EOF an den Kindprozess
//         wait(NULL); // Warte auf die Beendigung des Kindprozesses
//     } else {
//         // Kindprozess
//         close(pipefd[1]); // Schließe Schreibende der Pipe im Kindprozess

//         // Dupliziere das Leseende der Pipe auf STDIN
//         dup2(pipefd[0], STDIN_FILENO);
//         close(pipefd[0]); // Das originale Leseende wird nicht mehr benötigt

//         char *input;
//         while ((input = readline("cli> ")) != NULL) {
//             printf("Kindprozess: Eingabe '%s'\n", input);
//             free(input);
//         }

//         // Wenn `readline()` NULL zurückgibt, wurde EOF erkannt
//         printf("Kindprozess: EOF erkannt, beende mich.\n");
//         exit(EXIT_SUCCESS);
//     }

//     return 0;
// }


// // ---------------------------------------------------------------------------------

// int main(void) {
//     FILE *input_stream = fopen("input.txt", "r");

//     if (input_stream == NULL) {
//         perror("Fehler beim Öffnen der Eingabedatei");
//         return 1;
//     }

//     rl_instream = input_stream; // Setze den Eingabestream von readline auf input_stream

//     char *input;
//     while ((input = readline("cli> ")) != NULL) {
//         printf("Gelesene Zeile: %s\n", input);
//         free(input);
//     }

//     fclose(input_stream); // Vergiss nicht, den Stream zu schließen
//     return 0;
// }
