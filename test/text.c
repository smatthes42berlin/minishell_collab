#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_list {
    pid_t data;
    struct s_list *next;
} t_list;

t_list *create_node(int data) {
    t_list *new_node = malloc(sizeof(t_list));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(t_list **head, int data) {
    t_list *new_node = create_node(data);
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
        printf("%d ", current->data);
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

