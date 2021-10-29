// #include <Wire.h>

#define RMA 5   // Moteur Gauche Avancer
#define RMR 3   // Moteur Gauche Reculer
#define LMA 11  // Moteur Droite Avancer
#define LMR 6   // Moteur Droite Reculer

#define capG 4 // Capteur Gauche
#define capM 7 // Capteur Milieu
#define capD 8 // Capteur Droite

int zoneR = 0 ; // Testeur sur la zone rouge
int cG ;
int cD ;
int cM ;
int etat_prec ;

void setup() {
   // Wire.begin(); 

  pinMode(LMA, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(RMA, OUTPUT);
  pinMode(RMR, OUTPUT);
  pinMode(capG, INPUT);
  pinMode(capD, INPUT);
  pinMode(capM, INPUT);
  Serial.begin(9600);
   
}

void CheckCaps () {
  cG=digitalRead(capG);
  cD=digitalRead(capD);
  cM=digitalRead(capM);
}

void Forward(){
  analogWrite (LMA,85);
  analogWrite (LMR,0);
  analogWrite (RMA,80);
  analogWrite (RMR,0);

}

void ForwardVeryFast() { // Pour le dos d'ane
  analogWrite (LMA,140);
  analogWrite (LMR,0);
  analogWrite (RMA,125);
  analogWrite (RMR,0);
  delay(50);

}

void Backward() {
  analogWrite (LMA,0);
  analogWrite (LMR,80);
  analogWrite (RMA,0);
  analogWrite (RMR,70);

}

void Left () {
  analogWrite (LMA,0);
  analogWrite (LMR,20);
  analogWrite (RMA,55);
  analogWrite (RMR,0);
}

void Right () {
  analogWrite (LMA,65);
  analogWrite (LMR,0);
  analogWrite (RMA,0);
  analogWrite (RMR,0);

}

void Stop () {
  analogWrite (LMA,0);
  analogWrite (LMR,0);
  analogWrite (RMA,0);
  analogWrite (RMR,0);

}


void loop() {
  CheckCaps();
  Serial.print(cD);
  Serial.println(cM);
  Serial.print(cG);
  
  int a=0;
  

  Forward();

  if (!cG && !cM && !cD) {
    switch(etat_prec) {
    case 1: Left(); break;
    case 2: Right(); break;
}
}
  

  else if (!cG && !cM && cD) {
    Right();
    etat_prec=2;
  }

  else if (!cG && cM && !cD) {
    Forward();
  }
  
  else if (!cG && cM && cD) {
    Right();
    etat_prec=2;
  }
  else if (cG && !cM && !cD) {
    Left();
    etat_prec=1;
  }

  else if (cG && !cM && cD) {
    Backward();
    etat_prec=2;

  }

  else if (cG && cM && !cD) {
    Left();
    etat_prec=1;
  }
  else if (cG && !cM && !cD) {
    Left();
    etat_prec=1;
  }

  else if (cG && cM && cD) {
    if (a<2)
    {ForwardVeryFast();
    a++;}
    else 
      Forward();
  }
/*
  // Si Milieu = Noir && Gauche = Blanc && Droite = Blanc ==> Avancer
  if (!cG && cM && !cD) {
    Forward();
  }

  // Si Milieu = Blanc && Gauche = Blanc && Droite = Blanc && Avant zone Rouge ==> Reculer
  else if (!cG && !cM && !cD && !zoneR) {
    Stop();
  }

  // Si Milieu = Blanc && Gauche = Blanc && Droite = Blanc  && Aprés zone Rouge ==> Lighne discontinue ==> Avancer tres rapidement
  else if (!cG && !cM && !cD && zoneR) {
    ForwardVeryFast();
  }

  // Si Milieu = Noir && Gauche = Noir && Droite = Noir && Avant zone rouge ==> Dos d'ane ==> Avancer trés rapidement
  else if (cG && cM && cD && !zoneR) {
    ForwardVeryFast();
  }

  // Si Milieu = Noir && Gauche = Noir && Droite = Noir && Aprés zone rouge ==> Dos d'ane ==> Avancer trés rapidement
  else if (cG && cM && cD && zoneR) {
    Left();
   }

  // Si Milieu = Blanc && Gauche = Blanc && Droite = Noir ==> Tourner a droite
  // Si Milieu = Noir && Gauche = Blanc && Droite = Noir ==> Tourner a Gauche
  else if ((!cG && !cM && cD) || (!cG && cM && cD)) {
    Right();
  }

    // Si Milieu = Blanc && Gauche = Noir && Droite = Blanc ==> Tourner a Gauche
    // Si Milieu = Noir && Gauche = Noir && Droite = Blanc ==> Tourner a Gauche
  else if ((cG && !cM && !cD) || (cG && cM && !cD)) {
    Left();
  }
*/
}
