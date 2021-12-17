#Ce fichier explique l'ensemble de procedure a suivre pour pouvoir travailler sur le Porjet Train 1 a distance
Pre-requis :
- Un compte github
- Le logiciel Git (lien : https://git-scm.com/downloads)

Il existe plusieurs possiblités pour travailler avec git sur un projet, ce fichier en traitera deux.

# Avec un logiciel client pour git : Fork (conseillé)

Etape 1 : Télecharger le logiciel Fork (https://git-fork.com/)

A présent, le dossier projet se trouve sur uns erveur git et on veut travailler dessus depuis notre ordinateur pour modifier des elements 
avant de renvoyer ces modifciations ur le serveur git en question. Pour ça ond oit d'abord initialiser l'environnement de travail avec Fork.

Etape 2 : Ouvrir Fork et aller dans File > Clone

Une fenetre popup apparaît, il faut remplir les champs en suviant cette logique :

1)  Remplir le champ "Repository Url" par le lien HTTPS du projet sur le serveur GIT 
	(pour récupérer ce lien il faut se connecter sur https://github.com/ et 
	acceder aux "repository" partagés, puis cliquer sur "Projet-Train1", il 
	devrait apparaître normalement, et enfin cliquer sur le bouton "Code" 
	puis copier le lien dans le petit onglet HTTPS qui apparaît)
	
2)  Remplir le champ "Parent Folder" par l'endroit sur votre ordinateur ou vous 
	vouler travailler sur le projet.
	
3)  Remplir le champ "Name" par ce que vous voulez mais pour éviter des pb (on sait jamais)
	écrivez "Projet-Train1" qui est exactement le meme nom du projet sur le serveur github.

Etape 3 : Comment utiliser Fork ?

1) Tout d'abord il faut choisir la branche sur laquelle on doit travailler 
De base, fork choisit la branche master ou main selon son nom sur github.com (on peut changer le nom de cette branche depuis les
paramètres du projet "Projet-Train1" depuis github.com si on souhaite.))
Donc cliquer sur Branches > New branch et écrire develop pour le nom de cette nouvelle branche.

Ici ça marchera sans problème mais il faut comprendre pk : la branche "develop" existe a déjà été créé sur github.com
quand vous vous connectez a votre compte vous verrez deux branches "master" et "develop", si vous écrivez "developped" au lieu de "develop"
sur fork ça ne marchera pas.

2) De façon général, on utilise Fork que quand on doit upload des modifications dans le serveur github
Sinon on travaille (dans notre cas) avec Visual Studio 2008 ou un autre editeur de fichier comme Notepad++ pour
modifier les fichiers du projet. Donc une fois tt les modifs réalisées, on doit suivre cette procedure pour envoyer
ces modifications sur le serveur :

A - On vérifie quand même que le projet fonctionne toujours malgré les nouvelles modifs localement.

B - Si tout va bien, on ouvre le dossier du projet créé par Fork sur notre ordinateur (on ouvre pas Fork pour le moment)
	On ouvre un Shell Bash (clique droit souris > Bash Here) à l'endroit ou le dossier .git se trouve (c'est un dossier caché de base, attention à ça)

C - On tape sur le shell bash la commande suivante : "./clean.sh" , avec ça on nettoie complétement notre solution 
	(On utilise pas l'option Nettoyer de visual studio 2008 car elle ne nettoie pas tout en réalité)
	
D - Maintenant qu'on a un projet qui marche et qui est nettoyé, on peut l'envoyer sur le serveur github. 
	On ouvre le logiciel Fork et on clique dans la fenêtre gauche du logiciel sur "Local Changes"
	On a à présent deux fenêtres : Unstaged et Staged. L'idée est la suivante : on doit "stage" tous les fichiers 
	qu'on souhaite envoyer sur le serveur et "discard" tous les autres. 
	
	Pour "stage" un fichier on double clique dessus ou alors on fait clique droit dessus > stage
	Pour discard un fichier on fait clique droit sur le fichier > discard
	
	A la fin on ne doit plus avoir aucun fichier dans la fenêtre Unstaged
	
	(A chaque fois qu'on clique sur un fichier on peut voir sa taille, 
	ça peut être utile sur les projets ou on travaille avec des
	fichiers volumineux. C'est juste pour éviter d'upload un fichier 
	de 1Gb sur le serveur par exemple car après on ne peut plus l'enlever du serveur..
	Mais ça ne nous concernera pas pour notre projet, c'est juste bon à savoir. )
	
E - On clique sur le bouton commit après avoir rempli "Commit subject" et/ou "Description" pour fournir une indication  
	sur les modifications qu'on apporte au projet.
	
F - Dans la branche "develop", celle ou on travaille 90% du temps du projet on peut voir sur la fenetre de droite une 
arborescence, elle représente l'ensemble des modifications approtés au projet (sur le serveur). Il faut la lire de bas 
(la modification la plus ancienne) en haut (la modificiation la plus récente). 

Pour envoeyr nos modifs on clique d'abord sur "Pull" (car si qq a deja apporté une modifs sur le serveur on doit
d'abord la récupérer avant d'envoyer notre mofid sinon on a une erreur donc toujours toujours faire Pull avant de faire un Push)

Puis une fois terminé on fait un Push (les boutons push et pull sont dans le menu en haut de Fork.
	
# Avec Git Bash uniquement (sans utiliser Fork ou un autre logiciel similaire)

1) Ouvrir un git bash là ou on veut travailler sur notre ordinateur (local)

2) taper la liste des commandes suivantes :

- git init
- git clone lien_https (remplacer lien_https par le lien HTTPS sur github.com comme expliquer dans la partie d'avant)
- cd Projet-Train1/
- git checkout develop

3) Pour faire des push / pull

Apres avoir modifier les fichiers on ouvre un script bash la ou le dossier .git (caché) se trouve
et on tape :

 - ./clean.sh
 - git pull
 - git commit -m "message a ecrire ici = description du commmit"
 - git push
 
 normalement c'est tout
 Ca semble plus rapide que pour fork mais fork permet grâce a son interface GUI de mieux voir les changement apporter au projet
 et l'arborescence est assez clair aussi de ce point de vue là.
