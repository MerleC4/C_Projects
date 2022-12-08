#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
/*
* File: calls.c
* Author: Merle Crutchfield
* Purpose: This is used to link together several phone calls from an input
* file and then check to see based on the user stdin if they had talked at
* all or if they are connected through any numbers. It uses a similar data
* structure of two linked list nodes to tie together the calls like in last
* weeks assignment, but also encorporated the BFS when checking to see if 
* they are connected at all. This also runs with no valgrind errors and no
* memory not freed.
*/


/*
* Linked list of phone number info
*/
typedef struct phoneNode {
    char *number;
    int level;
    struct countNode *countHead;
    struct phoneNode *queue;
    struct phoneNode *next;
} phoneNode;

/*
* Linked list of numbers attached
*/
typedef struct countNode {
    int num;
    struct phoneNode *called;
    struct countNode *next;
} countNode;

/*
* makePhoneNode(char) -- Makes a phoneNode, and uses the char input
* as its phone number. Returns the phoneNode.
*/
phoneNode *makePhoneNode(char *number) {
    phoneNode *temp = malloc(sizeof(phoneNode));
    if (!temp) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    temp->number = strdup(number);
    temp->level = -1;
    temp->countHead = NULL;
    temp->queue = NULL;
    temp->next = NULL;
    return temp;
}

/*
* makeCountNode(phoneNode) -- Makes a countNode, and uses the phoneNode input
* as its called value. Returns the countNode.
*/
countNode *makeCountNode(phoneNode *node) {
    countNode *temp = malloc(sizeof(countNode));
    if (!temp) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    temp->num = 1;
    temp->called = node;
    temp->next = NULL;
    return temp;
}

/*
* validNum(char) -- Makes sure that the input is in the right string order
* as the spec requires. Returns 1 if yes and 0 if not.
*/
int validNum(char *num) {
    if (strlen(num) != 12) {
        return 0;
    }
    for (int i = 0; i < 12; i++) {
        if (i == 3 || i == 7) {
            if (num[i] != '-') {
                return 0;
            }
        }
        else {
            if (num[i] < '0' || num[i] > '9') {
                return 0;
            } 
        }
    }
    return 1;
}

