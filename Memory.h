#ifndef MEMORY_H
#define MEMORY_H

#include "EEPROM.h"
// #include "Arduino.h"
#include "hardwareSerial.h"

struct DataChunk {
  const int offset;
  const int width;
};

class MemoryClass {
	public:
		void begin(const int size);
		void dump();
		const byte readByte(const int address);
		void readString(struct DataChunk chunk, char* dest);
		void writeString(struct DataChunk chunk, const char* string);
		void clearAll();
	private:
		int size;
};

void MemoryClass::begin(const int size) {
	this->size = size;
  if (!EEPROM.begin( size )) {
    Serial.println("failed to initialise EEPROM!");
  } else {
    Serial.printf("EEPROM Size: %d\n", size);
  }

	this->dump();
}

void MemoryClass::dump() {
  int i = 0;
  while(i < this->size) {
    if(i != 0 && i % 32 == 0) Serial.println("");
    char c = (char)EEPROM.read(i);
		if(c < 0x20 || c == 127 || c == 255) {
			Serial.print('.');
		} else {
    	Serial.print(c);
		}
    i ++;
  }
  Serial.println("");
}

const byte MemoryClass::readByte(const int address) {
	return EEPROM.read(address);
}

void MemoryClass::readString(struct DataChunk chunk, char* dest) {
	char data[32];
	int idx = 0;
	while(idx < chunk.width) {
		data[idx] = (char)EEPROM.read(chunk.offset + idx);
		idx ++;
	}
	strcpy(dest, data);
}

void MemoryClass::writeString(struct DataChunk chunk, const char* string) {
  if(strlen(string) > chunk.width - 1) {
    return; // TODO make this error out!
  }

  int cell = chunk.offset;
  for(int i = 0; i < strlen(string); i ++) {
    EEPROM.write(cell, string[i]);
    cell ++;
  }
  EEPROM.write(cell, 0);
  EEPROM.commit();
}

void MemoryClass::clearAll() {

}

MemoryClass Memory;

#endif