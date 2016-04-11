    /*===================================================================== 
    ~Le code permet a faire un jeu de feu de signalisation au
    ~niveau des intersections routier 
     -------   Manuel   ---------
         Par:Josaphat Mayuba,claude dzoti lappa,dorvelus rony,tchougnia alain jojo.
    >>---------PORT ENTREE------------------------
    PORT 42 == POWER // control processing
    PORT 26 == Bonton pousoir pieton
    <<---------PORT SORTI-------------------------
    Ligne 1
    PORT (2,3,4,5) ===> (LED ROUGE, LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
    Ligne 2
    PORT (6,7,8,9) ===> (LED ROUGE,LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
    Ligne 3
    PORT (10,11,12,13) ===> (LED ROUGE,LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
    Ligne 4
    PORT (23,24,25,26) ===> (LED ROUGE,LED JAUNE, LED VERT PASSAGE, LED VERT VIREMENT)
    <<--------AFFICHEUR 7 SEGMENT-------------------
    PORT (53,52,51,50,49,48,47) == >(A,B,C,D,E,F,G) 
    <<--------- TONALITÉ  ----------------
    PORT 45 
    <<------- DEL RG ----------------
    PORT (28,29) ===> (R,G)  Cote 1 et 3
    PORT (30,31) ===> (R,G)  Cote 2 et 4
   >>-----------  AUTRE VARIABLE  ----------------
  char demande;  verificateur pour la demande de passager avec bouton pousoir pour savoir
  etat de la presence de passagers
  demande = N Lors il y'a aucun passager
  demande = A Lors le passagers appui pendant le feu est a jaune
  demande = P Lors signal la presence des passagers
    ================================================ ===================== */
     const int power=42; //port control processing
    //broche de feu de route ligne 1
    const int led_virer_ligne1=5;//feu de virement vert
    const int led_vert_ligne1=4;
    const int led_jaune_ligne1=3;
    const int led_rouge_ligne1=2;
    //************************
     
    //broche pour le feu de route ligne 2
    const int led_virer_ligne2=9;//feu de virement vert
    const int led_vert_ligne2=8;
    const int led_jaune_ligne2=7;
    const int led_rouge_ligne2=6;
    //*********************
    //broche pour le feu de route ligne 3
    const int led_virer_ligne3=13;//feu de virement vert
    const int led_vert_ligne3=12; 
    const int led_jaune_ligne3=11;
    const int led_rouge_ligne3=10;
    //*****************************
    //**********************
    //broche pour le feu de route ligne 4
    const int led_virer_ligne4=25;//feu de virement vert
    const int led_vert_ligne4=24; // led vert
    const int led_jaune_ligne4=23; // led jaune
    const int led_rouge_ligne4=22; //led rouge
     
    //************************************
    int led_antend=33;//feu de temoin pour le passager en appuyant le bouton pousoir
    //AFFICHEUR SEPT SEGMENT
    const int A = 53;
    const int B = 52;
    const int C = 51;
    const int D = 50;
    const int E = 49;
    const int F = 48;
    const int G = 47;
    //AFFICHE 10 CHIFFRE ANODE COMMUN
    byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1}, // = 0
    { 1,0,0,1,1,1,1 }, // = 1
    { 0,0,1,0,0,1,0 }, // = 2
    { 0,0,0,0,1,1,0 }, // = 3
    { 1,0,0,1,1,0,0 }, // = 4
    { 0,1,0,0,1,0,0 }, // = 5
    { 0,1,0,0,0,0,0 }, // = 6
    { 0,0,0,1,1,1,1}, // = 7
    { 0,0,0,0,0,0,0 }, // = 8
    { 0,0,0,0,1,0,0} // = 9 
     
    };
    //PIN RG feu passager
    const int pinR = 28; // broche reliée à la couleur rouge de la DEL RG
    const int pinG = 29; // broche reliée à la couleur verte de la DEL RG
    
    const int pinR2 = 30; // broche reliée à la couleur rouge de la DEL RG 
    const int pinG2 = 31; // broche reliée à la couleur verte de la DEL RG 
    //tone
    const int ton=45;
    //bouton pousoir
    const int buttonPin = 26; // la broche du bouton poussoir
    int buttonState = 0; // variable pour l’état du bouton
    int buttonpower=0; //etant bouton control
    //*********************************
    //verificateur pour la demande de passager avec bouton pousoir
    //etat de presence de passager
    char demande='N';
    //arret son
    char arret='A';
    //**************************************
    void setup()
    {
      //configuration de port 
      //toutes le led
    pinMode( led_vert_ligne1 , OUTPUT);
    pinMode( led_jaune_ligne1 , OUTPUT);
    pinMode( led_rouge_ligne1 , OUTPUT);
    
    pinMode( led_vert_ligne2 , OUTPUT);
    pinMode( led_jaune_ligne2 , OUTPUT);
    pinMode( led_rouge_ligne2 , OUTPUT);
    
    pinMode( led_vert_ligne3 , OUTPUT);
    pinMode( led_jaune_ligne3 , OUTPUT);
    pinMode( led_rouge_ligne3 , OUTPUT);
    
    pinMode( led_vert_ligne4 , OUTPUT);
    pinMode( led_jaune_ligne4 , OUTPUT);
    pinMode( led_rouge_ligne4 , OUTPUT);
    
    pinMode( led_antend , OUTPUT);
    pinMode( led_virer_ligne1 , OUTPUT);
    pinMode( led_virer_ligne2 , OUTPUT);
    pinMode( led_virer_ligne3 , OUTPUT);
    pinMode( led_virer_ligne4 , OUTPUT);
    // ENTREE Processing
    pinMode( power , INPUT);
    //AFFICHEUR 7 SEGMENT
    //définition des broches en sortie
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    //PIN LED 3 COULEUR 
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinR2, OUTPUT);
    pinMode(pinG2, OUTPUT);
    //BOUTON pousoir
    pinMode (buttonPin, INPUT); // initialisation de la broche du bouton comme entrée
     
    //INITIALISATION
    Led_init();
    Serial.begin(9600);
    Serial.println("commence");
    }
    
    void loop()
    {
      
     //**********1**********
     buttonpower=digitalRead(power); //donne l'etat de control sur processing
     if (buttonpower== LOW){    //si bouton pousoir LOW
        init_passage();        //initialisation  de DEL
    int mills=1000;            //Multiplicateur time
     arret='C';      //
    while(mills!=0){  // verifi l'etat de multiplicateur 
    mills=mills-1;    //incremente le multiplicateur
    buttonState = digitalRead(buttonPin); //verifi l'etat de bouton pousoir
    if (demande=='A') {demande='P';}  // 
    if (buttonState == LOW) { demande='P'; ton_ok();}
    if(mills==800){feu_passager_ligne1();}
    attend();
     feu_vert_ligne1(); 
     feu_rouge_ligne2();
     delay(10);
     Serial.print(buttonState);
     }
     //**********2********************8*
     int mills_v=20;
     arret='C';
     while(mills_v!=0)
    { 
       mills_v=mills_v-1;
        buttonState = digitalRead(buttonPin);
     if (buttonState == LOW) {demande='P'; ton_ok();}
     attend();
     feu_vir_ligne1();
     feu_rouge_ligne2();
      delay(10);
    }
     //********3*************************
     int mills_j=500;
      arret='C';
     while(mills_j!=0)
      {
     mills_j=mills_j-1;
     buttonState = digitalRead(buttonPin);
     if (buttonState == LOW) {demande='P'; ton_ok();}
    attend();
    feu_jaune_ligne1();
     feu_rouge_ligne2();
     delay(10);
       }
     //*********4*****************************
      int mills_r=200;
      arret='C';
     while(mills_r!=0)
      {
       mills_r=mills_r-1;
       buttonState = digitalRead(buttonPin);
       if (demande!='P')
       {
       if (buttonState == LOW) {demande='A'; ton_ok();}
       }
       attend();
        feu_rouge_ligne1(); 
        feu_rouge_ligne2();
        if(mills_r==100){passage();}
        delay(10);
     }
     //**********5***************************
     int mills_r2=500;
      arret='C';
     while(mills_r2!=0)
      {
       mills_r2=mills_r2-1;
       buttonState = digitalRead(buttonPin);
       
       if (buttonState == LOW) {demande='P'; ton_ok();}
       
       attend();
        feu_rouge_ligne1(); 
        feu_vert_ligne2();
        if(mills_r2==200){feu_passager_ligne2();}
        delay(10);
     }
     //*****************6********************************
     int mills_v2=20;
      arret='C';
    while(mills_v2!=0){
    mills_v2=mills_v2-1;
    buttonState = digitalRead(buttonPin);
    if (demande=='A') {demande='P';}
    if (buttonState == LOW) {demande='P'; ton_ok();}
    attend();
      feu_vir_ligne2();
     feu_rouge_ligne1();
     delay(10);
     } 
     //**************7******************
     int mills_j2=300;
      arret='C';
     while(mills_j2!=0)
    {
       mills_j2=mills_j2-1;
        buttonState = digitalRead(buttonPin);
     if (buttonState == LOW) {demande='P'; ton_ok();}
    attend();
     feu_jaune_ligne2();
     feu_rouge_ligne1();
      delay(10);
    } 
     //***********8*********************
     int mills_j3=200;
      arret='C';
     while(mills_j3!=0)
    {
       mills_j3=mills_j3-1;
        buttonState = digitalRead(buttonPin);
      if (demande!='P')
       {
       if (buttonState == LOW) {demande='A'; ton_ok();}
       }
        
       if(mills_r==100){passage();}
       
    attend();
     feu_rouge_ligne2();
     feu_rouge_ligne1();
      delay(10);
    }
     }else{
         
       arret_complet();
     }
       
     
    }
    //************************toutes methodes********************
    //initialisation de toutes les Dels
    void Led_init(){
    digitalWrite( led_vert_ligne1 , HIGH );
    digitalWrite( led_jaune_ligne1 , HIGH );
    digitalWrite( led_rouge_ligne1 , HIGH );
    
    digitalWrite( led_vert_ligne2 , HIGH );
    digitalWrite( led_jaune_ligne2 , HIGH );
    digitalWrite( led_rouge_ligne2 , HIGH );
    
    digitalWrite( led_vert_ligne3 , HIGH );
    digitalWrite( led_jaune_ligne3 , HIGH );
    digitalWrite( led_rouge_ligne3 , HIGH );
    
    digitalWrite( led_vert_ligne4 , HIGH );
    digitalWrite( led_jaune_ligne4 , HIGH );
    digitalWrite( led_rouge_ligne4 , HIGH );
    digitalWrite( led_antend , HIGH );
    digitalWrite( led_virer_ligne1 , HIGH );
    digitalWrite( led_virer_ligne2 , HIGH );
    digitalWrite( led_virer_ligne3 , HIGH );
    digitalWrite( led_virer_ligne4 , HIGH );
    
    digitalWrite(pinR,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG2,LOW);
    sevenSegWrite(0);
    }
    void init_passage(){
      digitalWrite(pinR,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG2,LOW);
    }
    void feu_vert_ligne1()
    {
      //ALLUME VERT
    digitalWrite( led_vert_ligne1 , LOW );   
    digitalWrite( led_jaune_ligne1 , HIGH );
    digitalWrite( led_rouge_ligne1 , HIGH );
    digitalWrite( led_vert_ligne3 , LOW );   
    digitalWrite( led_jaune_ligne3 , HIGH );
    digitalWrite( led_rouge_ligne3 , HIGH );
    
      
    }
    void feu_vert_ligne2()
    {
      //ALLUME VERT
    digitalWrite( led_vert_ligne2 , LOW );   
    digitalWrite( led_jaune_ligne2 , HIGH );
    digitalWrite( led_rouge_ligne2 , HIGH );
    digitalWrite( led_vert_ligne4 , LOW );   
    digitalWrite( led_jaune_ligne4 , HIGH );
    digitalWrite( led_rouge_ligne4 , HIGH );
    
      
    }
    void feu_jaune_ligne1()
    {
      //ALLUME JAUNE
    digitalWrite( led_vert_ligne1 , HIGH );
    digitalWrite( led_jaune_ligne1 , LOW );
    digitalWrite( led_rouge_ligne1 , HIGH );
    digitalWrite( led_vert_ligne3 , HIGH );
    digitalWrite( led_jaune_ligne3 , LOW );
    digitalWrite( led_rouge_ligne3 , HIGH );
    //digitalWrite( led_passage , HIGH ); 
     
    }
    void feu_jaune_ligne2()
    {
      //ALLUME JAUNE
    digitalWrite( led_vert_ligne2 , HIGH );
    digitalWrite( led_jaune_ligne2 , LOW );
    digitalWrite( led_rouge_ligne2 , HIGH );
    digitalWrite( led_vert_ligne4 , HIGH );
    digitalWrite( led_jaune_ligne4 , LOW );
    digitalWrite( led_rouge_ligne4 , HIGH );
    //digitalWrite( led_passage , HIGH ); 
     
    }
    void feu_rouge_ligne1()
    {
    digitalWrite( led_vert_ligne1 , HIGH );
    digitalWrite( led_jaune_ligne1 , HIGH );
    digitalWrite( led_rouge_ligne1 , LOW );
    digitalWrite( led_vert_ligne3 , HIGH );
    digitalWrite( led_jaune_ligne3 , HIGH );
    digitalWrite( led_rouge_ligne3 , LOW );
    //digitalWrite( led_passage , HIGH );
     
    }
    void feu_rouge_ligne2()
    {
    digitalWrite( led_vert_ligne2 , HIGH );
    digitalWrite( led_jaune_ligne2 , HIGH );
    digitalWrite( led_rouge_ligne2 , LOW );
    digitalWrite( led_vert_ligne4 , HIGH );
    digitalWrite( led_jaune_ligne4 , HIGH );
    digitalWrite( led_rouge_ligne4 , LOW );
    
     
    }
    void feu_vir_ligne1(){
        buttonState = digitalRead(buttonPin);
     if (buttonState == LOW) {demande='P'; ton_ok();}
     attend();
      digitalWrite( led_virer_ligne1 , LOW );
      digitalWrite( led_vert_ligne1 , HIGH );
        digitalWrite( led_virer_ligne3 , LOW );
      digitalWrite( led_vert_ligne3 , HIGH );
      delay(200);
       digitalWrite( led_virer_ligne1 , HIGH );
       digitalWrite( led_vert_ligne1 , HIGH );
       digitalWrite( led_virer_ligne3 , HIGH );
       digitalWrite( led_vert_ligne3 , HIGH );
        delay(200);
       
    }
    void feu_vir_ligne2(){
        buttonState = digitalRead(buttonPin);
     if (buttonState == LOW) {demande='P'; ton_ok();}
     attend();
      digitalWrite( led_virer_ligne2 , LOW );
      digitalWrite( led_vert_ligne2 , HIGH );
      digitalWrite( led_virer_ligne4 , LOW );
      digitalWrite( led_vert_ligne4 , HIGH );
      delay(200);
       digitalWrite( led_virer_ligne2 , HIGH );
       digitalWrite( led_vert_ligne2 , HIGH );
        digitalWrite( led_virer_ligne4 , HIGH );
       digitalWrite( led_vert_ligne4 , HIGH );
        delay(200);
       
    }
    //SIGNALISATION DE PIETON
    void feu_passager_ligne1()
    {
     
    //allume la led en couleur vert
    digitalWrite(pinR,LOW);  
    digitalWrite(pinG,HIGH);
    delay(5000);  //attend 5 seconde
    int n=10;  //valeur n utiliser comme multiplicateur de delay
    while(n!=0){
        buttonState = digitalRead(buttonPin);
       if (buttonState == LOW) {demande='P'; ton_ok();}//____________
    attend();
    n=n-1;  //decrementation de la valeur de n
     //digitalWrite( led_passage , LOW );
    digitalWrite(pinR,HIGH); // active la couleur rouge  
    digitalWrite(pinG,LOW);
    sevenSegWrite(n);  //decremente lafficheur sept segment
     tone(ton,1000,100);
    delay(500);
    
    //digitalWrite( led_passage , HIGH );
    digitalWrite(pinR,LOW);  
    digitalWrite(pinG,LOW);
    delay(500);
    sevenSegWrite(0);
     
    }
     //eteint Dels R ET G
    digitalWrite(pinR,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG,LOW);
    digitalWrite( led_antend , HIGH );
    }
    void feu_passager_ligne2()
    {
     
    //allume la led en couleur vert
    digitalWrite(pinR2,LOW);  
    digitalWrite(pinG2,HIGH);
    delay(5000);  //attend 5 seconde
    int n=10;  //valeur n utiliser comme multiplicateur de delay
    while(n!=0){
       buttonState = digitalRead(buttonPin);
       if (buttonState == LOW) {demande='P'; ton_ok();}//__________________________
    n=n-1;  //decrementation de la valeur de n
    
     attend();
    digitalWrite(pinR2,HIGH); // active la couleur rouge  
    digitalWrite(pinG2,LOW);
    sevenSegWrite(n);  //decremente lafficheur sept segment
     tone(ton,1000,100);
    delay(500);
    digitalWrite(pinR2,LOW);  
    digitalWrite(pinG2,LOW);
    delay(500);
    sevenSegWrite(0);
     
    }
     //eteint Dels R ET G
    digitalWrite(pinR2,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG2,LOW);
    digitalWrite( led_antend , HIGH );
    }
    //afficheur sept segment
    void sevenSegWrite(byte digit) {
    byte pin = 53;
    for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    --pin;
    }
    }
    void feu_passager_arret()
    {
     
    //allume la led en couleur vert
    digitalWrite(pinR,LOW);  
    digitalWrite(pinG,HIGH);
    digitalWrite(pinR2,LOW);  
    digitalWrite(pinG2,HIGH);
    digitalWrite(pinG2,HIGH);
    delay(5000);  //attend 5 seconde
    int n=10;  //valeur n utiliser comme multiplicateur de delay
    while(n!=0){
    n=n-1;  //decrementation de la valeur de n
    digitalWrite(pinR,HIGH); // active la couleur rouge  
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,HIGH); // active la couleur rouge  
    digitalWrite(pinG2,LOW);
    sevenSegWrite(n);  //decremente lafficheur sept segment
     tone(ton,1000,100);
    delay(500);
    digitalWrite(pinR,LOW);  
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,LOW);  
    digitalWrite(pinG2,LOW);
    delay(500);
    sevenSegWrite(0);
     
    }
     // 
     digitalWrite(pinR,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,HIGH); // active la couleur rouge avec la valeur r
    digitalWrite(pinG2,LOW);
    digitalWrite( led_antend , HIGH );
    }
      //lu l'etat de bouton pousoir 
     void passage()
     {
      // lit l’état du bouton-poussoir
    if (demande == 'P') { 
      feu_passager_arret();
     demande='N';
    }
     }
     
     void arret_complet(){
    digitalWrite(pinR,LOW); // active la couleur rouge avec la valeur r
    digitalWrite(pinG,LOW);
    digitalWrite(pinR2,LOW); // active la couleur rouge avec la valeur r
    digitalWrite(pinG2,LOW);
      digitalWrite( led_rouge_ligne1 , HIGH);
      digitalWrite( led_rouge_ligne2 , HIGH);
      digitalWrite( led_rouge_ligne3 , HIGH);
      digitalWrite( led_rouge_ligne4 , HIGH);
      
     int m=millis()/1000%2;
     if(m==1){
     digitalWrite( led_jaune_ligne1 , LOW );
      digitalWrite( led_jaune_ligne2 , LOW );
       digitalWrite( led_jaune_ligne3 , LOW );
      digitalWrite( led_jaune_ligne4 , LOW );
     }else{
    digitalWrite( led_jaune_ligne1 , HIGH );
      digitalWrite( led_jaune_ligne2 , HIGH );
       digitalWrite( led_jaune_ligne3 , HIGH );
      digitalWrite( led_jaune_ligne4 , HIGH );}
    
     }
     
    void attend()
    {
      if(demande=='P'||demande=='A'){
      digitalWrite( led_antend , LOW );
    }
    }
    //ton lors le bouton pousoir appuyer
    void ton_ok(){
       tone(ton,2000,50);
       delay(100);
       tone(ton,2000,50);
       delay(100);
        
    }
