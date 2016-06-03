# sensornet
Network for sensor´s data

    O principal objetivo deste projeto é construir uma pequena arquitetura de Internet das Coisas voltada
    para a comunicação entre sensores, atuadores e controladores, integrado ao Banco de Dados MYSQL. O projeto 
    será organizado em camadas, onde na primeira camada temos os hardwares dos sensores e atuadores.
    
    
    Arquitetura 1
     Sensores e Atuadores baseados no arduino MEGA e UNO, ESP8266-01 e servidor rodando no Raspberry Pi.
    
   Camadas
   
    Para melhor entendimento do projeto vamos organizar em camadas.
    
    Primeira Camada
   
   Camada de sensores e atuadores, sejá qual for o sensor precisamos transmitir as seguintes informações
   Identificação, Dado, IP e Localidade. Neste utilizado um sensor de Luz transmitidos via Serial para uma 
   placa ESP8266-01.
   
   Segunda Camada
   
   A segunda camada é a comunicação entre os sensores e atuadores.
   Os dados via Serial são recebidos pelo ESP8266-01 e retransmitidos via Modbus TCP/IP. Um device master fica 
   responsável pela captação destes dados.
   
   Terceira Camada
   
   Disponibilizar os dados em um banco local.
   
   Quarta Camada
   
   Utilizar web services locais.
   
   Quinta Camada
   
   Disponibilidade na Internet.
   
   Sexta Camada
   
   Mineração de dados. Framework e API para requisição dos dados.
