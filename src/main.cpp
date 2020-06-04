#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTOR_A PA_7
#define MOTOR_B PA_6
#define ANALOG_IN PB1

#define SERVOPIN PA1

Servo servo;

void setup()
{

  pinMode(ANALOG_IN, INPUT_ANALOG);
  servo.attach(SERVOPIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();

  // Displays "Hello world!" on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.clearDisplay();
}

void loop()
{

  display.clearDisplay();
  display.setCursor(0, 0);

  servo.write(0);
  delay(1000);
  servo.write(45);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(45);
  delay(1000);
};
