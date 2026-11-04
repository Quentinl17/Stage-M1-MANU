# Étude de l'équation de McKendrick-Lotka

Ce dépôt contient les travaux réalisés pour un stage facultatif du **Master 1 MANU** (Modélisation et Analyse Numérique), à la **Faculté des Sciences de l'Université de Montpellier**.

## 📝 Présentation du projet
L'objectif avec ce stage était d'approfondir les notions d'Analyse Fonctionnelle étudiées durant la première année de Master. L'étude revient, dans un premier temps, sur la motivation de la structure en âge du modèle. Dans un deuxième temps, on propose la résolution du modèle de McKendrick-Lotka par la méthode des caractéristiques, qui a été étudié durant le premier semestre du Master. Dans un troisème temps, on réalise l'étude du modèle à l'aide de la théorie des semi-groupes et on retrouve les résultats obtenus avec la méthode des caractéristiques. Enfin, on termine ce rapport par une étude d'un modèle de McKendrick-Lotka non-linéaire.

## 📁 Contenu du dépôt
* `rapport` : Le code Latex complet du rapport, avec notamment la version finale du rapport au format pdf.
* `presentation` : Le code Latex complet du diaporama réalisé pour la présentation du projet, avec la version finale au format pdf.
* `programmation` : Le code permettant le tracé des caractéristiques en Python. Ajout d'un dossier `prog_cpp` contenant le code C++ d'un schéma volume fini permettant la résolution du modèle de McKendrick-Lotka linéaire avec l'affichage d'un GIF. On a également la solution de l'équation de renouvellement démographique qui est calculée de deux manières différentes, d'abord avec le schéma volume fini à l'aide de la condition au bord, puis avec des formules de quadrature de l'équation intégrale de Volterra.

## 👥 Équipe
* **Quentin Lahaye**
* Sous la direction du **Dr. Quentin Richard**.