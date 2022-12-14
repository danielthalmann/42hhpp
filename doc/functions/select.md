
# select

select, pselect, FD_CLR, FD_ISSET, FD_SET, FD_ZERO - 
Multiplexage d'entrées-sorties synchrones


## SYNOPSIS

```c++
/* D'après POSIX.1-2001 */

#include <sys/select.h>

/* D'après les standards précédents */

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

#include <sys/select.h>

int pselect(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, const struct timespec *timeout,
            const sigset_t *sigmask);
```


## DESCRIPTION

Les fonctions select() et pselect() permettent à un programme de surveiller 
plusieurs descripteurs de fichier, attendant qu'au moins l'un des descripteurs 
de fichier devienne « prêt » pour certaines classes d'opérations 
d'entrées-sorties (par exemple, entrée possible). Un descripteur de fichier est 
considéré comme prêt s'il est possible d'effectuer l'opération d'entrées-sorties
correspondante (par exemple, un read(2)) sans bloquer.

select() et pselect() ont un comportement identique, avec trois différences :

(i)
    La fonction select() utilise un délai exprimé avec une struct timeval 
	(secondes et microsecondes), alors que pselect() utilise une struct timespec
	(secondes et nanosecondes). 
(ii)
    La fonction select() peut modifier le paramètre timeout pour indiquer le 
	temps restant. La fonction pselect() ne change pas ce paramètre. 
(iii)
    La fonction select() n'a pas de paramètre sigmask et se comporte comme 
	pselect() avec une valeur NULL pour sigmask 

Il y a trois ensembles indépendants de descripteurs surveillés simultanément. 
Ceux de l'ensemble readfds seront surveillés pour vérifier si des caractères 
deviennent disponibles en lecture. Plus précisément, on vérifie si un appel 
système de lecture ne bloquera pas ; en particulier un descripteur en fin de 
fichier sera considéré comme prêt. Les descripteurs de l'ensemble writefds 
seront surveillés pour vérifier si une écriture ne bloquera pas. Ceux de 
exceptfds seront surveillés pour l'occurrence de conditions exceptionnelles. 
En sortie, les ensembles sont modifiés pour indiquer les descripteurs de fichier
qui ont changé d'état. Chacun des trois ensembles de descripteurs de fichier 
peut être spécifié comme NULL si aucun descripteur de fichier n'est surveillé 
pour la classe correspondante d'événements.

Quatre macros sont disponibles pour la manipulation des ensembles FD_ZERO() 
efface un ensemble. FD_SET() et FD_CLR() ajoutent et suppriment, respectivement, 
un descripteur de fichier dans un ensemble. FD_ISSET() vérifie si un descripteur 
de fichier est contenu dans un ensemble, principalement utile après le retour de 
select().

nfds est le numéro du plus grand descripteur de fichier des 3 ensembles, plus 1.

timeout est une limite supérieure au temps passé dans select() avant son retour. 
Elle peut être nulle, ce qui conduit select() à revenir immédiatement. (Ce qui 
sert pour des surveillances en polling). Si le timeout est NULL (aucun), 
select() peut bloquer indéfiniment.

sigmask est un pointeur sur un masque de signaux (voir sigprocmask(2)). S'il 
n'est pas NULL, alors pselect() remplace d'abord le masque de signaux en cours 
par celui indiqué dans sigmask, puis invoque la fonction « select », et enfin 
restaure le masque de signaux à nouveau.

Outre la différence de précision de l'argument timeout, l'appel pselect() suivant


    ready = pselect(nfds, &readfds, &writefds, &exceptfds, 
                    timeout, &sigmask);

est équivalent à l'exécution atomique des appels suivants :


    sigset_t origmask;

    sigprocmask(SIG_SETMASK, &sigmask, &origmask);
    ready = select(nfds, &readfds, &writefds, &exceptfds, timeout);
    sigprocmask(SIG_SETMASK, &origmask, NULL);

La raison pour laquelle pselect() est nécessaire est que si l'on veut attendre 
soit un signal, soit qu'un descripteur de fichier soit prêt, alors un test 
atomique est nécessaire pour éviter les situations de concurrence. (Supposons 
que le gestionnaire de signaux active un drapeau global et revienne. Alors un 
test de ce drapeau, suivi d'un appel select() peut bloquer indéfiniment si le 
signal arrive juste après le test mais avant l'appel. À l'inverse, pselect() 
permet de bloquer le signal d'abord, traiter les signaux déjà reçus, puis 
invoquer pselect() avec le sigmask, désiré, en évitant la situation de blocage.)  
Délai maximal
Les structures temporelles concernées sont définies dans <sys/time.h> comme ceci :

struct timeval {
    long    tv_sec;         /* secondes      */
    long    tv_usec;        /* microsecondes */
};

et

struct timespec {
    long    tv_sec;         /* secondes     */
    long    tv_nsec;        /* nanosecondes */
};

(Toutefois, voir plus loin les versions POSIX.1-2001.)

Certaines applications appellent select() avec les trois ensembles de 
descripteurs vides, nfds nul, et un délai timeout non nul, afin d'endormir, de 
manière portable, le processus avec une précision plus fine que la seconde.

Sous Linux, la fonction select() modifie timeout pour indiquer le temps restant 
mais la plupart des autres implémentations ne le font pas (POSIX.1-2001 autorise 
les deux comportements). Ceci pose des problèmes à la fois pour porter sur 
d'autres systèmes du code développé sous Linux qui utilise cette valeur de 
timeout modifiée, et pour porter sous Linux du code qui réutilise plusieurs 
fois la structure timeval sans la réinitialiser. La meilleure attitude à adopter 
est de considérer timeout comme indéfini après le retour de select().  

## VALEUR RENVOYÉE

En cas de réussite select() et pselect() renvoient le nombre de descripteurs de 
fichier dans les trois ensembles de descripteurs retournés (c'est-à-dire, le 
nombre total de bits à 1 dans readfds, writefds, exceptfds) qui peut être nul si 
le délai de timeout a expiré avant que quoi que ce soit d'intéressant ne se 
produise. Ils retournent -1 s'ils échouent, auquel cas errno contient le code 
d'erreur ; les ensembles et timeout ne sont plus définis, ne vous fiez plus à 
leur contenu après une erreur.  

## ERREURS

EBADF
    Un descripteur de fichier (dans l'un des ensembles) est invalide. (Peut-être 
	un descripteur de fichier qui était déjà fermé ou sur lequel une erreur 
	s'est produite. 
EINTR
    Un signal a été intercepté ; voir signal(7). 
EINVAL
    nfds est négatif ou la valeur contenue dans timeout n'est pas valide. 
ENOMEM
    Pas assez de mémoire pour le noyau. 