/*
* getPhone(phoneNode, char) -- Searches through the head pointer to
* find the phoneNode entered. If it exists it is returned and if not
* then NULL is returned.
*/
phoneNode *getPhone(phoneNode *head, char *num) {
    phoneNode *temp = head;
    while (temp) {
        if (strcmp(temp->number, num) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

/*
* addPhone(phoneNode, char) -- Adds the phoneNode entered into the
* head pointer. It iterates through til the end and then adds it.
*/
void addPhone(phoneNode *head, char *num) {
    phoneNode *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = makePhoneNode(num);
}

/*
* callLink(phoneNode, phoneNode) -- This links together the call that
* was made by the input file. It makes sure that the call was linked
* in both directions.
*/
void callLink(phoneNode *first, phoneNode *last) {
    countNode *temp = first->countHead;
    if (!temp) {
        first->countHead = makeCountNode(last);
        return;
    }
    while (temp->next) {
        if (temp->called == last) {
            temp->num++;
            return;
        }
        else {
            temp = temp->next;
        }
    }
    if (temp->called == last) {
        temp->num++;
        return;
    }
    else {
        temp->next = makeCountNode(last);
    }
}

/*
* firstInput(phoneNode, char) -- This is used for the input file and to
* build the phoneNode with all the phone calls connected together. It
* checks to make sure everything is valid, and if any errors are encountered
* it returns 1. If not returns 0.
*/
int firstInput(phoneNode *head, char *line) {
    int val = 0;
    char first[14];
    char last[14];
    char test[14];
    int inputs = sscanf(line, "%13s %13s %13s", first, last, test);
    if (inputs <= 0) {
        return 0;
    }
    if (inputs != 2) {
        fprintf(stderr, "Invalid input %d.\n", inputs);
        return 1;
    }
    if (!validNum(first) || !validNum(last)) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (strcmp(first, last) == 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    phoneNode *temp1 = getPhone(head, first);
    if (!temp1) {
        addPhone(head, first);
        temp1 = getPhone(head, first);
    }
    phoneNode *temp2 = getPhone(head, last);
    if (!temp2) {
        addPhone(head, last);
        temp2 = getPhone(head, last);
    }
    callLink(temp1, temp2);
    callLink(temp2, temp1);
    return val;
}

/*
* connected(phoneNode, phoneNode) -- This checks to see if two phone
* numbers are connected to each other. If they are, it returns how many
* times they called each other and if not it returns -1.
*/
int connected(phoneNode *first, phoneNode *last) {
    countNode *temp = first->countHead;
    while (temp) {
        if (temp->called == last) {
            return temp->num;
        }
        temp = temp->next;
    }
    return -1;
}

/*
* clearQueue(phoneNode) -- This is used to clear the head phoneNode queue
* values so that the BFS search can be done correctly.
*/
void clearQueue(phoneNode *head) {
    phoneNode *temp = head;
    while (temp) {
        temp->level = -1;
        temp->queue = NULL;
        temp = temp->next;
    }
}

/*
* BFS(phoneNode, phoneNode, phoneNode) -- This uses the BFS algorithm that we
* saw in the spec to run through and see by how many phone numbers are two
* connected. It uses a queue to iterate through and then pop the head if it
* is not there and runs through until completion. Returns -1 if they are not
* connected and the coresponding number if they are.
*/
int BFS(phoneNode *head, phoneNode *start, phoneNode *target) {
    clearQueue(head);
    phoneNode *queueTop = start;
    phoneNode *queueEnd = start;
    start->level = 0;
    start->queue = NULL;
    while (queueTop) {
        if (queueTop == target) {
            return queueTop->level - 1;
        }
        countNode *temp = queueTop->countHead;
        while (temp) {
            phoneNode *curr = temp->called;
            if (curr->level < 0) {
                queueEnd->queue = curr;
                queueEnd = curr;
                queueEnd->queue = NULL;
                curr->level = queueTop->level + 1;
            }
            temp = temp->next;
        }
        queueTop = queueTop->queue;
    }
    return -1;
}

/*
* secondInput(phoneNode, char) -- This is used for the user inputs of phone numbers
* to check and see if the two numbers have either called each other or if they are
* connected through other numbers. It first ensures that the input is valid, and then
* makes sure that the input is in the phoneNode linked list. It then calls several
* different methods to check for BFS and if it is connected. Returns 1 if an error
* was encountered and 0 if not.
*/
int secondInput(phoneNode *head, char *line) {
    int val = 0;
    char first[14];
    char last[14];
    char test[14];
    int inputs = sscanf(line, "%13s %13s %13s", first, last, test);
    if (inputs == 0) {
        return 0;
    }
    if (inputs != 2) {
        fprintf(stderr, "Cannot query a number that is not in the graph.\n");
        return 1;
    }
    if (!validNum(first) || !validNum(last)) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (strcmp(first, last) == 0) {
        fprintf(stderr, "Cannot query two itentical numbers.\n");
        return 1;
    }
    phoneNode *temp1 = getPhone(head, first);
    phoneNode *temp2 = getPhone(head, last);
    if (!temp1 || !temp2) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    int talked = connected(temp1, temp2);
    if (talked != -1) {
        printf("Talked %d times\n", talked);
        return val;
    }
    talked = BFS(head, temp1, temp2);
    if (talked == -1) {
        printf("Not connected\n");
    }
    else {
        printf("Connected through %d numbers\n", talked);
    }
    return val;
}

/*
* freeCountNode(phoneNode) -- This method frees all of the
* allocated memory in the countNodes.
*/
void freeCountNode(phoneNode *temp) {
    countNode *curr = temp->countHead;
    if (!curr) {
        return;
    }
    countNode *next = curr->next;
    free(curr);
    curr = next;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(int argc, char **argv)
{
    int val = 0;
    if (argc == 1) {
        fprintf(stderr, "Error: must specify input files to build calls graph.\n");
        return 1;
    }
    phoneNode *head;
    head = malloc(sizeof(phoneNode));
    if (!head) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        return 1;
    }
    head->number = strdup("first");
    head->level = -1;
    head->countHead = NULL;
    head->queue = NULL;
    head->next = NULL;

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            fprintf(stderr, "%s: No such file or directory\n", argv[i]);
            val = 1;
        }
        else {
            char *line = NULL;
            size_t size = 0;
            while (getline(&line, &size, file) != EOF) {
                val = firstInput(head, line);
            }
            free(line);
            fclose(file);
        }
    }
    char *line;
    size_t size = 0;
    while (getline(&line, &size, stdin) != EOF) {
        val = secondInput(head, line);
    }
    free(line);

    phoneNode *curr = head;
    phoneNode *temp;
    while (curr) {
        temp = curr->next;
        freeCountNode(curr);
        free(curr->number);
        free(curr);
        curr = temp;
    }

    return val;
}