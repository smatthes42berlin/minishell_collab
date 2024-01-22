#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;


t_list *create_node(pid_t pid) {
    t_list *new_node = malloc(sizeof(t_list));
    pid_t *pid_ptr = malloc(sizeof(pid_t));
    if (new_node == NULL || pid_ptr == NULL) {
        free(new_node);  // Vermeidung von Speicherlecks
        free(pid_ptr);
        return NULL;
    }
    *pid_ptr = pid;
    new_node->data = pid_ptr;
    new_node->next = NULL;
    return new_node;
}

void append_node(t_list **head, pid_t pid) {
    t_list *new_node = create_node(pid);
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_list *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}


void print_list(t_list *head) {
    t_list *current = head;
    while (current != NULL) {
        pid_t *pid_ptr = (pid_t *)current->data;
        if (pid_ptr != NULL) {
            printf("%d ", *pid_ptr);
        }
        current = current->next;
    }
    printf("\n");
}


void free_list(t_list *head) {
    t_list *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}



void fill_list_recursively(t_list **list, int current, int max) {
    if (current > max) {
        return;
    }

    pid_t pid = fork();
    if (pid == 0) { // Kindprozess
        // Hier könnten Sie execve aufrufen, um einen Befehl auszuführen
        // ...
        fill_list_recursively(list, current + 1, max);
        exit(0); // Beenden des Kindprozesses
    } else if (pid > 0) { // Elternprozess
       int status;
        printf("%i\n", pid);
       waitpid(pid, &status, 0); // Wartet auf die Beendigung des Kindprozesses

        // Fügen Sie hier Informationen zur Liste hinzu, z.B. den PID
        append_node(list, pid);

        // Fortsetzung der Rekursion im Elternprozess
        fill_list_recursively(list, current + 1, max);
    } else {
        // Fehlerbehandlung für fork
        perror("fork failed");
        exit(1);
    }
}


int main() {
    t_list *my_list = NULL;
    fill_list_recursively(&my_list, 1, 5);  // Fügt Zahlen von 1 bis 5 zur Liste hinzu
    print_list(my_list);  // Druckt die Liste
    free_list(my_list);   // Gibt den Speicher frei
    return 0;
}

