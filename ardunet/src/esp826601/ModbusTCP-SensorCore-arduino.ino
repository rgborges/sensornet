/*
 * Rafael Borges Batista
 * 
 * Programa lê dadado do arduino via serial, os dados são passados em bcd 
 * e o transmite em MODBUS TCP
 * 
 * 
 * TESTADO E FUNCIONANDO 
 * 
 * 
 */

#define TAMANHO_MAX_BUFFER 3
#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>

int idata[3] = { 0 , 0, 0}; //inicializa buffer
int soma = 0; //variável usada na conversão de bcd para inteiro
size_t tamanho = 0; //varável armazena quantos bits chega pela serial
ModbusTCPSlave Mb;  //Declara um objeto Modbus TCP

unsigned long timer;
unsigned long checkRSSIMillis;

void setup()
{

  //Mb.begin("Telecom-28778737", "passwordwificasa47893000", ip, gateway, subnet);
  Mb.begin("TP-LINK_3E50", "02184319");  // ssid e senha da rede 
  Serial.begin(19200);                   //velocidade padrão do modbus
  delay(1000);
  Mb.MBInputRegister[0] = 100;           //valor debug
  Mb.MBInputRegister[1] = 65500;         //valor debug
  Mb.MBInputRegister[2] = 300;           //valor debug
  Mb.MBInputRegister[3] = 400;           //valor debug
  Mb.MBInputRegister[4] = 500;           //valor debug

  Mb.MBHoldingRegister[0] = 0;           //Aqui será armazenado nossa variável

}

void loop()
{
  Mb.Run();   //Roda função modbus
  delay(10);
  if(Serial.available())
  {
    tamanho = Serial.available();
    if(tamanho ==3)
    {
           //Lê tres bits da serial
        for(int i = 0; i < 3 ; i++)
        {
           idata[i] = Serial.read() - 48; // - 48 para converção de char para int 
        }

        //Variáveis temporárias

        int x = idata[0] * 100;
        int y = idata[1] * 10;
        int z = idata[2] * 1;
        //O valor em inteiro é a soma de x y e z
        soma = x + y + z;
        //Atualiza Register com valor 
        Serial.println(soma);
        Mb.MBHoldingRegister[0] = soma;
        //Limpa Serial
        Serial.flush();

        //Reseta variáveis

        x = 0;
        y = 0;
        z = 0;

        for(int l = 0; l < TAMANHO_MAX_BUFFER; l ++)
        {
           idata[l] = 0;
        }
        
    }
  }
}


byte checkRSSI() {
  byte quality;
  long rssi = WiFi.RSSI();
  if (rssi <= -100)
    quality = 0;
  else if (rssi >= -50)
    quality = 100;
  else
    rssi = rssi + 100;
  quality = byte(rssi * 2);

  return quality;
}

