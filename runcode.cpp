#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YourWiFiName";
const char* password = "YourPassword";

ESP8266WebServer server(80);

// Motor pins
#define IN1 5
#define IN2 4
#define IN3 0
#define IN4 2

// IR sensors
#define IR_LEFT 14
#define IR_RIGHT 12

// Ultrasonic
#define TRIG 13
#define ECHO 15

long duration;
int distance;

// ===== Motor functions =====
void forward(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}

void backward(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
}

void left(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}

void right(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
}

void stopMotor(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
}

// ===== Ultrasonic =====
int getDistance(){
digitalWrite(TRIG,LOW);
delayMicroseconds(2);

digitalWrite(TRIG,HIGH);
delayMicroseconds(10);

digitalWrite(TRIG,LOW);

duration = pulseIn(ECHO,HIGH);
distance = duration * 0.034 / 2;
return distance;
}

// ===== Web Page =====
void handleRoot(){
String html = "<html><body><h2>Smart Trolley</h2>";
html += "<a href='/f'>Forward</a><br>";
html += "<a href='/b'>Backward</a><br>";
html += "<a href='/l'>Left</a><br>";
html += "<a href='/r'>Right</a><br>";
html += "<a href='/s'>Stop</a><br>";
html += "</body></html>";
server.send(200,"text/html",html);
}

// ===== Setup =====
void setup(){

Serial.begin(115200);

pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

pinMode(IR_LEFT,INPUT);
pinMode(IR_RIGHT,INPUT);

pinMode(TRIG,OUTPUT);
pinMode(ECHO,INPUT);

// WiFi connect
WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED){
delay(500);
Serial.print(".");
}

Serial.println("\nConnected");
Serial.println(WiFi.localIP());

// Routes
server.on("/", handleRoot);
server.on("/f", forward);
server.on("/b", backward);
server.on("/l", left);
server.on("/r", right);
server.on("/s", stopMotor);

server.begin();
}

// ===== Loop =====
void loop(){

server.handleClient();

// Sensor logic
int leftIR = digitalRead(IR_LEFT);
int rightIR = digitalRead(IR_RIGHT);

distance = getDistance();

// obstacle stop
if(distance < 20){
stopMotor();
}

// alignment correction
if(leftIR == LOW && rightIR == HIGH){
left();
}
if(rightIR == LOW && leftIR == HIGH){
right();
}
}
