#include "WiFi.h"

String wifiConnected = "";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Iniciando WiFi...");
  WiFi.mode(WIFI_STA);
  Serial.println("Configuração concluída!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Procurando...");

  int qtdeRedes = WiFi.scanNetworks();
  Serial.println("Verificação concluída.");

  if (qtdeRedes == 0)
  {
    Serial.println("Nenhuma rede encontrada.");
  }
  else
  {
    Serial.print("Total de rede(s) encontrada(s): ");
    Serial.println(qtdeRedes);

    for (int i = 0; i < qtdeRedes; i++)
    {
      Serial.print(i + 1);
      Serial.print(": ");

      Serial.print(WiFi.SSID(i)); // nome da rede encontrada
      Serial.print(" - Sinal (");

      Serial.print(WiFi.RSSI(i)); // intensidade do sinal
      Serial.print(") - Possui senha? ");

      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Não" : "Sim");
      delay(10);
    }

    Serial.println("Verificando a rede aberta com melhor sinal");
    for (int i = 0; i < qtdeRedes; ++i)
    {
      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
      {
        Serial.println("Rede aberta com melhor sinal: ");
        Serial.print("Nome da Rede: ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" - Sinal: ");
        Serial.print(WiFi.RSSI(i));
        Serial.println("------------------------------");

        Serial.println();

        if (wifiConnected == "")
        {
          Serial.print("Conectando a melhor rede aberta encontrada: ");
          Serial.println(WiFi.SSID(i));

          WiFi.begin(WiFi.SSID(i));

          int tentativas = 0;

          while (WiFi.status() != WL_CONNECTED)
          {
            Serial.print(".");
            tentativas++;
            if (tentativas == 100)
              break;
            delay(100);
          }

          Serial.println("");

          if (WiFi.status() == WL_CONNECTED)
          {
            wifiConnected = WiFi.SSID(i);
            Serial.println("WiFi conectado!" + wifiConnected);
          }
          else
          {
            wifiConnected = "";
            Serial.println("Não foi possível conectar.");
          }
          break;
        }
        else
        {
          Serial.println("ESP32 já conectado a rede: " + wifiConnected);
        }
        Serial.println("--------------------------------------");
      }
    }
  }
  delay(5000);
}