#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>
#include <utils.h>

int main(int argc,char * argv[]) {

    char button;

    // Verifica se a placa em questao e Galileo Gen2
    if (board_name() != BOARD_GALILEO_GEN2) {
        perror("Unsupported device\n");
        return -1;
    }

    for(;;) {
        button = gpio_read("/sys/class/gpio/gpio13/value");
        printf ("Read: %c\n", button);
        gpio_write("/sys/class/gpio/gpio14/value", button);
    }

    return 0;
}