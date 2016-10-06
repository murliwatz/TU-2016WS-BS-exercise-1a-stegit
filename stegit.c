#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *words[28] = {
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

int lookup_word(char *word) {
	int i = 0;
	for(; i < 28; i++) {
		if(strcmp(word, words[i]) == 0) break;
	}
	if(i >= 0 && i < 26) return i+97;
	if(i == 26) return '.';
	if(i == 27) return ' ';
	return -1;
}

int lookup_char(char c) {
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

void start_find_mode() {
	char c;
	char str[256];
	int i = 0;
	while((c = getchar()) != EOF && c != '\n') {
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	for(int j = 0; j < i; j++) {
		int x = lookup_char(str[j]);
		printf("%s ", words[x]);
	}
}

void start_hide_mode() {
	char c;
	char str[256];
	int i = 0;
        while((c = getchar()) != EOF && c != ' ') {
                str[i] = c;
                i++;
        }
	str[i] = '\0';
	c = lookup_word(str);
	printf("%c\n", c);
}

void print_usage() {
	fprintf(stderr, "Usage: stegit -f|-h [-o outputfile]\n");
}

int main(int argc, char** argv) {
	int opt;

	if(argc == 1) {
		print_usage();
		return EXIT_FAILURE;
	}
	while((opt = getopt(argc, argv, "fho")) != -1) {
		switch(opt) {
			case 'f':
				start_find_mode();
				break;
			case 'h':
				start_hide_mode();
				break;
			default:
				print_usage();
				return EXIT_FAILURE;				
		}
	}
	return EXIT_SUCCESS;	
}
