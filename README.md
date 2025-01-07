# **Système IoT de Suivi Cardiaque**

## **Introduction**
Le projet présente une solution connectée pour surveiller en temps réel les données cardiaques. Ce système repose sur une carte **Arduino Leonardo** équipée d'un capteur **ECG**, et utilise la connectivité **LoRaWAN** via **The Things Network (TTN)** pour transmettre les données. Ces informations sont ensuite affichées sur un tableau de bord **Node-RED** et enregistrées dans une base de données **PostgreSQL** pour un suivi médical.

## **Étapes d'installation**

### **1. Pré-requis**

#### **Matériel nécessaire**
- Carte **Arduino Leonardo**
- Capteur **ECG AD8232**
- Module **LoRa** (ex. RFM95)
- Passerelle **LoRaWAN**
- Ordinateur ou **Raspberry Pi** pour exécuter **Node-RED** et **PostgreSQL**

#### **Logiciels requis**
- **Arduino IDE** pour programmer l'Arduino
- **Node-RED** pour le traitement des données
- **PostgreSQL** pour le stockage
- Compte **TTN** pour la gestion LoRaWAN

### **2. Configuration initiale**

#### **Récupération des fichiers**
Clonez le dépôt GitHub :
```bash
git clone https://github.com/votre_utilisateur/projet-monitoring-cardiaque.git
```

#### **Configuration de l'Arduino**
1. Ouvrez `ecg_data_logger.ino` dans l'**IDE Arduino**.
2. Branchez le capteur **ECG** et le module **LoRa** selon le schéma fourni.
3. Téléversez le code sur l'**Arduino Leonardo**.

#### **Configuration sur TTN**
1. Créez une application sur **TTN**.
2. Renseignez les identifiants nécessaires : **AppEUI**, **DevEUI**, et **AppKey**.
3. Ajoutez un décodeur dans la section **Payload Formatter** pour interpréter les **BPM**.

### **3. Installation des outils logiciels**

#### **Installation de Node-RED**
1. Installez **Node-RED** :
   ```bash
   sudo apt update && sudo apt install -y nodejs npm
   sudo npm install -g --unsafe-perm node-red
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
   - Lecture des signaux **ECG** et calcul des **BPM** via **Arduino**.
   - Transmission des données via **LoRaWAN** vers **TTN**.

2. **Tableau de bord interactif**
   - Visualisation en temps réel des données **BPM** avec **Node-RED**.

3. **Archivage sécurisé**
   - Stockage des mesures dans **PostgreSQL** pour un suivi à long terme.

4. **Système d’alertes**
   - Notifications configurées pour détecter les **BPM** hors des seuils prédéfinis.

## **Organisation des fichiers**

### `ecg_data_logger.ino`
Code pour capturer et transmettre les données **ECG**.

### `dashboard_flows.json`
Configuration des flux **Node-RED** pour la gestion des données et leur affichage.

## **Améliorations possibles**

- Développement d'une application mobile pour consulter les données à distance.
- Intégration de capteurs supplémentaires (température, SPO2).
- Mise en œuvre d'algorithmes prédictifs pour détecter les anomalies cardiaques.

## **Contributions**
Vous avez des idées pour améliorer ce projet ? Soumettez vos suggestions via une **issue** ou une **pull request** sur le dépôt GitHub.

