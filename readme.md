###ARCADE###
================

Auteurs
-------
- Pierre Delavigne : pierre1.delavigne@epitech.eu
- Alexandre Crestien : alexandre.crestien@epitech.eu
- Ulysse Decottignies : ulysse.decottignies@epitech.eu

Description
-----------
Le projet Arcade est un jeu d'arcade développé en C++. Il permet aux joueurs de jouer à différents jeux en utilisant différentes bibliothèques d'affichage, notamment ncurses, SDL2 et SFML.

Structure du Répertoire
-----------------------
Le répertoire du projet est organisé de la manière suivante :

- `display`: Ce répertoire contient les différentes implémentations d'affichage du jeu, telles que `ncurses`, `SDL2` et `SFML`. Chaque implémentation d'affichage a son propre fichier `Makefile` et ses fichiers source correspondants.

- `doc`: Ce répertoire contient la documentation liée au projet.

- `game`: Ce répertoire contient les fichiers spécifiques aux jeux, y compris le fichier principal `Makefile` et les sous-répertoires pour les différents jeux.

- `include`: Ce répertoire contient les fichiers d'en-tête du projet.

- `lib`: Ce répertoire contient les bibliothèques utilisées par le projet.

- `Makefile`: Le fichier Makefile principal du projet.

- `Object`: Ce répertoire contient différents fichiers objets et ressources utilisés par le projet, tels que des fichiers graphiques, des fichiers de police, etc.

- `src`: Ce répertoire contient les fichiers source du projet.

Installation
------------
1. Assurez-vous d'avoir installé les bibliothèques nécessaires pour les différentes implémentations d'affichage (ncurses, SDL2, SFML).

2. Clonez ce référentiel vers votre machine locale.

3. Exécutez la commande `make` à la racine du projet pour compiler le jeu.

Utilisation
-----------
1. Après avoir compilé le jeu, exécutez le binaire généré avec la commande `./arcade /lib/+nom_de_la_lib.so`.

2. Choisissez le jeu auquel vous souhaitez jouer dans le menu principal.

3. Utilisez les commandes spécifiques au jeu pour jouer.

COMMANDES
    MENU
    - Touche Entrée : Valider la sélection.
    - Touche Échap : Quitter le jeu.
    - Flèches Haut/Bas : Changer de sélection.
    - Touche Gauche : Revenir au choix précédent.
    - Lettres : Écrire un nom d'utilisateur.
    - Touche Entrée : Supprimer une lettre de l'utilisateur.

    JEU
    - Flèches Gauche/Haut/Droite/Bas : Se déplacer.
    - Touche Espace : Recommencer le jeu.
    - Touche Q : Quitter Arcade.
    - Touche Échap : Retourner au menu.
    - Touche A : Bibliothèque graphique précédente.
    - Touche Z : Bibliothèque graphique suivante.
    - Touche O : Bibliothèque de jeu précédente.
    - Touche P : Bibliothèque de jeu suivante.

Contributions
-------------
Les contributions au projet sont les bienvenues ! Si vous souhaitez contribuer, veuillez suivre ces étapes :

1. Fork le référentiel.

2. Créez une branche pour votre fonctionnalité (`git checkout -b nouvelle-fonctionnalité`).

3. Effectuez les modifications nécessaires et committez-les (`git commit -am 'Ajouter une nouvelle fonctionnalité'`).

4. Pushez votre branche vers votre fork (`git push origin nouvelle-fonctionnalité`).

5. Créez une pull request pour fusionner vos modifications dans la branche principale.

Contact
-------
Pour toute question ou demande de renseignements, veuillez nous contacter aux adresses e-mail suivantes :
- Pierre Delavigne : pierre1.delavigne@epitech.eu
- Alexandre Crestien : alexandre.crestien@epitech.eu
- Ulysse Decottignies : ulysse.decottignies@epitech.eu
