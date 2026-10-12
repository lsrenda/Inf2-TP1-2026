const int PIN_BOTON = 2;
const int PIN_LED = 13;

bool ledEncendido = false;
int ultimaLectura = HIGH;
int estadoEstable = HIGH;
unsigned long tiempoInicio = 0;
unsigned long ultimoTiempoDebounce = 0;
const unsigned long tiempoDebounce = 50;
const unsigned long intervaloDeseado = 60000;

void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);   // pull-up interno
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
}

void loop() {
  int lectura = digitalRead(PIN_BOTON);

  if (lectura != ultimaLectura) {
    ultimoTiempoDebounce = millis();
  }

  if ((millis() - ultimoTiempoDebounce) > tiempoDebounce && lectura != estadoEstable) {
    estadoEstable = lectura;
    if (estadoEstable == LOW) {          // apretado = LOW
      ledEncendido = !ledEncendido;
      if (ledEncendido) tiempoInicio = millis();
      Serial.println(ledEncendido ? "LED ON" : "LED OFF (manual)");
    }
  }
  ultimaLectura = lectura;

  if (ledEncendido && millis() - tiempoInicio >= intervaloDeseado) {
    ledEncendido = false;
    Serial.println("LED OFF (60 s)");
  }

  digitalWrite(PIN_LED, ledEncendido ? HIGH : LOW);
}
