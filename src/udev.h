#ifndef __UDEV__
#define __UDEV__

#define UNKNOWN -1
#define DEFAULT_FILE_SIZE 4096
#define DEFAULT_BLOCK_SIZE 128

#define STRING_UNKNOWN    "Unknown"
#define STRING_NONE       "None"
#define STRING_MEGAHERZ   "MHz"
#define STRING_GIGAHERZ   "GHz"
#define STRING_KILOBYTES  "KB"

struct cache;
struct frequency;

struct cache* get_cache_info();
struct frequency* get_frequency_info();
void free_cache_struct(struct cache* cach);
void free_freq_struct(struct frequency* freq);

char* get_str_l1(struct cache* cach);
char* get_str_l2(struct cache* cach);
char* get_str_l3(struct cache* cach);
char* get_str_freq(struct frequency* freq);
long get_freq(struct frequency* freq);

void debugFrequency(struct frequency* freq);
void debugCache(struct cache* cach);

#endif
