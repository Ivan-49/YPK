
#define PIN_TRIG 2
#define PIN_ECHO 3


#define PIN_BUTTON_1 5
#define PIN_BUTTON_2 6
#define PIN_BUTTON_3 7
#define PIN_BUTTON_4 8

#define in1 9
#define in2 10
#define in3 11
#define in4 12


void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    
  pinMode(PIN_LED, OUTPUT); 

    Serial.begin (9600);
  //Определяем вводы и выводы
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop() {


  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  duration = pulseIn(PIN_ECHO, HIGH);
  cm = (duration / 2) / 29.1; // растояние до объекта
  
  photo = analogRead(PIN_PHOTO_SENSOR);

  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");
  Serial.print("освещенность: ");
  Serial.print(photo);
  Serial.println(" единиц.");
  Serial.print("people = ");
  Serial.print(people);
  Serial.println(" .");


  delay(250);
  if (cm< 10){
    if (people == true){
      people = false;
    }else{
      people = true;
    }
    delay(300);
  }
  if(people==true){
      if(light==true){
        light = false;
      }else{
        light = true;
      }
    }

  
  if (people){
    digitalWrite(PIN_LED, HIGH);
  }else{
    digitalWrite(PIN_LED, LOW);
  }

  if(people && photo>aaaaaaaaaaaa){
    dvig(2);
    delay(1000);
    dvig(-2);
  } 
}


void dvig(int corner){
    int dl = 5;

    if(corner<0){
      for(int i =0; i<-255*corner; i++){
      
        digitalWrite(in1, HIGH); 
        digitalWrite(in2, LOW); 
        digitalWrite(in3, LOW); 
        digitalWrite(in4, HIGH);
        delay(dl);

        digitalWrite(in1, HIGH); 
        digitalWrite(in2, HIGH); 
        digitalWrite(in3, LOW); 
        digitalWrite(in4, LOW);
        delay(dl);

        digitalWrite(in1, LOW); 
        digitalWrite(in2, HIGH); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, LOW);
        delay(dl);

        digitalWrite(in1, LOW); 
        digitalWrite(in2, LOW); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, HIGH);
        delay(dl);
      }
    }else{
      for(int i =0; i<255*corner; i++){
        digitalWrite(in1, LOW); 
        digitalWrite(in2, LOW); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, HIGH);
        delay(dl);

        digitalWrite(in1, LOW); 
        digitalWrite(in2, HIGH); 
        digitalWrite(in3, HIGH); 
        digitalWrite(in4, LOW);
        delay(dl);

        digitalWrite(in1, HIGH); 
        digitalWrite(in2, HIGH); 
        digitalWrite(in3, LOW); 
        digitalWrite(in4, LOW);
        delay(dl);

        digitalWrite(in1, HIGH); 
        digitalWrite(in2, LOW); 
        digitalWrite(in3, LOW); 
        digitalWrite(in4, HIGH);
        delay(dl);

      }
    }
}



