#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <LiquidCrystal_I2C.h>

#define btnstate1 5
#define btnstate2 6
#define btnstate3 7
#define btnstate4 4

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//matrix 객체 생성
Adafruit_8x16matrix matrix1 = Adafruit_8x16matrix();
Adafruit_8x16matrix matrix2 = Adafruit_8x16matrix();
Adafruit_8x16matrix matrix3 = Adafruit_8x16matrix();
Adafruit_8x16matrix matrix4 = Adafruit_8x16matrix();
Adafruit_8x16matrix matrix5 = Adafruit_8x16matrix();
Adafruit_8x16matrix matrix6 = Adafruit_8x16matrix();

//점자 코드
const int braille[59]={
  0b000111, //eng_start                   0
  0b000001,  //capital_start
  0b010111, //number_start
  0b000000, //공백(space) ascii :: 32
  0b100000, //a           ascii :: 97
  0b101000, //b
  0b110000, //c
  0b110100, //d
  0b100100, //e
  0b111000, //f
  0b111100, //g                               10
  0b101100, //h
  0b011000, //i
  0b011100, //j
  0b100010, //k
  0b101010, //l
  0b110010, //m
  0b110110, //n
  0b100110, //o
  0b111010, //p
  0b111110, //q                                   20
  0b101110, //r
  0b011010, //s
  0b011110, //t
  0b100011, //u
  0b101011, //v
  0b011101, //w
  0b110011, //x
  0b110111, //y
  0b100111, //z           ascii ::122
  0b011100, //0           ascii ::48                30
  0b100000, //1
  0b101000, //2
  0b110000, //3
  0b110100, //4
  0b100100, //5
  0b111000, //6
  0b111100, //7
  0b101100, //8
  0b011000, //9             ascii ::57
  0b111000, // 느낌표(!)             ascii ::33        40
  0b000001, // 작은따옴표(', 1)             ascii ::39
  0b001011, // 작은따옴표(', 2)             ascii ::39
  0b000111, // 작은따옴표(', 3)             ascii ::39
  0b000010, // 작은따옴표(', 4)             ascii ::39
  0b000111, // 소괄호 ( ( )             ascii ::40
  0b000011, // 소괄호 ( ) )             ascii ::41
  0b001000, // 반점(,)             ascii ::44
  0b001110, //온점(.)             ascii ::46
  0b100001, // 빗금(/, 1)             ascii ::47
  0b101010, // 빗금(/, 2)             ascii ::47 50
  0b000100, //콜론 (: ,1)             ascii ::58
  0b001000, //콜론 (: ,2)             ascii ::58
  0b000101, //세미콜론 (;, 1)             ascii ::59
  0b001010, //세미콜론 (;, 2)             ascii ::59
  0b001011, // 큰따옴표(", 1)             ascii ::66
  0b000111, // 큰따옴표(", 2)             ascii ::66
  0b000011, // 물결표(~, 1)             ascii ::126
  0b000011 // 물결표(~,2)             ascii ::126
};
int i=0,j=0,sentence_length=0;

//인풋
char input_string[96]="Mr and Mrs Dursley of number four Privet Drive were proud to say that they were perfectly normal";
//점자출력
uint8_t output[96];
uint8_t output1[16];
uint8_t output2[16];
uint8_t output3[16];
uint8_t output4[16];
uint8_t output5[16];
uint8_t output6[16];

//대기화면
static const uint8_t PROGMEM
smile_bmp[] =
{ B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111 },
neutral_bmp[] =
{ B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};


//점역 함수
void ascii_to_braille(char input1[]);

//이북
void ebook(char input[]);

//날씨정보 출력함수
void weatherinfo(char input2[]);
//뉴스 헤드라인 출력함수
void NewsHeadLine(char input3[]);
//matrix 출력 함수
void output_matrix();
//대기화면
void waiting_mode();

void setup() {
  
  pinMode(btnstate1,INPUT);
  pinMode(btnstate2,INPUT);
  pinMode(btnstate3,INPUT);
  pinMode(btnstate4,INPUT);
  
  Serial.begin(9600);
  //칩 주소값 입력
  matrix1.begin(0x70); 
  matrix2.begin(0x71); 
  matrix3.begin(0x72); 
  matrix4.begin(0x73); 
  matrix5.begin(0x74); 
  matrix6.begin(0x75);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Hello,");
  lcd.setCursor(0,1);
  lcd.print("I'm Tip_Flat");
  waiting_mode();
  
}

