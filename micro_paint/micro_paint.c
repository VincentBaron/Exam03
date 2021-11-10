/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:43:15 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/10 12:15:06 by vbaron           ###   ########.fr       */
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
        if (ret != 3)
            return (0);
        if (!(micro->width <= 300 && micro->width > 0) || !(micro->height <= 300 && micro->height > 0))
            return (0);
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

int is_in_rect(float i, float j, t_gen *micro)
{
    if (i < micro->start_hor || i > micro->start_hor + micro->sq_height || j < micro->start_hor || j > micro->start_hor + micro->sq_width)
        return (0);
    return (1);
}

int is_empty_rect(float i, float j, t_gen *micro)
{
     if (i < micro->start_vert || i > micro->start_vert + micro->sq_height || j < micro->start_hor || j > micro->start_hor + micro->sq_width)
        return (0);
    if (i - micro->start_vert < 1.0000000 || j - micro->start_hor < 1.00000000 || ((micro->start_vert + micro->sq_height) - i < 1.00000000) || ((micro->start_hor + micro->sq_width) - j < 1.00000000))
        return (1);
    return (0);
}

int draw_square(t_gen *micro)
{
    int i;
    int j;
    int R;
    int r;

    i = 0;
    while (i < micro->sq_height)
    {
        j = 0;
        while (j < micro->sq_width)
        {
            
            r = is_empty_rect(i, j, micro);
            R = is_in_rect(i, j, micro);
            if ((r && micro->type == 'r') || (R && micro->type == 'R'))
                micro->array[(int)(j + micro->width * i)] = micro->color;
            j++;
        }
        i++;
    }
    return (1);
}

int draw_squares(t_gen *micro)
{
    int ret;

    while ((ret = fscanf(micro->fd, "%c %f %f %f %f %c\n", &micro->type, &micro->start_hor, &micro->start_vert, &micro->sq_width, &micro->sq_height, &micro->color)) == 6)
    {
        draw_square(micro);
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
