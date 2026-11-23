
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Configuração da rede Wi-Fi
const char* nomeRede = "EscolhaONome";
const char* senhaRede = "EscolhaASenha";

// Servidor HTTP na porta 80
WebServer servidor(80);

// Página inicial de teste
void mostrarPaginaInicial() {
  const char* pagina = R"rawliteral(
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport"
            content="width=device-width, initial-scale=1">
      <title>Meu Aplicativo</title>
      <style>
        body {
          background: #101827;
          color: white;
          font-family: Arial, sans-serif;
          text-align: center;
          padding: 50px 20px;
        }
        h1 {
          color: #20c997;
        }
      </style>
    </head>
    <body>
      <h1>ESP32 funcionando!</h1>
      <p>Aplicativo carregado pela ESP32.</p>
      <p>Servidor local conectado com sucesso!</p>
    </body>
    </html>
  )rawliteral";

  servidor.send(
    200,
    "text/html; charset=utf-8",
    pagina
  );
}

void setup() {
  Serial.begin(115200);

  // Ativa o modo Access Point
  WiFi.mode(WIFI_AP);

  // Cria a rede Wi-Fi
  if (!WiFi.softAP(nomeRede, senhaRede)) {
    Serial.println("Falha ao criar a rede Wi-Fi");
    return;
  }

  Serial.println("Rede Wi-Fi criada!");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.softAPIP());

  // Define a rota da página principal
  servidor.on("/", HTTP_GET, mostrarPaginaInicial);

  // Inicia o servidor
  servidor.begin();

  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  servidor.handleClient();
  delay(2);
}
