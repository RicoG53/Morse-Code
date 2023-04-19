/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
char getCode(char c);
void dit();
void dah();
void letter();
void space();
void play(const char* input);
//End of Auto generated function prototypes by Atmel Studio

// Rico Garcia
// Timer Interrupts by Rico Garcia
// RBT211

// This application is designed to be both a morse code encoder and decoder. A morse code signal is sent from the UNO using an LED
// and recieved by the MEGA using a photoresistor. 
// This code and design was inspired by a gentleman by the name of Shjin from Arduino's Project Hub which can be found at
// https://create.arduino.cc/projecthub/shjin/adaptive-led-morse-code-decoder-and-timer-interrupt-8d18a7?ref=tag&ref_id=interrupt&offset=3
// alterations and changes were made both to the code and to the design so as to avoid plagiarising Shjin's work. 

#define DEBUG

const int UNIT_LENGTH = 100;
const int DIT_LENGTH = UNIT_LENGTH * 1;
const int DAH_LENGTH = UNIT_LENGTH * 3;
const int ELEMENT_GAP = UNIT_LENGTH * 1;
const int SHORT_GAP = UNIT_LENGTH * 2;
const int MEDIUM_GAP = UNIT_LENGTH * 4;

// here we provide a translation key so the application knows how to translate our message into morse code 
const char* codeset[]={
  /* ! */ "-.-.--",
  /* " */ ".-..-.",
  /* # */ NULL,
  /* $ */ "...-..-",
  /* % */ NULL,
  /* & */ ".-...",
  /* ' */ ".----.",
  /* ( */ "-.--.",
  /* ) */ "-.--.-",
  /* * */ NULL,
  /* + */ ".-.-.",
  /* , */ "--..--",
  /* - */ "-....-",
  /* . */ ".-.-.-",
  /* / */ "-..-.",
  /* 0 */ "-----",
  /* 1 */ ".----",
  /* 2 */ "..---",
  /* 3 */ "...--",
  /* 4 */ "....-",
  /* 5 */ ".....",
  /* 6 */ "-....",
  /* 7 */ "--...",
  /* 8 */ "---..",
  /* 9 */ "----.",
  /* : */ "---...",
  /* ; */ "-.-.-.",
  /* < */ NULL,
  /* = */ "-...-",
  /* > */ NULL,
  /* ? */ "..--..",
  /* @ */ ".--.-.",
  /* A */ ".-",
  /* B */ "-...",
  /* C */ "-.-.",
  /* D */ "-..",
  /* E */ ".",
  /* F */ "..-.",
  /* G */ "--.",
  /* H */ "....",
  /* I */ "..",
  /* J */ ".---",
  /* K */ "-.-",
  /* L */ ".-..",
  /* M */ "--",
  /* N */ "-.",
  /* O */ "---",
  /* P */ ".--.",
  /* Q */ "--.-",
  /* R */ ".-.",
  /* S */ "...",
  /* T */ "-",
  /* U */ "..-",
  /* V */ "...-",
  /* W */ ".--",
  /* X */ "-..-",
  /* Y */ "-.--",
  /* Z */ "--..",
  /* [ */ NULL,
  /* \ */ NULL,
  /* ] */ NULL,
  /* ^ */ NULL,
  /* _ */ "..--.-"
 };

const char* getCode(char c){
// for uppercase letters
  if ('a' <= c && c <= 'z'){
    c = c - ('a' - 'A');
  }

  if ('!' <= c && c <= '_'){
    return codeset[c - '!'];
  }

  return NULL;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(19200);
}

void dit(){
#ifdef DEBUG
  Serial.print(".");
#endif
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(ELEMENT_GAP);
}

void dah(){
#ifdef DEBUG
  Serial.print("-");
#endif
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(ELEMENT_GAP);
}

void letter()
{
#ifdef DEBUG
  Serial.print(" ");
#endif
  delay(SHORT_GAP);
}

void space(){
#ifdef DEBUG
  Serial.println();
#endif
  delay(MEDIUM_GAP);
}

void play(const char * input){
  int inputLength = strlen(input);

  for (int i = 0; i < inputLength; i++){
    char c = input[i];

    if (c == ' ') {
      space();
    }
    else {
      const char* code = getCode(c);
      
      if (code == NULL){
        continue;
      }

      int codeLength = strlen(code);
  
      for (int j = 0; j < codeLength; j++){
        if (code[j] == '.'){
          dit();  
        }
        else if (code[j] == '-'){
          dah();
        }
      }     
      letter();  
    }
  }
}

// this is where we input our message to be translated into morse code
const char* text = "my name is rico";

// message plays on repeat
void loop(){
  play(text);
}
