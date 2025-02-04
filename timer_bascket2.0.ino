#include <SoftwareSerial.h>
SoftwareSerial BT1(11, 10); // RX | TX

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

const int velocidadBluetooth = 9600;

//----------------------------------
//pines que controlan los display
//----------------------------------
//display 1
const byte f=3;//A0;//A0;//
const byte g=2;//13;//A1;//
const byte d=4;//A5;//A2;//
const byte a=5;//A3;//A2;//
const byte e=6;//A4;//A4;//
const byte b=7;//A1;//A0;//
const byte c=8;//A2;//13;//
//display 2
const byte f1=A4;//3;
const byte g1=A5;//4;
const byte d1=A3;//9;
const byte a1=A2;//8;
const byte e1=A1;//7;
const byte b1=A0;//6;
const byte c1=13;//5;
//display 2

//----------------------------------

//----------------------------------
//Variables utilizados para el conteo
//----------------------------------
const byte alarma = 9;
byte dis1=2;
byte dis2=4;
byte idis1=2;
byte idis2=4;

byte start = 0;

unsigned long previousMillis = 0;        

const long interval = 500;           // intervalo en milisegundo


const int tiempo = 500;


void Conteo(){
  if (dis2==0){
    dis1--;
    dis2=9;
  }else{
    dis2--;
  }
}

void Mostrar_numero(byte a, byte  b, byte c, byte  d, byte e, byte f, byte g, int num1){
  switch (num1) {
    case 0:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    }
    case 1:{
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    }
    case 2:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    }
    case 3:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    }
    case 4:{
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
    case 5:{
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
    case 6:{
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
    case 7:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    }
    case 8:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
    case 9:{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
    default:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
  }
  
}

void Resetear(){
 dis1=idis1;
 dis2=idis2;
}
void Comparar(String inputString){
    unsigned long currentMillis = millis();
    Serial.print(inputString);
    if (inputString.length()>2 && inputString[1]==':'){
      String tiempo = inputString.substring(2);//.toInt();
      int puntos = inputString.indexOf(':');
      String operacion = inputString.substring(0,puntos);
      if (operacion == "T"){
        dis1=String(tiempo[0]).toInt();
        dis2 =String(tiempo[1]).toInt();
        idis1=dis1;
        idis2=dis2;
        start=0;
      }
      Serial.println(operacion);
    }else if (inputString=="I"){
      BT1.println("Iniciar...");
      Resetear();
      start=1;
      currentMillis = millis();
      previousMillis = currentMillis;
    }else if (inputString=="D"){
      BT1.println("Dentener...");
      start=0;
    }else if (inputString=="R"){
      BT1.println("Reiniciar...");
      Resetear();
      //el pin de resetear resetear
      start=0;
    }else if(inputString=="T:60"){
      BT1.println("60 Segundos...");
      Resetear();
      idis1 = 6;
      idis2 = 0;
      dis1 = 6;
      dis2 = 0;
      start=0;
    }else if(inputString=="T:24"){
      BT1.println("24 Segundos...");
      idis1 = 2;
      idis2 = 4;
      dis1 = 2;
      dis2 = 4;
      start=0;
    }else if(inputString=="T:14"){
      BT1.println("14 Segundos...");
      idis1 = 1;
      idis2 = 4;
      dis1 = 1;
      dis2 = 4;
      start=0;
    }
    BT1.print(dis1);
    BT1.print(dis2);
    BT1.println(";");
}

void setup() {
  pinMode(alarma, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(g1, OUTPUT);

  Serial.begin(57600);

  Serial.begin(57600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Iniciando bluetooth...");
  BT1.begin(velocidadBluetooth);
  Serial.println("Bluetooth iniciado");

  Serial.println("Iniciado TIMER");
  Mostrar_numero(a,b,c,d,e,f,g,dis1);
  Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
}

void loop() {
  unsigned long currentMillis = millis();
  

  if (currentMillis - previousMillis >= interval && start==1) {
    
    previousMillis = currentMillis;
    Conteo();
    Mostrar_numero(a,b,c,d,e,f,g,dis1);
    Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
    
  
    if (dis1==0 && dis2==0){
      digitalWrite(alarma, HIGH);
      Mostrar_numero(a,b,c,d,e,f,g,10);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,10);
      delay(tiempo);
      Mostrar_numero(a,b,c,d,e,f,g,dis1);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
      delay(tiempo);
      Mostrar_numero(a,b,c,d,e,f,g,10);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,10);
      delay(tiempo);
      Mostrar_numero(a,b,c,d,e,f,g,dis1);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
      delay(tiempo);
      Mostrar_numero(a,b,c,d,e,f,g,10);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,10);
      delay(tiempo);
      Mostrar_numero(a,b,c,d,e,f,g,dis1);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
      delay(tiempo);
      dis1=idis1;
      dis2=idis2;
      start=0;
      Mostrar_numero(a,b,c,d,e,f,g,dis1);
      Mostrar_numero(a1,b1,c1,d1,e1,f1,g1,dis2);
      digitalWrite(alarma, LOW);
    }
  }
  while (BT1.available()){
     char inChar = (char)BT1.read();
     if (inChar == '\n' || inChar == ';' ) {
       stringComplete = true;
     }else{
       inputString += inChar;
     }
  }

  if (stringComplete) {
   
    Comparar(inputString);
    inputString = "";
    stringComplete = false;
  }
  
    
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '\n' || inChar == ';' ) {
      stringComplete = true;
    }else{
      inputString += inChar;
    }
    
    
  }
}
