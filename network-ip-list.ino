// Proximos desenvolvimentos
// Separar arquivos desenvolver OTA e pegar credenciais de rede via webserver

#include <WiFi.h> // Inclui a biblioteca WiFi para ESP32
#include <ESP32Ping.h> // Inclui a biblioteca ESP32Ping para a funcionalidade de ping

const char* ssid = "net-work"; // Define o SSID da rede WiFi para se conectar
const char* password = "passwd"; // Define a senha da rede WiFi para se conectar

WiFiServer server(80); // Cria um servidor WiFi na porta 80
std::vector<IPAddress> activeIPs; // Cria um vetor para armazenar os IPs ativos na rede

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial com a velocidade de 115200 bps
  WiFi.mode(WIFI_STA); // Define o modo WiFi para estação (cliente)
  WiFi.begin(ssid, password); // Conecta-se à rede WiFi com o SSID e a senha fornecidos

  while (WiFi.status() != WL_CONNECTED) { // Aguarda até que a conexão WiFi seja estabelecida
    delay(500); // Pausa o programa por 500 milissegundos
    Serial.print("."); // Imprime um ponto na saída serial
  }
  Serial.println("\nWiFi connected"); // Imprime uma mensagem indicando que a conexão WiFi foi estabelecida
  Serial.print("IP address: "); // Imprime "IP address: "
  Serial.println(WiFi.localIP()); // Imprime o endereço IP local na saída serial

  delay(2000); // Pausa o programa por 2000 milissegundos para garantir que a conexão seja estabelecida

  scanNetwork(); // Chama a função scanNetwork() para escanear a rede local

  server.begin(); // Inicia o servidor WiFi
}

void loop() {
  WiFiClient client = server.available(); // Verifica se um cliente se conectou ao servidor
  if (client) { // Se um cliente se conectou...
    Serial.println("Client connected"); // Imprime uma mensagem indicando que um cliente se conectou

    // Envia uma página HTML para o cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>IPs ativos:</h1>");
    for (const auto& ip : activeIPs) { // Para cada IP ativo na rede...
      client.println(ip.toString().c_str()); // Imprime o IP na página HTML
      client.println("<br>"); // Imprime uma quebra de linha na página HTML
    }
    client.println("</html>");

    client.stop(); // Encerra a conexão com o cliente
    Serial.println("Client disconnected"); // Imprime uma mensagem indicando que o cliente foi desconectado
  }
}

void scanNetwork() {
  IPAddress localIP = WiFi.localIP(); // Obtém o endereço IP local
  IPAddress subnet = WiFi.subnetMask(); // Obtém a máscara de sub-rede
  IPAddress gateway = WiFi.gatewayIP(); // Obtém o endereço IP do gateway

  // Imprime as informações de rede na saída serial
  Serial.print("IP local: ");
  Serial.println(localIP);
  Serial.print("Subnet: ");
  Serial.println(subnet);
  Serial.print("Gateway: ");
  Serial.println(gateway);

  // Calcula a faixa de rede
  IPAddress network = localIP & subnet; // Calcula o endereço de rede usando AND bit a bit entre o IP local e a máscara de sub-rede
  IPAddress broadcast = network | ~subnet; // Calcula o endereço de broadcast usando OR bit a bit entre o endereço de rede e o inverso da máscara de sub-rede

  // Imprime a faixa de rede na saída serial.
  Serial.print("Network: ");
  Serial.println(network);
  Serial.print("Broadcast: ");
  Serial.println(broadcast);

  // Escaneia os dispositivos na faixa de rede
  for (int i = 1; i < 255; i++) { // Para cada número de 1 a 254...
    IPAddress ip = network; // Copia o endereço de rede
    ip[3] = i; // Substitui o último octeto do endereço IP pelo número atual
    if (ip == localIP) continue; // Se o IP for o mesmo que o IP local, pula para o próximo número

    Serial.print("Pingando IP: ");
    Serial.println(ip); // Imprime o IP que está sendo pingado

    if (Ping.ping(ip)) { // Se o ping for bem-sucedido...
      Serial.print("Dispositivo encontrado em: ");
      Serial.println(ip); // Imprime o IP do dispositivo encontrado
      activeIPs.push_back(ip); // Adiciona o IP à lista de IPs ativos
    }
  }

  Serial.print("Total de IPs ativos: ");
  Serial.println(activeIPs.size()); // Imprime o total de IPs ativos
}