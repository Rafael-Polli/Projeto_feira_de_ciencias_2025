#ifndef SONS_H_INCLUDED
#define SONS_H_INCLUDED

#include <Notas.h>
#include <Arduino.h>

class Sons{
public:
    Sons(int pin_buzzer):pin_buzzer(pin_buzzer){
        digitalWrite(pin_buzzer, OUTPUT);
    };
    void pass_conclued(float);
    void pass_correct(float);
    void pass_incorrect(float);

private:
    int ritmo;
    int pin_buzzer;
    int tamanho;

    void base(int[],int[],int[],float,int);
};

#endif
