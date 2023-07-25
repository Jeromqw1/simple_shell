#ifndef _SHELL_H_
#define _SHELL_H_
<<<<<<< HEAD
=======

>>>>>>> 10405d716619d3bdec9d05646a670508d6e12b60
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
<<<<<<< HEAD

#endif
=======
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Read or Write buffer sizes */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH
#define READ_BUT_SIZE 1024
#define BUF_FLUSH_CHAR '\n'

/* Command chaining types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Converts numbers to options */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag indicating whetther a system getline() is used */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
* struct liststr - Singly linked list
* @num: The number field
* @str: A string
* @next: Points to the next node
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
* struct passinfo - Contains pseudo-arguments to pass into a function,
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getline containing arguments
* @argv: A string of strings generated from arg
* @path: A string path for the current command
* @argc: argument count
* @line_count: The error count
* @err_num: the error code for exit() calls
* @linecount_flag: If set, count this line of input
* @fname: The program filename
* @env: linked list local copy of environ
* @environ: Custom modified copy of the environ from LL env
* @history: The history node
* @alias: The alias node
* @env_changed: Set to 1 if environ was changed
* @status: The return status of the last executed command
* @cmd_buf: address of pointer to cmd_buf, set if chaning
* @cmd_buf_type:Type of command chaining (CMD_type ||, &&, ;)
* @readfd: the file descriptor from which to read line input
* @histcount: - The history line number count
* @current_dir: it can store up to 1024 characters
*/

typedef struct passinfo
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

	char current_dir[1024];
	char **cmd_buf;
	char cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
* struct builtin - Contains a built-in string and related function
* @type: The builtin command flag
* @func: The function
*/

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* These are functions prototypes */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int change_to_previous_directory(info_t *info, char *dir);
void update_directory_info(info_t *info, char *buffer);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void efree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int ufree(void **);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *conver_number(long int, int, int);
void remove_comments(char *);


int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int myunsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

int change_to_previous_directory(info_t *info, char *dir);
void update_directory_info(info_t *info, char *buffer);


#endif /* _SHELL_H_ */

>>>>>>> 10405d716619d3bdec9d05646a670508d6e12b60
