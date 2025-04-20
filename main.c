#include "hot_race.h"
#include <stdlib.h>

t_hash_map	*create_map(size_t capacity)
{
	t_hash_map	*map;
	size_t		i;

	capacity = next_prime(capacity);
	map = malloc(sizeof(t_hash_map));
	if (!map)
		return (NULL);
	map->capacity = capacity;
	map->size = 0;
	map->prime_for_second_hash = next_prime(capacity / 2);
	map->data = malloc(capacity * sizeof(t_data));
	if (!map->data)
		return (free(map), NULL);
	i = 0;
	while (i < capacity)
	{
		map->data[i].key = NULL;
		map->data[i].value = NULL;
		map->data[i].key_length = 0;
		map->data[i].value_length = 0;
		map->data[i].in_use = 0;
		i++;
	}
	return (map);
}

void	free_map(t_hash_map *map)
{
	size_t	i;

	if (!map)
		return ;
	if (map->data)
	{
		for (i = 0; i < map->capacity; i++)
		{
			if (map->data[i].in_use)
			{
				free(map->data[i].key);
				free(map->data[i].value);
			}
		}
		free(map->data);
	}
	free(map);
}

void	ft_read_input(t_hash_map *map)
{
	char *key;
	char *value;
	char *line;

	while (1)
	{
		key = NULL;
		value = NULL;
		line = new_get_line();
		if (!line)
			break;
		if (line[0] == '\n')
           break;
		key = line;
		value = new_get_line();
		if (key && value)
			handle_insert(map, &key, &value);
	}
}

// static void	read_key_value_pairs(t_hash_map *map)
// {
//     char	*line;
//     char	*key = NULL;
//     char	*value = NULL;
//     int		i = 0;

//     while ((line = get_next_line(0)))
//     {
//         if (line[0] == '\0')
//             return (free(line), free(key), free(value), (void)0);
//         if (i % 2 == 0)
//             key = line;
//         else
//         {
//             value = line;
// 			ft_putstr(value, ft_strlen(value));
//             if (key && value)
//                 handle_insert(map, &key, &value);
//         }
//         i++;
//     }
//     free(key);
//     free(value);
// }

static void	search_keys(t_hash_map *map)
{
    char			*to_search;
    unsigned int	search_len;
    char			*result;

    while ((to_search = get_next_line(0)))
    {
        if (to_search[0] == '\0')
            return (free(to_search), (void)0);
        search_len = ft_strlen(to_search);
        result = get(map, to_search, search_len);
        if (result)
            ft_putstr(result, ft_strlen(result));
        else
            ft_putstr(to_search, search_len), write(1, ": Not found.\n", 13);
        free(to_search);
    }
}

int	main(void)
{
    t_hash_map	*map;

    map = create_map(1048583);
    if (!map)
        return (1);
    ft_read_input(map);
    search_keys(map);
    free_map(map);
    return (0);
}
