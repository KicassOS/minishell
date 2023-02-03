/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <iazimzha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:05:11 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 19:21:00 by iazimzha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/inc/libft.h"

# define MALLOC_ERROR 5
# define CHDIR_ERROR 6
# define PWD_ERROR 7

# define OPERATOR "|<>"
# define NOTDEFINED 127
# define SYNTAX 2
# define PIPE 127
# define SMALLER '\x1d'
# define BIGGER '\x1c'
# define SHELL "minishell"
# define PROMPT "minish$ "
# define HEREPROMPT "heredoc> "

typedef enum e_enum
{
	WRITE = 1,
	READ = 0,
	RWRR = 0644,
	ERROR = -1,
}	t_enum;

// OUT: >
// IN: <
// APPEND: >>
// HERE: <<
typedef enum e_operator
{
	OUT = 2,
	IN = 3,
	APPEND = 4,
	HERE = 5,
}	t_operator;

typedef struct s_index
{
	int			i;
	int			pos;
}	t_index;

/*
  This struct represents a redirection
  operator is >, < or <<
  file is what's after the operator
  herepipe is used for the heredoc
  next points to the next redirection operator found
*/
typedef struct s_re
{
	int			operator;
	char		*file;
	int			herepipe[2];
	struct s_re	*next;
}	t_re;

/*
  This struct represents a parsed command
  Path is the path to the executable
  args is an array of arguments
  hasheredoc is true if a heredoc is present in the prompt, false otherwise
  isbuiltin is true if the command being executed is a builtin (env, export...)
  re is the redirection operator linked list, for all the I/O redirections 
  inside the command
  pid is the pid of the child process
  fd is the pipe used to communicate between this command and the next one
  fd[0] is in, fd[1] is out
*/
typedef struct s_cmd
{
	char	*path;
	char	**args;
	bool	hasheredoc;
	bool	isbuiltin;
	t_re	*re;
	int		pid;
	int		fd[2];
}	t_cmd;

/*
  This is the main structure of the program, it handles the safe freeing of all
  allocated resources
  lastexitstatus is the exit status of the command or pipe chain of commands
  that was last executed
  hasheredoc is true if the full prompt has a heredoc, this is used to check
  if the prompt should be added to the shell's history
  env is a linked list that represents the shell's environment
  commands is also a linked list of parsed commands
  mypipe and tmp_fd are 2 pipes used in the project
  all the booleans say whether or not a specific block of memory was allocated
  input is the prompt returned by the readline function
*/
typedef struct s_data
{
	int				lastexitstatus;
	bool			hasheredoc;
	struct s_slist	*env;
	struct s_slist	*commands;
	int				i;
	int				mypipe[2];
	int				tmp_fd[2];
	bool			env_allocated;
	bool			history_allocated;
	bool			input_allocated;
	char			*input;
}	t_data;

void	ft_del(void *content);
int		ft_strindexrev(const char *str, int c);
int		ft_strindex(const char *str, int c);
void	ft_delre(char *file);
void	ft_relstdelone(t_re *re, void (*del)(void *));
void	ft_relstclear(t_re **re, void (*del)(void *));
t_re	*ft_relstnew(int operator, char *file);
void	ft_relstadd_back(t_re **re, t_re *new);

char	**ft_tokenizer(char *str, t_data *data);
void	tokenize(char *str, t_data *data, t_slist **tokens);
int		ft_clean_tokens(t_slist **tokens, t_data *data);

int		ft_expander(char **token, t_data *data);
void	ft_determine_expansion_type(char **token, t_index *index,
			t_slist **parts, t_data *data);
int		ft_expand_var(char **str, int start, t_slist **list, t_slist **myenv);
void	ft_create_part_list(char **token, t_index *index,
			t_slist **parts, t_data *data);
bool	ft_is_valid_char(const char c);

void	ft_quoteremover(char **command);

t_slist	*ft_parser(char **command, t_data *data);
int		ft_sort_cmd(char **command, t_cmd *simplecmd, int y, t_data *data);
void	builtinflag(t_cmd *simplecmd);
void	ft_cmdargs(char **command, t_cmd *simplecmd, int *x, int *y);
void	ft_pathcmd(t_cmd *simplecmd, char **command, int *x, int *y);
void	ft_args(t_cmd *simplecmd, char **command, int *x, int *y);
void	ft_fillargs(t_cmd *simplecmd, char **command, int *x, int *y);
bool	ft_isredirection(char **command, int *y);
int		ft_distinguish(char **command, int *y, t_cmd *simplecmd, t_data *data);
void	ft_syntaxerr(t_data *data);
bool	ft_syntaxcheck(t_data *data);
bool	ft_emptystruct(t_slist *cmdtable, t_data *data);
void	ft_freepipecount(char **command, char **newcmd, t_slist	*cmdtable);
int		ft_splithelper(char **newstr, t_slist **cmdtable, t_data *data);

void	ft_execute(t_data *data);
void	ft_get_heredoc_input(t_data *data);
int		ft_execute_builtin(t_slist *cmdlist, t_data *data);
int		ft_child_redirect_std_fds(t_cmd *cmd, t_data *data, int *flag);
void	ft_childprocess(t_slist *cmdptr, t_data *data, int *flag);
char	*ft_child_search_myenv(t_slist **my_env, char *var);
int		ft_child_piping(t_slist *cmdlist, t_data *data, int *f);

void	ft_exit_errno(t_data *data);
void	ft_free_data_struct_content(t_data *data);
void	freedchar(char ***dchar);
void	ft_free_commandlist(t_slist **commands);
void	parser_freedchar(char ***dchar, int count);

void	ft_exit_expander(t_slist **slist, char **token, t_slist **my_env);
int		ft_exit_tokenizer(t_data *data, t_slist **tokens);

int		ft_cd(t_slist **my_env, char **args);
char	*ft_get_env_variable_value(t_slist **my_env, char *needle);
char	*ft_getcwd(void);
char	*ft_tilde_to_home(t_slist **my_env, char *path);
void	ft_free_args(char **args);
int		ft_count_subarrays(char **args);
void	ft_free(void **p);
t_slist	*ft_modify_env_var_value(t_slist **my_env, char *name, char *value);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_malloc(size_t num_bytes);
char	*ft_extract_variable_value(char *content);
char	*ft_extract_variable_name(char *content);
int		ft_indexof_last_occurence(char *s, char c);
t_slist	*ft_find_env_variable(t_slist **env, char *to_find);
t_slist	*ft_find_env_variable_by_name(t_slist **env, char *name_tofind);
t_slist	*ft_env_new_node(void *content);
char	*ft_create_env_varstring(char *name, char *value);
t_slist	*ft_overwrite_env_var_value(t_slist **my_env,
			char *oldval, char *newval);
char	*ft_extract_variable_name(char *content);
void	ft_env2(t_slist **my_env);
int		ft_pwd(char **args);
int		ft_unset(t_slist **my_env, char **args);
void	ft_delete_env_node(t_slist **env, char *needle);
int		ft_env(t_slist **env, bool export);
int		ft_export(t_slist **my_env, char **args);
int		ft_echo(char **args);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_builtin_exit(t_data *data);
int		ft_exit(t_data *data, char **args);
void	ft_cleanup(t_data *data);
void	ft_setup_signal(void);
bool	ft_only_spacetabs(char *input);
void	ft_setup_data(t_data *data);
char	*ft_extract_variable_name_export(char *content);
char	*ft_sanitize_var_name(char *str);
#endif
