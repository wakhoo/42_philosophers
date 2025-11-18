/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:06:00 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 13:02:10 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_alloc_code
{
	FALSE,
	TRUE,
	ALLOC,
	UNLINK,
	FREE,
	CLEAR,
	SIZE
}	t_alloc_code;

typedef struct s_common
{
	int				total_num;
	int				have_to_eat;
	int				num_ate_philos;
	int				death_flag;
	size_t			day_limit;
	size_t			start_day;
	size_t			eat;
	size_t			sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
}	t_common;

typedef struct s_philo
{
	int				id;
	int				ated_num;
	int				enough_eat;
	size_t			last_eat;
	size_t			current;
	t_common		*common;
	pthread_t		brain;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
}	t_philo;

typedef struct s_cctv
{
	t_philo			**philo;
	t_common		*common;
	pthread_t		observer;
}	t_cctv;

typedef struct s_bin
{
	void			*ptr;
	int				flag;
	struct s_bin	*next;
}	t_bin;

size_t	get_mstime(void);

void	init_set(int argc, char **argv, t_cctv **cctv);
void	*routine(void *data);
void	safe_print(char *str, t_philo *philo);
void	*checker(void *arg);
int		check_data(int argc, char **argv);

int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_strlen(const char *str);
int		check_digit(char *str);

void	error_exit(char *str);
void	error_exit_free(char *str);
void	alloc_error(void);

void	*ft_allocator(int size, t_alloc_code code, void *ptr, int critical);
void	*tlloc(int size, int flag);
void	tclear(int flag);
void	tfree(void *ptr);
void	tunlink(void *ptr);
t_bin	*al_lstnew(void *content, int critical);
void	al_lstclear(t_bin **al_lst, int free_critical);
int		al_lstdelone(t_bin **al_lst_head, t_bin *al_to_del);
void	al_lstadd(t_bin **al_lst, t_bin *addnew);

#endif