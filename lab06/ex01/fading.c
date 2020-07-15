#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <galileo2io.h>

int main(int argc,char * argv[]) {

    float period_time = 1000000.0;
    int board;

    board = board_name();
        
    if(board == BOARD_GALILEO_GEN1) {
        printf("Unsupported device\n");
        return 0;
    }

    // Enable PWM
    pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "1");

    // Configure period
    // frequency 1K Hz aka. period 1 ms
    // 1 * 1000 * 1000 ns
    pputs("/sys/class/pwm/pwmchip0/device/pwm_period", "1000000");

    // Duty cycle
    char duty_cycle[10];
    float i;
    for (i = 0.0; i < 1.0; i += 0.10) {
        sprintf(duty_cycle, "%d", (int) (i * period_time));
        pputs("/sys/class/pwm/pwmchip0/pwm3/duty_cycle", duty_cycle);
        // Wait 1s until increase duty cycle
        printf("duty cycle: %s\n", duty_cycle);
        sleep(1);
    }

    pputs("/sys/class/pwm/pwmchip0/pwm3/enable", "0");

    return 0;
}