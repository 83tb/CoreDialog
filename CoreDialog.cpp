#include "CoreDialog.h"

// nasz protokol:
// Header(0x06,0x85),SizeofPayload,Payload,Checksum
// ACK 0x06
// NEL = Next Line
// Size = ilosc bajtow
// Payload
// Czeksuma


// wylapujemy adres i wielkosc struktury
void CoreDialog::begin(uint8_t * ptr, uint8_t length, Stream *theStream){
	address = ptr;
	size = length;
	_stream = theStream;
	
	// dynamiczny bufor do parsowania rx, oszczedzamy RAM
	rx_buffer = (uint8_t*) malloc(size);
}

//struktura wysylana jest w formie binarnej: header | length info | checksum
void CoreDialog::sendData(){
  uint8_t CS = size;
  _stream->write(0x06);
  _stream->write(0x85);
  _stream->write(size);
  for(int i = 0; i<size; i++){
    CS^=*(address+i);
    _stream->write(*(address+i));
  }
  _stream->write(CS);

}

boolean CoreDialog::receiveData(){
  
  //zacznij od szukania znacznikow naglowka
  //jesli naglowek byl przed chwila - pomin

  if(rx_len == 0){
  
  // size check
    if(_stream->available() >= 3){
	
  // albo 0x06 zostanie znalezione albo bufor sie skonczy
      while(_stream->read() != 0x06) {
	
  	// w ten sposob pozbywamy sie smieci z bufora
		//ale musimy upewnic sie ze w buforze jest wystarczajaco duzo
		

		if(_stream->available() < 3)
      // jesli bufor sie skonczy, wyskoczymy z petli i zaczynamy na nowo
			return false;
		}
      if (_stream->read() == 0x85){
        rx_len = _stream->read();
		//przypilnujmy, zeby wielkosci structow byly takie same
        if(rx_len != size){
          rx_len = 0;
          return false;
        }
      }
    }
  }
  
  //jesli jestesmy tu to znaczy ze mamy naglowek
  //struktura sie zgadza, i jest git -> byte aligned

  
  if(rx_len != 0){
    while(_stream->available() && rx_array_inx <= rx_len){
      rx_buffer[rx_array_inx++] = _stream->read();
    }
    
    if(rx_len == (rx_array_inx-1)){
      //odczytalismy cala wiadomosc
      //na koncu jest zmienna uint8_t to czeksuma
      checksum = rx_len;
      for (int i = 0; i<rx_len; i++){
        checksum^=rx_buffer[i]; // XOR
      } 
      
      if(checksum == rx_buffer[rx_array_inx-1]){//CS good
        memcpy(address,rx_buffer,size);
		rx_len = 0;
		rx_array_inx = 0;
		return true;
		}
		
	  else{
	  // czeksuma nie zadzialala
		rx_len = 0;
		rx_array_inx = 0;
		return false;
	  }
        
    }
  }
  
  return false;
}