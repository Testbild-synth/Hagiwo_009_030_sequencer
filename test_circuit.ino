
//Encoder setting
#define  ENCODER_OPTIMIZE_INTERRUPTS //countermeasure of encoder noise
#include <Encoder.h>

//Oled setting
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

#define OLED_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define ENCODER_PIN1 2
#define ENCODER_PIN2  3
#define ENCODER_SW_PIN 12
#define CLK_PIN 13
#define ENCODER_COUNT_PER_ROTATION 4

#define OUT_CH1 5
#define OUT_CH2 6
#define OUT_CH3 7
#define OUT_CH4 8
#define OUT_CH5 9
#define OUT_CH6 10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//rotery encoder
Encoder myEnc(ENCODER_PIN1, ENCODER_PIN2);//use 3pin 2pin
int oldPosition  = -999;
int newPosition = -999;
int i = 0;

//push button
bool sw = 0;//push button
bool old_sw;//countermeasure of sw chattering
unsigned long sw_timer = 0;//countermeasure of sw chattering

bool disp_reflesh = 1;//0=not reflesh display , 1= reflesh display , countermeasure of display reflesh bussy
int clk_val = 0;

void setup() {
 // OLED setting
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.clearDisplay();
 display.setCursor(50, 50);
 display.print("Hello");
 display.display();
 //pin mode setting
 pinMode(ENCODER_SW_PIN, INPUT_PULLUP); //BUTTON
 pinMode(CLK_PIN, INPUT);
 pinMode(OUT_CH1, OUTPUT); //CH1
 pinMode(OUT_CH2, OUTPUT); //CH2
 pinMode(OUT_CH3, OUTPUT); //CH3
 pinMode(OUT_CH4, OUTPUT); //CH4
 pinMode(OUT_CH5, OUTPUT); //CH5
 pinMode(OUT_CH6, OUTPUT); //CH6
 Serial.begin(115200);
}


void loop() {
 oldPosition = newPosition;
 //-----------------Rotery encoder read----------------------
 newPosition = myEnc.read()/ENCODER_COUNT_PER_ROTATION;

 if ( newPosition   < oldPosition ) {//turn left
   Serial.println("left");
   oldPosition = newPosition;
 }
 if (digitalRead(CLK_PIN)!= clk_val){
  clk_val = digitalRead(CLK_PIN);
  Serial.println("CLOCK");
 }
 
 else if ( newPosition    > oldPosition ) {//turn right
   Serial.println("right");
 }
 sw = 1;
 if ((digitalRead(ENCODER_SW_PIN) == 0 ) && ( sw_timer + 300 <= millis() )) {
   sw_timer = millis();
   Serial.println("click");
   sw = 0;
 }
 if(millis()%1000 < 500){
  digitalWrite(OUT_CH1,HIGH);
  digitalWrite(OUT_CH2,HIGH);
  digitalWrite(OUT_CH3,HIGH);
  digitalWrite(OUT_CH4,HIGH);
  digitalWrite(OUT_CH5,HIGH);
  digitalWrite(OUT_CH6,HIGH);
 }
 else{
  digitalWrite(OUT_CH1,LOW);
  digitalWrite(OUT_CH2,LOW);
  digitalWrite(OUT_CH3,LOW);
  digitalWrite(OUT_CH4,LOW);
  digitalWrite(OUT_CH5,LOW);
  digitalWrite(OUT_CH6,LOW);
 }
}
 

 
