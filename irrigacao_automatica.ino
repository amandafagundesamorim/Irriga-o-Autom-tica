#define led 13     // Pino onde o LED está conectado
#define sens A0   // Pino analógico onde o sensor de umidade está conectado
#define rele 8     // Pino onde o relé está conectado

const int minUmidade = 55;  // Umidade mínima para ligar o relé (irrigação)
const int maxUmidade = 60;  // Umidade máxima para desligar o relé (irrigação)

void setup() {
  pinMode(led, OUTPUT);      // Configura o pino do LED como saída
  pinMode(rele, OUTPUT);     // Configura o pino do relé como saída
  pinMode(sens, INPUT);      // Configura o pino do sensor como entrada

  digitalWrite(led, LOW);    // Inicializa o LED como desligado
  digitalWrite(rele, HIGH);  // Inicializa o relé como desligado (assumindo relé ativo em LOW)
  Serial.begin(9600);        // Inicializa a comunicação serial para monitoramento
}

void loop() {
  // Lê o valor analógico do sensor de umidade
  int sensorValue = analogRead(sens);
  // Converte o valor lido (0-1023) para umidade percentual (100-0), invertendo a relação
  int umidade = map(sensorValue, 0, 1023, 100, 0);

  // Imprime o valor lido do sensor e a umidade calculada no monitor serial
  Serial.print("Valor do sensor: ");
  Serial.print(sensorValue);
  Serial.print(" - Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  // Verifica a umidade e controla o relé
  if (umidade <= minUmidade) {
    // Se a umidade estiver acima ou igual ao mínimo, liga o relé (irrigação ativada)
    digitalWrite(rele, LOW);  // Ativa o relé
    digitalWrite(led, HIGH);  // Ativa o led

    Serial.println("Solo seco. Irrigação ativada.");
  } else if (umidade > maxUmidade) {
    // Se a umidade estiver abaixo ou igual ao máximo, desliga o relé (irrigação desativada)
    digitalWrite(rele, HIGH);  // Desativa o relé
    digitalWrite(led, LOW);  // Desativa o led

    Serial.println("Solo úmido. Irrigação desativada.");
  }

  delay(3600000);  // Espera 1 hora antes de fazer uma nova leitura
}
