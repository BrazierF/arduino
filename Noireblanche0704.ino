#include <Adafruit_NeoPixel.h>
#define PINBL 12
#define NBLEDBL 21
#define PINNO 10
#define NBLEDNO 15
#define NBLED 21
#define FBLED 21

Adafruit_NeoPixel blanche = Adafruit_NeoPixel(21, PINBL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel noire = Adafruit_NeoPixel(15, PINNO, NEO_GRB + NEO_KHZ800);

int myarray2[NBLED];
char buffer[(NBLED+1)*100];
long tps = 5000;
long chrono = 0;
long raffraichissement = 6000 ;
int compt1 = 0;
int compt2 = 0;
char k =0 ;
boolean premier =true;
int nbdenotesrecu = 0;
int recep;



void setup() {
  Serial2.begin(9600); //MateGold 9600 SU,<value>
  Serial.begin(9600);
  noire.begin(); 
  blanche.begin(); 
  noire.show();
  blanche.show();// Initialize all pixels to 'off'

}



void loop() { 
  reception();
  afficher();
}

void reception(){
recep++;
while(Serial2.available()>0){
    k=Serial2.read();
    Serial.print(k);//Serial.print(recep);
    switch(k){
      //Fin de gamme : '.'(46)
      //Penser a une fonction d'erreur (renvoie des notes si le nb de notes n'est pas correcte)
      case 46: Serial.print(nbdenotesrecu);/*miseentampon();*/ nbdenotesrecu =0 ;compt1++;return;
     // Début de la transmission : ':'(58)
      case 58:nbdenotesrecu =0; compt2=0;
      case 84:raffraichissement = (long) Serial2.read()*100;break;
      ///Arret : '!' (33)
      case 33: arret();return;
      //Pause : '-'(45)
      case 45: pause();return;
      //Fin du morceau : '/'(47)
      case 47 :fin();return;  
      //Play : '>' (62)
      //devra etre effectuer apres l'envoi de la premiere ligne de notes a jouer
      case 62 : Serial.print("play");miseentampon();afficherdebut();return;
      default : buffer[nbdenotesrecu+compt1*NBLED]=k;nbdenotesrecu ++ ; break;
    }
  }
}

void afficher(){ 
  if(millis()-chrono>raffraichissement){
      blanche.show();
      noire.show();
      chrono=millis();
      Serial.print("afficher");
      miseentampon();
    }
  }

void afficherdebut(){ 
      blanche.show();
      noire.show();
      chrono=millis();
      Serial.print("afficher");
      miseentampon();
  }

uint32_t couleurb(int j){
  switch (j) 
  {
  case 35:
    return(blanche.Color(100, 0, 0));
  case 60: 
    return(blanche.Color(0,100, 0));
  case 127: 
    return (blanche.Color(0, 0, 100));
  case 4: 
    return (blanche.Color(100,100,100));
  case 0 :
    return(blanche.Color(0, 0, 0));
  } 
}

int32_t couleurn(int j){
  switch (j) 
  {
  case 35:
    return(noire.Color(100, 0, 0));
  case 60: 
    return(noire.Color(0,100, 0));
  case 127: 
    return (noire.Color(0, 0, 100));
  case 4: 
    return (noire.Color(100,100,100));
  case 0 :
    return(noire.Color(0, 0, 0));
  } 
}

void arret(){
  for(int i=0;i<NBLEDNO;i++){
        blanche.setPixelColor(i,couleurb(0));
        noire.setPixelColor(i,couleurn(0));
      }
  for(int i=NBLEDNO;i<NBLEDBL;i++){   
   blanche.setPixelColor(i,couleurb(0));}
      blanche.show();
      noire.show();
}
//void play(){}
void pause(){chrono=millis()-chrono;while(Serial2.read()!=62){}
chrono=millis()+chrono;
}
void fin(){  for(int i=0;i<NBLEDNO;i++){
        blanche.setPixelColor(i,couleurb(0));
        noire.setPixelColor(i,couleurn(0));
      }
  for(int i=NBLEDNO;i<NBLEDBL;i++){   
   blanche.setPixelColor(i,couleurb(0));}
}
void miseentampon(){
  int z =0;
  Serial.print("miseentampon");
   for(int i=0;i<FBLED;i++){
       /* if (i%2==1){
          noire.setPixelColor(i/2+1,couleurn(buffer[i-z+NBLED*compt2]));
        }
        else{*/
        Serial.print(buffer[i-z+NBLED*compt2]);Serial.print('m');
          blanche.setPixelColor(i/*2+1*/,couleurb(buffer[i-z+NBLED*compt2]));
        /*}
        if(i == 6||i==14 ||i==20 ||i==28||i==34||i==42){
          z++;
        }*/
      }
      compt2++;
}


