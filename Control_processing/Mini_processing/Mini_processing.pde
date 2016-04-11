import processing.serial.*;
import org.firmata.*;
import cc.arduino.*;
/**==============================================================
                  Control visuel de feu
================================================================
    Par:Josaphat Mayuba,claude dzoti lappa,dorvelus rony,tchougnia alain jojo.
    -------   Manuel   ---------
    -CONFIGURER LA CARTE AVEC ARDUINO LIBRARY EXEMPLE FIRMATA->SIMPLEDIGITALFIRMATA
                                                      ----------------------------
    
    >>---------PORT ENTREE-------------------------
    Ligne 1 et 3
    PORT (2,3,4,5) ===> (LED ROUGE, LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
    Ligne 2 et 4
    PORT (6,7,8,9) ===> (LED ROUGE,LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
   >>---------PORT ENTREE-------------------------
   PORT 10 doit etre connecter avec PORT 47 
   <<----------PORT SORTI-----------------------
   PORT 11 bouton power interface
================================================================*/
Arduino arduino;
int power=11; //control feu bouton power
//*****************************
 int lastime=0;
 char affiche;
 //**********Ligne 1 et 3 *************
int vir_ligne1=5;
int vert_ligne1=4;
int jaune_ligne1=3;
int rouge_ligne1=2;
//************Ligne 2 et 4 ****************
int vir_ligne2=9;
int vert_ligne2=8;
int jaune_ligne2=7;
int rouge_ligne2=6;
//********************************
int afficheur=10;
//*********NON UTILISER************
 int led_passage1=22;
int led_passage2=23;
//*******************************
int switchState1=0;
int switchState2=0;
int switchState3=0;
int switchState4=0;
int switchState5=0;
int switchState6=0;
int switchState7=0;
int switchState8=0;
int switchState9=0;
int switchState10=0;
int switchState11=0;
//******************
color eteint=#000000;
color rouge=#E02A19;
color jaune=#D9E019;
color vert=#19E027;
color value=vert;
color panneau=#5F5F58;
void setup(){
  //configuration port
  size(800,600);
  //configuration port carte arduino
  arduino = new Arduino(this, "COM8", 57600);
 arduino.pinMode(vir_ligne1,Arduino.INPUT);
  arduino.pinMode(vert_ligne1,Arduino.INPUT);
  arduino.pinMode(jaune_ligne1,Arduino.INPUT);
 arduino.pinMode(rouge_ligne1,Arduino.INPUT);
 //****************************************
  arduino.pinMode(vir_ligne2,Arduino.INPUT);
  arduino.pinMode(vert_ligne2,Arduino.INPUT);
 arduino.pinMode(jaune_ligne2,Arduino.INPUT);
  arduino.pinMode(rouge_ligne2,Arduino.INPUT);
 //******************************************
 arduino.pinMode(afficheur,Arduino.INPUT);
  arduino.pinMode(led_passage1,Arduino.INPUT);
  arduino.pinMode(led_passage2,Arduino.INPUT);
 //*****************************************
  arduino.pinMode(power,Arduino.OUTPUT);
 // arduino.pinMode(34,Arduino.OUTPUT);
}
void draw()
{
  
  fill(0);
   text("ligne 1",260,110);
    text("ligne 2",10,height/2);
     text("ligne 3",260,550);
      text("ligne 4",550,height/2);
       text("Power",710,180);
 panneau();
 
 compteur();
   vir_1();
 vert_1();
 jaune_1();
 rouge_1();
 // passage_led1();
  vir_2();
 vert_2();
  jaune_2();
 rouge_2();
 //   passage_led2();
   
 
 fill(value);
  rect(700,200,50,50);
}
//**************************************
 void vir_1()
 {
      
   switchState1 = arduino.digitalRead(vir_ligne1);
   if (switchState1==Arduino.LOW){ 
    fill(vert);
 }else{
  fill(eteint);
 }
   ellipse(180,150,50,50);
   ellipse(390,500,50,50);
 }
 void vert_1()
 {
     switchState2 = arduino.digitalRead(vert_ligne1);
   if (switchState2==Arduino.LOW){ 
    fill(vert);
  }else{
   fill(eteint);
 }
   ellipse(250,150,50,50);
   ellipse(320,500,50,50);
 }
 void jaune_1()
 {
  switchState3 = arduino.digitalRead(jaune_ligne1);
    if (switchState3==Arduino.LOW){ 
    fill(jaune);
    }else{
   fill(eteint);
  }
   ellipse(320,150,50,50);
   ellipse(250,500,50,50);
 }
 void rouge_1()
 {
    switchState4 = arduino.digitalRead(rouge_ligne1);
      if (switchState4==Arduino.LOW){ 
    fill(rouge);
   }else{
    fill(eteint);
 }
   ellipse(390,150,50,50);
   ellipse(180,500,50,50);
 }
 //**********************************************
 void vir_2()
 {
  switchState5 = arduino.digitalRead(vir_ligne2);
    if (switchState5==Arduino.LOW){ 
    fill(vert);
   }else{
  fill(eteint);
 }
   ellipse(490,230,50,50);
   ellipse(90,440,50,50);
 }
  void vert_2()
 {
     switchState6 = arduino.digitalRead(vert_ligne2);
       if (switchState6==Arduino.LOW){ 
     fill(vert);
    }else{
   fill(eteint);
  }
   ellipse(490,300,50,50);
   ellipse(90,370,50,50);
 }
 void jaune_2()
 {
     switchState7 = arduino.digitalRead(jaune_ligne2);
       if (switchState7==Arduino.LOW){ 
     fill(jaune);
   }else{
   fill(eteint);
  }
   ellipse(490,370,50,50);
   ellipse(90,300,50,50);
 }
  void rouge_2()
 {
    switchState8 = arduino.digitalRead(rouge_ligne2);
     if (switchState8==Arduino.LOW){ 
    fill(rouge);
    }else{
   fill(eteint);
  }
   ellipse(490,440,50,50);
   ellipse(90,230,50,50);
 }
 //*******************************************
 void passage_led1()
 {
   switchState9 = arduino.digitalRead(led_passage1);
     if (switchState9==Arduino.LOW){ 
    fill(eteint);
  }else{
   fill(vert);
 }
   rect(485,500,15,15);
   rect(485,170,15,15);
   rect(85,170,15,15);
    rect(85,495,15,15);
 }
  void passage_led2()
 {
     switchState10 = arduino.digitalRead(led_passage2);
      if (switchState10==Arduino.LOW){ 
   fill(vert);
  }else{
   fill(rouge);
 }
   rect(445,145,15,15);
   rect(120,145,15,15);
    rect(120,495,15,15);
   rect(445,495,15,15);
 }
  //**********************************************************

 void mouseClicked() {
  if (value == vert) {
     arduino.digitalWrite(power,Arduino.HIGH);
    value = rouge;
  } else {
       arduino.digitalWrite(power,Arduino.LOW);
    value = vert;
  } 
}
//****************************
void panneau(){
fill(panneau);
   rect (60, 190, 60, 300, 10);
  fill(panneau);
   rect (140, 470, 300, 60, 10);
   fill(panneau);
   rect (140, 120, 300, 60, 10);
    fill(panneau);
   rect (460, 190, 60, 300, 10);
   fill(0);
  rect(235,245,130,150);
}
//------------------Afficheur 7 segment------------------------------
 void chiffre_0()
 {
   
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  rect(260,325,10,45);//E
  rect(260,270,10,45);//F
   
 }
   
