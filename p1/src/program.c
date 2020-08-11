#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>
#include <utils.h>

int main(int argc,char * argv[]) {

    // Verifica se a placa em questao e Galileo Gen2
    if (board_name() != BOARD_GALILEO_GEN2) {
        perror("Unsupported device\n");
        return -1;
    }

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

    // Enable PWM
    pwm_write_enable("/sys/class/pwm/pwmchip0/pwm3/enable", 1);

    // Configure period
    // frequency 1K Hz aka. period 1 ms
    // 1 * 1000 * 1000 ns
    int period = pwm_frequency_to_period(1000);
    pwm_write_period("/sys/class/pwm/pwmchip0/device/pwm_period", period);

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
        
        float duty_cycle = (float) (value * scale) / 5.0;
        printf("duty_cycle = %f\n", duty_cycle);
        pwm_write_duty_cycle("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", duty_cycle, period);

        usleep(100);
    }

    pwm_write_enable("/sys/class/pwm/pwmchip0/pwm3/enable", 0);

    return 0;
}