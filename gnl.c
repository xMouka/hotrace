#include "hot_race.h"
#include <stdlib.h>
#include <unistd.h>

static char	*resize_line(char *line, int line_pos)
{
    char	*new_line;
    int		i;

    new_line = malloc(line_pos + 8192);
    if (!new_line)
    {
        free(line);
        return (NULL);
    }
    i = 0;
    while (i < line_pos)
    {
        new_line[i] = line[i];
        i++;
    }
    free(line);
    return (new_line);
}

static char	*finalize_line(char *line, int line_pos)
{
    line[line_pos] = '\0';
    return (line);
}

static char	*handle_read(int fd, char *buffer, int *pos, int *bytes_read)
{
    *bytes_read = read(fd, buffer, 8192);
    *pos = 0;
    if (*bytes_read <= 0)
        return (NULL);
    return ((char *)1);
}

static char	*process_char(char *line, char c, int *line_pos)
{
    line[*line_pos] = c;
    (*line_pos)++;
    if (*line_pos >= 8191)
        line = resize_line(line, *line_pos);
    return (line);
}

static char	*read_buffer(int fd, char *line, char *buffer, int *pos)
{
    static int	bytes_read = 0;
    int			line_pos = 0;
    char		*status;
    char        c;

    while (1)
    {
        if (*pos >= bytes_read)
        {
            status = handle_read(fd, buffer, pos, &bytes_read);
            if (!status)
            {
                if (line_pos > 0)
                    finalize_line(line, line_pos);
                else
                    free(line);
                return (NULL);
            }
        }
        while (*pos < bytes_read)
        {
            c = buffer[(*pos)++];
            if (c == '\n')
                return (finalize_line(line, line_pos));
            line = process_char(line, c, &line_pos);
            if (!line)
                return (NULL);
        }
    }
}

char	*get_next_line(int fd)
{
    static char	buffer[8192];
    static int	pos = 0;
    char		*line;

    line = malloc(8192);
    if (!line)
        return (NULL);
    return (read_buffer(fd, line, buffer, &pos));
}