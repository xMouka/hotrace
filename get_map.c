#include "hot_race.h"

void	*get(t_hash_map *map, char *key, unsigned int key_len)
{
	unsigned int	attempts;
	unsigned int	max_attempts;
	unsigned long idx;
	unsigned long step;

	attempts = 0;
	if (!map || !key || map->size == 0)
		return (NULL);
	idx = hash1(key, key_len) % map->capacity;
	step = hash2(key, key_len, map->prime_for_second_hash);
	if (map->capacity < 20)
		max_attempts = map->capacity;
	else
		max_attempts = 20;
	while (attempts < max_attempts)
	{
		if (!map->data[idx].in_use)
			return (NULL);
		if (map->data[idx].key_length == key_len
			&& ft_strcmp(map->data[idx].key, key) == 0)
			return (map->data[idx].value);
		idx = (idx + step) % map->capacity;
		attempts++;
	}
	return (NULL);
}
