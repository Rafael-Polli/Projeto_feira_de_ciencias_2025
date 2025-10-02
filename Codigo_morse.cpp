#include <string.h>
#include <Codigo_morse.h>

void Codigo_morse::code_morse(char letra){
    for(long i=0;i<strlen(caracteres);i++){//determina a posiçao do caractere
        if(letra==caracteres[i]){
            pos_caractere=i;
        }
    }
    for(int i=0;i<strlen(tradutor[pos_caractere]);i++){//lê os caracteres
        char tempo=tradutor[pos_caractere][i];
        if(tempo=='.'){
            tone(pin_buzzer,frequencia,d_curta);
            delay(pausa+d_curta);
        }
        if(tempo=='-'){
            tone(pin_buzzer,frequencia,d_longa);
            delay(pausa+d_longa);
        }
    }
}
