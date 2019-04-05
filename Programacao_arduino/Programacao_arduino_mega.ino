//-Informações de programação-----------------------------------------

//-Pinagem-----------------------------------------------------------

//-Digital-
//NUMERO DO PINO |DESCRICAO DE FUNCAO
//23             |Linha 1 só teclado matricial
//25             |Linha 2 só teclado matricial
//27             |Linha 3 só teclado matricial
//29             |Linha 4 só teclado matricial
//31             |Coluna 1 só teclado matricial
//33             |Coluna 2 só teclado matricial
//35             |Coluna 3 só teclado matricial
//48             |Acionamento do pino CE do modulo de comunicação via radio
//50             |Comunicação com o pino SCK do modulo de comunicação via radio
//51             |Comunicação com o pino MOSI do modulo de comunicação via radio
//52             |Comunicação com o pino MISO do modulo de comunicação via radio
//53             |Acionamento do pino CSN do modulo de comunicação via radio

//7              |Comunicação com o pino D7 do LCD
//8              |Comunicação com o pino D6 do LCD
//9              |Comunicação com o pino D5 do LCD
//10             |Comunicação com o pino D4 LCD
//11             |Comunicação com o pino E do LCD
//12             |Comunicação com o pino RS do LCD
//3              |Comunicação com o pino AUDIO-L do modulo MP3
//4              |Comunicação com o pino P04 do modulo MP3
//5              |Comunicação com o pino P05 do modulo MP3
//6              |Comunicação com o pino P06 do modulo MP3
//18             |Comunicação com o pino RX do modulo Bluetooth
//19             |Comunicação com o pino TX do modulo Bluetooth

//-------------------------------------------------------------------

//-Inclusão de bibliotecas-------------------------------------------

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include <Wtv020sd16p.h>

//-Variáveis---------------------------------------------------------

int resetPin = 3; //Pino Reset
int clockPin = 4; //Pino clock
int dataPin = 5; //Pino data (DI)
int busyPin = 6; //Pino busy

const uint64_t pipes[2] = {0x0c0a0c0a0cLL, 0x0a0c0a0c0aLL};

char mensagem[10];
String mensagemR;
boolean mensR = false;
char mensagemB[10];
String mensagemBR;
char presPonto[10] = "verdadeiro";
const byte LINHAS = 4;
const byte COLUNAS = 3;

char matriz_teclas[LINHAS][COLUNAS] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

String entUsu = "";
boolean pronto = false;
boolean gravado = false;
boolean n_inserido = false;

int audio1 = 1;
int audio2 = 2;
int audio3 = 3;
int audio4 = 4;
int audio5 = 5;
int audio6 = 1001;
int audio7 = 1002;
int audio8 = 1003;
int audio9 = 1004;
int audio10 = 1005;
int audio11 = 1006;
int audio12 = 1007;
int audio13 = 1008;
int audio14 = 1009;
int audio15 = 1010;
int audio16 = 1000;
int audio17 = 1103;
int audio18 = 1100;
int audio19 = 1101;
int audio20 = 1102;
int audio21 = 1201;
int audio22 = 1202;
int audio23 = 1203;
int audio24 = 1204;
int audio25 = 1205;

String linha1 = "";
String linha2 = "";
String linha3 = "";
String linha4 = "";
String linha5 = "";

byte PinosLinhas[LINHAS] = {23, 25, 27, 29};
byte PinosColunas[COLUNAS] = {31, 33, 35};

int rep = 0;

//-------------------------------------------------------------------

//-Definicoes de programacao-----------------------------------------

RF24 radio(53, 48); //CE,CSN
Keypad meuteclado = Keypad(makeKeymap(matriz_teclas), PinosLinhas, PinosColunas, LINHAS, COLUNAS);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
Wtv020sd16p wtv020sd16p(resetPin, clockPin, dataPin, busyPin);

//-------------------------------------------------------------------

//-Sub rotinas-------------------------------------------------------

//-Controle de audio-------------------------------------------------

