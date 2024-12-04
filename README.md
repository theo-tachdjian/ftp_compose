# FTP compose

Reprise du projet FTP en utilisant docker.

### Questions Job 2:

#### - Quelle sera votre nouvelle image de départ dans le Dockerfile ?
- Alpine pour démarrer avec un environnement légé
#### - Est-ce la même pour le client et le serveur ?
- Oui
#### - Comment optimiser la taille de l’image finale ?
- Réduire le plus possible le nombre d'étapes dans le Dockerfile -> inclure les commandes d'installation des packets, de build, et de clean en une seule étape
#### - Avez-vous besoin de copier tous les fichiers source ?
- Seulement ceux utilisés par le client / par le serveur

### Questions Job 3:

- SERVER_INTERNAL_PORT : Le port où le serveur est bindé dans le conteneur
- SERVER_PORT : Le port exposé sur le réseau où le client peut se connecter
- SERVER_ADDR : L'adresse où le client devra se connecter
