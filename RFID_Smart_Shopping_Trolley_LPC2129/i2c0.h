#ifndef I2C0_H
#define I2C0_H

void i2c0_init(void);
void i2c0_start(void);
void i2c0_restart(void);
void i2c0_stop(void);
void i2c0_write(unsigned char data);
unsigned char i2c0_read_ack(void);
unsigned char i2c0_read_nack(void);

#endif