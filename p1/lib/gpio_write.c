#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <utils.h>

/**
	Write char value for a given GPIO pin
	@param path: the path to GPIO value file
    @param value: the value to write
	@return: the number of char written
**/
int gpio_write(const char path[], char value) {
    int gpio;
    int n;

    if ((gpio = open(path, O_WRONLY)) == -1) {
        return -1;
    }

    lseek(gpio, 0, SEEK_SET);
	n = write(gpio, &value, sizeof value);
    
    close(gpio);
    return n;
}