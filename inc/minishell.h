/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iazimzha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:05:11 by iazimzha          #+#    #+#             */
/*   Updated: 2023/02/03 17:04:41 by iazimzha         ###   ########.fr       */
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
# define READLINE_ERROR 8
# define ENV_ERROR 24

//CHARSETS
# define METACHAR " \t\n|<>"
# define BLANK " \t\n"
# define OPERATOR "|<>"

//VALUES
# define NOTDEFINED 127
# define SYNTAX 2
# define LINUX_C 130
# define PIPE 127
# define SMALLER '\x1d'
# define BIGGER '\x1c'

//SHELLNAME
# define SHELL "minishell"

//PROMPTS
# define PROMPT "minishell$ "
# define HEREPROMPT "heredoc > "

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

// operator: redirectionoperator
// filename resp. HERELIMITER
typedef struct s_re
{
	int			operator;
	char		*file;
	int			herepipe[2];
	struct s_re	*next;
}	t_re;

// path: command(name) / relative path to command / absolute path to command
// args: args[0] is the command(name)
// fd[0] in fd[1] out
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

//printfunctions:
void	ft_print_slist(t_slist *tokenlst);
void	ft_printcharcmd(char **command);
void	ft_printsimplenode(t_cmd *simplecmd);
void	ft_printsimplecmd(t_slist *cmdtable);

//utils
void	ft_del(void *content);
int		ft_strindexrev(const char *str, int c);
int		ft_strindex(const char *str, int c);
void	ft_addto_lst(t_slist **lst, char *str);
void	ft_delre(char *file);
void	ft_relstdelone(t_re *re, void (*del)(void *));
void	ft_relstclear(t_re **re, void (*del)(void *));
t_re	*ft_relstnew(int operator, char *file);

int		ft_relstsize(t_re *re);
void	ft_relstadd_back(t_re **re, t_re *new);
void	ft_addto_re(t_re **re, int operator, char *file);

//1_errorhandle:
char	**ft_errorstr(t_data *data, char **finalcmd);
int		ft_errorint(t_data *data);
bool	ft_triple_re(t_slist *tokenlst, t_data *data);
//t_slist	*ft_errortoken(char *s, t_slist **tokenlst);
bool	ft_nonsense(char **command);
char	*ft_quoteerror(t_data *data);

//1_tokenizer:
char	**ft_tokenizer(char *str, t_data *data);
void	tokenize(char *str, t_data *data, t_slist **tokens);
int		ft_clean_tokens(t_slist **tokens, t_data *data);

//2_expander
int		ft_expander(char **token, t_data *data);
void	ft_determine_expansion_type(char **token, t_index *index,
			t_slist **parts, t_data *data);
int		ft_expand_var(char **str, int start, t_slist **list, t_slist **myenv);
void	ft_create_part_list(char **token, t_index *index,
			t_slist **parts, t_data *data);
bool	ft_is_valid_char(const char c);

//3_quote removal:
void	ft_quoteremover(char **command);

//4_parser:
t_slist	*ft_parser(char **command, t_data *data);
int		ft_initsimple(t_cmd *simplecmd, char **command, t_data *data);
int		ft_sort_cmd(char **command, t_cmd *simplecmd, int y, t_data *data);
bool	ft_checkbuiltin(char *commandpart);
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
int		ft_sortcmdret(char **command, t_cmd *simplecmd, t_data *data);

//5_executor
void	ft_execute(t_data *data);
void	ft_get_heredoc_input(t_data *data);
int		ft_execute_builtin(t_slist *cmdlist, t_data *data);
int		ft_child_redirect_std_fds(t_cmd *cmd, t_data *data, int *flag);
void	ft_childprocess(t_slist *cmdptr, t_data *data, int *flag);
char	*ft_child_search_myenv(t_slist **my_env, char *var);
int		ft_child_piping(t_slist *cmdlist, t_data *data, int *f);

//6_exit
void	ft_exit(t_data *data);
void	ft_exit_errno(t_data *data);
void	ft_free_data_struct_content(t_data *data);
void	freedchar(char ***dchar);
void	ft_free_commandlist(t_slist **commands);
void	parser_freedchar(char ***dchar, int count);

//7_signals
void	ft_sigfunc_here_doc(int sig);
void	ctrlc(struct termios *termi, int flag);
void	sighandler(int sig);

//builtins
int		builtin_echo(char **args);
//int		builtin_cd(char ***myenv, char **args);
int		builtin_pwd(void);
int		builtin_export(char ***myenv, char **args);
int		builtin_unset(char **myenv, char **args);
int		builtin_env(char **myenv, bool export);
int		builtin_exit(t_data *data, char **args);
int		ft_get_myenv_index(char **myenv, char *var);
int		ft_exchange_envvar(int i, char **myenv, char *replacement);
void	ft_dlstdel(void *content);
int		ft_construct_dir(char **curpath, char *arg);

//errorcleanup
void	ft_exit_expander(t_slist **slist, char **token, t_slist **my_env);
int		ft_exit_tokenizer(t_data *data, t_slist **tokens);
char	*ft_error_dlst(t_dlist **dlist);
int		ft_builtin_errormessage(char *builtin, char *message);
int		ft_errormessage(char *message);

// Debugging
// # define PRINT_HERE()
// (printf("In file %s, at line: %d\n", __FILE__, __LINE__))
// void	ft_print_tokens(char **tokens, char *label);
// void	ft_print_tokenlist(t_slist	**tokens);
// void	ft_print_tokenarray(char **tokens);
// void	ft_print_data(t_data *data);

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
void	ft_cleanup(t_data *data);
void	ft_setup_signal(void);
bool	ft_only_spacetabs(char *input);
void	ft_setup_data(t_data *data);
char	*ft_extract_variable_name_export(char *content);
char	*ft_sanitize_var_name(char *str);
#endif
