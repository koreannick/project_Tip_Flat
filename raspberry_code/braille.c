#include<stdio.h>

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
  //i = input index
  //j = output index
int i=0,j=0,sentence_length=0;
int output[1000];

int ascii_to_braille(char input[]);
void print_braille();

int main(int argc, char *argv[]){

  //input sentence
  char harryporter[123]="Mr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much.";

  ascii_to_braille(harryporter);
  print_braille();

  return 0;
}

int ascii_to_braille(char input[]){
    int i=0;
    //ascii => braile code temp
    char output_tmp;

    while(input[i]!='\0'){
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
    }
    sentence_length = j;

    return output;
}

void print_braille(){

    for(i=0;i<sentence_length;i++){
      printf("%d ",output[i]);
      if(i%10 ==0){
        printf("\n");
      }
    }

}
