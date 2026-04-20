// ============================================================
//  SISTEMA DE RIEGO AUTOMÁTICO
//  Hardware: Arduino Mega 2560 + Sensor de Humedad +
//            Relé + Minibomba Sumergible
// ============================================================

// ---------- PINES ----------
const int PIN_SENSOR   = A0;   // Sensor de humedad (analógico)
const int PIN_RELE = 8;    // Relé (activo en LOW por defecto)
const int PIN_LED      = 13;   // LED integrado (indicador)

// ---------- UMBRALES DE HUMEDAD (ajusta según tu sensor) ----------
// El sensor entrega 0–1023:
//   Valor ALTO  → suelo SECO
//   Valor BAJO  → suelo HÚMEDO
const int UMBRAL_SECO   = 700;  // Por encima → activar bomba
const int UMBRAL_HUMEDO = 400;  // Por debajo → apagar bomba

// ---------- TIEMPOS ----------
const unsigned long TIEMPO_RIEGO_MAX  =  6000UL; // 7 s máx de riego continuo
const unsigned long TIEMPO_PAUSA      =  5000UL; // 5 s de pausa tras riego
const unsigned long INTERVALO_LECTURA =  1000UL; // Leer sensor cada 1 s

// ---------- VARIABLES DE ESTADO ----------
bool  bombaEncendida   = false;
unsigned long tiempoInicioBomba = 0;
unsigned long ultimaLectura     = 0;
bool  enPausa = false;
unsigned long tiempoInicioPausa = 0;

// ============================================================
void setup() {
  Serial.begin(9600);

  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_LED,  OUTPUT);

  apagarBomba();   // Estado seguro al inicio

  Serial.println("=== SISTEMA DE RIEGO INICIADO ===");
  Serial.println("Umbral SECO  : " + String(UMBRAL_SECO));
  Serial.println("Umbral HÚMEDO: " + String(UMBRAL_HUMEDO));
  Serial.println("---------------------------------");
}

// ============================================================
void loop() {
  unsigned long ahora = millis();

  // -- Manejo del período de pausa post-riego --
  if (enPausa) {
    if (ahora - tiempoInicioPausa >= TIEMPO_PAUSA) {
      enPausa = false;
      Serial.println("[PAUSA] Terminada. Reanudando monitoreo...");
    } else {
      return;  // Esperar sin hacer nada
    }
  }

  // -- Leer sensor en intervalos regulares --
  if (ahora - ultimaLectura >= INTERVALO_LECTURA) {
    ultimaLectura = ahora;

    int valorHumedad = analogRead(PIN_SENSOR);
    int porcentaje   = map(valorHumedad, 1023, 0, 0, 100);

    Serial.print("[SENSOR] Valor: ");
    Serial.print(valorHumedad);
    Serial.print("  |  Humedad aprox: ");
    Serial.print(porcentaje);
    Serial.println("%");

    // -- Lógica de control de bomba --
    if (!bombaEncendida && valorHumedad > UMBRAL_SECO) {
      encenderBomba();
    }

    if (bombaEncendida && valorHumedad < UMBRAL_HUMEDO) {
      apagarBomba();
      iniciarPausa();
    }
  }

  // -- Seguridad: apagar bomba si supera tiempo máximo --
  if (bombaEncendida && (ahora - tiempoInicioBomba >= TIEMPO_RIEGO_MAX)) {
    Serial.println("[SEGURIDAD] Tiempo máximo alcanzado. Apagando bomba.");
    apagarBomba();
    iniciarPausa();
  }
}

// ============================================================
//  FUNCIONES AUXILIARES
// ============================================================

void encenderBomba() {
  digitalWrite(PIN_RELE, LOW);   // LOW activa la mayoría de módulos relé
  digitalWrite(PIN_LED,  HIGH);     
  bombaEncendida    = true;
  tiempoInicioBomba = millis();
  Serial.println(">>> BOMBA ENCENDIDA <<<");
}

void apagarBomba() {
  digitalWrite(PIN_RELE, HIGH);
  digitalWrite(PIN_LED,  LOW);
  bombaEncendida = false;
  Serial.println(">>> BOMBA APAGADA <<<");
}

void iniciarPausa() {
  enPausa           = true;
  tiempoInicioPausa = millis();
  Serial.println("[PAUSA] Esperando " + String(TIEMPO_PAUSA / 1000) + " segundos...");
}