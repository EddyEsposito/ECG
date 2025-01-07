//ARDUINO LEONARDO
#include <TheThingsNetwork.h>

// Configuration TTN
const char *appEui = "0123456789012345"; // Remplacez par votre AppEUI
const char *appKey = "51AA0D774FE1BCD8C057BD8AB25616D2"; // Remplacez par votre AppKey

#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

// Variables pour la détection de fréquence cardiaque
unsigned long lastBeatTime = 0; // Temps du dernier battement
unsigned long currentTime = 0; // Temps actuel
unsigned long lastSendTime = 0; // Temps du dernier envoi à TTN
int beatThreshold = 550; // Seuil pour détecter un battement
int previousReading = 0; // Lecture précédente d'A0
int currentReading = 0; // Lecture actuelle d'A0
unsigned long beatInterval = 0; // Intervalle entre les battements (en ms)
float heartRate = 0.0; // Fréquence cardiaque en BPM

// Variables pour la moyenne glissante
const int movingAverageSize = 10;
float bpmHistory[movingAverageSize] = {0};
int bpmIndex = 0;
float bpmSum = 0;
int bpmCount = 0; // Nombre d'éléments actuellement dans l'historique

void setup() {
  // Initialisation des ports série
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Attendre un maximum de 10s pour le moniteur série
  while (!debugSerial && millis() < 10000);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  // Initialisation des broches pour la détection
  pinMode(8, INPUT); // Détection leads off LO +
  pinMode(9, INPUT); // Détection leads off LO -
}

void loop() {
  // Lecture de la valeur de A0
  currentReading = analogRead(A0);

  // Détecter un battement lorsque la lecture dépasse le seuil
  if (currentReading > beatThreshold && previousReading <= beatThreshold) {
    currentTime = millis(); // Enregistrer l'heure du battement

    if (lastBeatTime > 0) {
      // Calculer l'intervalle entre les battements en ms
      beatInterval = currentTime - lastBeatTime;

      // Calcul de la fréquence cardiaque (BPM)
      heartRate = 60000.0 / beatInterval;

      // Mettre à jour l'historique et la moyenne
      updateMovingAverage(heartRate);

      // Afficher la fréquence cardiaque et la moyenne glissante
      debugSerial.print("Fréquence cardiaque: ");
      debugSerial.print(heartRate);
      debugSerial.println(" BPM");

      debugSerial.print("Moyenne glissante: ");
      debugSerial.print(calculateMovingAverage());
      debugSerial.println(" BPM");
    }

    // Mettre à jour le temps du dernier battement
    lastBeatTime = currentTime;
  }

  // Mise à jour de la lecture précédente
  previousReading = currentReading;

  // Vérification si les câbles sont déconnectés
  if ((digitalRead(8) == 1) || (digitalRead(9) == 1)) {
    debugSerial.println("Leads off!");
  }

  // Envoyer la moyenne glissante toutes les 15 secondes
  if (millis() - lastSendTime >= 15000) {
    sendHeartRateNotification((uint16_t)calculateMovingAverage());
    lastSendTime = millis(); // Mettre à jour le temps du dernier envoi
  }

  delay(10); // Attendre un peu avant de lire à nouveau
}

// Fonction pour mettre à jour l'historique des BPM
void updateMovingAverage(float bpm) {
  // Retirer la valeur la plus ancienne de la somme
  bpmSum -= bpmHistory[bpmIndex];

  // Ajouter la nouvelle valeur au tableau et à la somme
  bpmHistory[bpmIndex] = bpm;
  bpmSum += bpm;

  // Avancer l'index
  bpmIndex = (bpmIndex + 1) % movingAverageSize;

  // Mettre à jour le nombre d'éléments dans l'historique
  if (bpmCount < movingAverageSize) {
    bpmCount++;
  }
}

// Fonction pour calculer la moyenne glissante
float calculateMovingAverage() {
  return (bpmCount > 0) ? bpmSum / bpmCount : 0;
}

// Fonction pour envoyer une notification via TTN
void sendHeartRateNotification(uint16_t bpm) {
  byte payload[2];
  payload[0] = highByte(bpm);
  payload[1] = lowByte(bpm);

  debugSerial.println("Envoi de la notification...");
  ttn.sendBytes(payload, sizeof(payload));
  debugSerial.println("Notification envoyée !");
}
