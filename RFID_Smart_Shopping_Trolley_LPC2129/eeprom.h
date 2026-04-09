#ifndef EEPROM_H
#define EEPROM_H

void eeprom_save_last_bill(int amount);
int eeprom_read_last_bill(void);

#endif