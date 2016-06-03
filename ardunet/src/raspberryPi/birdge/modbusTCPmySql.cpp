/*
Cliente modbus TCP IP utilizando a biblioteca libmodbus no Raspberry Pi modelo 1
escrito por Rafael Borges Batista .

email: rafael.eng.auto@gmail.com

Dependências:

libmodbus 
modbus-dev 
gcc


comando de compilação via terminal

gcc programa.c -o objeto pkg-config --cflags ---libs libmodbus`

*/

#include <iostream>
#include <sstream>
#include <modbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <my_global.h>
#include <mysql.h>
#include <string>



using namespace std;

const char *ip = "192.168.1.102"; //IP do sensor 
int port = 502;                   //porta modbus  


void uint16ToString(uint16_t value, char *buffer)
{
    uint16_t a = 0;
    uint16_t b = 0;
    uint16_t c = 0;
    int tam = 3;
    
    buffer[2] = value % 10; //unidade
    buffer[1] = (value % 100) / 10; //dezena
    buffer[0] = value / 100; //centena
    
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

int main(int argc, char **argv)
{
    modbus_t *mb;
    uint16_t tab_reg[32];
    int rc;
    int i;
    mb = modbus_new_tcp(ip, port);
    
    
        if(mb == NULL)
        {
            fprintf(stderr, "Nao foi possivel alocar libmodbus \n");
            return -1;
        }
        if(modbus_connect(mb) == -1)
        {
            fprintf(stderr, "Falha na conexao \n");
            modbus_free(mb);
            return -1;
        }
        
        //Lê 5 registradores a partir do endereço 0
         rc == modbus_read_registers(mb, 0, 5, tab_reg);
         
         if(rc == -1)
         {
             printf("error \n");
             modbus_free(mb);
             return -1;
         }
         
 for(i = 0; i < rc; i++)
 {
     printf("reg[%d] = %d (0x%X) \n", i, tab_reg[i], tab_reg[i]);
 }
 
   modbus_close(mb);
   modbus_free(mb);
   
   //JOGA PARA O BANCO DE DADOS 
   MYSQL *con = mysql_init(NULL);
   char* valor = ""; 
   uint16ToString(tab_reg[0], valor);
   sstream value;
   value << tab_reg[0]; 
   query = "INSERT INTO node VALUES('Luminosidade','" + value.str() + "'," + "'192.168.1.102','São Paulo')" ;
   cout << query << endl;
  if (con == NULL) 

  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }  

  if (mysql_real_connect(con, "localhost", "monty", "SENAI", 
          "iot", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
  
  if (mysql_query(con, "DROP TABLE IF EXISTS node")) {
      finish_with_error(con);
  }
  
  if (mysql_query(con, "CREATE TABLE node(id TEXT,value INT,ip TEXT,place TEXT)")) 
  {      
      finish_with_error(con);
  }
  
  if (mysql_query(con, query) 
  {
      finish_with_error(con);
  }
   
    return 0;
}