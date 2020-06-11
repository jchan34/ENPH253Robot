
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
#define PWMFREQ 2000
#define SERVOPIN PA1
void handle_interrupt();
void handle_interrupt_schmitt();
volatile int i = 0;
volatile int j = 0;
int reading;
int angle;
Servo servo;
int servoAngle = 0;
boolean hitServoEdge = false;
void setup()
{
  //  pinMode(INTERRUPTPIN, INPUT_PULLUP);
  // pinMode(TAPESENSOR, INPUT_ANALOG);
  //pinMode(MOTOR_A, OUTPUT);
  //pinMode(MOTOR_B, OUTPUT);
  pinMode(ANALOG_IN, INPUT_ANALOG);
  servo.attach(SERVOPIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(2000);

  // Displays "Hello world!" on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.clearDisplay();
  pwm_start(MOTOR_A, PWMFREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_B, PWMFREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
}

void handle_interrupt()
{
  i++;
}

void loop()
{

  display.clearDisplay();

  if (analogRead(ANALOG_IN) > 512)
  {
    pwm_start(MOTOR_A, PWMFREQ, 2 * (analogRead(ANALOG_IN) - 512), RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B, PWMFREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
    display.println("Forwards");
    display.setCursor(0, 15);
    display.println(2 * (analogRead(ANALOG_IN) - 512));
    display.display();
  }
  else
  {
    pwm_start(MOTOR_A, PWMFREQ, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(MOTOR_B, PWMFREQ, -2 * (analogRead(ANALOG_IN) - 511), RESOLUTION_10B_COMPARE_FORMAT);
    display.println("Backwards");
    display.setCursor(0, 15);
    display.println(-2 * (analogRead(ANALOG_IN) - 511));
    display.display();
  }

};