void loop() {
  
  if(digitalRead(btnstate4) == LOW){
    
    Serial.println("#################waiting#############");
  waiting_mode();
  }
  
  if(digitalRead(btnstate1) == LOW){
    
    Serial.println("#################ebook#############");
    for(i=0; i<96; i++){
      output[i]=0;
    }
    //인풋 점역
    char input_string[96]="Mr and Mrs Dursley of number four Privet Drive were proud to say that they were perfectly normal";
    
    ebook(input_string);
    ouput_matrix();
    for(i=0; i<96; i++){
      Serial.print(i);
      Serial.print("  ::  ");
      Serial.println(output[i]);    
    }
    Serial.println("#################ebook#############");
    
  }
  if(digitalRead(btnstate2) == LOW){
    
    Serial.println("#################weather#############");
    for(i=0; i<96; i++){
      output[i]=0;
    }
    Serial.println("#################weather#############");
    
    //날씨정보
    char input_string[96]="2016 06 28 today weather        very sunny      2016 06 28 today weather        very sunny      ";
    weatherinfo(input_string);
    ouput_matrix();  
    for(i=0; i<96; i++){
      Serial.print(i);
      Serial.print("  ::  ");
      Serial.println(output[i]);    
    }
    
  }
  if(digitalRead(btnstate3) == LOW){
    
    Serial.println("#################NewsHeadLine#############");

    for(i=0; i<96; i++){
      output[i]=0;
    }
    char input_string[96]="hyundai public sector union members draw criticisms     car without sideview mirrors to hit road";
    //뉴스정보
    NewsHeadLine(input_string);
    ouput_matrix();
    for(i=0; i<96; i++){
      Serial.print(i);
      Serial.print("  ::  ");
      Serial.println(output[i]);    
    }
    Serial.println("#################NewsHeadLine#############");
    
  }
}

void ouput_matrix(){
  //칩 주소값 입력
  matrix1.begin(0x70); 
  matrix2.begin(0x71); 
  matrix3.begin(0x72); 
  matrix4.begin(0x73); 
  matrix5.begin(0x74); 
  matrix6.begin(0x75);
  //점자 디스플레이초기화
  matrix1.clear();
  //점자 패턴 입력
  matrix1.drawBitmap(0, 0, output1, 8, 16, LED_ON);
  //점자 출력
  matrix1.writeDisplay();
  //점자 디스플레이초기화
  matrix2.clear();
  //점자 패턴 입력
  matrix2.drawBitmap(0, 0, output2, 8, 16, LED_ON);
  //점자 출력
  matrix2.writeDisplay();
  //점자 디스플레이초기화
  matrix3.clear();
  //점자 패턴 입력
  matrix3.drawBitmap(0, 0, output3, 8, 16, LED_ON);
  //점자 출력
  matrix3.writeDisplay();
  //점자 디스플레이초기화
  matrix4.clear();
  //점자 패턴 입력
  matrix4.drawBitmap(0, 0, output4, 8, 16, LED_ON);
  //점자 출력
  matrix4.writeDisplay();
  //점자 디스플레이초기화
  matrix5.clear();
  //점자 패턴 입력
  matrix5.drawBitmap(0, 0, output5, 8, 16, LED_ON);
  //점자 출력
  matrix5.writeDisplay();
  //점자 디스플레이초기화
  matrix6.clear();
  //점자 패턴 입력
  matrix6.drawBitmap(0, 0, output6, 8, 16, LED_ON);
  //점자 출력
  matrix6.writeDisplay();
}

