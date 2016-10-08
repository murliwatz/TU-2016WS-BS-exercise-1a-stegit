/**
 * @brief main c file for the implementation of stegit
 * @author Paul Pröll, 1525669
 * @date 2016-10-08
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "stegit.h"

static const char *WORDS[28] = {
		"das", // a
		"Gut", // b
		"ist", // c
		"und", // d
		"ich", // e
		"finde", // f
		"gehe", // g
		"heute", // h
		"toll", // i
		"genial", // j
		"man", // k
		"denke", // l
		"richtig", // m
		"nett", // n
		"satt", // o
		"der", // p
		"Qualle", // q
		"cool", // r
		"Himmel", // s
		"klar", // t
		"unten", // u
		"Vogel", // v
		"will", // w
		"rein", // x
		"gehen", // y
		"Zweck", // z
		"la", // .
		"freundlich" // <space> 
};

// program mode
static enum {
	FIND_MODE,
	HIDE_MODE
} mode;

static char* progname;

static int output = 0; // for output file (0 = no file, 1 = create file)
static char ofile[128]; // name of output file
static FILE* fd; // file descriptor of output file


/* === Implementations === */

int main(int argc, char** argv) {

	parse_args(argc, argv);

	// if output file should be created, set file descriptor to file
	// otherwise the text will be printed to the standard output
	if(output == 1) {
		fd = fopen(ofile, "w");
	} else {
		fd = stdout;
	}
	if(mode == FIND_MODE) {
		(void) start_find_mode(fd);
	} else if (mode == HIDE_MODE) {
		(void) start_hide_mode(fd);
	}
	exit(EXIT_SUCCESS);	
}

static int lookup_word(char *word) {
	int i = 0;
	for(; i < 28; i++) {
		if(strcmp(word, WORDS[i]) == 0) break;
	}
	switch(i) {
		case 26:
			return '.';
		case 27:
			return ' ';
		default:
			if(i >= 0 && i < 26) {
				return i + 97;
			} else {
				return -1;
			}
	}
}

static int lookup_char(char c) {
	switch(c) {
		case '.':
			return 26;
		case ' ':
			return 27;
		default:
			if(c > 96 && c < 96 + 26) {
				return c-97;
			} else {
				return -1;
			}
	}
}

static void start_hide_mode(FILE* fd) {
	char c;
	int found = 0;
	char str[MAX_INPUT_LENGTH];
	// read until end of file or enter is pressed
	int i = 0;
	while((c = getchar()) != EOF && c != '\n') {
		str[i] = c;
		i++;
	}
	str[i] = '\0';

	// looking up characters
	for(int j = 0; j < i; j++) {
		if((found = lookup_char(str[j])) != -1) {
			(void) fprintf(fd, "%s", WORDS[found]);
		} else {
			(void) print_lookup_error();
		}
		// if not the last word, print <space>
		if(j < i-1) fprintf(fd, " "); 
	}
}

static void start_find_mode(FILE* fd) {
	char c;
	char str[MAX_WORD_LENGTH];
	int found = 0;
	do {
		// building a word
		int i = 0;
        while((c = getchar()) != EOF && c != ' ') {
        	str[i] = c;
        	i++;
        }
		str[i] = '\0';

		// looking up word
		if((found = lookup_word(str)) != -1) {
			(void) fprintf(fd, "%c", (char)found);
		} else {
			(void) print_lookup_error();
		}
	} while(c == ' ' && c != EOF);
}

static void print_usage(void) {
	(void) fprintf(stderr, "%s: Usage: stegit -f|-h [-o outputfile]\n", progname);
	(void) free_resources();
	exit(EXIT_FAILURE);	
}

static void print_lookup_error(void) {
	(void) fprintf(stderr, "%s: Error during looking up\n", progname);
	(void) free_resources();
	exit(EXIT_FAILURE);	
}

static void parse_args(int argc, char** argv) {
	int opt;

	if(argc > 0) {
		progname = argv[0];
	}
	if(argc != 2 && argc != 4) {
		(void) print_usage();
	}
	while((opt = getopt(argc, argv, "fho:")) != -1) {
		switch(opt) {
			case 'f':
				mode = FIND_MODE;
				break;
			case 'h':
				mode = HIDE_MODE;
				break;
			case 'o':
				output = 1;
				strcpy(ofile,optarg);
				break;
			default:
				(void) print_usage();		
		}
	}
}

static void free_resources(void) {
	if(fd != NULL) {
		(void) fclose(fd);
	}
}
