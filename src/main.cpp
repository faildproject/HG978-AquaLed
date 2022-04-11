#include <Arduino.h>
#include <Kelvin2RGB.h>

#define RED_PIN 19
#define GREEN_PIN 26
#define BLUE_PIN 25
#define WHITE_PIN 18 // with some Red,Green & Blue LEDs

Kelvin2RGB KRGB;
const int freq = 20000;
const int Red_Ch = 0;
const int Green_Ch = 1;
const int Blue_Ch = 2;
const int White_Ch = 3;
const int resolution = 11;

void writeRGB(float red, float green, float blue){
  uint32_t red_pwm = red * 2048.;
  uint32_t green_pwm = green * 2048.;
  uint32_t blue_pwm = blue * 2048.;
  Serial.printf("R%d,G%d,B%d \r\n",red_pwm,green_pwm,blue_pwm);
  ledcWrite(Red_Ch, red_pwm);
  ledcWrite(Green_Ch, green_pwm);
  ledcWrite(Blue_Ch, blue_pwm);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ledcSetup(Red_Ch, freq, resolution);
  ledcSetup(Green_Ch, freq, resolution);
  ledcSetup(Blue_Ch, freq, resolution);
  ledcSetup(White_Ch, freq, resolution);

  ledcAttachPin(RED_PIN,Red_Ch);
  ledcAttachPin(GREEN_PIN,Green_Ch);
  ledcAttachPin(BLUE_PIN,Blue_Ch);
  ledcAttachPin(WHITE_PIN,White_Ch);

  writeRGB(0,0,0);
  ledcWrite(White_Ch, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint32_t i = 1000; i <= 12000; i++)
  {
    /* code */
    KRGB.convert_NB(i,100);
    
    delay(2);
    Serial.printf("K,%d->",i);
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
  }

  for (uint32_t i = 12000; i >= 1000; i--)
  {
    /* code */
    KRGB.convert_NB(i,100);
    Serial.printf("K,%d->",i);
    delay(2);
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
  }
  // increase the LED brightness
  for(int32_t dutyCycle = 0; dutyCycle <= 2048; dutyCycle++){   
    // changing the LED brightness with PWM
    Serial.printf("W%d\r\n",dutyCycle);
    ledcWrite(White_Ch, dutyCycle);
    delay(5);
  }

  // decrease the LED brightness
  for(int32_t dutyCycle = 2048; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    Serial.printf("W%d\r\n",dutyCycle);
    ledcWrite(White_Ch, dutyCycle);   
    delay(5);
  }
  
  
  
}