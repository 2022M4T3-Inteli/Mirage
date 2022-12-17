#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Porta do buzzer
const int buzzer = 2;
// ssid e senha da rede wifi
const char* ssidPrincipal = "Inteli-welcome";
const char* pwdPrincipal = "";

// Número de access points (beacons)
#define NB_APS 3
#define MAX_PONTOS 10
// Distância 
#define DIST_PONTO_A1y 0
#define DIST_PONTO_A3x 8
// Classe ponto apenas para encapsular as coordenadas x e Y e facilitar a construção do ARRAY
class Ponto{
  private:
    float coordX = 0;
    float coordY = 0;
  public:
    // Constroi o ponto colocando os valores nos atributos
    Ponto(float x,float y){
      coordX = x;
      coordY = y;
    };
    Ponto(){    }; // Construtor vazio por requisição do compilador
    void put( float x, float y){ coordX = x; coordY = y;};
    float x(){ return coordX;};
    float y(){ return coordY;};
};
// Classe representa um componente que armazena os 3 pontos (nos objetos da classe Ponto)
// assim como as 3 distâncias a cada um desses pontos
// Para facilitar, chamamos os beacons de A1, A2, A3, etc mas eles são armazenados na verdade
// nos pontos 0,1, 2, etc dos respectivos vetores onde eles são armazenados
//  A2(0,y2)  |\
//            | \->dA2
//            |  \
//            |   \ b(xMedio,yMedio)
//            |   /
//            |  /->dA1
//   A1(0,0)  | /                       A3(x3,0)
//            --------------------------|-----
  // Funções extras para construir o objeto sem usar o construtor
 class Triangulacao{
  private:
    Ponto listaPontos[MAX_PONTOS]; // Lista de objetos Ponto com as coordenadas dos 3 pontos
    float listaDistancias[MAX_PONTOS]; // Lista das distancias a cada um dos pontos A1, A2 e A3
  float yPonto_A1_A2(){   // Formula que calcula a coordenada y do Ponto B usando apenas A1 e A2
      float dA1_2 = pow(listaDistancias[0],2);
      float dA2_2 = pow(listaDistancias[1],2);
      float y2_2  = pow(listaPontos[1].y(),2);
      float y2_x2 = 2*(listaPontos[1].y());
      if(y2_x2==0){
        y2_x2 = 1;
      }
      float yb = (dA1_2 - dA2_2 + y2_2) / y2_x2;
      return(yb);
  };
  float xPonto_A1_A2(){   // Formula que calcula a coordenada x do Ponto B usando apenas A1 e A2
      float dA1_2 = pow(listaDistancias[0],2);
      float yb = yPonto_A1_A2();
      float xb = sqrt(abs(dA1_2 - yb));
      return(xb);
  };
  float yPonto_A1_A3(){   // Formula que calcula a coordenada x do Ponto B usando apenas A1 e A3
      float dA1_2 = pow(listaDistancias[0],2);
      float dA2_2 = pow(listaDistancias[2],2);
      float y2_2  = pow(listaPontos[2].x(),2);
      float y2_x2 = 2*(listaPontos[2].x());
      if(y2_x2==0){
        y2_x2 = 1;
      }
      float yb = (dA1_2 - dA2_2 + y2_2) / y2_x2;
      return(yb);
  };
  float xPonto_A1_A3(){   // Formula que calcula a coordenada y do Ponto B usando apenas A1 e A3
      float dA1_2 = pow(listaDistancias[0],2);
      float yb = yPonto_A1_A3();
      float xb = sqrt(abs(dA1_2 - yb));
      return(xb);
  };
  public:
    Triangulacao(){};
  // Constroi o componente (objeto) de triangulação preenchendo a posição dos 2 beacons da ponta
  // o central é sempre (0,0) e as 3 distancias aos 3 pontos A1, A2 e A3
    Triangulacao(float yA1,float xA3,float d1, float d2, float d3){
      adicionaPonto(0,0,0);
      adicionaPonto(1,0,yA1);
      adicionaPonto(2,xA3,0);
      putDistancia(0,d1);
      putDistancia(1,d2);
      putDistancia(2,d3);
    };
  void adicionaPonto(int nr,float x, float y){
        listaPontos[nr].put(x,y);
  };
  void putDistancia(int nrPonto, float d){
        listaDistancias[nrPonto] = d;
  };
  /////// Calculo dos valores de x e y medios combinando os valores achados atraves de A1 e A2 com A1 e A3
  float pontoXMedio(){
    Serial.println("pontoXMedio");
    float xMedio = (xPonto_A1_A2() + xPonto_A1_A3())/2;
    return(xMedio);
  };
  float pontoYMedio(){
     Serial.println("pontoYMedio");
    float yMedio = (yPonto_A1_A2() + yPonto_A1_A3())/2;
    return(yMedio);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
};
Triangulacao *t = NULL;

//Vetores com nomes de rede e senhas dos Access Points
const char* SSIDS[4]={"Inteli-welcome","Carlinhos","Pablinho2","Pablinho3"};
const char* PWD[4]={"","Carlinhos","Pablinho2","Pablinho3"};
String guardaRede;
//Variável para medir a distância
int distancia[3]={0,0,0};
int indice=0;
// Definições para o FTM
// Number of FTM frames requested in terms of 4 or 8 bursts (allowed values - 0 (No pref), 16, 24, 32, 64)
const uint8_t FTM_FRAME_COUNT = 16;
// Requested time period between consecutive FTM bursts in 100’s of milliseconds (allowed values - 0 (No pref) or 2-255)
const uint16_t FTM_BURST_PERIOD = 2;
// Semaphore to signal when FTM Report has been received
xSemaphoreHandle ftmSemaphore;
// Status of the received FTM Report
bool ftmSuccess = true;
/*void Triangulacao{
  
}*/

// Funcao para enviar os dados da distância para o servidor
void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  
  // Cria um objeto HTTPClient para fazer a requisição
  HTTPClient http;   
    
    // Especifica a URL e o tipo de arquivo da requisição
    http.begin("https://bvfvm2-8080.preview.csb.app/getdistances");  
    http.addHeader("Content-Type", "application/json");
     
    StaticJsonDocument<200> doc;

    // Add values in the document
    doc["dist1"]=distancia[0];
    doc["dist2"]=distancia[1];
    doc["dist3"]=distancia[2];
     
    String requestBody; // String que armazena o JSON
    serializeJson(doc, requestBody); // Serializa a String para JSON
    
    int httpResponseCode = http.POST(requestBody); // Faz a requisição POST
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
}

