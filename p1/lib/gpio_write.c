#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <utils.h>

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