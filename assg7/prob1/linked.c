#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
/*
* File: linked.c
* Author: Merle Crutchfield
* Purpose: This links together webpages and checks to make sure that
* they are connected. It does this by making an adjacency list, which
* I implemented by using two structs. The first one is a pageNode which
* links the linkNodes together. The second is a linkNode, which contains
* the pageNodes that are linked together. It runs through and can take
* inputs from a file or from a user input stream.
*/


/*
* Linked list of pages
*/
typedef struct pageNode {
    char *name;
    struct linkNode *linkNodeHead;
    struct pageNode *next;
    int visited;
} pageNode;

/*
* Linked list of nodes
*/
typedef struct linkNode {
    struct pageNode *linked;
    struct linkNode *next;
} linkNode;

/*
* makeLinkNode(pageNode) -- Makes a linkNode, and uses the pageNode input
* as what it is linked to. Returns the linkNode made.
*/
linkNode *makeLinkNode(pageNode *page) {
    linkNode *temp = malloc(sizeof(linkNode));
    if (!temp) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    temp->linked = page;
    temp->next = NULL;
    return temp;
}

/*
* makePageNode(char[]) -- Makes a pageNode, and uses the name input
* as what it is named. Returns the pageNode made.
*/
pageNode *makePageNode(char *name) {
    pageNode *temp = malloc(sizeof(pageNode));
    if (!temp) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        exit(1);
    }
    temp->name = strdup(name);
    temp->linkNodeHead = makeLinkNode(temp);
    temp->next = NULL;
    return temp;
}

/*
* getPageNode(pageNode, char[]) -- Finds and returns the pageNode of the
* name entered. Iterates through the head pageNode to find them.
*/
pageNode *getPageNode(pageNode *head, char *pageName) {
    pageNode *temp = head;
    while (temp) {
        if (strcmp(temp->name, pageName) == 0) {
            return temp;
        }
        else {
            temp = temp->next;
        }
    }
    return temp;
}

/*
* markNotVisited(pageNode) -- Iteates through the head node and marks
* all of the visited values to 0 for the dfs.
*/
void markNotVisited(pageNode *head) {
    pageNode *temp = head;
    while (temp) {
        temp->visited = 0;
        temp = temp->next;
    }
}

/*
* dfs(pageNode, pageNode) -- Uses the dfs algorithm from the spec
* to check and see if they are linked. Returns 1 if they are
* linked and 0 if they are not.
*/
int dfs(pageNode *fromPage, pageNode *toPage) {
    if (fromPage == toPage) {
        return 1;
    }
    if (fromPage->visited == 1) {
        return 0;
    }
    fromPage->visited = 1;
    linkNode *temp = fromPage->linkNodeHead;
    while (temp) {
        if (dfs(temp->linked, toPage)) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/*
* addPages(pageNode, char[]) -- Adds the pages to the head pageNode.
* Reads through the whole line and makes sure the input is valid.
* It also checks for any of the errors specified in the spec.
* Returns 1 if there is an error anywhere.
*/
int addPages(pageNode *head, char *line) {
    int val = 0;
    int error = 0;
    char str[65];
    int count;
    while (sscanf(line, "%64s%n", str, &count) == 1) {
        error = 0;
        pageNode *temp = head;
        line += count;
        temp = head;
        while (temp->next) {
            if (strcmp(str, temp->name) == 0) {
                fprintf(stderr, "%s already exists as a page name.\n", str);
                val = 1;
                error = 1;
            }
            temp = temp->next;
        }
        if (strcmp(str, temp->name) == 0) {
            fprintf(stderr, "%s already exists as a page name.\n", str);
            val = 1;
            error = 1;
        }
        if (!error) {
            pageNode *new = malloc(sizeof(pageNode));
            if (!new) {
                fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
                exit(1);
            }
            temp->next = makePageNode(str);
        }
    }
    return val;
}

/*
* addLinks(pageNode, char[]) -- Adds the link to the head pageNode.
* Reads through the whole line and makes sure the input is valid.
* It also checks for any of the errors specified in the spec.
* Returns 1 if there is an error anywhere.
*/
int addLinks(pageNode *head, char *line) {
    int val = 0;
    char str[65];
    int count;
    if (sscanf(line, "%64s%n", str, &count) != 1) {
        fprintf(stderr, "No source page entered to addLinks commands.\n");
        return 1;
    }
    pageNode *source = getPageNode(head, str);
    if (!source) {
        fprintf(stderr, "Source page: %s not found in graph.\n", str);
        return 1;
    }
    line += count;
    while (sscanf(line, "%64s%n", str, &count) == 1) {
        pageNode *page = getPageNode(head, str);
        if (!page) {
            fprintf(stderr, "Linked page: %s, does not exist.\n", str);
            return 1;
        }
        else {
            linkNode *curr = source->linkNodeHead;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = makeLinkNode(page);
        }
        line += count;
    }
    return val;
}

/*
* isConnected(pageNode, char[]) -- Checks to make sure the input is valid.
* It then gets both the starting and ending pageNode to make sure they exist.
* It then marks the values as not Visited and runs the dfs. Prints out if they
* are connected or not. Returns 1 if there is an error anywhere.
*/
int isConnected(pageNode *head, char *line) {
    int val = 0;
    char first[65];
    char last[65];
    char test[65];
    if (sscanf(line, "%64s %64s %64s", first, last, test) != 2) {
        fprintf(stderr, "Incorrect usage of @isConnected command.\n");
        return 1;
    }
    pageNode *page1 = getPageNode(head, first);
    pageNode *page2 = getPageNode(head, last);
    if (!page1) {
        fprintf(stderr, "%s: page does not exist.\n", first);
        return 1;
    }
    if (!page2) {
        fprintf(stderr, "%s: page does not exist.\n", last);
        return 1;
    }
    markNotVisited(head);
    printf("%d\n", dfs(page1, page2));
    return val;
}

int main(int argc, char **argv)
{
    int val = 0;
    pageNode* head = NULL;
    head = (pageNode*)malloc(sizeof(pageNode));
    if (!head) {
        fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
        return 1;
    }
    // Initialized head to avoid memory errors
    head->next = NULL;
    head->name = strdup("first");
    head->linkNodeHead = makeLinkNode(head);

    FILE *file = stdin;
    if (argc == 2) {
        char *filename = argv[1];
        file = fopen(filename, "r");
        if (!file) {
            fprintf(stderr, "%s: No such file or directory\n", filename);
            return 1;
        }
    }
    if (argc > 2) {
        fprintf(stderr, "Too many command link arguments\n");
        val = 1;
    }

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, file) != EOF) {
        printf("\nline: %s\n", line);
        char str[65];
        int count;
        int num = sscanf(line, "%64s%n", str, &count);
        line += count;
        if (num > 0) {
            if (strcmp(str, "@addPages") == 0) {
                val = addPages(head, line);
            }
            else if (strcmp(str, "@addLinks") == 0) {
                val = addLinks(head, line);
            }
            else if (strcmp(str, "@isConnected") == 0) {
                val = isConnected(head, line);
            }
            else {
                fprintf(stderr, ": Invalid command.\n");
                val = 1;
            }
        }
        line = NULL;
        size = 0;
    }

    fclose(file);

    return val;
}