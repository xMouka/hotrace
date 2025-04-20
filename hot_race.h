#ifndef HOT_RACE_H

#define HOT_RACE_H

#undef _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast,inline")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("movbe")
#pragma GCC target("aes,pclmul,rdrnd")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#pragma GCC optimize "Ofast,unroll-loops,omit-frame-pointer,inline"
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("rdrnd", "popcnt", "avx", "bmi2")
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data {
    char *key;
    char *value;
    unsigned int key_length;
    unsigned int value_length;
    int in_use;
} t_data;

typedef struct s_hash_map {
    size_t capacity;
    size_t size;
    t_data *data;
    unsigned int prime_for_second_hash;
} t_hash_map;

#define LOCAL_READ_SIZE 8192
#define LOCAL_INITIAL_ALLOC 128
typedef struct s_buffer_ctx
{
	char buf[LOCAL_READ_SIZE];
	ssize_t len;
	ssize_t pos;
} t_buffer_ctx;

typedef struct s_line_state
{
	size_t alloc;
	char *line;
	ssize_t line_len;
	int done;
	int res;
} t_line_state;

char    *get_next_line(int fd);
char *ft_strdup(const char *str);
int	ft_strcmp(const char *str1, const char *str2);
int	ft_strlen(const char *str);
unsigned int ft_sqrt(unsigned int x);
int is_prime(unsigned int n);
unsigned int next_prime(unsigned int n);
char *ft_strdup_len(const char *str, int len);
void ft_putstr(const char *str, int len);
unsigned long hash1(const char *str, int len);
unsigned long hash2(const char *str, int len, unsigned int prime);
void free_map(t_hash_map *map);
void	resize_map(t_hash_map *map);
void	handle_insert(t_hash_map *map, char **key, char **value);
char	*get_next_line(int fd);
void	insert(t_hash_map *map, char *key, char *value, unsigned int key_len,
        unsigned int value_len);
void	*get(t_hash_map *map, char *key, unsigned int key_len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*new_get_line(void);
#endif