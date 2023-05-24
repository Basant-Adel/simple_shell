#ifndef SHELL_H
#define SHELL_H

/* The C Standard Library */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

/* The C Macro Definition Documentation */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#define shell_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL,\
	NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

#define NOT_FOUND 127
#define PERMISSION_DENIED 126
extern char **environ;

/* Typedefs  */

/**
 * struct liststr - singly linked list
 *@num: the number field
 *@str: a string
 *@next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passshell - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@fileDescriptor: the fileDescriptor from which to read line input
 *@histcount: the history line number count
 */

typedef struct passshell
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int fileDescriptor;
	int histcount;
} shell_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(shell_t *);
} built_in_table;

/* Prototypes  */

int main_shell_loop(shell_t *, char **);
int get_built_in_command(shell_t *);
void find_command(shell_t *);
void run_command(shell_t *shell);
int is_command(shell_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(shell_t *, char *, char *);
void write_string_char_by_char(char *);
int write_char(char);
int write_char_to_buffer(char c, int fileDescriptor);
int write_string_to_buffer(char *str, int fileDescriptor);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *str_cpy_specific_char(char *, char *, int);
char *str_cat_specific_char(char *, char *, int);
char *_strchr(char *, char);
char **str_to_words(char *, char *);
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_ptr(void **);
int interactive(shell_t *);
int is_delim(char, char *);
int _erratoi(char *);
void print_error(shell_t *, char *);
int print_base_10(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);
int use_exit(shell_t *);
int _cd(shell_t *shell);
int _help(shell_t *);
int print_history(shell_t *);
int _alias(shell_t *);
int get_line(shell_t *shell, char **ptr, size_t *length);
void siginal(int);
void reset_shell(shell_t *);
void init_shell(shell_t *, char **);
void free_shell(shell_t *, int);
char *get_env(shell_t *, const char *);
int print_env(shell_t *);
int _setenv(shell_t *);
int _unsetenv(shell_t *);
int create_env_list(shell_t *);
char **get_environ(shell_t *);
int unset_env(shell_t *, char *);
int set_env(shell_t *, char *, char *);
char *get_history(shell_t *shell);
int write_history(shell_t *shell);
int read_history(shell_t *shell);
int build_history_list(shell_t *shell, char *buf, int linecount);
int renumber_history(shell_t *shell);
list_t *add_node(list_t **, const char *, int);
int delete_node(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);
int is_chain(shell_t *, char *, size_t *);
void check_chain(shell_t *, char *, size_t *, size_t, size_t);
int replace_node_alias(shell_t *);
int replace_shell_vars(shell_t *);
int replace_string_shell_vars(char **, char *);
void printCanNotOpen(char *programName, char *fileName);
int print_node_alias(list_t *node);
int add_update_node_alias(shell_t *shell, char *str);
int delete_node_alias(shell_t *shell, char *str);
int _setenv(shell_t *shell);
int _unsetenv(shell_t *shell);
int set_env(shell_t *shell, char *var, char *value);
int unset_env(shell_t *shell, char *var);
ssize_t input_buffer(shell_t *shell, char **buf, size_t *len);
ssize_t get_input(shell_t *shell);
ssize_t read_buf(shell_t *shell, char *buf, size_t *i);

#endif
