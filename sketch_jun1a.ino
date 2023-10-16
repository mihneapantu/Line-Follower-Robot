//Definire constante si asignare plini de pe placa arduino
#define led 3
#define enA 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enB 5

//Definim vitezele motoarelor in regim normal cand senzorii nu intersecteaza linia neagra
 int motor1Speed = 100; //Viteza primului motor
 int motor2Speed = 100; //Viteza celui de-al doilea motor
 
 //Definim vitezele pentru cazul in care senzorii gasesc linia neagra
 int rightSpeed = 250; //Viteza de rotatie la dreapta
 int leftSpeed = 250;  //Viteza de rotatie la stanga


 void setup() {
  //Setam senzorii IR ca input, folosind pinii analogici de pe placa arduino
  pinMode(A0, INPUT); // senzorul din stanga
  pinMode(A1, INPUT); // senzorul din dreapta

  //Setarea pinilor de output
  pinMode(led,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);

  
}

void loop() {
  //Citire valoare senzori
  int rightIR = digitalRead(A1);
  int leftIR = digitalRead(A0);
  

//Citim valorile senzorilor si ne dam seama daca intersecteaza linia neagra sau nu in functie de
//valoarea citia, 0 nu au intersectat linia, 1 in caz contrar.
if(rightIR == 0 && leftIR == 0) 
{  
    digitalWrite(led, LOW);
    moveForward(); //Deplasare in fata
}

  else if(rightIR == 0 && leftIR == 1) 
  {
    turnRight(); //Viraj usor la dreapta
    digitalWrite(led, HIGH);
  }

  else if(rightIR == 1 && leftIR == 0) 
  {
    turnLeft(); //Viraj usor la stanga
    digitalWrite(led, HIGH);
  }

  else if(rightIR == 1 && leftIR == 1) 
  {
    Stop();  //Oprire
    digitalWrite(led, LOW);
  }
}


void moveForward()
{
  //REGIM NORMAL DE FUNCTIONARE, MASINA NU INTERSECTEAZA LINIA NEAGRA

  //pinii in1-4 controleaza directia de rotatie a rotilor
  //in1 si 2 sunt utilizati pentru un motor, 3 si 4 pentru celalalt
  //cand unul e pe high si celalt pe low, motorul se roteste, in caz contrat se opreste.
  //pinii ENA si ENB controloeaza viteza de rotatie a motoarelor.

  //am testat si am vazut ca in combinatia aceasta motoarele se misca in fata
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //am setat viteza de rotatie a motoarelor
  analogWrite(enA, motor1Speed);
  analogWrite(enB, motor2Speed);
}


void turnRight()
{
  //Pentru a putea face masina sa se miste la dreapta in cazul in care senzorul
  //identifica linia neagra, motoarele din partea dreapta se vor misca in fata iar cele
  //din partea stanga in spate
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //Crestem viteza de rotatie a motoarelor 
  analogWrite(enA, leftSpeed);
  analogWrite(enB, rightSpeed);
}

void turnLeft()
{
  //Pentru a putea face masina sa se miste la stanga in cazul in care senzorul
  //identifica linia neagra, motoarele din partea stanga se vor misca in fata iar cele
  //din partea dreapta in spate
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  //Crestem viteza de rotatie a motoarelor 
  analogWrite(enA, leftSpeed);
  analogWrite(enB, rightSpeed);
}

void Stop()
{
  //Oprim masina in cazul in care masina intalneste in traseu o linie orizontala neagra detectata
  //de senzorii IR, setam toti pinii de control ai rotatiei pe low si motoarele se vor opri.
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
