#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

typedef struct Node {
    char* str;
    struct Node* next;
} Node;

void init_head(Node** head) {
    *head = (Node*) malloc(sizeof(Node));
    if (*head == NULL) {
        perror("malloc");
        exit(1);
    }
}

void add_node(char* str, size_t str_len, Node** tail) {
    (*tail)->next = (Node*) malloc(sizeof(Node));
    if ((*tail)->next == NULL) {
        perror("malloc");
        exit(1);
    }

    Node *node = (*tail)->next;
    node->str = (char*) malloc(sizeof(char) * (str_len + 1));
    if (node->str == NULL) {
        perror("malloc");
        exit(1);
    }

    strcpy(node->str, str);
    *tail = node;
}

void print_list(Node *head) {
    Node* node = head->next;
    while (node != NULL) {
        printf("%s\n", node->str);
        node = node->next;
    }
}

int main()
{
    Node* head;
    init_head(&head);
    Node* tail = head;

    char buf[BUF_SIZE];

    while(1) {

        if (fgets(buf, BUF_SIZE, stdin) == NULL) {
            if (ferror(stdin) != 0) {
                perror("fgets");
                return 1;
            }
            break;
        }

        if (buf[0] == '.') {
            break;
        }

        add_node(buf, strlen(buf), &tail);
    }
    print_list(head);
    return 0;
}