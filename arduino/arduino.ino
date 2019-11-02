#include "../Debouncer.cpp"
#include "../Filter.cpp"

int ANALOG_PIN = A0;
int ONBOARD_LED = 13;

int LOW_SIGNAL_THRESHOLD = 300; // Average low signal is 200
int HIGH_SIGNAL_THRESHOLD = 400; // Average high signal is 480

unsigned long TICK_INTERVAL_MILLIS = 2000;

int DEBOUNCE_MAXIMUM = 5;

unsigned long lastReportTimeMillis;

Debouncer *lowDebouncer;
Debouncer *highDebouncer;

Filter *filter;

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

  lowDebouncer = new Debouncer(DEBOUNCE_MAXIMUM, true); // Start assuming that we're up
  highDebouncer = new Debouncer(DEBOUNCE_MAXIMUM, false);
  filter = new Filter();
}

void loop() {
  int val = analogRead(ANALOG_PIN);

  bool isSignalLow = val < LOW_SIGNAL_THRESHOLD;
  bool isSignalHigh = HIGH_SIGNAL_THRESHOLD < val;

  bool isLow = lowDebouncer->debounce(isSignalLow);
  bool isHigh = highDebouncer->debounce(isSignalHigh);

  if (isHigh) {
    digitalWrite(ONBOARD_LED, HIGH);
  } else {
    digitalWrite(ONBOARD_LED, LOW);
  }

  bool transitionedToHigh = filter->activated(isLow, isHigh);

  if (transitionedToHigh) {
    char usageMessage[60];
    sprintf(usageMessage, "USAGE: %d", val);

    send(usageMessage);
  }

  if (isTimeForTick()) {
    char tickMessage[60];
    sprintf(tickMessage, "TICK: %d", val);

    send(tickMessage);
  }

  delay(20);
}

