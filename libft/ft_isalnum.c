/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:23:44 by dyanez-m          #+#    #+#             */
/*   Updated: 2023/09/15 21:58:30 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	alpha;
	int	num;

	alpha = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
	num = (c >= '0' && c <= '9');
	return (alpha || num);
}
