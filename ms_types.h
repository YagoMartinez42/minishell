/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42madrid.es>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:32:33 by samartin          #+#    #+#             */
/*   Updated: 2024/05/15 15:41:21 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPES_H
# define MS_TYPES_H
# include <signal.h>
# include "./libft/libft.h"

typedef struct s_redir
{
	int		type;
	char	*k_word;
}	t_redir;

typedef struct s_command
{
	char	*command;
	t_list	*args;
	t_list	*redirs;
}	t_command;

typedef struct s_execData
{
	int		fd[2][2];
	int		count;
	int		pid[1024];
	int		r_type;
}	t_execData; // Comprobar nombres, no tengo intra todavía

typedef struct s_minishell
{
	char	**env;
	char	*pwd;
	int		exit_code;
}	t_minishell;

typedef enum e_wvar
{
	ENV,
	PWD,
	EXIT_CODE
}	t_wvar;

typedef enum e_quote_status
{
	NONE,
	SINGLE,
	DOUBLE
}	t_q_status;

typedef enum e_errors
{
	QUOTES,
	PIPES,
	REDIRS
}	t_errors;

typedef enum e_exports
{
//	NO_TYPE,
	INVALID,
	EXISTS,
	NEW
}	t_exports;

typedef enum e_free
{
	SET,
	FREE
}	t_free;

typedef enum e_token_type
{
	NO_TOKEN, //nothing (yet)
	ARG, //argument
	INFILE, //word == '<'
	HERE_DOC, // word == '<<'
	OUTFILE, //word == '>'
	OUTFILE_ADD, //word == '>>'
	WRONG_REDIR
}	t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	token_type;
	int				pos;
}	t_token; // Comprobar nombres, no tengo intra todavía

/* Pointer to function for the builtins */
typedef void	(*t_p2built)(t_list *);

#endif