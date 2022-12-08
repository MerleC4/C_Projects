#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
/*
* File: graph.c
* Author: Merle Crutchfield
* Purpose: This is used to create the graph for the three nodes that
* I created. It will make sure that they are made correctly and that
* there is no memory errors either. It has a header file that contains
* the structs for the nodes, and writes out the methods algorithms in
* this file.
*/

targetNode *targetNodeHead = NULL;

/*
* makeTargetNode(char) -- Makes a targetNode, making sure that there are no
* memory errors ever. Initializes all values to either 0 or NULL and returns
* the targetNode.
*/
targetNode *makeTargetNode(char *target) {
	targetNode *curr = malloc(sizeof(targetNode));
	if (!curr) {
		fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
		freeFile();
        exit(1);
	}
	curr->name = strdup(target);
	if (!curr->name) {
		fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
		freeFile();
        exit(1);
	}
	curr->visited = 0;
	curr->target = 0;
	curr->dHead = NULL;
	curr->cHead = NULL;
	curr->next = NULL;
	return curr;
}

/*
* makeDependencyNode(targetNode) -- Makes a dependencyNode, making sure that there 
* are no memory errors ever. Initializes all values to the target or NULL and returns
* the dependencyNode.
*/
dependencyNode *makeDependencyNode(targetNode *target) {
	dependencyNode *curr = malloc(sizeof(dependencyNode));
	if (!curr) {
		fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
		freeFile();
        exit(1);
	}
	curr->tcurr = target;
	curr->next = NULL;
	return curr;
}

/*
* makeCommandNode(char) -- Makes a commandNode, making sure that there 
* are no memory errors ever. Initializes the command to the command that
* was passed and then returns the commandNode.
*/
commandNode *makeCommandNode(char *command) {
	commandNode *curr = malloc(sizeof(commandNode));
	if (!curr) {
		fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
		freeFile();
        exit(1);
	}
	curr->command = strdup(command);
	if (!curr->command) {
		fprintf(stderr, "Memory Error: requesting more memory than is free.\n");
		freeFile();
        exit(1);
	}
	curr->next = NULL;
	return curr;
}

/*
* getTargetNode(char) -- Finds the targetNode inside of the main targetNode
* pointer and returns it.
*/
targetNode *getTargetNode(char *name) {
	targetNode *curr = targetNodeHead;
	while (curr) {
		if (strcmp(curr->name, name) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return curr;
}

/*
* addTargetNode(char) -- Adds a new targetNode to the targetNode pointer
* by checking to make sure that it doesn't already exist in it. It then
* iterates through until the end and then adds it before returning it.
*/
targetNode *addTargetNode(char *target) {
	targetNode *temp = getTargetNode(target);
	if (temp) {
		return temp;
	}
	temp = makeTargetNode(target);
	targetNode *curr = targetNodeHead;
	while (curr->next) {
		curr = curr->next;
	}
	curr->next = temp;
	return temp;
}

/*
* addDependencyNode(targetNode, char) -- Adds a dependencyNode to the targetNode
* that was passed. It iterates through and checks to see if it already exists which
* is not allowed. If it reaches the end, it adds it.
*/
void addDependencyNode(targetNode *target, char *name) {
	targetNode *temp = addTargetNode(name);
	dependencyNode *curr = target->dHead;
	if (!curr) {
		target->dHead = makeDependencyNode(temp);
		return;
	}
	while (curr->next) {
		if (curr->tcurr == temp) {
			fprintf(stderr, "Error: %s already has dependency %s\n", target->name, temp->name);
			freeFile();
			exit(1);
		}
		curr = curr->next;
	}
	if (curr->tcurr == temp) {
		fprintf(stderr, "Error: %s already has dependency %s\n", target->name, temp->name);
		freeFile();
		exit(1);
	}
	curr->next = makeDependencyNode(temp);
}

/*
* addCommandNode(targetNode, char) -- Adds a commandNode to the head targetNode.
* It checks to make sure that it does not already exist and then iterates through
* until the end where it adds it.
*/
void addCommandNode(targetNode *target, char *command) {
	commandNode *curr = target->cHead;
	if (!curr) {
		target->cHead = makeCommandNode(command);
		return;
	}
	while (curr->next) {
		curr = curr->next;
	}
	curr->next = makeCommandNode(command);
}

/*
* postOrder(targetNode) -- This is used to do the post order traversal as
* defined in the spec. It follows the algorithm of checking to make sure
* that the visited values haven't been reached and then uses recursion to
* print out the correct order.
*/
void postOrder(targetNode *target) {
	if (target->visited == 1) {
		return;
	}
	target->visited = 1;
	dependencyNode *curr = target->dHead;
	while (curr) {
		postOrder(curr->tcurr);
		curr = curr->next;
	}
	printf("%s\n", target->name);
	commandNode *temp = target->cHead;
	while (temp) {
		printf("  %s\n", temp->command);
		temp = temp->next;
	}
}

/*
* freeInside(targetNode) -- This frees the inside values in the targetNode
* passed, which are the dependencyNodes and the commandNodes. It also makes
* sure to free the name string.
*/
void freeInside(targetNode *target) {
	dependencyNode *curr = target->dHead;
	while (curr) {
		dependencyNode *temp = curr->next;
		free(curr);
		curr = temp;
	}
	commandNode *curr2 = target->cHead;
	while (curr2) {
		commandNode *temp = curr2->next;
		free(curr2->command);
		free(curr2);
		curr2 = temp;
	}
	free(target->name);
}

/*
* freeFile() -- This frees the head targetNode and uses the freeInside() method
* to free the inside nodes in each targetNode.
*/
void freeFile() {
	targetNode *curr = targetNodeHead;
	while (curr) {
		targetNode *temp = curr->next;
		freeInside(curr);
		free(curr);
		curr = temp;
	}
}