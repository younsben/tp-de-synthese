# tp-de-synthese
Compte-rendu de tp système du groupe Leo Sarcy-Younés Ben ameur

Détails des questions :

                                TP1
                                
TD1_Q1 : Renvoie un message de bienvenue dans la console. Et attend qu'on tape la commande "exit" pour fermer le shell.

TD1_Q2 : Execute la commande tapée par l'utilisateur, sauf si c'est "exit", dans ce cas on ferme le shell.

TD1_Q3 : Permets l'utilisation du raccourci clavier <ctrl>+d comme étant une alternative à la fonction "exit". Et affiche "Bye bye ..." à la fermeture du shell.

TD1_Q4 : Va afficher la sortie du programme précédent,  si le s'est terminé de manière normale,  alors en sortie on renvoie "exit:" valeur de sortie. Autrement si il a été interrompu par un signal, le programme renvoie "sign:"  numéro de signal.

TD1_Q5 : En plus de renvoyer la sortie, le code renvoie aussi le temps que la commande a mis à s'exécuter.

TD1_Q6 : Permet de prendre en compte jusqu'à 16 arguments dans la commande

                                TP2
                                
TD2_Q1 : Affiche simplement les arguments passés en entrée (adresse du serveur et nom du fichier). Affiche une erreur s'il n'y a pas assez d'arguments.

TD2_Q2 : Récupère et affiche les informations du serveur, entre autre son adresse IPv4.

TD2_Q3 : Créer un lien (socket) entre le client et le serveur pour qu'ils puissent communiquer entre eux.

TD2_Q4 : Crée une requète de lecture au format 0x0001 + "nomFichier" + 0x00 + "nomOde" + 0x00 puis l'envoie au serveur sur le port 1069.
nb : Lorsque le port était faux ou que le serveur n'était pas ouvert, nous avions sur Wireshark, juste après notre requête, une deuxième indiquant "Unreachable", désormais, nous ne voyons plus ce "unreachable" ce qui nous laisse penser que le serveur reçoit bien la requête. Néanmoins, il ne nous renvoie pas le premier paquet que nous ne pouvons donc pas acquitter. Nous avons essayé de résoudre ce problème et en sommes arrivés à la conclusion qu'il y avait un problème de configuration sur notre serveur TFTP. Malheuresement par manque de temps, nous n'avons pas pu aller plus loin.
