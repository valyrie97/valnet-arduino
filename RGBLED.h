#ifndef RGBLED_H
#define RGBLED_H

struct RGBLED {
  int pinR;
  int pinG;
  int pinB;
	int channelR;
	int channelG;
	int channelB;
};

struct RGBLED STATUS_LED = { 0, 2, 15, 0, 1, 2 };

struct LEDColor {
  int r;
  int g;
  int b;
};

struct LEDColor RED = { 255, 0, 0 };
struct LEDColor GREEN = { 0, 255, 0 };
struct LEDColor BLUE = { 0, 0, 255 };
struct LEDColor CYAN = { 0, 50, 255 };
struct LEDColor MAGENTA = { 255, 0, 255 };
struct LEDColor YELLOW = { 255, 255, 0 };

struct LEDColor BLACK = { 0, 0, 0 };
struct LEDColor WHITE = { 255, 255, 255 };

void initRGBLED(struct RGBLED led) {
	ledcSetup(led.channelR, 5000, 8);
	ledcAttachPin(led.pinR, led.channelR);
	ledcSetup(led.channelG, 5000, 8);
	ledcAttachPin(led.pinG, led.channelG);
	ledcSetup(led.channelB, 5000, 8);
	ledcAttachPin(led.pinB, led.channelB);
}

void setRGBLEDColor(struct RGBLED led, struct LEDColor color) {
  ledcWrite(led.pinR, color.r);
  ledcWrite(led.pinG, color.g);
  ledcWrite(led.pinB, color.b);
}

#endif