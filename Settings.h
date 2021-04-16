#ifndef SETTINGS_H
#define SETTINGS_H

#include "Memory.h"
#include "StrUtil.h"

#define EEPROM_SIZE 512

#define SSID_WIDTH 32
#define PASSWD_WIDTH 32
#define RSA_KEY_WIDTH 64
#define FLAGS_WIDTH 16

struct WiFiNetworkSettings {
	char ssid[SSID_WIDTH];
	char passwd[PASSWD_WIDTH];
};

const struct WiFiNetworkSettings NULL_WIFI_SETTINGS = {"", ""};

bool operator==(const WiFiNetworkSettings& lhs, const WiFiNetworkSettings& rhs)
{
	return lhs.ssid == rhs.ssid && lhs.passwd == rhs.passwd;
}


const struct DataChunk SSID_CHUNK =        {0x000, SSID_WIDTH};
const struct DataChunk PASSWD_CHUNK =      {0x020, PASSWD_WIDTH};
const struct DataChunk PUBLIC_KEY_CHUNK =  {0x040, RSA_KEY_WIDTH};
const struct DataChunk PRIVATE_KEY_CHUNK = {0x080, RSA_KEY_WIDTH};
const struct DataChunk FLAGS_CHUNK =       {0x0C0, FLAGS_WIDTH}; //ends at 0x0D0
// EEPROM ENDS AT 0x200

class SettingsClass {
	public:
		void begin();
		void writeWifi(const char* ssid, const char* passwd);
		void clearWifi();
		struct WiFiNetworkSettings readWifi();
};

void SettingsClass::begin() {
	Memory.begin(EEPROM_SIZE);

	if(Memory.readByte(0) == 255) {
		Memory.clearAll();
	}
}

void SettingsClass::writeWifi(const char* ssid, const char* passwd) {
	Memory.writeString(SSID_CHUNK, ssid);
	Memory.writeString(PASSWD_CHUNK, passwd);
}

void SettingsClass::clearWifi() {
	Memory.writeString(SSID_CHUNK, "");
	Memory.writeString(PASSWD_CHUNK, "");
}

struct WiFiNetworkSettings SettingsClass::readWifi() {
	if(Memory.readByte(SSID_CHUNK.offset) == 0) return NULL_WIFI_SETTINGS;
	

	// char ssid = *(Memory.readString(SSID_CHUNK));
	// char passwd = *(Memory.readString(PASSWD_CHUNK));

	WiFiNetworkSettings net;

	char ssid[SSID_WIDTH];
	char passwd[PASSWD_WIDTH];
	Memory.readString(SSID_CHUNK, ssid);
	Memory.readString(PASSWD_CHUNK, passwd);
	strcpy(net.ssid, ssid);
	strcpy(net.passwd, passwd);

	return net;
}

SettingsClass Settings;

#endif