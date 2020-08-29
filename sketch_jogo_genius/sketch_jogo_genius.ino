/*******************************************************************************************
*                       Projeto Jogo Genius                                                *                            
*       Matriais: 4 Led's 5mm, 4 Resisitor 10K, 4 Resistor 220 ohm e 4 Push Boutton        *                                                          
*                     Autor: Jean Theodoro                                                 *     
********************************************************************************************/


int sequencia[20];
int tons[4] = {262, 292, 230, 245};
int leds[4] = {A0, A1, A2, A3};
int botoes[4] = {7, 6, 5, 4};
int rodada = 0;
int passo = 0;
bool game_over = false;


void setup() {
  // put your setup code here, to run once:

  pinMode(A0, OUTPUT); //liga o led red ou vermelho
  pinMode(A1, OUTPUT); //liga o led blue ou azul
  pinMode(A2, OUTPUT); //liga o led green ou verde
  pinMode(A3, OUTPUT); //liga o led yellow ou amarelo

  pinMode(3, OUTPUT); //liga o som

  //pinos de entrada ou de leitura
  pinMode(7, INPUT); //pino que le o botao vermelho
  pinMode(6, INPUT); //pino que le o botao azul
  pinMode(5, INPUT); //pino que le o botao verde
  pinMode(4, INPUT); //pino que le o botao amarelo

  //inicializando os dados dos pinos de saida
  digitalWrite(3, LOW);
  for(int z = 0; z < 3; z++)
      leds[z];     

  Serial.begin(9600);
}



void loop() {

  proximarodada();
  reproduzirsequencia();
  sequenciaJogador();
  if(game_over == true) {
    sequencia[20] = {};
    rodada = 0;
    passo = 0;
    game_over = false;
  }
  delay(1000);
}

void proximarodada() {

  randomSeed(analogRead(0));
  int sorteio = random(4);
  sequencia[rodada] = sorteio;
  rodada = rodada + 1;
  Serial.println(sorteio);
}

void reproduzirsequencia() {
  int cont;
  for ( cont = 0 ; cont < rodada; cont++) {
    
    digitalWrite(leds[sequencia[cont]], HIGH);
    tone(3, tons[sequencia[cont]]);
    delay(500);
    digitalWrite(leds[sequencia[cont]], LOW);
    noTone(3);
  }
}

void sequenciaJogador() {

  int bntClick = 0;

  for (int i = 0; i < rodada; i++) {
    bool jogada = false;

    while (!jogada) {
      for (int j = 0; j <= 3; j++) {
        if (digitalRead(botoes[j]) == HIGH) {
          bntClick = j;
          tone(3, tons[j]);
          digitalWrite(leds[j], HIGH);
          delay(300);
          digitalWrite(leds[j], LOW);
          noTone(3);
          jogada = true;
        }
      }
    }
    if (sequencia[passo] != bntClick) {
      for (int k = 0; k <= 3; k++) {
        tone(3, 70);
        digitalWrite(leds[k], HIGH);
        delay(300);
        digitalWrite(leds[k], LOW);
        noTone(3);
      }
      game_over = true;
      break;
    }
    passo = passo + 1;
  }
  passo = 0;
}
