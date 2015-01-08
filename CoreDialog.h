/******************************************************************
*  CoreDialog Library 
*  Kuba Kucharski


*  
*This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>
******************************************************************/
#ifndef CoreDialog_h
#define CoreDialog_h


// tak bedzie ladniej
#define details(name) (byte*)&name,sizeof(name)


#include "Arduino.h"
#include "Stream.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

class CoreDialog {
public:
void begin(uint8_t *, uint8_t, Stream *theStream);
void sendData();
boolean receiveData();
private:
Stream *_stream;
uint8_t * address;  //address of struct - to jest adres w pamieci, nie adres urzadzenia
uint8_t size;       //size of struct
uint8_t * rx_buffer; //address for temporary storage and parsing buffer
uint8_t rx_array_inx;  //index for RX parsing buffer
uint8_t rx_len;		//RX packet length according to the packet
uint8_t checksum;	   // czeksuma
};



#endif