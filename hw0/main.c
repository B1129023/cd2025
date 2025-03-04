#include <stdio.h>
#include <stdlib.h>

typedef struct link_list {
    unsigned char c;  
    int num; 
    struct link_list *next;
    struct link_list *prev;
} link_list;

void insert_or_update(link_list **head, unsigned char ch) {
    link_list *current = *head;

    if (current == NULL) {
        *head = (link_list *)malloc(sizeof(link_list));
        if (*head == NULL) {
            printf("memory malloc failed!\n");
            exit(1);
        }
        (*head)->c = ch;
        (*head)->num = 1;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return;
    }

    while (current != NULL) {
        if (current->c == ch) {
            current->num++; 
            return;
        }
        if (current->next == NULL) break;  
        current = current->next;
    }

    link_list *new_node = (link_list *)malloc(sizeof(link_list));
    if (new_node == NULL) {
        printf("memory malloc failed!\n");
        exit(1);
    }
    new_node->c = ch;
    new_node->num = 1;
    new_node->next = NULL;
    new_node->prev = current;
    current->next = new_node;
}

void read_self(char *filename, link_list **head) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("cannot open file: %s\n", filename);
        return;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {  
        insert_or_update(head, (unsigned char) ch);
    }
    fclose(fp);
}

void print_linked_list(link_list *head) {
    link_list *current = head;
    while (current != NULL) {
        if (current->c == '\n') {
            printf("'\\n' : %d\n", current->num);
        } else if (current->c == '\t') {
            printf("'\\t' : %d\n", current->num);
        } else if (current->c == ' ') {
            printf("' ' : %d\n", current->num);
        } else {
            printf("'%c' : %d\n", current->c, current->num);
        }
        current = current->next;
    }
}

void free_linked_list(link_list *head) {
    link_list *current = head;
    while (current != NULL) {
        link_list *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    link_list *head = NULL;  
    read_self("main.c", &head);
    print_linked_list(head);
    free_linked_list(head);
    return 0;
}
