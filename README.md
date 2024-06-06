# network-ip-list
Busca todos os IPs ativos por iteração
# Projeto de Estudo sobre as Bibliotecas WiFi.h e ESP32Ping.h

### Introdução
Este projeto tem como objetivo aprimorar as técnicas de manipulação de redes com o ESP32, além de prática na lógica para cálculos de endereço de rede e broadcast. O objetivo é criar um servidor WiFi que escaneie a rede local e exiba as informações dos dispositivos conectados.

### Componentes
* Microcontrolador ESP32
* Biblioteca WiFi.h para gerenciamento da conexão WiFi
* Biblioteca ESP32Ping.h para a funcionalidade de ping

### Funcionamento
1. Conexão WiFi: O ESP32 se conecta à rede WiFi local utilizando as credenciais definidas no código.
2. Criação do Servidor WiFi: Um servidor WiFi é criado na porta 80.
3. Escanear a Rede Local: A função scanNetwork() é chamada para escanear a rede local e encontrar os dispositivos conectados.
4. Exibição das Informações: As informações dos dispositivos conectados são exibidas em uma página HTML no servidor WiFi.

### Código
O código é dividido em três principais funções: setup(), loop() e scanNetwork().
* setup(): Inicializa a comunicação serial, configura o modo WiFi, conecta-se à rede WiFi local e define as rotas do servidor WiFi.
* loop(): Verifica se um cliente se conectou ao servidor e envia uma página HTML com as informações dos dispositivos conectados.
* scanNetwork(): Escaneia a rede local, calcula a faixa de rede e o endereço de broadcast, e pings os dispositivos na faixa de rede para encontrar os dispositivos conectados.

### Cálculos de endereço de rede e broadcast
#### Rede:
Suponha que temos um localIP de 192.168.1.100 e uma subnet de 255.255.255.0.
1. Primeiro, precisamos converter esses endereços IP para a representação binária:
localIP: 192.168.1.100 => 11000000.10101000.00000001.01100100 subnet: 255.255.255.0 => 11111111.11111111.11111111.00000000
2. Agora, aplicamos a operação bit a bit AND em cada par correspondente de bits:
```
  11000000.10101000.00000001.01100100  (localIP)
& 11111111.11111111.11111111.00000000  (subnet)
---------------------------------------
  11000000.10101000.00000001.00000000
```
Convertendo de volta para a representação decimal, obtemos 192.168.1.0. Este é o endereço de rede para o localIP e subnet fornecidos.
A operação AND bit a bit é usada aqui porque queremos manter os bits do localIP onde a subnet tem bits definidos como 1 (indicando a parte da rede do endereço IP) e zerar os bits onde a subnet tem bits definidos como 0 (indicando a parte do host do endereço IP).

### Broadcast:
Suponha que temos um network de 192.168.1.0 e uma subnet de 255.255.255.0.
1. Primeiro, precisamos converter esses endereços IP para a representação binária:
network: 192.168.1.0 => 11000000.10101000.00000001.00000000 subnet: 255.255.255.0 => 11111111.11111111.11111111.00000000
2. Agora, aplicamos a operação bit a bit NOT (~) na subnet:
```
~ 11111111.11111111.11111111.00000000  (subnet)
---------------------------------------
  00000000.00000000.00000000.11111111

```
Em seguida, aplicamos a operação bit a bit OR (|) entre o network e o resultado da operação NOT:

```
  11000000.10101000.00000001.00000000  (network)
| 00000000.00000000.00000000.11111111  (~subnet)
---------------------------------------
  11000000.10101000.00000001.11111111

```
Convertendo de volta para a representação decimal, obtemos 192.168.1.255. Este é o endereço de broadcast para a network e subnet fornecidos.
A operação OR bit a bit é usada aqui porque queremos manter os bits do network onde a subnet tem bits definidos como 1 (indicando a parte da rede do endereço IP) e definir os bits onde a subnet tem bits definidos como 0 (indicando a parte do host do endereço IP) para 1. A operação NOT é usada para inverter os bits da subnet, transformando 0s em 1s e vice-versa.

### Observações
* O código utiliza as bibliotecas WiFi.h e ESP32Ping.h para gerenciar a conexão WiFi e realizar o ping.
* As credenciais da rede WiFi local devem ser definidas nas variáveis ssid e password.
* O servidor WiFi é criado na porta 80.

### Autor
Wanderson Vicente
Data
04/06/2024
