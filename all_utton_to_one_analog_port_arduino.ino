// ======= Определение пинов =======
#define PIN_TRIG 2   // Пин для ультразвукового датчика (триггер)
#define PIN_ECHO 3   // Пин для ультразвукового датчика (эхо)
#define PIN_LED 4    // Пин для светодиодной ленты

// Массив для пинов моторов.  Первый мотор - шторы, второй - вешалка.
const int motorPins[][4] = {
  {5, 6, 7, 8},  // Мотор 1 (шторы)
  {9, 10, 11, 12} // Мотор 2 (вешалка)
};

// ======= Определение констант =======
const int buttons_pin = A0; // Аналоговый пин для кнопок
const int button_ranges[] = {100,150,200,600,1100}; // Диапазоны значений для кнопок

// ======= Глобальные переменные =======
int opusk = 2;         // Глобальная переменная для управления мотором
float duration;       // Переменная для хранения длительности импульса от ультразвукового датчика
float cm;             // Переменная для хранения расстояния в сантиметрах
bool people = false;  // Флаг для определения наличия человека
bool light = false;   // Флаг для определения состояния освещения
int curtain = 0;       // Переменная для хранения состояния штор
int hanger = 0;        // Переменная для хранения состояния вешалки


// ======= Функция для определения нажатой кнопки =======
int getButtonPressed() {
    int analogValue = analogRead(buttons_pin); 
    for (size_t i = 1; i < (sizeof(button_ranges) / sizeof(button_ranges[0])); i++) { 
        if (analogValue < button_ranges[i] && analogValue > button_ranges[i - 1]) { 
            return i;  
        }
    }
    return 0;  
}

// ======= Функция для управления моторами =======
void dvigM(int motorIndex, int corner) {
    int dl = 5; // Задержка для управления мотором (можно настроить)

    if (motorIndex < 0 || motorIndex >= 2) {
        Serial.println("Ошибка: Неверный индекс мотора!");
        return;
    }

    // Массив последовательности состояний пинов
    const int states[4][4] = {
        {HIGH, LOW, LOW, HIGH},
        {HIGH, HIGH, LOW, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, LOW, HIGH, HIGH}
    };

    int numSteps = abs(255 * corner); // Количество шагов для вращения
    int direction = corner > 0 ? 1 : -1; // Направление вращения (1 для прямого, -1 для обратного)

    for (int step = 0; step < numSteps; step++) {
        for (int pinIndex = 0; pinIndex < 4; pinIndex++) {
            digitalWrite(motorPins[motorIndex][pinIndex], states[(step * direction + 4000) % 4][pinIndex]);
            //Используем (step * direction + 4000) % 4 для того что бы step оставался в рамках от 0 до 3. 4000 можно заменить любым другим числом.
        }
        delay(dl);
    }
}


// ======= Функция setup() =======
void setup() {
    Serial.begin(9600);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            pinMode(motorPins[i][j], OUTPUT);
        }
    }
}

// ======= Функция loop() =======
void loop() {
  // ------ Ультразвуковой датчик ------
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  duration = pulseIn(PIN_ECHO, HIGH);
  cm = (duration / 2) / 29.1; // растояние до объекта
  

  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");
  Serial.print("освещенность: ");
  Serial.print("people = ");
  Serial.print(people);
  Serial.println(" .");

    // ------ Кнопки и логика управления ------
    int button = getButtonPressed();   // Получаем нажатую кнопку - **Объявление здесь!**
    int analogValue = analogRead(buttons_pin);
    Serial.print("Analog value: ");
    Serial.print(analogValue);
    Serial.print(", Button: ");
    Serial.println(button);

    if (people == true) { 
        if (button == 1) {    
            dvigM(0, opusk);   
            curtain++;       
        } else if (button == 2) {  
            dvigM(0, opusk);   
            curtain--;       
        } else if (button == 3) {  
            if (hanger == 0) { 
                hanger = 1;    
                dvigM(1, 2);      
            } else if (hanger == 1) {  
                hanger = 0;    
                dvigM(1, -2);     
            }
        } else if (button == 4) {  
            if (light == true) {  
                light = false;      
                digitalWrite(PIN_LED, LOW);  
            } else if (light == false) {   
                light = true;       
                digitalWrite(PIN_LED, HIGH); 
            }
        }
    }

    if (people == false) {  
        light = false;         
        digitalWrite(PIN_LED, LOW); 
        if (hanger == 0) {      
            hanger = 1;        
            dvigM(1, 2);         
        }
    }
  
    if (cm < 15) {   
        if (people == true) {  
            people = false;     
        } else if (people == false) { 
            people = true;      
        }
    }
}