void chiffre_1()
{ 
  fill(rouge);
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
}
void chiffre_2()
{
  
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(270,370,60,10);//D
  rect(260,325,10,45);//E
  rect(270,315,60,10);//G
}
void chiffre_3()
{
   
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  rect(270,315,60,10);//G
}
void chiffre_4()
{
    
  //************************
  fill(rouge);
  
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
  rect(260,270,10,45);//F
  rect(270,315,60,10);//G
}
void chiffre_5()
{
   
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
   
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  
  rect(260,270,10,45);//F
  rect(270,315,60,10);//G
}
void chiffre_6()
{ 
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
 
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  rect(260,325,10,45);//E
  rect(260,270,10,45);//F
  rect(270,315,60,10);//G
}
void chiffre_7()
{
    
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
 
}
void chiffre_8(){
  
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  rect(260,325,10,45);//E
  rect(260,270,10,45);//F
  rect(270,315,60,10);//G
 
 // ( positionX,positionY , largeur,longueur)
}
void chiffre_9()
{
  
  //************************
  fill(rouge);
  rect(270,260,60,10);//A
  rect(330,270,10,45);//B
  rect(330,325,10,45);//C
  rect(270,370,60,10);//D
  rect(260,270,10,45);//F
  rect(270,315,60,10);//G
}
//----------------------------------------------------------
void compteur()
{
  //lors affiche devient niveau haut l'afficheur se met a decompter
   
   switchState11 = arduino.digitalRead(afficheur);
 if (switchState11 ==Arduino.HIGH){affiche='O';}
 //pour remettre le temps a 0 seconde on prend le temps reel-temp ecouler
   int m = millis()-lastime; //methode de calcul de temps avec millis
//l'afficheur fonctionne selon le temp m  pour synchroniser avec la seconde
 if (affiche=='O'){
  // int m = millis();
  println(m);
  if(m>=0 && m<=1000){
    chiffre_9();
  }
  if(m>=1000 && m<=2000)
  {
    chiffre_8();
  }
  if(m>=2000 && m<=3000)
  {
    chiffre_7();
  }
  if(m>=3000 && m<=4000)
  {
    chiffre_6();
  }
  if(m>=4000 && m<=5000)
  {
    chiffre_5();
  } 
  if(m>=5000 && m<=6000)
  {
    chiffre_4();
  }
  if(m>=6000 && m<=7000)
  {
    chiffre_3();
  } 
    if(m>=7000 && m<=8000)
  {
    chiffre_2();
  } 
   if(m>=8000 && m<=9000)
  {
    chiffre_1();
  } 
    if(m>=9000)
  {
    chiffre_0();
    lastime=millis();
    affiche='N';
  }}else{chiffre_0();}
}
