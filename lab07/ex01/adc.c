#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>

int main(int argc,char * argv[]) {

    char data[80];
    int board;
    int voltate_raw = 0;
    int voltage_scale = 0;
    double scale;
    int value;

    board = board_name();
        
    if(board == BOARD_GALILEO_GEN1) {
        printf("Unsupported device\n");
        return 0;
    }

    // Open files for reading
    if((voltate_raw = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", O_RDONLY)) < 0) {
        perror("Opening in_voltage0_raw");
        return -1;
    }

    if ((voltage_scale = open("/sys/bus/iio/devices/iio:device0/in_voltage0_scale", O_RDONLY)) < 0) {
        perror("Opening in_voltage0_scale");
        return -1;
    }

    // Get scale
    lseek(voltage_scale, 0, SEEK_SET);
    read(voltage_scale, &data, sizeof data);

    scale = atof(data) / 1000.0;

    // Read voltage_raw
    for (;;) {
        lseek(voltate_raw, 0, SEEK_SET);
        read(voltate_raw, &data, sizeof data);
        value = atoi(data);

        printf("Voltage Raw: %d\t Voltage Scale: %f\t Voltage: %f\n", value, scale, value * scale);
        usleep(100);
    }
    
    return 0;
}