#include "../Debouncer.cpp"

int ANALOG_PIN = A0;
int ONBOARD_LED = 13;

int SIGNAL_THRESHOLD = 300;

unsigned long TICK_INTERVAL_MILLIS = 2000;

int DEBOUNCE_MAXIMUM = 5;

unsigned long lastReportTimeMillis;

bool previousState;

Debouncer *debouncer;

void send(const char *message) {
  Serial.println(message);

  lastReportTimeMillis = millis();
}

bool isTimeForTick() {
  unsigned long elapsedTimeMillis = millis() - lastReportTimeMillis;

  return elapsedTimeMillis > TICK_INTERVAL_MILLIS;
}

void setup() {
  Serial.begin(9600);

  pinMode(ANALOG_PIN, INPUT);
  pinMode(ONBOARD_LED, OUTPUT);

  send("STARTED");

  debouncer = new Debouncer(DEBOUNCE_MAXIMUM);
}

void loop() {
  int val = analogRead(ANALOG_PIN);

  bool signal = val > SIGNAL_THRESHOLD;

  bool isUp = debouncer->debounce(signal);

  if (isUp) {
    digitalWrite(ONBOARD_LED, HIGH);
  } else {
    digitalWrite(ONBOARD_LED, LOW);
  }

  if (isUp && !previousState) {
    char usageMessage[60];
    sprintf(usageMessage, "USAGE: %d", val);

    send(usageMessage);
  }

  previousState = isUp;

  if (isTimeForTick()) {
    char tickMessage[60];
    sprintf(tickMessage, "TICK: %d", val);

    send(tickMessage);
  }

  delay(20);
}