void rep_audio(String audio)
{
  if (audio == "001")
  {
    Serial.println(F("Reproduzindo audio da Linha 1"));
    wtv020sd16p.asyncPlayVoice(audio1);
  }
  else if (audio == "002")
  {
    Serial.println(F("Reproduzindo audio da Linha 2"));
    wtv020sd16p.asyncPlayVoice(audio2);
  }
  else if (audio == "003")
  {
    Serial.println(F("Reproduzindo audio da Linha 3"));
    wtv020sd16p.asyncPlayVoice(audio3);
  }
  else if (audio == "004")
  {
    Serial.println(F("Reproduzindo audio da Linha 4"));
    wtv020sd16p.asyncPlayVoice(audio4);
  }
  else if (audio == "005")
  {
    Serial.println(F("Reproduzindo audio da Linha 5"));
    wtv020sd16p.asyncPlayVoice(audio5);
  }
  else if (audio == "1001")
  {
    Serial.println(F("Reproduzindo audio da tecla 1"));
    wtv020sd16p.asyncPlayVoice(audio6);
  }
  else if (audio == "1002")
  {
    Serial.println(F("Reproduzindo audio da tecla 2"));
    wtv020sd16p.asyncPlayVoice(audio7);
  }
  else if (audio == "1003")
  {
    Serial.println(F("Reproduzindo audio da tecla 3"));
    wtv020sd16p.asyncPlayVoice(audio8);
  }
  else if (audio == "1004")
  {
    Serial.println(F("Reproduzindo audio da tecla 4"));
    wtv020sd16p.asyncPlayVoice(audio9);
  }
  else if (audio == "1005")
  {
    Serial.println(F("Reproduzindo audio da tecla 5"));
    wtv020sd16p.asyncPlayVoice(audio10);
  }
  else if (audio == "1006")
  {
    Serial.println(F("Reproduzindo audio da tecla 6"));
    wtv020sd16p.asyncPlayVoice(audio11);
  }
  else if (audio == "1007")
  {
    Serial.println(F("Reproduzindo audio da tecla 7"));
    wtv020sd16p.asyncPlayVoice(audio12);
  }
  else if (audio == "1008")
  {
    Serial.println(F("Reproduzindo audio da tecla 8"));
    wtv020sd16p.asyncPlayVoice(audio13);
  }
  else if (audio == "1009")
  {
    Serial.println(F("Reproduzindo audio da tecla 9"));
    wtv020sd16p.asyncPlayVoice(audio14);
  }
  else if (audio == "1010")
  {
    Serial.println(F("Reproduzindo audio da tecla *"));
    wtv020sd16p.asyncPlayVoice(audio15);
  }
  else if (audio == "1000")
  {
    Serial.println(F("Reproduzindo audio da tecla 0"));
    wtv020sd16p.asyncPlayVoice(audio16);
  }
  else if (audio == "1011")
  {
    Serial.println(F("Reproduzindo audio da tecla #"));
    wtv020sd16p.asyncPlayVoice(audio17);
  }
  else if (audio == "1100")
  {
    Serial.println(F("Reproduzindo audio de linha ja inserida"));
    wtv020sd16p.asyncPlayVoice(audio18);
  }
  else if (audio == "1101")
  {
    Serial.println(F("Reproduzindo audio de linha gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio19);
  }
  else if (audio == "1102")
  {
    Serial.println(F("Reproduzindo audio de linha nao encontrada"));
    wtv020sd16p.asyncPlayVoice(audio20);
  }
  else if (audio == "1201")
  {
    Serial.println(F("Reproduzindo audio de linha 001 gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio21);
  }
  else if (audio == "1202")
  {
    Serial.println(F("Reproduzindo audio de linha 002 gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio22);
  }
  else if (audio == "1203")
  {
    Serial.println(F("Reproduzindo audio de linha 003 gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio23);
  }
  else if (audio == "1204")
  {
    Serial.println(F("Reproduzindo audio de linha 004 gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio24);
  }
  else if (audio == "1205")
  {
    Serial.println(F("Reproduzindo audio de linha 005 gravada com sucesso"));
    wtv020sd16p.asyncPlayVoice(audio25);
  }
  else
  {
    Serial.println(F("Erro ao reproduzir o audio"));
  }
}

//-------------------------------------------------------------------

//-Verificacao da entrada de dados do teclado matricial--------------

void verifica_entUsu()
{
  Serial.println(entUsu.length());

  if (entUsu.length() == 3)
  {
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print(F("Gravando linha"));
    delay(500);
    
    if ((entUsu == "001") || (entUsu == "002") || (entUsu == "003") || (entUsu == "004") || (entUsu == "005"))
    {
      if ((entUsu == linha1) || (entUsu == linha2) || (entUsu == linha3) || (entUsu == linha4) || (entUsu == linha5))
      {
        Serial.println(F("Linha ja solicitada"));
        rep_audio("1100");
        lcd.clear();
        delay(500);
        lcd.print("Linha ja");
        lcd.setCursor(0, 1);
        lcd.print("inserida");
        delay(500);
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Aguardando linha");
        lcd.setCursor(0, 1);
        lcd.print(" ");
        n_inserido = true;
      }
      else
      {
        n_inserido = false;
      }
 
      if ((linha1 == "") && (gravado == false) && (n_inserido == false))
      {
        linha1 = entUsu;
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha gravada");
        rep_audio("1201");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if ((linha2 == "") && (gravado == false) && (n_inserido == false))
      {
        linha2 = entUsu;
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha gravada");
        rep_audio("1202");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if ((linha3 == "") && (gravado == false) && (n_inserido == false))
      {
        linha3 = entUsu;
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha gravada");
        rep_audio("1203");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if ((linha4 == "") && (gravado == false) && (n_inserido == false))
      {
        linha4 = entUsu;
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha gravada");
        rep_audio("1204");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if ((linha5 == "") && (gravado == false) && (n_inserido == false))
      {
        linha5 = entUsu;
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha gravada");
        rep_audio("1205");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      
      pronto = false;
      n_inserido = false;
      entUsu = "";
    }
    else
    {
      Serial.println(F("Linha inserida esta incorreta"));
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("Linha incorreta");
      rep_audio("1102");
      delay(1000);
      lcd.clear();
      delay(500);
      lcd.print("Aguardando linha");
      pronto = false;
      entUsu = "";
    }
  }
  else
  {
    Serial.println(F("Linha inserida esta incorreta"));
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Linha incorreta");
    rep_audio("1102");
    delay(1000);
    lcd.clear();
    delay(500);
    lcd.print("Aguardando linha");
    pronto = false;
    entUsu = "";
  }
}

//-------------------------------------------------------------------

//-Verificacao da entrada de dados do onibus-------------------------

void verifica_entBus()
{
  Serial.println(mensagemR.length());
  if (mensagemR.length() == 3)
  {
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Apagando linha");
    delay(500);
    
    if ((mensagemR == linha1) || (mensagemR == linha2) || (mensagemR == linha3) || (mensagemR == linha4) || (mensagemR == linha5))
    {
      rep_audio(mensagemR);
      mensR = true;
      
      if (mensagemR == linha1)
      {
        linha1 = "";
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha apagada");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if (mensagemR == linha2)
      {
        linha2 = "";
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha apagada");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if (mensagemR == linha3)
      {
        linha3 = "";
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha apagada");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if (mensagemR == linha4)
      {
        linha4 = "";
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha apagada");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else if (mensagemR == linha5)
      {
        linha5 = "";
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Linha apagada");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.print("Aguardando linha");
      }
      else
      {
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Erro ao apagar");
        lcd.setCursor(0, 1);
        lcd.print("a linha");
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.setCursor(0, 0);
        lcd.print("Aguardando linha");
        lcd.setCursor(0, 1);
        lcd.print(" ");
      }
      
      //mensagemR = "";
    }
    else
    {
      Serial.println(F("Linha proxima nao inserida"));
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("Linha nao");
      lcd.setCursor(0, 1);
      lcd.print("inserida");
      delay(1000);
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      lcd.print("Aguardando linha");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      //mensagemR = "";
    }
  }
  else
  {
    Serial.println(F("Linha inserida esta incorreta"));
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Linha incorreta");
    delay(1000);
    lcd.clear();
    delay(500);
    lcd.print("Aguardando linha");
    //mensagemR = "";
  }
}

//-------------------------------------------------------------------

//-Comunicacao wireless----------------------------------------------

void wireless_communication()
{
  if (radio.available())
  {
    memset(mensagem, ' ', sizeof(mensagem));
    radio.read(mensagem, sizeof(mensagem));
    mensagemR = String(mensagem);
    mensagemR.trim();
    Serial.println(mensagem);
    Serial.println(mensagemR);
 
    if (mensagem)
    {
      verifica_entBus();
    }
  }
  if (mensR)
  {
    Serial.println("Teste de mensagem " + mensagemR);
    Serial.println("Enviando mensagem");
    radio.stopListening();
    Serial.println(presPonto);
    radio.write(presPonto, sizeof(presPonto));
    radio.startListening();
    mensR = false;
  }
  
  mensagemR = "";
}

//-------------------------------------------------------------------

//-Comunicacao bluetooth---------------------------------------------

void bluetooth_communication()
{
  if (Serial1.available())
  {
    memset(mensagemB, 0, sizeof(mensagemB));
    Serial1.readBytesUntil('\n', mensagemB, sizeof(mensagemB));
    mensagemBR = (String) mensagemB;
    mensagemBR.trim();
    Serial.println("Dado recebido via Bluetooth: " + mensagemBR);
    entUsu = mensagemBR;
    if (mensagemBR)
    {
      verifica_entUsu();
      Serial.println("Dado 1: Linha " + linha1);
      Serial.println("Dado 2: Linha " + linha2);
      Serial.println("Dado 3: Linha " + linha3);
      Serial.println("Dado 4: Linha " + linha4);
      Serial.println("Dado 5: Linha " + linha5);
    }
  }
  
  mensagemBR = "";
}

//-------------------------------------------------------------------

//-Acionamento do audio ao apertar um botÃ£o no teclado matricial-----

void acio_tecla(char tecla)
{
  if (tecla == '1')
  {
    rep_audio("1001");
  }
  else if (tecla == '2')
  {
    rep_audio("1002");
  }
  else if (tecla == '3')
  {
    rep_audio("1003");
  }  
  else if (tecla == '4')
  {
    rep_audio("1004");
  }
  else if (tecla == '5')
  {
    rep_audio("1005");
  }
  else if (tecla == '6')
  {
    rep_audio("1006");
  }
  else if (tecla == '7')
  {
    rep_audio("1007");
  }
  else if (tecla == '8')
  {
    rep_audio("1008");
  }
  else if (tecla == '9')
  {
    rep_audio("1009");
  }
  else if (tecla == '*')
  {
    rep_audio("1010");
  }
  else if (tecla == '0')
  {
    rep_audio("1000");
  }
  else if (tecla == '#')
  {
    rep_audio("1011");
  }
}

//-------------------------------------------------------------------

//-Teclado matricial-------------------------------------------------

void teclado_matricial()
{
  char tecla = meuteclado.getKey();
  
  if (tecla)
  {
    acio_tecla(tecla);
  }
  
  if (tecla != '#')
  {
    entUsu += String(tecla);
  }
  else
  {
    Serial.println("Texto digitado: " + entUsu);
    lcd.setCursor(0, 1);
    lcd.print(" ");
    pronto = true;
  }
  
  if (tecla)
  {
    Serial.println("Tecla pressionada: " + String(tecla));
    lcd.setCursor(0, 1);
    lcd.print(entUsu);
  }
  if (pronto)
  {
    verifica_entUsu();
    Serial.println("Dado 1: Linha " + linha1);
    Serial.println("Dado 2: Linha " + linha2);
    Serial.println("Dado 3: Linha " + linha3);
    Serial.println("Dado 4: Linha " + linha4);
    Serial.println("Dado 5: Linha " + linha5);
  }
}

//-------------------------------------------------------------------

//-Programacao-------------------------------------------------------

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  while (!Serial || !Serial1 || !Serial2)
  {
    ;
  }
  
  Serial.println(F("Iniciando...\n"));
  Serial.println(F("Configurando modulos..."));
  
  radio.begin();
  printf_begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  //radio.printDetails();
  radio.startListening();
 
  wtv020sd16p.reset();
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Carregando...");
  delay(1000);
  lcd.clear();
  Serial.println(F("Modulos configurados\n"));
  Serial.println(F("Iniciado\n"));
  lcd.setCursor(0, 0);
  lcd.print("Aguardando linha");
  Serial.println(F("Aguardando acionamento das teclas..."));
}

void loop()
{
  teclado_matricial();
  wireless_communication();
  bluetooth_communication();
}

//-------------------------------------------------------------------
