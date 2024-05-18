# Utilisez une image de base
FROM ubuntu:latest

# Installez les dépendances nécessaires
RUN apt-get update && apt-get install -y \
    build-essential \
    libboost-all-dev

# Copiez les fichiers nécessaires dans le conteneur
COPY index.html /app/index.html
COPY server.cpp /app/server.cpp

# Définissez le répertoire de travail
WORKDIR /app

# Compilez le serveur C++
RUN g++ server.cpp -o server -lboost_system -lpthread

# Exposez le port 80
EXPOSE 80

# Commande pour démarrer le serveur
CMD ["./server"]
