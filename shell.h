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

int main(int argc, char **argv);
int main_shell_loop(shell_t *shell, char **argv);
int get_built_in_command(shell_t *shell);
void find_command(shell_t *shell);
void run_command(shell_t *shell);
int is_command(shell_t *shell, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(shell_t *shell, char *pathstr, char *cmd);
void write_string_char_by_char(char *str);
int write_char(char ch);
int write_char_to_buffer(char ch, int fileDescriptor);
int write_string_to_buffer(char *str, int fileDescriptor);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char *str_cpy_specific_char(char *dest, char *str, int n);
char *str_cat_specific_char(char *dest, char *str, int n);
char *_strchr(char *s, char c);
char **str_to_words(char *str, char *d);
char *_memset(char *s, char b, unsigned int n);
void free_str(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int free_ptr(void **ptr);
int interactive(shell_t *shell);
int is_delim(char c, char *delim);
int _erratoi(char *s);
void print_error(shell_t *shell, char *estr);
int print_base_10(int input, int fileDescriptor);
char *convert_num(long int num, int base, int flags);
void rm_comments(char *buf);
int use_exit(shell_t *shell);
int _cd(shell_t *shell);
int _help(shell_t *shell);
int print_history(shell_t *shell);
int _alias(shell_t *shell);
int get_line(shell_t *shell, char **ptr, size_t *length);
void siginal(__attribute__((unused))int sig_num);
void reset_shell(shell_t *shell);
void init_shell(shell_t *shell, char **argv);
void free_shell(shell_t *shell, int all);
char *get_env(shell_t *shell, const char *name);
int print_env(shell_t *shell);
int create_env_list(shell_t *shell);
char **get_environ(shell_t *shell);
char *get_history(shell_t *shell);
int write_history(shell_t *shell);
int read_history(shell_t *shell);
int build_history_list(shell_t *shell, char *buf, int linecount);
int renumber_history(shell_t *shell);
list_t *add_node(list_t **head, const char *str, int num);
int delete_node(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_index_node(list_t *head, list_t *node);
int is_chain(shell_t *shell, char *buf, size_t *p);
void check_chain(shell_t *shell, char *buf, size_t *p, size_t i, size_t len);
int replace_node_alias(shell_t *shell);
int replace_shell_vars(shell_t *shell);
int replace_string_shell_vars(char **old, char *new);
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
