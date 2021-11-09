/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:50:07 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/09 11:13:55 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_H
#define MICRO_H

typedef struct s_micro
{
    FILE *fd;
    int width;
    int height;
    char bgrd;
    char *array;
} t_gen;

#endif