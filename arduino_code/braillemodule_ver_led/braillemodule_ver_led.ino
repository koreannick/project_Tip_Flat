/***************************************
 * PKNU ICE 201211682 Lee Eun Yeong
 * Capstone Design - Project 'Tip_Flat'
 * character => braille
 * Rx module
 * LED Output
 * * last updated 170429 16:35
 **************************************/
char input_char, output_char, output_led, capital_led;

//set led_PinMap
const int ledpin[12] = {13,12,11,10,9,8,7,6,5,4,3,2};

//set braille code
const int braille[28]={
  0b100000, //a
  0b101000, //b
  0b110000, //c
  0b110100, //d
  0b100100, //e
  0b111000, //f
  0b111100, //g
  0b101100, //h
  0b011000, //i
  0b011100, //j
  0b100010, //k
  0b101010, //l
  0b110010, //m
  0b110110, //n
  0b100110, //o
  0b111010, //p
  0b111110, //q
  0b101110, //r
  0b011010, //s
  0b011110, //t
  0b100011, //u
  0b101011, //v
  0b011101, //w
  0b110011, //x
  0b110111, //y
  0b100111, //z
  0b000111, //eng_start
  0b000001  //capital_start
  };
//braille code mk.2
/***************************************
const int braille[74]={
  0b000000, //공백(space)
  0b100000, //a
  0b101000, //b
  0b110000, //c
  0b110100, //d
  0b100100, //e
  0b111000, //f
  0b111100, //g
  0b101100, //h
  0b011000, //i
  0b011100, //j
  0b100010, //k
  0b101010, //l
  0b110010, //m
  0b110110, //n
  0b100110, //o
  0b111010, //p
  0b111110, //q
  0b101110, //r
  0b011010, //s
  0b011110, //t
  0b100011, //u
  0b101011, //v
  0b011101, //w
  0b110011, //x
  0b110111, //y
  0b100111, //z
  0b000111, //eng_start
  0b000001,  //capital_start
  0b100000, //1
  0b101000, //2
  0b110000, //3
  0b110100, //4
  0b100100, //5
  0b111000, //6
  0b111100, //7
  0b101100, //8
  0b011000, //9
  0b011100, //0
  0b000010, //.
  0b001000, //,
  0b001001, //+
  0b000110, //-
  0b100001, //*
  0b001100, // (= ,1)
  0b001100,  // (= ,2)
  0b001110, //온점(.)
  0b000100, //콜론 (: ,1)
  0b001000, //콜론 (: ,2)
  0b000101, //세미콜론 (;, 1)
  0b001010, //세미콜론 (;, 2)
  0b111000, // 느낌표(!)
  0b100001, // 빗금(/, 1)
  0b101010, // 빗금(/, 2)
  0b001000, // 반점(,)
  0b001011, // 큰따옴표(", 1)
  0b000111, // 큰따옴표(", 2)
  0b001000, // 가운데점(.)
  0b000001, // 작은따옴표(', 1)
  0b001011, // 작은따옴표(', 2)
  0b000111, // 작은따옴표(', 3)
  0b000010, // 작은따옴표(', 4)
  0b000111, // 소괄호 ( ( )
  0b000011, // 소괄호 ( ) )
  0b000011, // 물결표(~, 1)
  0b000011, // 물결표(~,2)
  0b001011, // 중괄호({, 1)
  0b001010, // 중괄호({, 2)
  0b000101, // 중괄호(}, 3)
  0b000111, // 중괄호(}, 4)
  0b001011, // 대괄호([, 1)
  0b000010, // 대괄호([, 2)
  0b000001, // 대괄호(], 3)
  0b000111, // 대괄호(], 4)
  };
  **************************************/

void setup() {
  //Serial 통신, Rx
  Serial.begin(9600);
  //핀 할당.
  for(int i=0;i<12;i++){
    pinMode(ledpin[i],OUTPUT);
  }
}

void loop() {

  //시리얼 입력시에만 작동.
  if(Serial.available()){
    input_char = Serial.read();
    //input_char log
    Serial.println((int)input_char);

    if(input_char >=97){
      output_char=input_char-97;

      //output_char log
      Serial.println((int)output_char);

      //Ascii => braille
      output_led=braille[(int)output_char];

      for(int i=11; i>=6; i--){
       digitalWrite(ledpin[i],0);
      }
    }else{
      output_char=input_char-65;
      //output_char log
      Serial.println((int)output_char);

      //Ascii => braille
      capital_led=braille[27];
      output_led=braille[(int)output_char];

      for(int i=11; i>=6; i--){
        //output log
       Serial.println(capital_led&0b000001);
       //braille output
       digitalWrite(ledpin[i],(capital_led&0b000001));
       //output_led 오른쪽으로 한칸 쉬프트
       capital_led=capital_led>>1;
      }
    }

    for(int i=5; i>=0; i--){
      //output log
     Serial.println(output_led&0b000001);
     //braille output
     digitalWrite(ledpin[i],(output_led&0b000001));
     //output_led 오른쪽으로 한칸 쉬프트
     output_led=output_led>>1;
    }

  }
}
