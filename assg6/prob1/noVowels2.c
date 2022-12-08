#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
/*
* File: noVowels2.c
* Author: Merle Crutchfield
* Purpose: Takes in a sequence of strings and makes sure each
* string is valid. It then uses a linked list of nodes, which
* is also a linked list, to store the coresponding same pairs
* of words with no vowels. At the end, it prints them all out.
*/


/*
* Linked list of strings
*/
typedef struct node {
    char *word;
    struct node *next;
} node;

/*
* Linked list of nodes
*/
typedef struct listNode {
    struct node *words;
    struct listNode *next;
} listNode;

/*
* containsBadVal(str[]) -- This method runs a for loop that
* checks for each value in a string if they are not a letter
* of the alphabet, when lowercased, to ensure that it is a 
* valid string. Returns 1 if it is not a good string and 0
* if it is.
*/
int containsBadVal(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z') {
            return 1;
        }
    }
    return 0;
}

/*
* noVowelCompare(strFirst[], str[]) -- This method runs a for
* loop on the first string entered and then every other string
* in the sequence of strings. This for loop checks to see if
* the char at the location is a vowel, and if it is then it
* removes it when creating the new string without vowels. It
* then checks to see if they are the same and resets the 
* initial array of characters. Returns 1 if same and 0 if not.
* Used calloc on noValFirst/noVal so they are always initialized
* so I didn't get vanguard errors.
*/
int noVowelCompare(char strFirst[], char str[]) {
    char *noValFirst;
    char *noVal;
    noValFirst = (char *)calloc(65, sizeof(char));
    noVal = (char *)calloc(65, sizeof(char));
    if (!noValFirst || !noVal) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    int index = 0;
    int check = 1;
    for (int i = 0; strFirst[i] != '\0'; i++) {
        if (!(tolower(strFirst[i]) == 'a' || tolower(strFirst[i]) == 'e' 
            || tolower(strFirst[i]) == 'i' || tolower(strFirst[i]) == 'o'
            || tolower(strFirst[i]) == 'u')) {
            noValFirst[index] = tolower(strFirst[i]);
            index = index + 1;
        }
    }
    index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(tolower(str[i]) == 'a' || tolower(str[i]) == 'e' 
            || tolower(str[i]) == 'i' || tolower(str[i]) == 'o'
            || tolower(str[i]) == 'u')) {
            noVal[index] = tolower(str[i]);
            index = index + 1;
        }
    }
    if (noValFirst && noVal) {
        check = strcmp(noValFirst, noVal);
        if (!check) {
            return 1;
        }
    }
    // Have to clear origional array of chars for no errors
    memset(noValFirst, 0, 65);
    memset(noVal, 0, 65);
    return 0;
}

/*
* vowelsList(char*, listNode*) -- This method takes in the
* string entered by the user and the head of the linked list
* of lists. It then checks iterates through the linked list
* to check if they are the same without vowels. If yes, it
* adds it to the list of that node, and if not it iterates
* through. It then will add it to the end if it isn't in it.
*/
void vowelsList(char *str, listNode *head) {
    int test = 0;
    listNode *curr = head;
    // Iterates through til last node so we don't end up w NULL
    while (curr->next) {
        test = noVowelCompare(str, curr->words->word);
        if (test) {
            node *temp = malloc(sizeof(node));
            temp = curr->words;
            while (temp->next) {
                temp = temp->next;
            }
            node *new = malloc(sizeof(node));
            if (!new) {
                fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
                exit(1);
            }
            new->word = strdup(str);
            new->next = NULL;
            temp->next = new;
            return;
        }
        curr = curr->next;
    }
    // Last node check without iterating to NULL
    test = noVowelCompare(str, curr->words->word);
    if (test) {
        node *temp = malloc(sizeof(node));
        if (!temp) {
            fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
            exit(1);
        }
        temp = curr->words;
        while (temp->next) {
            temp = temp->next;
        }
        node *new = malloc(sizeof(node));
        if (!new) {
            fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
            exit(1);
        }
        new->word = strdup(str);
        new->next = NULL;
        temp->next = new;
        return;
    }
    // New node case
    listNode *newList = malloc(sizeof(listNode));
    node *start = malloc(sizeof(node));
    if (!newList || !start) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    start->word = strdup(str);
    start->next = NULL;
    newList->words = start;
    newList->next = NULL;
    curr->next = newList;
}

int main(void)
{
    listNode* head = NULL;
    head = (listNode*)malloc(sizeof(listNode));
    node* top = NULL;
    top = malloc(sizeof(node));
    if (!head || !top) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        return 1;
    }
    // Initialized head to avoid memory errors
    top->word = "";
    top->next = NULL;
    head->words = top;
    head->next = NULL;

    char str[65];
    int r = scanf("%64s", str);
    int val = 0;
    while (r > 0) {
        if (containsBadVal(str)) {
            fprintf(stderr, "Bad string input: %s\n", str);
            val = 1;
        } else {
            vowelsList(str, head);
        }
        r = scanf("%64s", str);
    }
    if (r == 0) {
        fprintf(stderr, "Bad string input\n");
        return 1;
    }
    // head first node is empty string, don't wanna print out extra whitespace
    if (head->next) {
        listNode *temp = head->next;
        while (temp) {
            node *tempWord = temp->words;
            while (tempWord) {
                printf("%s ", tempWord->word);
                tempWord = tempWord->next;
            }
            printf("\n");
            temp = temp->next;
        }
    }
    return val;
}