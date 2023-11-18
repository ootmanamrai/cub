/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otamrani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:27:13 by otamrani          #+#    #+#             */
/*   Updated: 2023/11/18 22:27:17 by otamrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

t_garbage	*ft_lst_new(void *ptr)
{
	t_garbage	*new;

	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}
void	ft_lst_add_back(t_garbage **alst, t_garbage *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = (*alst);
	(*alst) = new;
}