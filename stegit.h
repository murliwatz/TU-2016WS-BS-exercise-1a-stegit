#ifndef STEGIT_H_
#define STEGIT_H_

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

// program mode
enum {
	FIND_MODE,
	HIDE_MODE
} mode;

int output = 0; // for output file generation (0 = no file, 1 = create file)
char ofile[128]; // name of output file

int lookup_char(char c);
int lookup_word(char* word);

void start_find_mode(FILE* fd);
void start_hide_mode(FILE* fd);

#endif