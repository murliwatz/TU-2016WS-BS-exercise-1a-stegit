/**
 * @brief main c file for the implementation of stegit
 * @author Paul Pröll, 1525669
 * @date 2016-10-08
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
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
				return c - 97;
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
			bail_out(EXIT_FAILURE, "Error during looking up\n");
		}
		// if not the last word, print <space>
		if(j < i-1) {
			(void) fprintf(fd, " "); 
		} 
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
			bail_out(EXIT_FAILURE, "Error during looking up\n");
		}
	} while(c == ' ' && c != EOF);
}

static void bail_out(int exitcode, const char *fmt, ...)
{
    va_list ap;

    (void) fprintf(stderr, "%s: ", progname);
    if (fmt != NULL) {
        va_start(ap, fmt);
        (void) vfprintf(stderr, fmt, ap);
        va_end(ap);
    }
    if (errno != 0) {
        (void) fprintf(stderr, ": %s", strerror(errno));
    }
    (void) fprintf(stderr, "\n");

    free_resources();
    exit(exitcode);
}

static void parse_args(int argc, char** argv) {
	int opt;

	if(argc > 0) {
		progname = argv[0];
	}
	if(argc != 2 && argc != 4) {
		bail_out(EXIT_FAILURE, "Usage: stegit -f|-h [-o outputfile]\n");
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
				bail_out(EXIT_FAILURE, "Usage: stegit -f|-h [-o outputfile]\n");		
		}
	}
}

static void free_resources(void) {
	if(fd != NULL) {
		(void) fclose(fd);
	}
}
