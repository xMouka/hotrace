#include "hot_race.h"

static void	init_new_data(t_data *data, size_t capacity)
{
    size_t	i;

    i = 0;
    while (i < capacity)
    {
        data[i].key = NULL;
        data[i].value = NULL;
        data[i].key_length = 0;
        data[i].value_length = 0;
        data[i].in_use = 0;
        i++;
    }
}

static void	rehash_old_data(t_hash_map *map, t_data *old_data, size_t old_cap)
{
    size_t	i;

    i = 0;
    while (i < old_cap)
    {
        if (old_data[i].in_use)
        {
            insert(map, old_data[i].key, old_data[i].value,
                old_data[i].key_length, old_data[i].value_length);
            free(old_data[i].key);
            free(old_data[i].value);
        }
        i++;
    }
}

void	resize_map(t_hash_map *map)
{
    t_data	*old_data;
    size_t	old_capacity;

    old_data = map->data;
    old_capacity = map->capacity;
    map->capacity = next_prime(map->capacity * 2);
    map->prime_for_second_hash = next_prime(map->capacity / 2);
    map->data = malloc(map->capacity * sizeof(t_data));
    if (!map->data)
    {
        map->data = old_data;
        map->capacity = old_capacity;
        return ;
    }
    init_new_data(map->data, map->capacity);
    map->size = 0;
    rehash_old_data(map, old_data, old_capacity);
    free(old_data);
}