================================================================================
    BIBLIOTHÈQUE MFC (MICROSOFT FOUNDATION CLASS) : Vue d'ensemble du projet 
    RFID
===============================================================================

L'Assistant Application a créé cette application RFID pour
vous. Cette application ne montre pas seulement l'essentiel de l'utilisation de 
Microsoft Foundation Classes, mais constitue également un point de départ pour 
l'écriture de votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui constituent
votre application RFID.

RFID.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à 
    l'aide d'un Assistant Application.
    Il contient des informations sur la version de Visual C++ utilisée pour 
    générer le fichier ainsi que des informations relatives aux plateformes, 
    configurations et fonctionnalités projet que vous avez sélectionnées dans 
    l'Assistant Application.

RFID.h
    Il s'agit du fichier d'en-tête principal de l'application. Il inclut 
    d'autres en-têtes spécifiques au projet (dont Resource.h) et déclare la 
    classe d'application CRFIDApp.

RFID.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CRFIDApp.

RFID.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows utilisées 
    par le programme. Il inclut les icônes, les bitmaps et les curseurs qui 
    sont stockés dans le sous-répertoire RES. Ce fichier peut être directement 
    modifié dans Microsoft Visual C++. Vos ressources de projet se trouvent 
    dans 1036.

res\RFID.ico
    Il s'agit du fichier icône utilisé comme icône de l'application. Cette 
    icône est incluse par le fichier de ressources principal 
    RFID.rc.

res\RFID.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par 
    Microsoft Visual C++. Vous devez placer toutes les ressources non 
    modifiables par l'éditeur de ressources dans ce fichier.

/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame principale :
    Le projet inclut une interface MFC standard.

MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frame CMainFrame, qui 
    est dérivée de
    CFrameWnd et qui contrôle toutes les fonctionnalités du frame SDI.

res\Toolbar.bmp
    Ce fichier bitmap permet de créer des images en mosaïque pour la barre 
    d'outils.
    La barre d'outils et la barre d'état initiales sont construites dans la 
    classe CMainFrame. Modifiez le bitmap de cette barre 
    d'outils à l'aide de l'éditeur de ressources et mettez à jour le tableau 
    IDR_MAINFRAME TOOLBAR dans RFID.rc afin d'ajouter des 
    boutons à la barre d'outils.
/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée un type de document et un affichage :

RFIDDoc.h, RFIDDoc.cpp - document
    Ces fichiers contiennent votre classe CRFIDDoc. Modifiez ces 
    fichiers pour ajouter vos données de document spéciales et implémenter 
    l'enregistrement et le chargement de fichiers (via 
    CRFIDDoc::Serialize).

ChildView.h, ChildView.cpp - affichage du document
    Ces fichiers contiennent votre classe CChildView.
    Les objets CChildView permettent d'afficher des objets 
    CRFIDDoc.





/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers permettent de générer un fichier d'en-tête précompilé (PCH) 
    nommé RFID.pch et un fichier de types précompilé nommé 
    StdAfx.obj.

Resource.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de 
    ressources.
    Microsoft Visual C++ lit et met à jour ce fichier.

RFID.manifest
	Les fichiers manifestes d'application sont utilisés par Windows XP pour 
        décrire la dépendance d'une application	vis à vis de versions 
        spécifiques d'assemblys cote à cote. Le chargeur utilise ces 
        informations pour charger l'assembly approprié à partir du cache de 
        l'assembly ou l'assembly privé à partir de l'application. Le manifeste 
        d'application peut être inclus afin d'être redistribué en tant que 
        fichier manifeste externe installé dans le même dossier que le fichier 
        exécutable de l'application ; il peut également être inclus dans le 
        fichier exécutable en tant que ressource.
/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code 
source que vous devez ajouter ou personnaliser.

Si votre application utilise une bibliothèque MFC dans une DLL partagée, vous 
devez redistribuer les DLL MFC. Si votre application utilise une autre langue 
que celle définie dans les paramètres régionaux du système d'exploitation, vous 
devez également redistribuer les MFC90XXX.DLL des ressources localisées 
correspondantes.
Pour plus d'informations sur ces deux rubriques, consultez la section relative 
à la redistribution des applications Visual C++ dans la documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