//점역 함수 본문
void ascii_to_braille(char input[]){
  
    int i=0;
    int j=0;
    //ascii => braile code temp
    sentence_length=0;
    char output_tmp;
    //점자 없을때까지
    while(input[i]!='\0' || sentence_length<=96){

      //소문자
      if(input[i] >= 97 && input[i] <= 122){
        // output_tmp = harryporter[i] - 96;
        output_tmp = input[i]-93;
        output[j] = braille[(int)output_tmp];
        j++;
      }
      //대문자
      else if(input[i] >= 65 && input[i] <= 90){
        // output_tmp = harryporter[i] - 64;
        output_tmp = input[i]-61;
        output[j] = braille[1];
        j++;
        output[j] = braille[(int)output_tmp];
        j++;
      }
      //숫자
      else if(input[i] >= 48 && input[i] <= 57){
        // output_tmp = harryporter[i] - 19;
        output_tmp = input[i] - 18;
        output[j] = braille[(int)output_tmp];
        j++;
      }else{
          if(input[i] == '!'){
            output[j] = braille[40];
            j++;
          }else if(input[i] == 32){
            output[j] = braille[3];
            j++;
          }else if(input[i] == 39){
            output[j] = braille[41];
            j++;
            output[j] = braille[42];
            j++;
          }else if(input[i] == 40){
            output[j] = braille[45];
            j++;
          }else if(input[i] == 41){
            output[j] = braille[46];
            j++;
          }else if(input[i] == 44){
            output[j] = braille[47];
            j++;
          }else if(input[i] == 46){
            output[j] = braille[48];
            j++;
          }else if(input[i] == 47){
            output[j] = braille[49];
            j++;
            output[j] = braille[50];
            j++;
          }else if(input[i] == 58){
            output[j] = braille[51];
            j++;
            output[j] = braille[52];
            j++;
          }else if(input[i] == 59){
            output[j] = braille[53];
            j++;
            output[j] = braille[54];
            j++;
          }else if(input[i] == 66){
            output[j] = braille[55];
            j++;
            output[j] = braille[56];
            j++;
          }else if(input[i] == 126){
            output[j] = braille[57];
            j++;
            output[j] = braille[58];
            j++;
          }

      }
      i++;
    sentence_length = j;
    }

    for(i=0; i<96; i++){
      if(i<16){
        output1[i]=output[i];
      }else if(i>=16 && i<32){
        output2[i-16] = output[i];
      }else if(i>=32 && i<48){
        output3[i-32] = output[i];
      }else if(i>=48 && i<64){
        output4[i-48] = output[i];
      }else if(i>=64 && i<80){
        output5[i-64] = output[i];
      }else if(i>=80 && i<96){
        output6[i-80] = output[i];
      }
    }
}
void ebook(char input1[]){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("E-Book Mode");
    lcd.setCursor(0,1);
    lcd.print("Harry Porter");
    ascii_to_braille(input1);
  
}
//날씨정보 출력함수
void weatherinfo(char input2[]){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("2017 06 28");
  lcd.setCursor(0,1);
  lcd.print("Very Sunny");
  ascii_to_braille(input2);
    
}
//뉴스 헤드라인 출력함수
void NewsHeadLine(char input3[]){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("News HeadLine,");
  lcd.setCursor(0,1);
  lcd.print("Popular News");
  ascii_to_braille(input3);
}

void waiting_mode(){
  while(digitalRead(btnstate1)!=LOW && digitalRead(btnstate2)!=LOW && digitalRead(btnstate3)!=LOW){
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello,");
  lcd.setCursor(0,1);
  lcd.print("I'm Tip_Flat");
    
  matrix1.clear();
  matrix2.clear();
  matrix3.clear();
  matrix4.clear();
  matrix5.clear();
  matrix6.clear();
  matrix1.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix1.writeDisplay();
  matrix2.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix2.writeDisplay();
  matrix3.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix3.writeDisplay();
  matrix4.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix4.writeDisplay();
  matrix5.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix5.writeDisplay();
  matrix6.drawBitmap(0, 0, smile_bmp, 8, 16, LED_ON);
  matrix6.writeDisplay();
  delay(1000);
  
  matrix1.clear();
  matrix2.clear();
  matrix3.clear();
  matrix4.clear();
  matrix5.clear();
  matrix6.clear();
  matrix1.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix1.writeDisplay();
  matrix2.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix2.writeDisplay();
  matrix3.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix3.writeDisplay();
  matrix4.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix4.writeDisplay();
  matrix5.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix5.writeDisplay();
  matrix6.drawBitmap(0, 0, neutral_bmp, 8, 16, LED_ON);
  matrix6.writeDisplay();
  delay(100);
  }
}

