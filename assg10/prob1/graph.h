/*
* File: graph.h
* Author: Merle Crutchfield
* Purpose: This is the header file for the graph.c file. It defines the
* three nodes that I use for this assignment, and has all of the methods
* available in it.
*/
#ifndef _GRAPH_H
#define _GRAPH_H
#include <sys/stat.h>

/*
* targetNode definition
*/
typedef struct targetNode {
	int build;
	int exist;
	time_t sec;
	time_t nano;
	int target;
	int visited;
	char *name;
	struct dependencyNode *dHead;
	struct commandNode *cHead;
	struct targetNode *next;
} targetNode;

/*
* dependencyNode definition
*/
typedef struct dependencyNode {
	targetNode *tcurr;
	struct dependencyNode *next;
} dependencyNode;

/*
* commandNode definition
*/
typedef struct commandNode {
	char *command;
	struct commandNode *next;
} commandNode;

targetNode *makeTargetNode(char *target);
dependencyNode *makeDependencyNode(targetNode *target);
commandNode *makeCommandNode(char *command);
targetNode *getTargetNode(char *name);
targetNode *addTargetNode(char *target);
void addDependencyNode(targetNode *target, char *name);
void addCommandNode(targetNode *target, char *command);
void postOrder(targetNode *target);
void freeInside(targetNode *target);
void freeFile();
void commandPrint(targetNode *target);

extern targetNode *targetNodeHead;

#endif