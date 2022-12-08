#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
/*
* File: myMake2.c
* Author: Merle Crutchfield
* Purpose: This is used as the main make file that is used to simulate a 
* MakeFile. It does this by taking in a MakeFile and a Target file which
* reads in targets and dependencies and then creates the graph, then uses
* the post order traversal to prints them out.
*/
extern targetNode *targetNodeHead;
int commandCount;
char *line;
FILE *file;

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
* readLine(file, char, char) -- It iterates through a file and makes sure
* that the command entered is valid. If it is, then it uses the line
* to create a targetNode which it returns.
*/
targetNode *readLine(FILE *file, char *line, char *targetName) {
	char *curr = line;
	char colon;
	char input[65];
	int val;
	if (sscanf(curr, "%64[^:]%[:]%n", input, &colon, &val) != 2 || colon != ':') {
		if (input[0] == '\t') {
			fprintf(stderr, "Error in file, command with no target\n");
		} else if (strlen(curr) == 0) {
			fprintf(stderr, "Target %s not found\n", targetName);
		} else {
			fprintf(stderr, "Illegal line: %s", input);
		}
		freeFile();
		exit(1);
	}
	curr += val;
	char *target = input;
	if (sscanf(input, "%s", target) != 1) {
		fprintf(stderr, "Target %s not found\n", targetName);
		freeFile();
		exit(1);
	}
	targetNode *node = addTargetNode(target);
	if (node->target == 1) {
		fprintf(stderr, "Repeated target: %s\n", input);
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
	char *fileName;
	char *targetName;
	if (argc == 1) {
		fileName = "myMakefile";
		targetName = NULL;
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "-f") == 0) {
			fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
			freeFile();
			return 1;
		}
		fileName = "myMakefile";
		targetName = argv[1];
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "-f") != 0 || strcmp(argv[2], "-f") == 0) {
			fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
			freeFile();
			return 1;
		}
		fileName = argv[2];
		targetName = NULL;
	}
	else if (argc == 4) {
		if (strcmp(argv[1], "-f") == 0) {
			if (strcmp(argv[2], "-f") == 0 || strcmp(argv[3], "-f") == 0) {
				fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
				freeFile();
				return 1;
			}
			fileName = argv[2];
			targetName = argv[3];
		}
		else if (strcmp(argv[2], "-f") == 0) {
			if (strcmp(argv[1], "-f") == 0 || strcmp(argv[3], "-f") == 0) {
				fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
				freeFile();
				return 1;
			}
			fileName = argv[3];
			targetName = argv[1];
		}
		else {
			fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
			freeFile();
			return 1;
		}
	}
	else {
		fprintf(stderr, "Usage: mymake2 [-f makefile] [target]\n");
		freeFile();
		return 1;
	}

	file = fopen(fileName, "r");
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
		fprintf(stderr, "Error in file, command with no target\n");
		freeFile();
		return 1;
	}

	targetNode *curr = readLine(file, line, targetName);

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
				curr = readLine(file, line, targetName);
			}
		}
	}

	if ((targetName == NULL) & (targetNodeHead->target == 0)) {
		targetName = targetNodeHead->next->name;
	}
	targetNode *node = getTargetNode(targetName);
	if (!node || node->target == 0) {
		fprintf(stderr, "%s not defined in the input file.\n", argv[2]);
		fclose(file);
		freeFile();
		return 1;
	}
	commandCount = 0;
	postOrder(node);
	if (commandCount == 0) {
		printf("%s is up to date.\n", node->name);
	}
	freeFile();

	return 0;
}