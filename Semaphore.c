
/*Inicialmente, define-se o tipo das variáveis de contagem. Que serão incrementadas dentro da rotina de contagem para
utilizar definicoes de tempo em diversas áreas do código. Define-se todas as variáves de contagem como volatile unsigned int
dado que esse tipo de variavel possui o qualificador de um dado variavel. Como os contadores são atualizados a cada rotina do temporizador
é prudente utilizar os volatiles*/
volatile unsigned int cont=0;
volatile unsigned int contAux=0;
volatile unsigned int cont2=0;

/*Define-se também o tipo das variáves de leitura das portas lógicas*/
int readAnalogPin= A0;
int readAnalogOut=0;
unsigned int YellowLedVeic=0;
const byte interruptPin = 2;
int pushButton = 6;
const byte changeLedPin0 = 4;
const byte changeLedPin1 = 5;

/*Aqui, define-se as variáveis auxiliares do programa. Essas variáveis serão utilizadas para avaliar os estados do sistema! Inicialmente,
define-se estado 2 para a variável verify apenas para inicialização do sistema, já que a variavel nunca receberá o mesmo valor futuramente.*/
int actualState=0;
int lastState=0;
int verify=2;


/*A função a seguir verifica se houveram mudanças no estado do sistema no quesito dia e noite. A função recebe dois parâmetros: o estado
atual do sistema e o estado anterior à chamada da função. Se o estado atual é igual ao estado anterior, a funcao retorna 0, já se o estado anterior
é diferente do estado atual, a função retorna 1. As saídas dessa função serão tratadas na MAIN do programa. */
int verifyChanges(int actualState, int lastState){
  if (actualState == lastState){
  	return 0;
  }
  else{
  	return 1;
  	}
}

/*Aqui, define-se uma função que para dado valor de entrada, mostra-se o valor correspondente nos display's 7 segmentos*/

void display7Seg(int value){
  if (value == 9){
    digitalWrite(11, HIGH);
  	digitalWrite(10, LOW);
  	digitalWrite(9, LOW);
  	digitalWrite(8, HIGH);

  }
    if (value == 8){
    digitalWrite(11, HIGH);
  	digitalWrite(10, LOW);
  	digitalWrite(9, LOW);
  	digitalWrite(8, LOW);

  }
    if (value == 7){
    digitalWrite(11, LOW);
  	digitalWrite(10, HIGH);
  	digitalWrite(9, HIGH);
  	digitalWrite(8, HIGH);

  }
    if (value == 6){
    digitalWrite(11, LOW);
  	digitalWrite(10, HIGH);
  	digitalWrite(9, HIGH);
  	digitalWrite(8, LOW);

  }
    if (value == 5){
    digitalWrite(11, LOW);
  	digitalWrite(10, HIGH);
  	digitalWrite(9, LOW);
  	digitalWrite(8, HIGH);

  }
    if (value == 4){
    digitalWrite(11, LOW);
  	digitalWrite(10, HIGH);
  	digitalWrite(9, LOW);
  	digitalWrite(8, LOW);

  }
    if (value == 3){
    digitalWrite(11, LOW);
  	digitalWrite(10, LOW);
  	digitalWrite(9, HIGH);
  	digitalWrite(8, HIGH);

  }
    if (value == 2){
    digitalWrite(11, LOW);
  	digitalWrite(10, LOW);
  	digitalWrite(9, HIGH);
  	digitalWrite(8, LOW);

  }
    if (value == 1){
    digitalWrite(11, LOW);
  	digitalWrite(10, LOW);
  	digitalWrite(9, LOW);
  	digitalWrite(8, HIGH);
  }
     if (value == 0){
    digitalWrite(11, LOW);
  	digitalWrite(10, LOW);
  	digitalWrite(9, LOW);
  	digitalWrite(8, LOW);
  }
     if (value == 16){
    digitalWrite(11, HIGH);
  	digitalWrite(10, HIGH);
  	digitalWrite(9, HIGH);
  	digitalWrite(8, HIGH);
  }
}

/*-------------------------------- FUNCOES DE CONTAGEM ----------------------------------------------
As funções a seguir foram implementadas para resolver com mais facilidade os problemas de contagem que serão utilizados durante o
código. Como todas as esperas acontecem em tempos padronizados, mostra-se relevante o uso de funções previamente implementadas para
a organização do código!

A conta para todas as funções de contagem é a mesma, já que utilizamos a mesma rotina de interrupcao mas com diversas variáveis para a
contagem!

(Prescaler/Relogio)*Faixa = (64/16e6)*(124+1) = 0.008s

Logo, para encontrar a quantidade de iterações dos contadores para cada tempo proposto, faz-se:

Quantidade de iterações = Tempo Proposto (em milisegundos)/ 8

- Para 1 s, tem-se 125 iterações.
- Para 0.5, tem-se 63 iterações.
- Para alguns milisegundos, usados na troca rápida entre os displays, utiliza-se 2 iterações apenas.
*/

