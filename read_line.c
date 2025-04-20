/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalyout <fbalyout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:08:02 by yel-moun          #+#    #+#             */
/*   Updated: 2025/04/20 18:24:50 by fbalyout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hot_race.h"

ssize_t	refill_buffer(t_buffer_ctx *ctx)
{
	ctx->len = read(0, ctx->buf, LOCAL_READ_SIZE);
	ctx->pos = 0;
	return (ctx->len);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

int	ensure_capacity(char **line, size_t *alloc, ssize_t line_len)
{
	size_t	new_alloc;
	char	*tmp;

	if (line_len + 1 >= (ssize_t)*alloc)
	{
		new_alloc = (*alloc) * 2;
		tmp = ft_realloc(*line, *alloc, new_alloc);
		if (!tmp)
		{
			free(*line);
			*line = NULL;
			return (0);
		}
		*line = tmp;
		*alloc = new_alloc;
	}
	return (1);
}

int	read_line_from_buffer(t_buffer_ctx *ctx, char **line, ssize_t *line_len,
		size_t *alloc)
{
	int	done;

	done = 0;
	while (ctx->pos < ctx->len && !done)
	{
		if (!ensure_capacity(line, alloc, *line_len))
			return (-1);
		(*line)[*line_len] = ctx->buf[(ctx->pos)++];
		done = ((*line)[(*line_len)++] == '\n');
	}
	return (done);
}

char	*new_get_line(void)
{
	static t_buffer_ctx	ctx = {.buf = {0}, .len = 0, .pos = 0};
	t_line_state		state;

	state.alloc = LOCAL_INITIAL_ALLOC;
	state.line = malloc(state.alloc);
	state.line_len = 0;
	state.done = 0;
	while (!state.done)
	{
		if (ctx.pos >= ctx.len)
			if (refill_buffer(&ctx) <= 0)
				break ;
		state.res = read_line_from_buffer(&ctx, &state.line, &state.line_len,
				&state.alloc);
		if (state.res == -1)
			return (NULL);
		state.done = state.res;
	}
	if (state.line_len == 0)
		return (free(state.line), NULL);
	return (state.line[state.line_len] = '\0', state.line);
}
