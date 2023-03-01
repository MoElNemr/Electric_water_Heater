/*
 * EEPROM_interface.h
 *
 * Created: 12/16/2022 10:18:38 PM
 *  Author: AMIT
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


#define EEPROM_FIXED_ADDRESS    0x50


void EEPROM_writeByte(u16 byteAddress,u8 data);
void EEPROM_readByte (u16 byteAddress,u8* returnedData);


#endif /* EEPROM_INTERFACE_H_ */