#Ce fichier explique l'ensemble de la procédure a suivre pour pouvoir travailler sur le Projet Train 1 à distance
Pre-requis :
- Un compte github
- Le logiciel Git (lien : https://git-scm.com/downloads)

Il existe plusieurs possiblités pour travailler avec git sur un projet, ce fichier en traitera deux.

# Avec un logiciel client pour git : Fork (conseillé)

Etape 1 : Télecharger le logiciel Fork (https://git-fork.com/)

A présent, le dossier projet se trouve sur un serveur git et on veut travailler dessus depuis notre ordinateur. 

Etape 2 : Ouvrir Fork et aller dans File > Clone

Une fenetre popup apparaît, il faut remplir les champs en suivant cette logique :

1)  Remplir le champ "Repository Url" par le lien HTTPS du projet sur le serveur GIT 
	
2)  Remplir le champ "Parent Folder" par l'endroit sur votre ordinateur ou vous 
	vouler travailler sur le projet.
	
3)  Remplir le champ "Name" par le nom du projet sur github, "Projet-Train1".

Etape 3 : Comment utiliser Fork ?

1) Tout d'abord il faut choisir la branche sur laquelle on va travailler 
De base, fork choisit la branche master ou main selon son nom sur github.com (on peut changer le nom de cette branche depuis les
paramètres du projet "Projet-Train1" depuis github.com si on souhaite.)
Pour choisir la branche de travail, cliquez sur Branches > New branch et taper "develop" pour le nom de cette nouvelle branche.
Il faut penser au préalable à créer la branche "develop" sur github sans quoi cela risque de ne pas fonctionner.

2) De façon général, on utilise Fork que quand on doit upload des modifications dans le serveur github
Sinon on travaille (dans notre cas) avec Visual Studio 2008 ou un autre editeur de fichier comme Notepad++ pour
modifier les fichiers du projet. Une fois toutes les modifications réalisées, on doit suivre la procedure ci-dessous pour envoyer
ces modifications sur le serveur :

A - On vérifie que le projet fonctionne toujours malgré les nouvelles modifications en local.

B - Si ça fonctionne, on ouvre le dossier du projet créé par Fork sur notre ordinateur (on ouvre pas Fork pour le moment)
	On ouvre un terminal Bash (clique droit souris > Bash Here) à l'endroit ou le dossier .git se trouve (c'est un dossier caché de base)

C - On utilise l'option Nettoyer de visual studio 2008 pour débarrasser le projet de fichiers encombrants.
	
D - Maintenant qu'on a un projet qui marche et qui est nettoyé, on peut l'envoyer sur le serveur github. 
	On ouvre le logiciel Fork et on clique dans la fenêtre gauche du logiciel sur "Local Changes"
	On a à présent deux fenêtres : Unstaged et Staged. L'idée est la suivante : on doit faire passer en "Staged" tous les fichiers 
	qu'on souhaite envoyer sur le serveur et "discard" tous les autres. 
	
	Pour passer en "Staged" un fichier on double clique dessus ou alors on fait clic droit dessus > stage
	Pour discard un fichier on fait clic droit sur le fichier > discard
	
	A la fin on ne doit plus avoir aucun fichier dans la fenêtre Unstaged
	(A chaque fois qu'on clique sur un fichier on peut voir sa taille, 
	ça peut être utile sur les projets ou on travaille avec des
	fichiers volumineux. C'est juste pour éviter d'upload un fichier 
	trop lourd sur le serveur par exemple car après on ne peut plus l'enlever du serveur...)
	
E - On clique sur le bouton commit après avoir remplit "Commit subject" et/ou "Description" pour fournir une indication  
	sur les modifications qu'on apporte au projet.
	
F - Dans la branche "develop", celle ou on travaille 90% du temps du projet on peut voir sur la fenetre de droite une 
arborescence, elle représente l'ensemble des modifications apportés au projet (sur le serveur). Il faut la lire de bas 
(la modification la plus ancienne) en haut (la modificiation la plus récente). 

Pour envoyer nos modifications on clic d'abord sur "pull" (Si quelqu'un a deja "push" une modification sur le serveur on doit
d'abord la récupérer avant d'envoyer notre modification sinon on a une erreur donc il faut toujours faire push avant de faire un push)

Puis une fois terminé on fait un push (les boutons push et pull sont dans le menu en haut de Fork).
	
# Avec Git Bash uniquement (sans utiliser Fork ou un autre logiciel similaire)

1) Ouvrir un git bash là ou on veut travailler sur notre ordinateur (local)

2) taper la liste des commandes suivantes :

- git init
- git clone lien_https (remplacer lien_https par le lien HTTPS sur github.com comme expliqué dans la partie d'avant)
- cd Projet-Train1/
- git checkout develop

3) Pour faire des push / pull

Apres avoir modifier les fichiers on ouvre un script bash là ou le dossier .git (caché) se trouve
et on tape :

 - ./clean.sh
 - git pull
 - git commit -m "message a ecrire ici = description du commmit"
 - git push
