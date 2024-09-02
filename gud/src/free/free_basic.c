/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:27:49 by david             #+#    #+#             */
/*   Updated: 2024/09/02 16:37:57 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
