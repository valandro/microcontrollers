#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

extern char gpio_read(const char path[]);
extern int gpio_write(const char path[], const char value);
extern int pwm_frequency_to_period(const int frequency);
extern int pwm_write_enable(const char path[], const int enable);
extern int pwm_write_period(const char path[], const int period);
extern int pwm_write_duty_cycle(const char path[], const float duty_cycle, const int period);

#ifdef __cplusplus
};
#endif

#endif