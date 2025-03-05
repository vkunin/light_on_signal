#define trigPin 10
#define echoPin 11
#define led 9

unsigned long startTime = 0;
unsigned long ledOnTime = 0;
int time_waiting_for_signal = 3000;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

long measure_distance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("distance: ");
  Serial.println(distance);
  return distance;
}

bool wait_for_signal() {
  long distance = measure_distance();
  if (distance < 10) {
    return true;
  } else {
    return false;
  }
}

void light_led(){
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
}

void light_led_on_signal() {
  startTime = millis();
  while(true){
    if ((millis() - startTime) > time_waiting_for_signal) {
      return;
    }
    if (wait_for_signal()) {
      light_led();
      startTime = millis();
    }
    delay(100);
  }
}

void loop() {
  light_led_on_signal();
  Serial.println("All done");
  delay(100);
  exit(0);

  delay(500);
}
