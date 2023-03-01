#include "EWH.h"


u8 state = 1;
u8 * ptr = &state;

int main(void)
{
	EWH_SET_DIRECTION();
	EWH_INIT();
	
	u16 sensor;
	u8 desired_temp;
	EWH_FIRST_TIME_CHECK(desired_temp);
	EEPROM_readByte(EEPROM_ADDRES,&desired_temp);
	u8 up = 0 ;
	u8 down = 0 ;

    while (1) 
    {
		EWH_GET_SENSOR(&sensor);
		if (state == 1)
		{
			// go to setting temp
			up   = DIO_getPinValue(EWH_UP_BUTTON_PORT,EWH_UP_BUTTON_PIN);
			down = DIO_getPinValue(EWH_DOWN_BUTTON_PORT,EWH_DOWN_BUTTON_PIN);
			
			if (up == 1 || down == 1)
			{
				_delay_ms(500);
				set_temp(& desired_temp,state);
				EEPROM_writeByte(EEPROM_ADDRES,desired_temp);
			}
			// end of the setting temp mode
			SSD_displayMultiNumber(sensor);
		
			if (sensor <= desired_temp-5)
			{
				EWH_START_HEATER(sensor,desired_temp,up,down);
			}
		
			else if (sensor >= desired_temp+5)
			{
				EWH_START_COOLER();
			}
		}
		else
		{
			EWH_SHUTDOWN();
		}
	    
    }
	
}

void __vector_1(void)__attribute__ ((signal));
void __vector_1(void)
{
	if (state == 1)
	{
		*ptr = 0;
	}
	else
	{
		*ptr = 1;
	}
			
}

