#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
/*
* File: myMake.c
* Author: Merle Crutchfield
* Purpose: This is used as the main make file that is used to simulate a 
* MakeFile. It does this by taking in a MakeFile and a Target file which
* reads in targets and dependencies and then creates the graph, then uses
* the post order traversal to prints them out.
*/
extern targetNode *targetNodeHead;

/*
* isEmpty(char) -- Checks to see if the line is empty. Returns 1 if
* yes and 0 if not.
*/
int isEmpty(char *line) {
	char *curr = line;
	while (*curr) {
		if (!isspace(*curr)) {
			return 0;
		}
		curr++;
	}
	return 1;
}

/*
* readLine(file, char) -- It iterates through a file and makes sure
* that the command entered is valid. If it is, then it uses the line
* to create a targetNode which it returns.
*/
targetNode *readLine(FILE *file, char *line) {
	char *curr = line;
	char colon;
	char input[65];
	int val;
	if (sscanf(curr, "%64[^:]%[:]%n", input, &colon, &val) != 2 || colon != ':') {
		fprintf(stderr, "Invalid input line: %s\n", input);
		fclose(file);
		free(line);
		freeFile();
		exit(1);
	}
	curr += val;
	char *target = input;
	if (sscanf(input, "%s", target) != 1) {
		fprintf(stderr, "Empty target specified.\n");
		fclose(file);
		free(line);
		freeFile();
		exit(1);
	}
	targetNode *node = addTargetNode(target);
	if (node->target == 1) {
		fprintf(stderr, "%s is already a target\n", input);
		fclose(file);
		free(line);
		freeFile();
		exit(1);
	}
	node->target = 1;
	while (sscanf(curr, "%64s%n", input, &val) == 1) {
		addDependencyNode(node, input);
		curr += val;
	}
	return node;
}

int main(int argc, char **argv) {
	FILE *file;
	char *line;
	if (argc != 3) {
		fprintf(stderr, "Incorrect arguments. Usage: mymake aMakeFile aTarget\n");
		freeFile();
		return 1;
	}
	
	file = fopen(argv[1], "r");
	if (!file) {
		fprintf(stderr, "%s: No such file or directory\n", argv[1]);
		freeFile();
		return 1;
	}

	targetNodeHead = makeTargetNode("head");
	line = NULL;
	size_t size = 0;
	ssize_t val = getline(&line, &size, file);
	while (val != EOF && isEmpty(line)) {
		val = getline(&line, &size, file);
	}

	if (line[0] == '\t') {
		fprintf(stderr, "First line must be a target.\n");
		fclose(file);
		free(line);
		freeFile();
		return 1;
	}

	targetNode *curr = readLine(file, line);

	while ((val = getline(&line, &size, file)) != EOF) {
		if (!isEmpty(line)) {
			if (line[0] == '\t') {
				char *command = line;
				while (isspace(*command)) {
					command++;
				}
				if (!(*command == '\0')) {
					char *commandTail = line + strlen(line) - 1;
					while (isspace(*commandTail)) {
						*commandTail = '\0';
						commandTail--;
					}
					addCommandNode(curr, command);
				}
			}
			else {
				curr = readLine(file, line);
			}
		}
	}
	free(line);

	targetNode *node = getTargetNode(argv[2]);
	if (!node || node->target == 0) {
		fprintf(stderr, "%s not defined in the input file.\n", argv[2]);
		fclose(file);
		freeFile();
		return 1;
	}
	postOrder(node);
	fclose(file);
	freeFile();

	return 0;
}