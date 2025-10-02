#ifndef CODIGO_MORSE_H_INCLUDED
#define CODIGO_MORSE_H_INCLUDED

#include <Arduino.h>

class Codigo_morse{
public:
    Codigo_morse(int pin_buzzer):pin_buzzer(pin_buzzer){};
    void code_morse(char letra);

private:
    const char* caracteres="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    const char* tradutor[36]={".-", "-...", "-.-.", "-..", ".", "..-.","--.","....","..",".---","-.-",".-..",
                 "--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",
".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};

    int pos_caractere;
    int pin_buzzer;
    int d_longa=300;
    int d_curta=100;
    int frequencia = 800;
    int pausa = 150;
};

#endif
