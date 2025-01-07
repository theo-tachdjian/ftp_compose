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

### Variables d'environnement:

- SERVER_INTERNAL_PORT : Le port où le serveur est bindé dans le conteneur
- SERVER_PORT : Le port exposé sur le réseau où le client peut se connecter
- SERVER_ADDR : L'adresse où le client devra se connecter

- DB_PORT : Le port à utiliser pour se connecter à la base de données
- DB_ADDR : L'adresse à utiliser pour se connecter à la base de données
- DB_USER : L'utilisateur pour la base de données
- DB_NAME : Le nom de la base de données
- DB_PASSWD : Le mot de passe de l'utilisateur de la base de données

- ES_PORT : Le port à utiliser pour exposer l'API HTTP d'Elasticsearch
- ELASTIC_USERNAME : L'utilisateur pour que les autres services puissent intéragir avec Elasticsearch
- ELASTIC_PASSWORD : Le mot de passe de l'utilisateur pour que les autres services puissent intéragir avec Elasticsearch
- KIBANA_PORT : Le port à utiliser pour le service Kibana
