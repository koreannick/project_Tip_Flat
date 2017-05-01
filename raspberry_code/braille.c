#include<stdio.h>

int main(int argc, char *argv[]){

  const int braille[75]={
    0b000111, //eng_start
    0b000001,  //capital_start
    0b010111, //number_start
    0b000000, //공백(space) ascii :: 32    0
    0b100000, //a           ascii :: 97
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
    0b100111, //z           ascii ::122
    0b011100, //0           ascii ::48
    0b100000, //1
    0b101000, //2
    0b110000, //3
    0b110100, //4
    0b100100, //5
    0b111000, //6
    0b111100, //7
    0b101100, //8
    0b011000, //9             ascii ::57
    0b111000, // 느낌표(!)             ascii ::33
    0b000001, // 작은따옴표(', 1)             ascii ::39
    0b001011, // 작은따옴표(', 2)             ascii ::39
    0b000111, // 작은따옴표(', 3)             ascii ::39
    0b000010, // 작은따옴표(', 4)             ascii ::39
    0b000111, // 소괄호 ( ( )             ascii ::40
    0b000011, // 소괄호 ( ) )             ascii ::41
    0b001000, // 반점(,)             ascii ::44
    0b001110, //온점(.)             ascii ::46
    0b100001, // 빗금(/, 1)             ascii ::47
    0b101010, // 빗금(/, 2)             ascii ::47
    0b000100, //콜론 (: ,1)             ascii ::58
    0b001000, //콜론 (: ,2)             ascii ::58
    0b000101, //세미콜론 (;, 1)             ascii ::59
    0b001010, //세미콜론 (;, 2)             ascii ::59
    0b001011, // 큰따옴표(", 1)             ascii ::66
    0b000111, // 큰따옴표(", 2)             ascii ::66
    0b000011, // 물결표(~, 1)             ascii ::126
    0b000011 // 물결표(~,2)             ascii ::126
  };

  char harryporter[123]="Mr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much.";
  char output_tmp;
  int output[1000],i=0;

  while(harryporter[i]!='\0'){
    //소문자
    if(harryporter[i] >= 97 && harryporter[i] <= 122){
      // output_tmp = harryporter[i] - 96;
      output[i] = braille[(int)output_tmp];
      i++;
    }
    //대문자
    else if(harryporter[i] >= 65 && harryporter[i] <= 90){
      // output_tmp = harryporter[i] - 64;
      output[i] = braille[0];
      i++;
      output[i] = braille[(int)output_tmp];
    }
    //숫자
    else if(harryporter[i] >= 48 && harryporter[i] <= 57){
      // output_tmp = harryporter[i] - 19;
      output[i] = braille[(int)output_tmp];
    }else{

    }


  }

  return 0;
}
