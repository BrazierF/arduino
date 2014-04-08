#include <Adafruit_NeoPixel.h>
#define PINBL 12
#define PINNO 10
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



void setup() {
  Serial2.begin(9600); //MateGold 9600 SU,<value>
  Serial.begin(9600);
  noire.begin(); blanche.begin(); delay(15000);
  noire.show();blanche.show();// Initialize all pixels to 'off'
  
}

void loop() { 
  while(Serial2.available()>0){
  buffer[compt1]=Serial2.read();Serial.print(buffer[compt1]);compt1++;delay(2);}
  raffraichissement = (long) buffer[0]*100; 
  maj();
  afficher();
}


void afficher(){ 
  if(millis()-chrono>raffraichissement){
     maj();
  }
  else{ if(premier){int z=0;
    for(int i=0;i<FBLED;i++){
      if (i%2==1){noire.setPixelColor(i,couleurn(myarray2[i-z]));}
        else{blanche.setPixelColor(i/2+1,couleurb(myarray2[i-z]));
      }
      if(i == 6||i==14 ||i==20 ||i==28||i==34||i==42){z++;
    }blanche.setPixelColor(i/2+1,couleurb(myarray2[i-z]));}
    blanche.show();
    noire.show();
    premier=false;
    Serial2.print('*');delay(5);
}}
  while(Serial2.available()>0){
  buffer[compt1]=Serial2.read();Serial.print(buffer[compt1]);compt1++;delay(2);}
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

void maj(){int j=0;chrono=millis();
 while(j<NBLED){ //Serial.print(j);
 if((NBLED+1)*compt2 + j+1<compt1){
    k = buffer[(NBLED+1)*compt2 + j+1];}else{k=0;Serial.print("attente");}
    
    if (k==47){for(int v=0;v<NBLED;v++){
      myarray2[v]=0;}
     for (int zero=0; zero<(NBLED+1)*100;zero++){buffer[zero]=0;}
      compt2=0;compt1=0;
    return;}
    else {
        myarray2[j]=k;
         j++;
      }
    }
  if (j!=NBLED-1 && buffer[(NBLED+1)*compt2 + j+1]){Serial2.print('?');}
 
    compt2++;
    premier=true;
}