// Funcao para pegar os dados do servidor
void getDataFromServer() {
 
  Serial.println("Pegando dados do Servidor...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://bvfvm2-8080.preview.csb.app/getdistances");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
     
    int httpResponseCode = http.GET();
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
      deserializeJson(doc, response);
      int action = doc["action"];
      String sensor = doc["sensor"];
      String status1 = doc["status"];
      //Exemplo no caso de vetores/arrays no JSON
      //double latitude = doc["data"][0];
      //double longitude = doc["data"][1];
      Serial.println(action);
      Serial.println(sensor);
      Serial.println(status1);
    }
}
// FTM report handler with the calculated data from the round trip
void onFtmReport(arduino_event_t *event) {
  const char * status_str[5] = {"SUCCESS", "UNSUPPORTED", "CONF_REJECTED", "NO_RESPONSE", "FAIL"};
  wifi_event_ftm_report_t * report = &event->event_info.wifi_ftm_report;
  // Set the global report status
  ftmSuccess = report->status == FTM_STATUS_SUCCESS;
  if (ftmSuccess) {
    // The estimated distance in meters may vary depending on some factors (see README file)
    distancia[indice]= report->dist_est;
    Serial.printf("FTM Estimate: Distance RAW: %.4f,Distance: %.4f m, Return Time: %u ns\n", (float)report->dist_est, (float)(report->dist_est-4010) / 1000, report->rtt_est);
    // Pointer to FTM Report with multiple entries, should be freed after use
    //free(report->ftm_report_data);
  } else {
    Serial.print("FTM Error: ");
    Serial.println(status_str[report->status]);
  }
  // Signal that report is received
  xSemaphoreGive(ftmSemaphore);
}
// Initiate FTM Session and wait for FTM Report
bool getFtmReport(){
  if(!WiFi.initiateFTM(FTM_FRAME_COUNT, FTM_BURST_PERIOD)){
    Serial.println("FTM Error: Initiate Session Failed");
    return false;
  }
  // Wait for signal that report is received and return true if status was success
  return xSemaphoreTake(ftmSemaphore, portMAX_DELAY) == pdPASS && ftmSuccess;
}
// Função que mede a distância de um beacon até a tag, utilizando do FTM
void MedirDistancia(int rede){
  // Create binary semaphore (initialized taken and can be taken/given from any thread/ISR)
  ftmSemaphore = xSemaphoreCreateBinary();
  
  // Listen for FTM Report events
  WiFi.onEvent(onFtmReport, ARDUINO_EVENT_WIFI_FTM_REPORT);
  
  // Connect to AP that has FTM Enabled
  Serial.println("Connecting to FTM Responder");
  WiFi.begin(SSIDS[rede], PWD[rede]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
    WiFi.disconnect();
    delay(2000);
    WiFi.reconnect();
    delay(2000); 
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Initiating FTM session with Frame Count ");
  Serial.print(FTM_FRAME_COUNT);
  Serial.print(" and Burst Period ");
  Serial.print(FTM_BURST_PERIOD * 100);
  Serial.println(" ms");
  getFtmReport();
  delay(2000);
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  WiFi.mode(WIFI_STA); 
  t = new Triangulacao(DIST_PONTO_A1y, DIST_PONTO_A3x, 1, 1, 1);
  Serial.println("X: " + String(t->pontoXMedio()) + "\nY: " + String(t->pontoYMedio()));
}

// Função que recebe o estado do buzzer do servidor
int getBuzzerStatus(){
  if (WiFi.status() == WL_CONNECTED) {  //Check WiFi connection status

    Serial.println("Iniciando o GET request do buzzer...");
    HTTPClient http;

    http.begin("https://bvfvm2-8080.preview.csb.app/getbuzzer");  // Especifica o destino da requisicao
    http.addHeader("Content-Type", "application/json");       // Especifica o tipo de conteudo

    StaticJsonDocument<200> doc; // Cria um documento JSON

    int httpResponseCode = http.GET();  // Envia a requisicao

    if (httpResponseCode > 0) {  // Verifica se a requisicao foi bem sucedida

      String response = http.getString();  // Recebe a resposta do servidor
      Serial.println(httpResponseCode);  // Printa o codigo de resposta
      Serial.println(response);          // Printa a resposta da requisicao

      deserializeJson(doc, response); // Deserializa a resposta do servidor
      int buzzerStatus = doc["status"]; // Atribui o valor do status do buzzer a variavel buzzerStatus

      return buzzerStatus;
      
    }
    else{

      Serial.print("Error on GET request: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Libera o espaco alocado para a requisicao

  }
  else{
    Serial.println("Error in WiFi connection");
  }
}

void loop() {
  Serial.println("Calculando distâncias:");
  for(int i=1; i<4;i++) // Realiza o cálculo de distância para cada rede/beacon
  {
    indice=i-1;
    MedirDistancia(i);
  }
  delay(1000);

  WiFi.begin(ssidPrincipal, pwdPrincipal); // Conecta na rede principal

  while (WiFi.status() != WL_CONNECTED) {  // Espera a conexão com a rede principal
    delay(1000);
    Serial.println("Connecting to Main WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Checa qual o estado do buzzer e toca o buzzer de acordo com o estado
  if(getBuzzerStatus() == 1){
    delay(100);
    tone(buzzer, 200);
    delay(100);
  }
  else{
    delay(100);
    noTone(buzzer);
    delay(100);
  }

  // Posta os dados do calculo da distancia para o servidor
  if (WiFi.status() == WL_CONNECTED) {
  postDataToServer();
  }else{
    Serial.println("Error in WiFi connection");
  }
  delay(1000);
}