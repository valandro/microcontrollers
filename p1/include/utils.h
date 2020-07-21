#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

extern char gpio_read(const char path[]);
extern int gpio_write(const char path[], const char value);

#ifdef __cplusplus
};
#endif

#endif