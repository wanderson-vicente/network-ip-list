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

### Observações
* O código utiliza as bibliotecas WiFi.h e ESP32Ping.h para gerenciar a conexão WiFi e realizar o ping.
* As credenciais da rede WiFi local devem ser definidas nas variáveis ssid e password.
* O servidor WiFi é criado na porta 80.

### Autor
Wanderson Vicente
Data
04/07/2024
