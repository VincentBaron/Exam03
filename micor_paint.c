/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micor_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:43:15 by vbaron            #+#    #+#             */
/*   Updated: 2021/11/09 11:22:30 by vbaron           ###   ########.fr       */
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
        
        ret = fscanf(micro->fd, "%d %d %c", &micro->width, &micro->height, &micro->bgrd);
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

    while (i < micro->height)
    {
        f = -1;
        while (++f < micro->width)
            write(1, &micro->bgrd, 1);
        write(1, "\n", 1);
        i++;
    }
    return(1);
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
    display(&micro);
    return (0);
}
