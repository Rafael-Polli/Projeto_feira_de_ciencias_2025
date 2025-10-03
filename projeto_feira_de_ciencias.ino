// C++ code
// Programa: Fechadura Eletrônica = 100%
#include <Sons.h>
#include <Codigo_morce.h>
#include <Keypad.h>
#include <Servo.h>

Servo servo1;
static char password[4];

#define ledVermelho  2
#define ledVerde  3
#define Pin_Servo  13
#define pin_buzzer 4

Sons s1(pin_buzzer);
Codigo_morce c1(pin_buzzer);

int prazo=5000;
int t_pisca_led=1500;

unsigned long tempo=0;
unsigned long t_led=0;
int posicao=0;
bool continuar=false;
bool condicao_pisca_led=true;
bool contar=false;

const byte N_Lin=4;
const byte N_Col=4;

/* Construção da matriz de caracteres */
char m_tec[N_Lin][N_Col]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

/* Pinos utilizados pelas linhas e colunas do teclado*/
byte Pin_Lin[N_Lin]={12,11,10,9};
byte Pin_Col[N_Col]={8,7,6,5};
Keypad tec=Keypad(makeKeymap(m_tec),Pin_Lin,Pin_Col,N_Lin,N_Col);


void setup(){
/* Configura os pinos dos LEDs como saída */
  pinMode(ledVermelho,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  servo1.attach(Pin_Servo);
  Serial.begin(9600);
  Serial.println("Inicie com #...");
  Serial.println();
  trancada();
  randomSeed(analogRead(A0));
}

void loop(){
    tempo=millis();
    pisca_led(condicao_pisca_led);
    
    if(tec.getKey()=='#'){
        continuar=true;
        pass_random();
        iniciar();
        
        Serial.println("Tente Novamente");
        Serial.println("Inicie com #...");
        Serial.println();
    }
    delay(100);
}

void verific_teclas(char key,bool clicado){
    if(key == '*'){
        posicao = 0;
        clicado=false;
        continuar=false;
      trancada();
        //
        Serial.print(key);
        Serial.println();
    }
    if(key == '*' || key == '#'){
      clicado=false;
    } 
    if((clicado && key != password[posicao]) && contar){
      posicao=0;
        clicado=false;
        continuar=false;
        contar=false;
        tempo=millis();
        s1.pass_incorrect(2);
        //
        Serial.print(key);
        Serial.print("  errado");
        Serial.println();
    }
    if((clicado && key == password[posicao]) && contar){
        posicao ++;
        clicado=false;
        if(posicao<4){
          c1.code_morce(password[posicao]);
          }
        tempo=millis();
        //
        Serial.print(key);
        Serial.print("  certo");
        Serial.println();
  }
  if (posicao==(sizeof(password)/sizeof(char))) {
      destrancada();
        contar=false;
        tempo=millis();
    }
}

void iniciar(){
    contar=true;
    bool clicado=false;
    Serial.println("Iniciado");
    c1.code_morce(password[posicao]);
    while(continuar){
        char key=tec.getKey();
        verific_tempo(prazo,contar);
        pisca_led(condicao_pisca_led);
        if(key){
          clicado=true;
            Serial.print("digitado: ");
          verific_teclas(key,clicado);                        
        }
        delay(100);
    }
}

void verific_tempo(int prazo,bool contar){
  if((millis() - tempo >= prazo) && contar){
        posicao=0;
        tempo=millis();
        continuar=false;
        Serial.println("Tempo Esgotado");
        s1.pass_incorrect(2);
    }
}

void pass_random(){
  char caracteres[]={'0','1','2','3','4','5','6','7',
                   '8','9','A','B','C','D'};
  int quantidade=4;
    long pos_aleatoria[4];
  long pos_anterior[4];
  
  pos_anterior[0]= -1;
    unsigned int i=0;
    bool continuar=true;
    while(continuar){
        pos_aleatoria[i]=random(sizeof(caracteres)/sizeof(char));
        if(pos_aleatoria[i] != pos_anterior[-1+i]){ 
          pos_anterior[i]=pos_aleatoria[i];
          i++;
            continuar=true;
        }
        if(i>(quantidade-1)){
          continuar=false;
        }
    }
    Serial.print("Senha Aleatoria: ");
    for(int x=0;x<quantidade;x++){        
        Serial.print(caracteres[pos_aleatoria[x]]);
        password[x]=caracteres[pos_aleatoria[x]];
  }
    Serial.println();
}

void trancada(){
  condicao_pisca_led=true;
  digitalWrite(ledVerde,LOW);
  servo1.write(130);
  Serial.print("TRANCADA ");
}

void destrancada(){  
  digitalWrite(ledVerde,HIGH);
  digitalWrite(ledVermelho,LOW);
  condicao_pisca_led=false;
  servo1.write(160);
  s1.pass_conclued(1.5);
  //s1.pass_correct(1);
  Serial.println("ABERTA");
}

void pisca_led(bool condicao_pisca_led){
  if((millis()-t_led <= t_pisca_led) && condicao_pisca_led){
    digitalWrite(ledVermelho,HIGH);
  }
    if((millis()-t_led > t_pisca_led) && condicao_pisca_led){
      digitalWrite(ledVermelho,LOW);    
  }
    if(millis()-t_led >= t_pisca_led*2){
      t_led=millis();
    }
}
