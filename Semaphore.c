volatile unsigned int cont=0;
int readAnalogPin= A0;
int readAnalogOut=0;
unsigned int YellowLedVeic=0;
const byte interruptPin = 2;
int pushButton = 6;


void countOneSec(){
  cont=0;
  while (cont < 125){}
}


void pressButtonFunction(){
  countOneSec();
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
}



void nightFunction(){
  digitalWrite(A4, HIGH);
  digitalWrite(A3, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A5, LOW);
  
  
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
}

void setup() {

  cli();
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(14,INPUT);
  pinMode(pushButton,INPUT);
  Serial.begin(9600);           //  setup serial
  configuracao_Timer0();
  sei();
  
}

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
  // Insira aqui o codigo a s do temporizadorer executado pela interrupcao periodica
  cont++;
}


void loop(){
  
  YellowLedVeic=digitalRead(A2);
  readAnalogOut = analogRead(readAnalogPin);  // read the input pin
  
   Serial.println(readAnalogOut);
  
  if (readAnalogOut < 90){
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A5, LOW);
    
    if (digitalRead(pushButton) == HIGH){
    	pressButtonFunction();
    }
  }
  else {
    nightFunction();
  }
  
}