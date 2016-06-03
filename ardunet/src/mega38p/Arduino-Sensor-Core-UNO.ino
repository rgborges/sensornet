//Rafael Borges Batista
// TESTADO E FUNCIONANDO
/*
 * Programa lê entrada analógica e a transmite em BCD pela Serial
 */

#define TAMANHO_MAX_BUFFER 3

int idata[3] = { 0, 0, 0}; //buffer que armazena os bits da variável analógica
int sensor = 0;
void setup() 
{
 
   Serial.begin(19200); // SÓ PARA DEBUG
}

void loop() 
{

  sensor = map(analogRead(0),0, 1023, 0, 255);
   idata[2] = sensor % 10;  //unidade  
   idata[1] = (sensor % 100) / 10;  //dezena 
   idata[0] = sensor / 100;  //centena

  for(int k = 0; k < TAMANHO_MAX_BUFFER ; k ++)
  {
       Serial.print(idata[k]);
  }

  Serial.println("");
  

  //RESETA Buffer

  for(int i = 0; i < TAMANHO_MAX_BUFFER; i++)
  {
      idata[i] = 0; 
  } 

   delay(2000); //delay de dois segundos
  
  
}
