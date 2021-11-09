/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:43:15 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/09 15:54:54 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./micro.h"

int ft_strlen(char *s)
{
    int i;

    if (!s)
        return (-1);
    
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int read_file(t_gen *micro)
{
        int ret;
        
        ret = fscanf(micro->fd, "%d %d %c\n", &micro->width, &micro->height, &micro->bgrd);
        return (1);
}

int draw_back(t_gen *micro)
{
    int i;
    
    i = 0;
    if (!(micro->array = malloc(sizeof(char) * (micro->width * micro->height + 1))))
        return (0);
    while (i < (micro->width * micro->height))
    {
        micro->array[i] = micro->bgrd;
        i++;
    }
    micro->array[i] = '\0';
    return (1);
}

int display(t_gen *micro)
{
    int i;
    int f;

    i = -1;
    while (++i < micro->height)
    {
        f = -1;
        while (++f < micro->width)
            write(1, &micro->array[f + i * micro->width], 1);
        write(1, "\n", 1);
    }
    return(1);
}

int draw_square(t_gen *micro)
{
    int i;
    int j;

    i = micro->start_vert + 0.5;
    while (i < micro->height && i - (micro->start_vert + 0.5) < micro->sq_height)
    {
        j = micro->start_hor + 0.5;
        while (j < micro->width && j - (micro->start_hor + 0.5) < micro->sq_width)
        {
            micro->array[(int)(j + micro->width * i)] = micro->color;
            j++;
        }
        i++;
    }
    return (1);
}

int draw_squares(t_gen *micro)
{
    int i;
    int ret;

    while ((ret = fscanf(micro->fd, "%c %f %f %f %f %c\n", &micro->type, &micro->start_hor, &micro->start_vert, &micro->sq_width, &micro->sq_height, &micro->color)) == 6)
    {
        if (micro->type == 'R')
            draw_square(micro);
        // else if (micro->type == 'r')
        //     draw_empty_square(micro);
    }
    return (1);
}

int main(int ac, char **av)
{
    t_gen micro;
    
    if(ac != 2)
    {
        write(1, "Error: argument\n", ft_strlen("Error: argument\n"));
        return(1);
    }
    if (!(micro.fd = fopen(av[1], "r")))
    {
        write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
        return (1);
    }
    
    if (!read_file(&micro))
    {
        write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
        return (1);
    }
    draw_back(&micro);
    draw_squares(&micro);
    display(&micro);
    return (0);
}
