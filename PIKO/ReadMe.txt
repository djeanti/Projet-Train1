================================================================================
    BIBLIOTH�QUE MFC (MICROSOFT FOUNDATION CLASS) : Vue d'ensemble du projet 
    PIKO
===============================================================================

L'Assistant Application a cr�� cette application PIKO pour
vous. Cette application ne montre pas seulement l'essentiel de l'utilisation de 
Microsoft Foundation Classes, mais constitue �galement un point de d�part pour 
l'�criture de votre application.

Ce fichier contient un r�sum� du contenu de chacun des fichiers qui constituent
votre application PIKO.

PIKO.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ g�n�r�s � 
    l'aide d'un Assistant Application.
    Il contient des informations sur la version de Visual C++ utilis�e pour 
    g�n�rer le fichier ainsi que des informations relatives aux plateformes, 
    configurations et fonctionnalit�s projet que vous avez s�lectionn�es dans 
    l'Assistant Application.

PIKO.h
    Il s'agit du fichier d'en-t�te principal de l'application. Il inclut 
    d'autres en-t�tes sp�cifiques au projet (dont Resource.h) et d�clare la 
    classe d'application CPIKOApp.

PIKO.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CPIKOApp.

PIKO.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows utilis�es 
    par le programme. Il inclut les ic�nes, les bitmaps et les curseurs qui 
    sont stock�s dans le sous-r�pertoire RES. Ce fichier peut �tre directement 
    modifi� dans Microsoft Visual C++. Vos ressources de projet se trouvent 
    dans 1036.

res\PIKO.ico
    Il s'agit du fichier ic�ne utilis� comme ic�ne de l'application. Cette 
    ic�ne est incluse par le fichier de ressources principal 
    PIKO.rc.

res\PIKO.rc2
    Ce fichier contient les ressources qui ne sont pas modifi�es par 
    Microsoft Visual C++. Vous devez placer toutes les ressources non 
    modifiables par l'�diteur de ressources dans ce fichier.


/////////////////////////////////////////////////////////////////////////////

L'Assistant Application cr�e une classe de bo�te de dialogue :

PIKODlg.h, PIKODlg.cpp - bo�te de dialogue
    Ces fichiers contiennent votre classe CPIKODlg. Cette classe 
    d�finit le comportement de la bo�te de dialogue principale de votre 
    application. Le mod�le de cette bo�te de dialogue se trouve dans le fichier 
    PIKO.rc, qui peut �tre modifi� dans Microsoft Visual C++.


/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers permettent de g�n�rer un fichier d'en-t�te pr�compil� (PCH) 
    nomm� PIKO.pch et un fichier de types pr�compil� nomm� 
    StdAfx.obj.

Resource.h
    Il s'agit du ficher d'en-t�te standard, qui d�finit les nouveaux ID de 
    ressources.
    Microsoft Visual C++ lit et met � jour ce fichier.

/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code 
source que vous devez ajouter ou personnaliser.

Si votre application utilise une biblioth�que MFC dans une DLL partag�e, vous 
devez redistribuer les DLL MFC. Si votre application utilise une autre langue 
que celle d�finie dans les param�tres r�gionaux du syst�me d'exploitation, vous 
devez �galement redistribuer les MFC90XXX.DLL des ressources localis�es 
correspondantes.
Pour plus d'informations sur ces deux rubriques, consultez la section relative 
� la redistribution des applications Visual C++ dans la documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
