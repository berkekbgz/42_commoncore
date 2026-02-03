/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:42:17 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 18:27:42 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

int	ft_putchar(char c);
int	ft_putstr(char *s, int n);
int	ft_putptr(void *p);
int	ft_puthex(unsigned long long val, char use_upper, char use_alternate);
int	ft_putint(int i);
int	ft_putuint(unsigned int i);

#endif