void countMiliSecs(){
  cont=0;
  while (cont < 2){}
}

void countOneSec(){
  cont=0;
  while (cont < 125){}
}

void countHalfSec(){
  cont=0;
  while (cont < 63){}
}
/*-------------------------------- FIM DAS FUNCOES DE CONTAGEM ----------------------------------------*/

/*Aqui, inicia-se uma função de controle dos displays de 7 segmentos. A função recebe como parâmetros dois números que serão
exibidos nos displays. O parâmetro numLed0 refere-se ao valor a ser exibido no display dos carros, enquanto o parâmetro numLed1
refere-se ao valor exibido no display dos pedestres. A funcao recebe também o valor type, que é 1 se a contagem deve ser feita com
os dois leds acesos e com o tempo de 1s entre cada estado ou qualquer outro valor se o tempo entre cada estado é menor que 1s e
o led precisam alternar entre aceso e apagado */


void controlDisplays(int numLed0, int numLed1, int type){
  // Zeramos o contador auxiliar que avalia um segundo de espera.
  contAux = 0;
  if (type == 1){
    while (contAux < 125){
    digitalWrite(changeLedPin0, LOW);
  	digitalWrite(changeLedPin1, HIGH);
  	display7Seg(numLed1);
    // Logo depois de exibir o valor esperado em um display, alterenamos os displays mudando os valores de changeLedPin0 e changeLedPin1
  	countMiliSecs();
    digitalWrite(changeLedPin0, HIGH);
  	digitalWrite(changeLedPin1, LOW);
  	display7Seg(numLed0);
  	countMiliSecs();
  }}
  else{
    // Por saber que al entrar nesse trecho de código o semáforo dos pedestres precisa piscar, faz-se necessário um conjunto de if's para
    //avaliar se o led estava aceso ou apagado e mudar seu estado.
    if (digitalRead(A4) == HIGH){
        digitalWrite(A4, LOW);
      }
      else {
        digitalWrite(A4, HIGH);
      }
    while (contAux < 63){
      // Aqui, entramos na condição de quando o tempo de contagem entre os estados dos displays é menor que 1s.
    digitalWrite(changeLedPin0, LOW);
  	digitalWrite(changeLedPin1, HIGH);
  	display7Seg(numLed1);
  	countMiliSecs();
    // Aqui também, logo depois de exibir o valor esperado em um display, alterenamos os displays mudando os valores de changeLedPin0 e changeLedPin1

    digitalWrite(changeLedPin0, HIGH);
  	digitalWrite(changeLedPin1, LOW);
  	display7Seg(numLed0);
  	countMiliSecs();
    }}
}


/*A função a seguir implementa o que deve acontecer quando o botão dos pedestres é pressionado*/

void pressButtonFunction(){
  // Inicialmente o sistema espera um pouco. No caso, 0.5s
  countHalfSec();

  //Logo em seguida mostro amarelo para os carros e mantenho o valor anterior no semafaro dos pedestres.

  digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);

  // Mantenho o amarelo para os carros por 1.5 s
  countHalfSec();

  // Abro o semáforo para os pedestres e fecho para os carros
  digitalWrite(A2, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A5, HIGH);

  //Em seguida, começo uma contagem regressiva do 9 ao 5 e do 5 ao 1 nos displays dos carros e dos pedestres respectivamente.

  controlDisplays(9,5,1);
  controlDisplays(8,4,1);
  controlDisplays(7,3,1);
  controlDisplays(6,2,1);
  controlDisplays(5,1,1);

  // Quando o valor do display dos pedestres chega em zero, uso a função de controle dos displays com o parametro Type =2
  // para piscar o display utilzando o valor 16 (dado que valores maiores que 9 fazem o display apagar.)
  digitalWrite(A5, LOW);
  controlDisplays(4,0,2);
  controlDisplays(4,16,2);
  controlDisplays(3,0,2);
  controlDisplays(3,16,2);
  controlDisplays(2,0,2);
  controlDisplays(2,16,2);
  controlDisplays(1,0,2);
  controlDisplays(1,16,2);

  // Desligo os displays no final da rotina, já que os displays não precisam ficar acesos.
  digitalWrite(changeLedPin0, HIGH);
  digitalWrite(changeLedPin1, HIGH);
}


