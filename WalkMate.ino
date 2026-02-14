#define trigPinCenter 8
#define echoPinCenter 9
#define trigPinRight 6
#define echoPinRight 7

#define vibroRight 3
#define vibroLeft 4

long duration;
int distanceCenter, distanceRight;

void setup() {
  pinMode(trigPinCenter, OUTPUT);
  pinMode(echoPinCenter, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);

  pinMode(vibroRight, OUTPUT);
  pinMode(vibroLeft, OUTPUT);

  digitalWrite(vibroRight, LOW);
  digitalWrite(vibroLeft, LOW);

  Serial.begin(9600);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // ограничение по времени
  int distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  distanceCenter = getDistance(trigPinCenter, echoPinCenter);
  distanceRight = getDistance(trigPinRight, echoPinRight);

  Serial.print("Center: ");
  Serial.print(distanceCenter);
  Serial.print(" cm | Right: ");
  Serial.print(distanceRight);
  Serial.println(" cm");

  // ---- Центральный датчик ----
  if (distanceCenter > 0 && distanceCenter <= 50) {
    digitalWrite(vibroRight, HIGH);
    digitalWrite(vibroLeft, HIGH);
  } 
  else if (distanceCenter > 50 && distanceCenter <= 100) {
    digitalWrite(vibroRight, HIGH);
    digitalWrite(vibroLeft, HIGH);
    delay(100);
    digitalWrite(vibroRight, LOW);
    digitalWrite(vibroLeft, LOW);
    delay(200);
  } 
  else {
    // ---- Правый датчик ----
    if (distanceRight > 0 && distanceRight <= 50) {
      digitalWrite(vibroRight, HIGH);
    } 
    else if (distanceRight > 50 && distanceRight <= 100) {
      digitalWrite(vibroRight, HIGH);
      delay(100);
      digitalWrite(vibroRight, LOW);
      delay(200);
    } 
    else {
      digitalWrite(vibroRight, LOW);
    }

    // Центральный не видит ничего → левый мотор выключен
    digitalWrite(vibroLeft, LOW);
  }

  delay(50);
}