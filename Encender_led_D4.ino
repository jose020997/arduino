#include <ESP8266WiFi.h>

const char* ssid = "sagemcom7670";
const char* password = "JMZYCJNW2MYCJM";


WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  //Configuración  del GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5,LOW);
  pinMode(0, OUTPUT);
  digitalWrite(0,LOW);
  pinMode(16, OUTPUT);
  digitalWrite(16,LOW);
  pinMode(12, OUTPUT);
  
  
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  
  server.begin(); //Iniciamos el servidor
  Serial.println("Servidor Iniciado");


  Serial.println("Ingrese desde un navegador web usando la siguiente IP:");
  Serial.println(WiFi.localIP()); //Obtenemos la IP
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  { 
    Serial.println("Nuevo Cliente");
    
    //esperamos hasta que hayan datos disponibles
    while(!client.available()&&client.connected())
    {
    delay(1);
    }
    
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    Serial.println(linea1);

    if (linea1.indexOf("LED1=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
      digitalWrite(2,HIGH);
    }
    if (linea1.indexOf("LED1=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(2,LOW);
    }


     if (linea1.indexOf("LED2=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
      digitalWrite(4,HIGH);
    }
    if (linea1.indexOf("LED2=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(4,LOW);
    }

    if (linea1.indexOf("LED3=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
      digitalWrite(0,HIGH);
    }
    if (linea1.indexOf("LED3=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(0,LOW);
    }

    if (linea1.indexOf("LED4=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
      digitalWrite(5,HIGH);
    }
    if (linea1.indexOf("LED4=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(5,LOW);
    }
    if (linea1.indexOf("LED5=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {
      digitalWrite(16,HIGH);
    }
    if (linea1.indexOf("LED5=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(16,LOW);
    }
    if (linea1.indexOf("Agua=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(12,LOW);
    }
    if (linea1.indexOf("Agua=ON")>0)//Buscamos un LED=OFF en la 1°Linea
    {
      digitalWrite(12,HIGH);
    }
    client.flush(); 
                
    Serial.println("Enviando respuesta...");   
    //Encabesado http    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");// La conexión se cierra después de finalizar de la respuesta
    client.println();
    //Pagina html  para en el navegador
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>Naylam Mechatronics</title>");
    client.println("<body>");
    client.println("<h1 align='center'>Test ESP8266</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
    client.println("<button onClick=location.href='./?LED1=ON'>LED ON</button>");           
    client.println("<button onClick=location.href='./?LED1=OFF'>LED OFF</button>");

    client.println("<button onClick=location.href='./?LED2=ON'>LED2 ON</button>");           
    client.println("<button onClick=location.href='./?LED2=OFF'>LED2 OFF</button>");

    client.println("<button onClick=location.href='./?LED3=ON'>LED3 ON</button>");           
    client.println("<button onClick=location.href='./?LED3=OFF'>LED3 OFF</button>");

    client.println("<button onClick=location.href='./?Agua=ON'>Agua ON</button>");           
    client.println("<button onClick=location.href='./?Agua=OFF'>Agua OFF</button>");

    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    
    delay(1);
    Serial.println("respuesta enviada");
    Serial.println();

  }
}