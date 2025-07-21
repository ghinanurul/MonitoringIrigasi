#define BLYNK_TEMPLATE_ID "TMPL6X5xlZuQS"
#define BLYNK_TEMPLATE_NAME "Irigasi Monitor"
#define BLYNK_AUTH_TOKEN "3vZntTM2Ou5S4r34zYt-LCILrToCga-B"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define Echo 15
#define Trig 4
#define Merah 14
#define Kuning 12
#define Hijau 13

//float X=400/397.63;
char auth[] = "3vZntTM2Ou5S4r34zYt-LCILrToCga-B";
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

float distance = 0;
float ketinggian = 0;


void ukur_jarak(){
  digitalWrite(Trig,LOW);
  delay(2);
  digitalWrite(Trig, HIGH);
  delay(10);
  digitalWrite(Trig, LOW);

  int duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;
  ketinggian = 350 - distance ;

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" CM");

  Serial.print("Ketinggian Air : ");
  Serial.print(ketinggian);
  Serial.println(" CM");
  
}

void kirim_blynk(){
Blynk.virtualWrite(V0, ketinggian);
Blynk.virtualWrite(V4, ketinggian);
  if (distance < 100){
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 1);
}
else if (distance >= 100 && distance <= 150){
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 1);
  Blynk.virtualWrite(V3, 0);
}
else if (distance > 150){
  Blynk.virtualWrite(V1, 1);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
}

}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Merah, OUTPUT);
  pinMode(Kuning, OUTPUT);
  pinMode(Hijau, OUTPUT);
  timer.setInterval(2000L,kirim_blynk);
}

void loop() {
   
  digitalWrite(Merah, LOW);
  digitalWrite(Hijau, LOW);
  digitalWrite(Kuning, LOW);


  ukur_jarak();
  int ketinggian = 350 - distance ;
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" CM");

  Serial.print("Ketinggian Air : ");
  Serial.print(ketinggian);
  Serial.println(" CM");

  if( distance > 100 && distance < 150)
  {
    Serial.println("Waspada");
    digitalWrite(Kuning, HIGH);
  }
  else if (distance > 0 && distance < 100)
  {
    Serial.println("Bahaya");
    digitalWrite(Merah, HIGH);
  }
  else 
  {
    Serial.println("Aman");
    digitalWrite(Hijau, HIGH);
  }
  Blynk.run();
  timer.run();
  delay(500);
}