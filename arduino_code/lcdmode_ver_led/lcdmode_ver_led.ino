/***************************************
 * PKNU ICE 201211682 Lee Eun Yeong
 * Capstone Design - Project 'Tip_Flat'
 * Tx module
 * LCD Output
 * last updated 170429 16:35
 **************************************/
#include <LiquidCrystal.h>
//set_lcd pin
LiquidCrystal lcd(7,8,9,10,11,12);
//set btn pin
const int btn_pin = 4;
//init input_char value
char input_char='a';
//init btn_state value
int btn_state=0;

void setup() {
  //핀할당
  pinMode(btn_pin,INPUT);
  lcd.begin(32, 4);
  lcd.print("Input Character");
  //Serial 통신, Tx
  Serial.begin(9600);
}

void loop() {
  //read btn_state
  btn_state = digitalRead(btn_pin);

  if(btn_state == LOW){
    //대문자 Z 다음에 소문자 a
    if(input_char==91){
      input_char = 97;
    }
    //소문자 z 다음에 대문자 A
    if(input_char >= 122){
      input_char = 65;
    }
    else{
      //글자 ++
      input_char++;
    }
    //input_char Tx
    Serial.print(input_char);
  }
  
  lcd.setCursor(0, 1);
  lcd.print(input_char);
  delay(100);
} 
