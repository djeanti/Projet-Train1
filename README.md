# Code implemented as part of a project at Polytech Paris-Saclay

#This file explains the procedure to follow in order to work with this project.
Requirements :
- A github account
- The framework git (link : https://git-scm.com/downloads)
- Visual Studio 2008

There are a lot of possibilities to use git when working on a project, this readme will talk about two of them.

## With a client software for git : Fork (recommended)

Step 1: Download the Fork software (https://git-fork.com/)

Now the project folder is on a git server and we want to work on it from our computer. 

Step 2: Open Fork and go to File > Clone.

A popup window appears, you have to fill in the fields following this logic:

1) Fill the "Repository Url" field with the HTTPS link of the project on the GIT server 
	
2) Fill the field "Parent Folder" by the location on your computer where you want 
	you want to work on the project.
	
3) Fill the "Name" field with the name of the project on github, "Project-Train1".

Step 3 : How to use Fork ?

1) First of all we have to choose the branch we are going to work on 
Basically, fork chooses the master or main branch according to its name on github.com (you can change the name of this branch from the
parameters of the project "Projet-Train1" from github.com if you want).
To choose the working branch, click on Branches > New branch and type in "develop" for the name of this new branch.
It is necessary to think beforehand to create the "develop" branch on github, otherwise it may not work.

2) In general, we use Fork only when we have to upload modifications in the github server
Otherwise we work (in our case) with Visual Studio 2008 or another file editor like Notepad++ to
modify the project files. Once all the modifications are done, we have to follow the procedure below to send
these modifications on the server:

A - We check that the project still works despite the new modifications locally made.

B - If it works, we open the project folder created by Fork on our computer (we don't open the application for the time being)
	We open a Bash terminal (right click mouse > Bash Here) at the place where the .git folder is (it is a hidden folder)

C - We use the option Clean of visual studio 2008 to rid the project of cumbersome files.
	
D - Now that we have a project that works and that is cleaned up, we can send it to the github server. 
	We open the Fork software and we click in the left window of the software on "Local Changes".
	We now have two windows: Unstaged and Staged. The idea is the following: we must make all the files we want to send to the server "Staged". 
	that we want to send to the server and "discard" all the others. 
	
	To make a file "Staged" we double click on it or we right click on it > stage
	To discard a file you right click on the file > discard
	
	At the end you should have no more files in the Unstaged window
	(Each time you click on a file you can see its size, 
	This can be useful on projects where we work with large files.
	It's just to avoid uploading a file too heavy on the server because afterwards it's hard to remove it from the server...)
	
E - You click on the commit button after filling in "Commit subject" and/or "Description" to give an indication  
	on the modifications you make to the project.
	
F - In the "develop" branch, the one where we work 90% of the time, we can see on the right window a 
tree, it represents all the modifications made to the project (uploaded to the server). You have to read it from the bottom 
(the oldest modification) to the top (the most recent modification). 

To send our modifications we first click on "pull" (In case someone has already "pushed" a modification on the server we have to retrieve before sending our modifications otherwise we get an error so we must always do a pull before doing a push)

Then once finished we make a push (the buttons push and pull are in the menu at the top of Fork).
	
## With Git Bash only (without using Fork or other similar software)

1) Open a git bash where we want to work on our computer (locally)

2) type the following list of commands:

- git init
- git clone link_https (replace link_https by the HTTPS link on github.com as explained in the previous section)
- cd Project-Train1/
- git checkout develop

3) To make push / pull

After having modified the files we open a bash script where the .git folder (hidden) is located
and we type :

 - ./clean.sh
 - git commit -m "message to write here = description of the commit"
 - git pull
 - git push
