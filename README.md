# **Système IoT de Suivi Cardiaque**

## **Introduction**
Le projet présente une solution connectée pour surveiller en temps réel les données cardiaques. Ce système repose sur deux cartes **Arduino** (Leonardo et Uno), un capteur **ECG**, et utilise la connectivité **LoRaWAN** via **The Things Network (TTN)** pour transmettre les données. Ces informations sont ensuite affichées sur un tableau de bord **Node-RED** et enregistrées dans une base de données **PostgreSQL** pour un suivi médical.

## **Étapes d'installation**

### **1. Pré-requis**

#### **Matériel nécessaire**
- Carte **Arduino Leonardo**
- Carte **Arduino Uno**
- Capteur **ECG AD8232**
- Module **LoRa** (ex. RFM95)
- Passerelle **LoRaWAN**
- Ordinateur ou **Raspberry Pi** pour exécuter **Node-RED** et **PostgreSQL**

#### **Logiciels requis**
- **Arduino IDE** pour programmer les Arduinos
- **Node-RED** pour le traitement des données
- **PostgreSQL** pour le stockage
- Compte **TTN** pour la gestion LoRaWAN

### **2. Configuration initiale**

#### **Récupération des fichiers**
Clonez le dépôt GitHub :
```bash
git clone https://github.com/EddyEsposito/ECG.git
```

#### **Configuration des Arduinos**
1. **Pour la simulation des signaux** :
   - Ouvrez `heart_rate_simulation.ino` dans l'**IDE Arduino**.
   - Connectez l'**Arduino Uno** et le matériel nécessaire (simulateur de signal).
   - Téléversez le code sur l'**Arduino Uno**.

2. **Pour la transmission des données** :
   - Ouvrez `heart_rate_notification.ino` dans l'**IDE Arduino**.
   - Branchez le capteur **ECG** et le module **LoRa** à l'**Arduino Leonardo** selon le schéma fourni.
   - Téléversez le code sur l'**Arduino Leonardo**.

#### **Configuration sur TTN**
1. Créez une application sur **TTN**.
2. Renseignez les identifiants nécessaires : **AppEUI**, **DevEUI**, et **AppKey**.
3. Ajoutez un décodeur dans la section **Payload Formatter** pour interpréter les **BPM**.

### **3. Installation des outils logiciels**

#### **Installation de Node-RED**
1. Installez **Node-RED** via le script officiel :
   ```bash
   curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/install.sh | bash
   ```
2. Démarrez **Node-RED** :
   ```bash
   node-red
   ```
3. Importez le fichier `dashboard_flows.json` pour configurer les flux.

#### **Configuration de PostgreSQL**
1. Installez **PostgreSQL** :
   ```bash
   sudo apt install -y postgresql postgresql-contrib
   ```
2. Créez une base et une table pour stocker les données :
   ```sql
   CREATE DATABASE monitoring;
   CREATE TABLE heart_data (
       id SERIAL PRIMARY KEY,
       timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
       bpm INT NOT NULL
   );
   ```
3. Configurez **Node-RED** pour insérer automatiquement les données dans **PostgreSQL**.

## **Fonctionnalités**

1. **Acquisition et envoi des données**
   - Lecture des signaux **ECG** et calcul des **BPM** via **Arduino Leonardo**.
   - Transmission des données via **LoRaWAN** vers **TTN**.
   - Simulation des signaux cardiaques via **Arduino Uno** pour des tests.

2. **Tableau de bord interactif**
   - Visualisation en temps réel des données **BPM** avec **Node-RED**.

3. **Archivage sécurisé**
   - Stockage des mesures dans **PostgreSQL** pour un suivi à long terme.

4. **Système d’alertes**
   - Notifications configurées pour détecter les **BPM** hors des seuils prédéfinis.

## **Organisation des fichiers**

### `heart_rate_simulation.ino`
Code pour simuler des données **ECG** sur l'**Arduino Uno**.

### `heart_rate_notification.ino`
Code pour capturer et transmettre les données **ECG** via l'**Arduino Leonardo**.

### `dashboard_flows.json`
Configuration des flux **Node-RED** pour la gestion des données et leur affichage.

## **Améliorations possibles**

- Développement d'une application mobile pour consulter les données à distance.
- Intégration de capteurs supplémentaires (température, SPO2).
- Mise en œuvre d'algorithmes prédictifs pour détecter les anomalies cardiaques.

## **Contributions**
Vous avez des idées pour améliorer ce projet ? Soumettez vos suggestions via une **issue** ou une **pull request** sur le dépôt GitHub.

