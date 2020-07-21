#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <utils.h>

/**
	Read char value for a given GPIO pin
	@param pathc: the path to GPIO value file
	@return: the char value
**/
char gpio_read(const char path[]) {
    char value;
    int gpio;

    if ((gpio = open(path, O_RDONLY)) == -1) {
        return -1;
    }

    lseek(gpio, 0, SEEK_SET);
	read(gpio, &value, sizeof value);
    
    close(gpio);

    return value;
}