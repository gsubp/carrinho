// pinos do sensor ultrassonico
#define trigPin A1
#define echoPin A2

//L298N pinos de controle
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;
//LEDS
const int LedRed = 9;
const int LedGreen = 8;

bool goesForward = false;
 
void setup() {
  Serial.begin(9600); // begin serial communitication  
  Serial.println("Test!"); // print test no monitor serial
  pinMode(LedRed, OUTPUT); 
  pinMode(LedGreen, OUTPUT);
  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
}
 
void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  long duration;
  long distance; 
  delay(50);
  // start the scan
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;// converter a distancia para cm
  
  // se a distancia do obstaculo for menor que 20 cm fazer uma curva para evitar uma colisao
  if (distance < 20) {   
   Serial.println ("Obstaculo detectado!" );
  
    Serial.println ("Detalhes do Obstaculo:");
    Serial.print ("Distancia do carrinho é " );
    Serial.print ( distance);
    Serial.print ( " CM!");// printa a distancia em cm.

    Serial.println (" O Obstaculo pode ser uma ameaça ao carrinho!");
    Serial.println (" Fazendo uma curva!");
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    turnLeft();
    delay(300);
    moveStop();
    delay(300);
    moveForward();
    delay(400);
  }
  else {
    Serial.println ("Nenhum obstaculo detectado. Seguindo em frente!");
    delay (15);
    moveForward();
    delay(400);  
  } 
}

// para carrinho
void moveStop(){
  
  digitalWrite(LedGreen, LOW);
  digitalWrite(LedRed, HIGH);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

// seguir em frente
void moveForward(){

  if(!goesForward){

    goesForward=true;
    digitalWrite(LedGreen, HIGH);
    digitalWrite(LedRed, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

// ré
void moveBackward(){

  goesForward=false;

  digitalWrite(LedGreen, HIGH);
  digitalWrite(LedRed, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

//virar para esquerda
void turnLeft(){

  digitalWrite(LedGreen, HIGH);
  digitalWrite(LedRed, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

