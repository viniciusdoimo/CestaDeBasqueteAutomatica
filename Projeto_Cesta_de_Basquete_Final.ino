//-------------------- VARIÁVEIS -------------------------------
//Constante para o pino que irá receber o sinal do botão de zerar o placar.
#define pinZeraJogo  11

// Constante para o pino da sinaleira que irá sinalizar que o sistema está operando.
#define pinSinaleira  12

// Constante para o pino que irá  controlar o dígito da unidade.
#define pinUnidade A1

// Constante para o pino que irá  controlar o dígito da dezena.
#define pinDezena A0

// Constante para o pino que irá  receber o sinal do sensor.
#define pinSensorB A2

// Variável para controlar o tempo em que cada digito fica aceso.
#define tempPisca 1

// Variável para controlar a ativação do sensor.
bool sensorAtivado = true;

// Variável para fazer a contagem das unidade.
int contUnidade = 0;

// Variável para fazer a contagem das dezena.
int contDezena = 0;

// Vetor para Armazenar os pinos corretos que formam cada número no display.
int digDisplay[10][8] = {
  {1, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 1, 0, 1},
  {0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 0, 1, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 1},
  {0, 0, 1, 1, 0, 0, 1, 0},
  {0, 0, 0, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 0, 1, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0}
};

// Declaração Das Funções Auxiliares.

// Função responsável controlar a impressão  dos dígitos numéricos no display.
void display();

// Função
void setPinDisplay();

// -------------------- SETUP --------------------
void setup() {

  // Seta o pino da sinaleira como pino de saída, e em seguida acende a sinaleira.
  pinMode(pinSinaleira, OUTPUT);
  digitalWrite(pinSinaleira, HIGH);

  // Seta o pino do botão de zerar como pino de entrada com o resistor de 10k habilitado.
  pinMode(pinZeraJogo, INPUT_PULLUP);

  // Seta o pino do sensor como pino de entrada.
  pinMode(pinSensorB, INPUT);

  // Seta os pinos de controle do display como pinos de saída.
  pinMode(pinUnidade, OUTPUT);
  pinMode(pinDezena, OUTPUT);

  // For para setar os pinos numéricos do display como pinos de saída.
  for (int x = 3; x < 11; x++) {
    pinMode(x, OUTPUT);
  }
}

// -------------------- LOOP --------------------
void loop() {

  display();

  // Verifica se o sensor identificou algum objeto.
  if (!digitalRead(pinSensorB)) {

    /* Uma segunda verificação é feita para garantir que há objeto sobre
       o sensor e verifica se a variável de controle do sensor está ativada
       para não contabilizar mais pontos enquanto o mesmo objeto
       ainda está passando sobre o alcance do sensor. */
    if (!digitalRead(pinSensorB) && sensorAtivado) {
      contUnidade++;

      /* Quando a variável da unidade atinge 10 pontos, a unidade é zerada
         e a variável da dezena é somado mais 1. */
      if (contUnidade == 10) {
        contDezena++;
        contUnidade = 0;
      }

      /* Quando a variável da dezena atinge 10 pontos, quer dizer que a
         contagem total atingiu 100 pontos e as variáveis de contagem
         são zeradas. */
      if (contDezena == 10) {
        contDezena = 0;
        contUnidade = 0;
      }

      /* Ao passar aqui a primeira vez, a variável de controle do sensor
         é desabilitada para que não faça mais contagens até que o mesmo
         objeto passa totalmente sobre o alcance do sensor. */
      sensorAtivado = false;
    }
  }
  else {
    /* Quando o objeto termina de passar sobre o sensor, a variável de
       controle do sensor é habilitada novamente. */
    sensorAtivado = true;
  }

  // Verifica se o botão de zerar o placar foi ativado.
  if (!digitalRead(pinZeraJogo)) {
    // Zera a contagem.
    contDezena = 0;
    contUnidade = 0;
  }
}

// -------------------- Funções Auxiliares --------------------

// -------------------- setPinDisplay --------------------
void display () {
  // Seta os pinos para escrever o dígito da dezena.
  setPinDisplay(contDezena);

  //Liga o dígito da dezena.
  digitalWrite(pinDezena, 1);

  // Espera o tempo determinado.
  delay(tempPisca);

  // E desliga o dígito da dezena.
  digitalWrite(pinDezena, 0);

  // Seta os pinos para escrever o dígito da unidade.
  setPinDisplay(contUnidade);

  //Liga o dígito da unidade.
  digitalWrite(pinUnidade, 1);

  // Espera o tempo determinado.
  delay(tempPisca);

  // E desliga o dígito da unidade.
  digitalWrite(pinUnidade, 0);
}

// -------------------- setPinDisplay --------------------
void setPinDisplay(byte digito) {

  // For para setar os pinos responsáveis por formar o número no display.
  for (int x = 3; x < 11; x++) {
    digitalWrite (x, digDisplay[digito][x - 3]);
  }
}
