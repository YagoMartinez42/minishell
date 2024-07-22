/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:36:10 by dlanzas-          #+#    #+#             */
/*   Updated: 2024/07/22 16:34:07 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "ms_types.h"

// Replace_line needed proto just because
void			rl_replace_line(const char *text, int clear_undo);

// Main
void			startup(char **env);
void			listen(int in, int out);
void			s_handler(int sig);
t_minishell		ms_wideuse_values(void *setting, int wvar);

// Error management
int				check_line(char *line);
void			error_exit(int num_error);
void			error_prompt(int num_error);
void			free_list(t_list *list);

// Parsings
int				check_dollar(char *str, int position);
int				find_pipe(char *str);
t_q_status		eval_quotes_state(char c, t_q_status quotes);
t_token_type	check_redir_type(t_token_type t_type, char redir);
int				is_whitespace(char c);
size_t			skip_whitespace(char *str);
int				str_is_num(char *str);
int				is_redir(char *str);
t_list			*tokenize_whole(char *line);
t_list			*clear_command_list(t_list *command_list);
t_list			*add_command_set(t_list *command_list);
void			add_param(t_list *command_list, char *token);
void			add_redir_type(t_list *command_list, t_token_type token_type);
void			add_redir_word(t_list *command_list, char *token);
char			*unquote_n_xpd(char *word);
char			*expand_vars(char *str);
char			*find_var(char *name);
char			*join_parts(char *str, char *content, int *position, \
				int name_len);
int				var_size(char *str);
int				env_len(char **env);
int				list_size(t_list *command_list);
char			*get_str_exit_code(void);

// Builtins
int				builtins(t_command *command_node, int l_size);
void			set_ms_wd(void);
void			print_wd(t_list *args);
void			ft_echo(t_list *args);
void			ft_cd_envel(t_list *args);
void			ft_exp_envel(t_list *args);
void			ft_export(char *args);
void			ft_unset(t_list *args);
void			ft_exit(t_list *args);
int				b_out_redir(t_list *redir, int l_size);
int				b_in_redir(t_list *redir, int l_size);

//Builtins + redirs
void			b_redirs(t_command	**command);

// Try execute
char			**list_to_array(void);

// Delete
void			print_env(t_list *args);

// Execute
void			m_launch(int argc, int fd[2], int pid[1024], int count);
void			m_launch_fork(int pid[1024], int count);
void			m_start(t_command *command, int fd[2][2], int r_type);
void			m_middle(t_command *command, int fd[2][2], int count, \
				int r_type);
void			m_end(t_command *command_list, int fd[2][2], int count, \
				int r_type);
void			exec_commands(int l_size, t_list *command_list);
void			execute(t_command *command);
void			execute_one(t_command *command);
void			execution(int l_size, t_list *command_list);
char			*p_path(char *command);

// Redirs
int				execin_redir(t_list *redir, int l_size);
int				execout_redir(t_list *redir, int l_size);
int				redir_type(t_list *command_list);
char			*ms_heredoc(char *keyword);
void			remove_temps(void);
void			*ft_free(char **substr, int num);

//Pruebas
void			free_command(void *command, t_free type);

#endif