void setup() {
  // Desabilito as interrupcoes para garantir que as GPIOS serão habilitadas corretamente como entradas os saídas
  cli();
  //Inicio declarando as portas de saída
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(changeLedPin1,OUTPUT);
  pinMode(changeLedPin0,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  //Declaro a entrada do conversor analogico digital.
  pinMode(14,INPUT);

  //Inicio os displays apagados, colocando valor alto nas entradas de controle dos dois.
  digitalWrite(changeLedPin0, HIGH);
  digitalWrite(changeLedPin1, HIGH);

  // Declaro o pushButton como uma entrada
  pinMode(pushButton,INPUT);
 // Configuro a saída serial para debugar o conversor analogico digital
  Serial.begin(9600);           //  setup serial
  configuracao_Timer0();

  //Habilito as interrupcoes novamente.
  sei();}


void configuracao_Timer0(){
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Configuracao Temporizador 0 (8 bits) para gerar interrupcoes periodicas a cada 8ms no modo Clear Timer on Compare Match (CTC)
  // Relogio = 16e6 Hz
  // Prescaler = 1024
  // Faixa = 125 (contagem de 0 a OCR0A = 124)
  // Intervalo entre interrupcoes: (Prescaler/Relogio)*Faixa = (64/16e6)*(124+1) = 0.008s

  // TCCR0A – Timer/Counter Control Register A
  // COM0A1 COM0A0 COM0B1 COM0B0 – – WGM01 WGM00
  // 0      0      0      0          1     0
  TCCR0A = 0x02;

  // OCR0A – Output Compare Register A
  OCR0A = 124;

  // TIMSK0 – Timer/Counter Interrupt Mask Register
  // – – – – – OCIE0B OCIE0A TOIE0
  // – – – – – 0      1      0
  TIMSK0 = 0x02;

  // TCCR0B – Timer/Counter Control Register B
  // FOC0A FOC0B – – WGM02 CS02 CS01 CS0
  // 0     0         0     1    0    1
  TCCR0B = 0x05;
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// Rotina de servico de interrupcao do temporizador
ISR(TIMER0_COMPA_vect){
  // Aqui, a rotina de interrupcoes só vai incrementar variaveis auxiliares que serão utilizadas em outras partes do código.
  cont++;
  contAux++;
  cont2++;
}

//Aqui, define-se uma funcao auxiliar que irá receber o estado (dia ou noite) e setar os valores das GPIOS para
//emular o funcionamento do circuito.
void putState(int state){

//Se o estado é 1, quer dizer que é dia! Logo o semafaro dos carros deve estar aberto e dos pedestres fechados!
//Deve existir também a leitura do botão por varredura! Assim, quando o botão for pressionado devemos entrar na Rotina
//pressButtonFunction que descreve o funcionamento do sistema quando o botão é pressionado.
	if (state == 1){
    digitalWrite(A3, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A5, LOW);
    digitalWrite(A4, HIGH);
    //Aqui, os displays são desligados! Para garantir que nenhum número esteja sendo transmitido em um momento desnecessário.
    digitalWrite(changeLedPin0, HIGH);
    digitalWrite(changeLedPin1, HIGH);
    if (digitalRead(pushButton) == HIGH){
    	pressButtonFunction();
    }
  }
  //Quando o estado é 0, então é noite! Quando é noite o botão de passagem é desabilitado, logo não há uma varredura.

  else if (state==0) {
    digitalWrite(A4, HIGH);
  	digitalWrite(A3, LOW);
    digitalWrite(A1, LOW);
  	digitalWrite(A5, LOW);

    YellowLedVeic=digitalRead(A2);
  // Durante a noite o semáforo dos veículos deve piscar o amarelo por 0.5s, ou seja, uma contagem até 63 de um dos
  //contadore é necessário.
  // Se o LED esta apagado a 63*8=500ms ou mais, acende o LED
  if ((YellowLedVeic==0)&&(cont>=65)) {
    cont = 0;
    digitalWrite(A2, HIGH);
  }
  // Se o LED esta aceso a 63*8=500ms ou mais, apaga o LED
  if ((YellowLedVeic==1)&&(cont>=65)) {
    cont = 0;
    digitalWrite(A2, LOW);
  }
    digitalWrite(changeLedPin0, HIGH);
    digitalWrite(changeLedPin1, HIGH);
  }}




void loop(){
  //Aqui, insere-se um delay de 1 ms para evitar o problema de lentidão no simulador.
  _delay_ms(1);
  // Le-se o valor da entrada analógica a fim de verificar se é dia ou noite! Se é noite, o valor da leitura será
  //maior que 90, se não, é menor.
  readAnalogOut = analogRead(readAnalogPin);
  if (readAnalogOut < 90){
          actualState = 1;
        }
        else{
          actualState = 0;}
  // verifica-se se houve uma mudança no estado do sistema!
  verify=verifyChanges(actualState, lastState);
  if (verify == 0){
    //Se não houve mudança, utilizamos a funcao putState para emular o estado atual.
    putState(actualState);
    cont2=0;}

  else {
    // Se houve mudança, esperamos 2 segundos para garantir que o estado não mudou por um passáro ou algo que possa
    //alterar a leitura do sensor momentaneamente. E enquanto esperamos, emulamos o valor do estado anterior com o
    //uso da funcao putState
    while (cont2 < 250){
      putState(lastState);
    }
    // Por fim, atribuimos a variável lastState o valor do acutalState para a transferencia instantanea dos estados
    //passado e futuro. 
  }
  lastState = actualState;
}
