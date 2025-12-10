# Contrôleur Intelligent de Température

Ce projet est un contrôleur de température intelligent écrit en langage C.  
Il permet de configurer un lieu, mesurer aléatoirement des températures simulées, détecter des alertes, enregistrer les mesures et produire un rapport journalier complet.

---

## 📌 Fonctionnalités

- Configuration personnalisée :
  - Type de lieu : **Maison**, **Serveur**, ou **Serre**
  - Seuil minimum et maximum
  - Intervalle de mesure (en secondes)

- Simulation de températures selon le type de lieu
- Détection automatique des niveaux d’alerte :
  - **Niveau 1** – Dépassement léger
  - **Niveau 2** – Dépassement important
  - **Niveau 3** – Dépassement critique

- Enregistrement de toutes les mesures dans `journal.txt`
- Génération d’un fichier de rapport : `rapport_journalier.txt`
- Affichage du rapport de fin en console
- Arrêt du programme en appuyant sur la touche **Q**

---

## 📂 Fichiers générés

| Fichier | Description |
|--------|-------------|
| **config.txt** | Contient la configuration choisie par l’utilisateur |
| **journal.txt** | Historique de toutes les mesures avec date et heure |
| **rapport_journalier.txt** | Résumé complet : min, max, moyenne, alertes |

---

## 🧪 Simulation des températures

Selon le type de lieu, le programme génère une température aléatoire dans :

- **Maison** : 15°C → 50°C  
- **Serveur** : 20°C → 60°C  
- **Serre** : 20°C → 60°C  

Ces valeurs sont analysées et classées selon 3 niveaux d’alerte.

---

## ⚠️ Conditions d’alerte

Le programme compare chaque température aux seuils :

- ✔ Entre seuil_min et seuil_max → Normal  
- ⚠ ± marge → Niveau 1  
- ❗ Dépassement significatif → Niveau 2  
- 🔥 Dépassement critique → Niveau 3  

Après 3 alertes consécutives du même type, un compteur d’alerte est incrémenté.

---

## 📝 Commandes utiles

- **Q** : Arrêter proprement le programme  
- Les mesures se font automatiquement selon l’intervalle du fichier de configuration.

---

## ▶️ Compilation

Utilisez **GCC** sous Windows :

