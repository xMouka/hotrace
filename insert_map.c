#include "hot_race.h"

static void	update_existing_entry(t_data *entry, char *value, unsigned int len)
{
    free(entry->value);
    entry->value = ft_strdup_len(value, len);
    entry->value_length = len;
}

static int	find_insert_index(t_hash_map *map, char *key, unsigned int key_len,
        unsigned long *idx)
{
    unsigned int	attempts;
    unsigned int	max_attempts;
    unsigned long	step;

    attempts = 0;
    *idx = hash1(key, key_len) % map->capacity;
    step = hash2(key, key_len, map->prime_for_second_hash);
    if (map->capacity < 20)
        max_attempts = map->capacity;
    else
        max_attempts = 20;
    while (attempts < max_attempts)
    {
        if (!map->data[*idx].in_use
            || (map->data[*idx].key_length == key_len
                && ft_strcmp(map->data[*idx].key, key) == 0))
            return (1);
        *idx = (*idx + step) % map->capacity;
        attempts++;
    }
    return (0);
}

void	insert(t_hash_map *map, char *key, char *value, unsigned int key_len,
        unsigned int value_len)
{
    unsigned long	idx;

    if (!map || !key || !value)
        return ;
    if ((double)map->size / map->capacity >= 0.75)
        resize_map(map);
    if (!find_insert_index(map, key, key_len, &idx))
    {
        resize_map(map);
        insert(map, key, value, key_len, value_len);
        return ;
    }
    if (map->data[idx].in_use)
        update_existing_entry(&map->data[idx], value, value_len);
    else
    {
        map->data[idx].key = ft_strdup_len(key, key_len);
        map->data[idx].value = ft_strdup_len(value, value_len);
        map->data[idx].key_length = key_len;
        map->data[idx].value_length = value_len;
        map->data[idx].in_use = 1;
        map->size++;
    }
}

void	handle_insert(t_hash_map *map, char **key, char **value)
{
    unsigned int key_len = ft_strlen(*key);
    unsigned int value_len = ft_strlen(*value);

    insert(map, *key, *value, key_len, value_len);
    free(*key);
    free(*value);
    *key = NULL;
    *value = NULL;
}