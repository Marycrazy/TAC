// --- definitions ---
#define BUZZER_PIN 3
#define PIR_PIN 7
#define LED_PIN 8
#define TIME_THRESHOLD_BUZZER 10000ul // 10000ul = 10000 unsigned long
#define TIME_THRESHOLD_LED 30000ul // 30000ul = 30000 unsigned long

// --- states ---
enum class DETECTION_STATE {
  IDLE,
  MOTION_DETECTED
};

// --- prototypes ---
void state_machine();
DETECTION_STATE check_idle(unsigned long &time);
DETECTION_STATE check_motion_detected(unsigned long time);
DETECTION_STATE check_motion_stopped(unsigned long time);

// --- start of the program ---
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  state_machine();
}
// --- end of the program ---

// --- functions ---
DETECTION_STATE check_idle(unsigned long &time) {
  bool sensor = digitalRead(PIR_PIN);
  if (sensor) {
    Serial.println("Motion detected!");
    time = millis();
    return DETECTION_STATE::MOTION_DETECTED;
  }
  return DETECTION_STATE::IDLE;
}

DETECTION_STATE check_motion_detected(unsigned long time) {
  bool sensor = digitalRead(PIR_PIN);
  if (!sensor && millis() - time > TIME_THRESHOLD_LED) {
    Serial.println("Motion stopped!");
    return DETECTION_STATE::IDLE;
  }
  digitalWrite(BUZZER_PIN, millis() - time < TIME_THRESHOLD_BUZZER ? HIGH : LOW);
  digitalWrite(LED_PIN, millis() - time < TIME_THRESHOLD_LED ? HIGH : LOW);
  return DETECTION_STATE::MOTION_DETECTED;
}

void state_machine() {
  static DETECTION_STATE state = DETECTION_STATE::IDLE;
  static unsigned long time = millis();

  switch (state) {
    case DETECTION_STATE::IDLE: state = check_idle(time);
      break;
    case DETECTION_STATE::MOTION_DETECTED: state = check_motion_detected(time);
      break;
    default: Serial.println("ERROR: Invalid state");
      break;
  }
}