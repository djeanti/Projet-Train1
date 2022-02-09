#Ce script doit etre mis à l'endroit ou le dossier .git se trouve (ce dossier est cachee de base, aller dans
#View de l'explorateur de fichier et cocher "fichier cachés" pour qu'il apparaisse.
#Ce script permet de nettoyer une solution visual studio avant de le commit sur un serveur git par exemple.
#!/bin/sh
nomProjet=PIKO #seul truc a changer si le nom du projet est pas le meme
cd $nomProjet/
rm *.suo *.ncb
cd Debug/
rm *.ilk *.pdb
cd ../$nomProjet/
rm *.user
cd Debug/
rm *