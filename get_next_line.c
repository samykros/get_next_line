/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/1 18:49:27 by spascual           #+#    #+#             */
/*   Updated: 2023/10/1 14:11:37 by spascual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c

#include "get_next_line.h"

static char	*read_from_file(int fd)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1]; // Why + 1, works the same without, for /0?

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (strdup(buffer)); // No capicheo del todo
}

static char *join_and_free(char *s1, char *s2)
{
    char *new_str;

    new_str = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (new_str);
}

static char *lines(int fd, char **str)
{
	char    *temp;
	char    *line_break;
	char    *new_str;
	char    *line;

    // Continuar leyendo hasta que se encuentre un salto de línea o se acabe el archivo
    while ((line_break = ft_strchr(*str, '\n')) == NULL)
	{
        temp = read_from_file(fd);
        if (temp == NULL) // No más que leer
            break;
        *str = join_and_free(*str, temp);
    }
    if (line_break != NULL) // Si se encontró un salto de línea, procesa la línea
	{
        line = strdup(*str); // Copia la línea actual
        new_str = strdup(""); // Prepara str para la próxima llamada
        if (str)
            free(*str);
        *str = new_str;
        free(new_str);
        return (line);
    }
    return (NULL); // En caso de que no haya más saltos de línea
}

char *get_next_line(int fd)
{
    static char *str; // Mantiene el texto restante de llamadas anteriores
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || (read (fd, 0, 0) < 0)) // || (read (fd, 0, 0) < 0))
        return (NULL);
    if (str == NULL)
        str = strdup(""); // Inicializa str si es la primera llamada
    line = lines(fd, &str);
    // Maneja el caso de la última línea sin salto de línea
    if (line == NULL && *str)
	{
        free(str);
        //free(line); // why does this not break?
        str = NULL;
    }
    return (line);
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1)
	{
        perror("Error al abrir el archivo");
        return 1;
    }

    char *line;
    int i = 9;
     while (i > 0)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line); 
        i--;
    }

    close(fd);
    return 0;
}