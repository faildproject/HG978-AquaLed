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
const int resolution_bit = 11;
const int resolution_steps = 2048;

float MorgenSonne = 1000;
float MittagsSonne = 6000;
float AbendSonne =1000;

float Mondlicht = 4000;

void writeRGB(float red, float green, float blue){
  uint32_t red_pwm = red * float(resolution_steps);
  uint32_t green_pwm = green * float(resolution_steps);
  uint32_t blue_pwm = blue * float(resolution_steps);
  //Serial.printf("R%d,G%d,B%d \r\n",red_pwm,green_pwm,blue_pwm);
  ledcWrite(Red_Ch, red_pwm);
  ledcWrite(Green_Ch, green_pwm);
  ledcWrite(Blue_Ch, blue_pwm);
}

void sunrise(uint32_t time_in_s, uint32_t steps){
  uint32_t _t_last = millis();
  uint32_t _period = (time_in_s*1000)/steps;
  uint32_t _steps_red = steps;
  uint32_t _steps_green = float(_steps_red) * 0.4;
  uint32_t _steps_blue = float(_steps_green) * 0.7;
  uint32_t _steps_white = float(_steps_blue) * 0.6;
  float red = 0.0;
  float green = 0.0;
  float blue = 0.0;
  float white = 0.0;
  
  while(millis()<(time_in_s*1000)){
    if((millis()-_t_last)>=_period){
      _t_last=millis();

      // Goto 100%
      red += 1.0/ float(_steps_red);
      
      if (red >= 0.3)
      {
        green += 1.0/ float(_steps_green);
      }

      if (green >= 0.6){
        blue += 1.0/ float(_steps_blue);
      }

      if (blue >= 0.5){
        white += 1.0/ float(_steps_white);
      }

      ledcWrite(White_Ch, white);
      writeRGB(red,green,blue);
      Serial.printf("t: %d Step: %d \t R%.2f,G%.2f,B%.2f,W%.2f \r\n",millis(),steps,red,green,blue,white);
      steps--;
      if(steps<=0){
        return;
      }
    }
  }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ledcSetup(Red_Ch, freq, resolution_bit);
  ledcSetup(Green_Ch, freq, resolution_bit);
  ledcSetup(Blue_Ch, freq, resolution_bit);
  ledcSetup(White_Ch, freq, resolution_bit);

  ledcAttachPin(RED_PIN,Red_Ch);
  ledcAttachPin(GREEN_PIN,Green_Ch);
  ledcAttachPin(BLUE_PIN,Blue_Ch);
  ledcAttachPin(WHITE_PIN,White_Ch);

  writeRGB(0,0,0);
  ledcWrite(White_Ch, 0);
}

void loop() {
    sunrise(15,2048);
    
    /*
    KRGB.convert_NB(MorgenSonne,100);
    Serial.printf("Sonnenaufgang ");
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
    delay(10000);
  
    KRGB.convert_NB(MittagsSonne,100);
    Serial.printf("Mittagssonne ");
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
    delay(10000);

    KRGB.convert_NB(AbendSonne,100);
    Serial.printf("Mittagssonne ");
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
    delay(10000);

    KRGB.convert_NB(Mondlicht,100);
    Serial.printf("Mondlicht ");
    writeRGB(KRGB.red(),KRGB.green(),KRGB.blue());
    delay(10000);
    */

}