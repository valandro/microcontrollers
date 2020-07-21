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

    // Enable PWM
    pwm_write_enable("/sys/class/pwm/pwmchip0/pwm3/enable", 1);

    // Configure period
    // frequency 1K Hz aka. period 1 ms
    // 1 * 1000 * 1000 ns
    int period = pwm_frequency_to_period(1000);
    pwm_write_period("/sys/class/pwm/pwmchip0/device/pwm_period", period);

    // Duty cycle
    float i;
    for (i = 0.0; i < 1.0; i += 0.10) {
        pwm_write_duty_cycle("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", i, period);
        // Wait 1s until increase duty cycle
        printf("Duty cycle: %f\n", i);
        sleep(1);
    }

    pwm_write_enable("/sys/class/pwm/pwmchip0/pwm3/enable", 0);

    return 0;
}