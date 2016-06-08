#include <Ultrasonic.h>
#include <IRremote.h>// Libreria para usar receptor I.R:

void autonomo();
void control();

int RECV_PIN = 2;//Se define el pin de entrada de arduino
IRrecv irrecv(RECV_PIN);
decode_results results;

#define PINO_TRG  7
#define PINO_ECHO 4

Ultrasonic ultrasonic(PINO_TRG, PINO_ECHO);

int led = 13;             //Led que se activara con el sensor

int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int vel = 255;            // Velocidad de los motores (0-255)

//declaramos funciones de los movimintos del coche
void adelante();
void atras();
void derecha();
void izquierda();
void parar();
void acelerar();
void desacelerar();


void setup()  { 
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  
  attachInterrupt(0, control, HIGH) ;
  
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);


  pinMode(2,  OUTPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);//iniciamos puerto serial
  irrecv.enableIRIn();//inicia recepcion
  

  //INTERRUPCION
  attachInterrupt( 0, control, FALLING);
 } 
 
void loop()  { 

   
  autonomo();
  //control();

}

void autonomo(){
                       
     //Variable para almacenar distancia en centimetros
      float cmMsec;

      //Lee los valores del ultrsonico
      long microsec = ultrasonic.timing();
      
      //Capturamos distancia
      cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
      delay(50);
      Serial.println(cmMsec);
      
  if(cmMsec <= 10 && cmMsec >=2){
        digitalWrite(led, HIGH);              //Si detecta obstaculo enciende el led

        analogWrite(derB, 0);                 //Paramos los motores
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, 0);
        delay(200);

        analogWrite(derB, vel);               //Reversa
        analogWrite(izqB, vel);
        delay(2000);

        analogWrite(derB, 0);                 //Giramos
        analogWrite(izqB, 0);
        analogWrite(derA, 0);
        analogWrite(izqA, vel);
        delay(1500);

        digitalWrite(led, LOW);

        }else{
            analogWrite(derB, 0);     
            analogWrite(izqB, 0); 
            analogWrite(derA, vel);  
            analogWrite(izqA, vel); 
          }
  }

  void control(){
    
  if(irrecv.decode(&results)){
  Serial.println(results.value);
  irrecv.enableIRIn();
  }
  
      //Selecciona la opcion de movimiento
 switch(results.value)
 {
   case 3261853764 :
   adelante();
   break;
   case 4105841032:
   parar();
   break;
   case 3693766967:
   atras();
   break;
   case 1400905448:
   derecha();
   break;
   case 1972149634:
   izquierda();
   break;
   case 1595074756:
   acelerar();
   break;
   case 412973352:
   desacelerar();
   break; 
   
  }
    

     }
 
   //----------------Funciones de movimiento-----------------
  void adelante(){
       analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, vel);  
      analogWrite(izqA, vel); 
  }
  
  void atras(){
        analogWrite(derA, 0);    
       analogWrite(izqA, 0);
       analogWrite(derB, vel);  
       analogWrite(izqB, vel);
  }
  
  void parar(){
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);    
      analogWrite(izqA, 0);
  }
  void derecha(){
      analogWrite(derB, 0);     
      analogWrite(izqB, 0);
      analogWrite(izqA, 0);
      analogWrite(derA, vel);  
      delay(800);
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);    
      analogWrite(izqA, 0);
  }
  
  void izquierda(){
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);  
      analogWrite(izqA, vel);   
      delay(800);
      analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, 0);    
      analogWrite(izqA, 0); 
  }
  
  void acelerar(){
   if(vel <255)
    {
      vel = 255;
      }
       analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, vel);  
      analogWrite(izqA, vel); 
  }
  
  void desacelerar(){
   if(vel =255)
    {
      vel = 128;
      }
       analogWrite(derB, 0);     
      analogWrite(izqB, 0); 
      analogWrite(derA, vel);  
      analogWrite(izqA, vel); 
  }
