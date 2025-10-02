#include <Sons.h>

void Sons::pass_conclued(float ritmo){
    int musica[]={
        NOTA_G5, NOTA_FS5, NOTA_DS5, NOTA_A4,
        NOTA_GS4, NOTA_E5, NOTA_GS5, NOTA_C6
    };
    int duracoes[]={
        t025,t025,t025,t025,
        t025,t025,t025,t05
    };
    int pausas[]={
        0,0,0,0,
        0,0,0,0
    };
    tamanho=sizeof(musica)/sizeof(int);
    base(musica,duracoes,pausas,ritmo,tamanho);
}

void Sons::pass_correct(float ritmo){
    int musica[]={
        NOTA_A4,NOTA_AS4,NOTA_B4,NOTA_C5
    };
    int duracoes[]={
        t025,t025,t025,t1
    };
    int pausas[]={
        0,0,0,0
    };
    tamanho=sizeof(musica)/sizeof(int);
    base(musica,duracoes,pausas,ritmo,tamanho);
}

void Sons::pass_incorrect(float ritmo){
    int musica [] = {
        NOTA_E4, NOTA_DS4, NOTA_D4, NOTA_CS4,
        NOTA_C4, NOTA_B3
    };
    int duracoes [] = {
        t05,t05,t05,t05,
        t2,t2
    };
    int pausas [] = {
        0,0,0,0,
        t05,0
    };
    tamanho=sizeof(musica)/sizeof(int);
    base(musica,duracoes,pausas,ritmo,tamanho);
}

void Sons::base(int musica[],int duracoes[],int pausas[],float ritmo, int tamanho){
    for(int nota=0;nota<tamanho;nota++){
        int duracaoNota = duracoes[nota]/ritmo;
        tone(pin_buzzer, musica[nota], duracaoNota);
        delay(duracaoNota);
        if(pausas[nota]!=0){
            delay(pausas[nota]);
        }
        noTone(pin_buzzer);
    }
}
