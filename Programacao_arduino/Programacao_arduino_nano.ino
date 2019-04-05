//- Informacoes de programacao --------------------------------------

//- Pinagem ---------------------------------------------------------

//- Digital -

//NUMERO DO PINO |DESCRICAO DE FUNCAO
//9              |Acionamento do pino CSN do modulo de comunicação via radio
//10             |Acionamento do pino CE do modulo de comunicação via radio
//11             |Comunicação com o pino MISO do modulo de comunicação via radio
//12             |Comunicação com o pino MOSI do modulo de comunicação via radio
//13             |Comunicação com o pino SCK do modulo de comunicação via radio
//3              |Comunicação com o pino D7 do LCD
//4              |Comunicação com o pino D6 do LCD
//5              |Comunicação com o pino D5 do LCD
//6              |Comunicação com o pino D4 LCD
//7              |Comunicação com o pino E do LCD
//8              |Comunicação com o pino RS do LCD

//- Analógico -
//NUMERO DO PINO |DESCRICAO DE FUNCAO
//A1             |Acionamento do buzzer
//A2             |Sinal do botão de avança
//A3             |Sinal do botão de recua
//A4             |Sinal do botão de confirma e edita
//A5             |Sinal do botão de reset

//-------------------------------------------------------------------

//-------------------------------------------------------------------

//- Inclusao de bibliotecas -----------------------------------------

#include <SPI.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h> // LCD
#include <Wire.h> // Comunicação IC2
#include <TimerOne.h>

//-------------------------------------------------------------------

//- Definicoes de programacao ---------------------------------------

#define selec 3
#define avan 4
#define retor 5
#define resetbuzz 6
#define buzz 7

//- Variaveis -------------------------------------------------------

const uint64_t pipes[2] = {0x0a0c0a0c0aLL, 0x0c0a0c0a0cLL};
char mensagemT[10];
char mensagem[10];
String mensagemR;
char resp[4] = "prox";
int contador = 1;
int menu = 1;
boolean aciona = false;
boolean EstAnt1 = false;
boolean EstAnt2 = false;
boolean EstAnt3 = false;
boolean EstAnt4 = false;
boolean editar = false;
boolean resetado = false;
String linhaSelec;
String linhaCor = "001";
String linha1 = "001";
String linha2 = "002";
String linha3 = "003";
String linha4 = "004";
String linha5 = "005";

//-------------------------------------------------------------------

//- Definições de programação ---------------------------------------

RF24 radio(9,10); //ce,cs pin
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

//-------------------------------------------------------------------

//- Comunicacao serial ----------------------------------------------

void serialEvent()
{
  String leitura = Serial.readString();
  
  if ((leitura == "prox") || (leitura == "Prox") || (leitura == "PROX"))
  {
    radio.stopListening();
    linhaSelec.toCharArray(mensagemT,sizeof(mensagemT));
    Serial.println(linhaSelec);
    Serial.println(mensagemT);
    radio.write(mensagemT,sizeof(mensagemT));
    radio.startListening();
  }
}

//-------------------------------------------------------------------

//- Acionamento do buzzer quando houver deficiente no ponto ---------

void timerIsr()
{
  for (int i = 0 ; i < 500 ; i++)
  {
    digitalWrite (buzz, LOW);
    delay (2);
    digitalWrite (buzz, HIGH);
    delay (2);
  }
}

void acio_buzzer()
{
  Timer1.attachInterrupt(timerIsr);
  
  do
  {
    int estado1 = digitalRead(resetbuzz);
    if (estado1 && !EstAnt4)
    {
      EstAnt4 = true;
    }
    else if (!estado1 && EstAnt4)
    {
      resetado = true;
      Timer1.detachInterrupt();
      radio.stopListening();
      Serial.println(resp);
      radio.write(resp,sizeof(resp));
      radio.startListening();
      EstAnt4 = false;
    }
  }while (!resetado);
  
  resetado = false;
}

//-------------------------------------------------------------------

//- Comunicacao wireless --------------------------------------------

void wireless_communication()
{
  if(radio.available())
  {
    memset(mensagem,' ',sizeof(mensagem));
    radio.read(mensagem,sizeof(mensagem));
    mensagemR = String(mensagem);
    mensagemR.trim();
    Serial.println(mensagem);
    Serial.println(mensagemR);
    
    if (mensagemR == "verdadeiro")
    {
      acio_buzzer();
    }
  }
}

