#include "ESP8266WiFi.h"  
#include <Wire.h> //comunicacion de pines
#include <Adafruit_GFX.h> //permite la programacion
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN  //parpadeo del microcontrolador 
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)  
#endif

int screen_roll_delay = 800; // pausa 

void setup() {
  // Monitor Serie: 115200 baud

  //configuraciones de oled 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();    // Limpiar buffer.
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  display.println("2.4GHz WiFi Scanner");
  Serial.begin(115200); 
  Serial.println("Setup begins....");

  //Se desconecta de un AP si estaba conectado 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Iniciando");
  display.println("------------------");
  display.display();
  delay(5000);  //Pantalla de Inicio
}  

void loop() {
  Serial.println("Iniciar Escaner...");

  // Actualiza OLED
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.println("Scanear...");
  display.display();

  //Agarra 1 red Wifi con (WiFi.scanNetworks)
  digitalWrite(0, HIGH);  // Enciende el led 
  int n = WiFi.scanNetworks();
  Serial.println("Completado!!!");
  
  if (n == 0) {  
    Serial.println("No existen redes Wifi!!!");

    // Actualiza OLED
    display.clearDisplay();
    display.display();
    display.setCursor(0,0);
    display.println("Scanear...");
    display.println("No se habilitaron Redes Wifi");
    display.display();
    digitalWrite(0, LOW);  // Apaga LED
  }      
  else  
  {
    Serial.print(n);
    Serial.println("Redes Encontradas:");
    Serial.println("----------------");

    for (int i = 0; i < n; ++i)
    {
      digitalWrite(0, HIGH); //LED encendido
      
      // Imprimir SSID (Service Set Identifier) y RSSI (Identificador de intensidad de la señal recibida) para cada RED encontrada 
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm | ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?"No Encriptado":"Encriptado");

      //Actualizar OLED con wifi encontrado, mostrar SSID y RSSI
      display.clearDisplay();
      display.display();
      display.setCursor(0,0);
      display.print("Network ");
      display.print(i+1);
      display.print(" of ");
      display.println(n);
      display.display();
      display.println(WiFi.SSID(i));
      display.println("-------------------");
      display.print(WiFi.RSSI(i));
      display.print("dBm | ");
      display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?"OPEN":"Encriptado");
      display.display();

      delay(screen_roll_delay);  // Retraso leve para dar tiempo a que el OLED pueda leerlo mientras parpadea
      digitalWrite(0, LOW);   // LED OFF
      delay(screen_roll_delay); 
      digitalWrite(0, HIGH);   // LED ON
      delay(screen_roll_delay);  
      digitalWrite(0, LOW);   // LED OFF
      delay(screen_roll_delay); 
    }  
  }   
  Serial.println("");
}  
