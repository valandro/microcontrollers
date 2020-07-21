#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

enum BOARD_NAME
{
	BOARD_GALILEO_GEN1=1,
	BOARD_GALILEO_GEN2=2,
	BOARD_UNKNOWN=-1
};

extern int board_name(void);
extern char gpio_read(const char path[]);
extern int gpio_write(const char path[], const char value);

#ifdef __cplusplus
};
#endif

#endif