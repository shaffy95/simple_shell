#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
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
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* toem_parse.c */
int is_command_executable(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_executable_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_shellErrors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_source.c */
int _string_length(char *);
int _string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *_string_concatenate(char *, char *);

/* toem_string.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

/* toem_operations.c */
char *copyLimitedString(char *, char *, int);
char *concatenateLimitedStrings(char *, char *, int);
char *findCharacterInString(char *, char);

/* toem_string1.c */
char **split_string(char *, char *);
char **strtow2(char *, char);

/* toem_pointer.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_mem.c */
int free_and_null_pointer(void **);

/* toem_helper.c */
int shell_is_active(info_t *);
int char_is_delim(char, const char *);
int char_is_alpha(int);
int string_to_integer(char *);

/* toem_shellErrors1.c */
int erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_func.c */
int exitShell(info_t *);
int changeCurrentDirectory(info_t *);
int showHelp(info_t *);

/* toem_util.c */
int display_history(info_t *);
int unset_alias(info_t char *);
int set_alias(info_t *, char *);
int print_alias_string(list_t *);
int alias_command(info_t *);
ssize_t input_buffer(info_t *, char **, size_t *);

/*toem_buffer.c */
ssize_t read_buffer(info_t *, char *, size_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(_attribute_((unused))int sig_num);

/* toem_input.c */
void initialize_info(info_t *);
void configure_info(info_t *, char **);
void release_info(info_t *, int);

/* toem_cmd.c */
char *getenv(info_t *, const char *);
int print_environment(info_t *);
int setenv(info_t *);
int unsetenv(info_t *);
int populate_environment_list(info_t *);

/* toem_env.c */
char **get_environ(info_t *);
int unsetenv(info_t *, char *);
int setenv(info_t *, char *, char *);

/* toem_hist.c */
char *get_history_file(info_t *info);
int create_or_append_history(info_t *info);
int read_history(info_t *info);
int add_history_entry(info_t *info, char *buf, int linecount);
int update_history(info_t *info);

/* toem_node.c */
list_t *insert_snode(list_t **, const char *, int);
list_t *insert_enode(list_t **, const char *, int);
size_t print_dlist(const list_t *);
int remove_si_node(list_t **, unsigned int);
void free_linked_list(list_t **);

/* toem_node1.c */
size_t list_length(const list_t *);
char **list_to_array(list_t *);
size_t print_linked_list(const list_t *);
list_t *find_pnode(list_t *, char *, char);
ssize_t get_inode(list_t *, list_t *);

/* toem_replace.c */
int chain_delimeter(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
