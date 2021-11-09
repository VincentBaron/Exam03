/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:50:07 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/09 15:00:07 by vbaron           ###   ########.fr       */
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
    float sq_width;
    float sq_height;
    float start_vert;
    float start_hor;
    char type;
    char color;
} t_gen;

#endif