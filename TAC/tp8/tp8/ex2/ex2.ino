#define BUTTON_PIN 2
#define DISPLAY_A 3
#define DISPLAY_B 4
#define DISPLAY_C 5
#define DISPLAY_D 6
#define DISPLAY_E 7
#define DISPLAY_F 8
#define DISPLAY_G 9

bool flag = false;

void display_number(int num);
void start_timer();
void set_flag();

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for (int i = DISPLAY_A; i <= DISPLAY_G; i++) pinMode(i, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), set_flag, RISING);
}

void loop() {
  start_timer();
}

void display_number(int num) {
  static const byte NUMBERS[][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1 
  {1,1,0,1,1,0,1}, // 2 
  {1,1,1,1,0,0,1}, // 3  
  {0,1,1,0,0,1,1}, // 4  
  {1,0,1,1,0,1,1}, // 5 
  {1,0,1,1,1,1,1}, // 6 
  {1,1,1,0,0,0,0}, // 7   
  {1,1,1,1,1,1,1}, // 8  
  {1,1,1,1,0,1,1}  // 9  
  };
  for (int i = 0; i < 7; i++) digitalWrite(DISPLAY_A + i, NUMBERS[num][i]);
}

void set_flag() {
  static unsigned long last_interrupt_time = 0;
  if (millis() - last_interrupt_time > 50) {
    flag = true;
    last_interrupt_time = millis();
  }
}

void start_timer() {
  static int current_number = 10;
  static unsigned long time = 0;
  if (flag && millis() - time > 1000) {
    current_number--;
    if (current_number < 0) {
      current_number = 9;
    }
    display_number(current_number);
    time = millis();
    if (current_number == 0) {
      flag = false;
    }
  }
}