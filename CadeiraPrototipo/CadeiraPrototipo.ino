#define IN1_PIN  4
#define IN2_PIN  5
#define IN3_PIN  6
#define IN4_PIN  7
#define VRY_PIN  A0  // Defina o pino VRY_PIN
#define VRX_PIN  A1  // Defina o pino VRX_PIN

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 600
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  600

int speed = 0;  // Velocidade nos eixos X e Y

bool wasJoystickMoved = false;   // Variável de controle para verificar se o joystick foi movido

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
}

void loop() {
  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);

  if (abs(xValue - 512) > 10 || abs(yValue - 512) > 10) {
    // Joystick foi movido
    wasJoystickMoved = true;

    // Calcula a velocidade com base no valor do joystick
    speed = map(max(abs(xValue - 512), abs(yValue - 512)), 0, 512, 0, 255);

    if (xValue > RIGHT_THRESHOLD) {
      // Virar à direita com o motor do eixo X em um único sentido
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
      analogWrite(IN3_PIN, speed);
      analogWrite(IN4_PIN, speed);
    } else if (xValue < LEFT_THRESHOLD) {
      // Virar à esquerda
      digitalWrite(IN4_PIN, LOW);
      digitalWrite(IN3_PIN, HIGH);
      analogWrite(IN2_PIN, speed);
      analogWrite(IN1_PIN, speed);
    } else if (yValue > UP_THRESHOLD) {
      // Mover para frente
      analogWrite(IN1_PIN, speed);
      analogWrite(IN2_PIN, 0);
      analogWrite(IN3_PIN, speed);
      analogWrite(IN4_PIN, 0);
    } else if (yValue < DOWN_THRESHOLD) {
      // Mover para trás
      analogWrite(IN1_PIN, 0);
      analogWrite(IN2_PIN, speed);
      analogWrite(IN3_PIN, 0);
      analogWrite(IN4_PIN, speed);
    }
  } else if (wasJoystickMoved) {
    // Joystick voltou à posição neutra após ter sido movido
    analogWrite(IN1_PIN, 0);
    analogWrite(IN2_PIN, 0);
    analogWrite(IN3_PIN, 0);
    analogWrite(IN4_PIN, 0);
    wasJoystickMoved = false;
  }
}