//-------------------------------------------------------------------

//- Configuracao de pinos -------------------------------------------

void config_pins()
{
  pinMode(selec, INPUT);
  pinMode(avan, INPUT);
  pinMode(retor, INPUT);
  pinMode(resetbuzz, INPUT);
  pinMode(buzz, OUTPUT);
}

//-------------------------------------------------------------------

//- Programacao -----------------------------------------------------

void setup()
{
  Serial.begin(9600);
  
  while (!Serial)
  {
  }
  
  Serial.println(F("Iniciando...\n"));
  Serial.println(F("Configurando pinos..."));
  
  config_pins();
  
  Serial.println(F("Pinos configurados..."));
  Serial.println(F("Recuperando configuracoes salvas..."));
  
// Configurações
  
  Serial.println(F("Configuracoes salvas recuperadas\n"));
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 1);
  
  lcd.print("    Iniciando...    ");
  
  delay(500);
  lcd.setCursor(0, 2);
  
  lcd.print("    Carregando...   ");
  
  Serial.println(F("Configurando modulos..."));
  
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  //radio.printDetails();
  radio.startListening();
  Timer1.initialize(2000000);
  delay (500);
  lcd.clear();
  
  Serial.println(F("Modulos configurados\n"));
 
  Serial.println(F("Iniciado\n"));
}

void loop()
{
  int estado1 = digitalRead(selec);
  int estado2 = digitalRead(avan);
  int estado3 = digitalRead(retor);
  
  if (!editar)
  {
    if (estado1 && !EstAnt1)
    {
      EstAnt1 = true;
    }
    else if (!estado1 && EstAnt1)
    {
      lcd.clear();
            
      editar = true;
      EstAnt1 = false;
    }
  }
  else
  {
    if (estado1 && !EstAnt1)
    {
      EstAnt1 = true;
    }
    else if (!estado1 && EstAnt1)
    {
      lcd.clear();
      
      editar = false;
      linhaSelec = linhaCor;
      EstAnt1 = false;
    }
    
    if (estado2 && !EstAnt2)
    {
      EstAnt2 = true;
    }
    else if (!estado2 && EstAnt2)
    {
      contador = contador + 1;
      EstAnt2 = false;
    }

    if (estado3 && !EstAnt3)
    {
      EstAnt3 = true;
    }
    else if (!estado3 && EstAnt3)
    {
      contador = contador - 1;
      EstAnt3 = false;
    }
 
    if (contador > 5)
    {
      contador = 1;
    }
    else if (contador < 1)
    {
      contador = 5;
    }
  }
  
  if (editar)
  {
    lcd.setCursor(0, 0);
    lcd.print("Editando...        ");

    if ((contador >= 1) && (contador < 4))
    {
      menu = 1;
    }
    else if (contador >= 4)
    {
      menu = 2;
    }

    switch (menu)
    {
      case 1:
        lcd.setCursor(1, 1);
        lcd.print("-001                ");
        lcd.setCursor(1, 2);
        lcd.print("-002                ");
        lcd.setCursor(1, 3);
        lcd.print("-003                ");
      break;
      case 2:
        lcd.setCursor(1, 1);
        lcd.print("-004                ");
        lcd.setCursor(1, 2);
        lcd.print("-005                ");
        lcd.setCursor(0, 3);
        lcd.print("                   ");
      break;
    }

    switch (contador)
    {
      case 1:
        lcd.setCursor(0, 1);
        lcd.print(">");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(" ");
        
        linhaCor = linha1;
      break;
      case 2:
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(">");
        lcd.setCursor(0, 3);
        lcd.print(" ");
        
        linhaCor = linha2;
      break;
      case 3:
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(">");
        
        linhaCor = linha3;
      break;
      case 4:
        lcd.setCursor(0, 1);
        lcd.print(">");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(0, 3);
        lcd.print(" ");
        
        linhaCor = linha4;
      break;
      case 5:
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(">");
        lcd.setCursor(0, 3);
        lcd.print(" ");
        
        linhaCor = linha5;
      break;
    }
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    
    lcd.setCursor(0, 1);
    lcd.print(" Linha selecionada  ");

    lcd.setCursor(8, 2);
    lcd.print(linhaCor);

    lcd.setCursor(0, 3);
    lcd.print("                    ");
  }
   
  wireless_communication();
}

//-------------------------------------------------------------------
