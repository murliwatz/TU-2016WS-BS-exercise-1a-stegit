/**
 * @brief header file for the implementation of stegit
 * @author Paul Pröll, 1525669
 * @date 2016-10-08
*/

#ifndef STEGIT_H_
#define STEGIT_H_

/* === Constants === */

#define MAX_WORD_LENGTH (16)
#define MAX_INPUT_LENGTH (256)

/* === Prototypes === */

/**
 * @brief Looks up a character for hide mode
 * @param c The word that should be looked up
 * @return The index of words array; -1 if character not found
 */
static int lookup_char(char c);

/**
 * @brief Looks up a word that has to be in the words array
 * @param c The word that should be looked up
 * @return The associated index of the words array; -1 in case if word can't be found in the array
 */
static int lookup_word(char* word);

/**
 * @brief Starts the find mode procedere
 * @param fd File descriptor for the output
 */
static void start_find_mode(FILE* fd);

/**
 * @brief Starts the hide mode procedere
 * @param fd File descriptor for the output
 */
static void start_hide_mode(FILE* fd);

/**
 * @brief Prints synopsis on stderr
 */
static void print_usage(char* progname);

#endif