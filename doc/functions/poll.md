# poll, ppoll 

Attendre un événement concernant un descripteur de fichier  

### SYNOPSIS

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int délai);

#define _GNU_SOURCE
#include <poll.h>

int ppoll(struct pollfd *fds, nfds_t nfds, 
        const struct timespec *délai, const sigset_t *sigmask);
```

## DESCRIPTION


poll() est une variation de select(2) : il attend que l'un des descripteurs de 
fichier parmi un ensemble soit prêt pour effectuer des entrées-sorties.

L'ensemble des descripteurs de fichier à surveiller est indiqué dans l'argument 
fds qui est un tableau de structures nfds du type :


struct pollfd {
    int   fd;         /* Descripteur de fichier */
    short events;     /* Événements attendus    */
    short revents;    /* Événements détectés    */
};

Le champ fd contient un descripteur de fichier ouvert. Le champ events est un 
paramètre d'entrée, un masque de bits indiquant les événements qui intéressent 
l'application. Le champ revents est un paramètre de sortie, rempli par le noyau 
avec les événements qui se sont effectivement produits. Les bits renvoyés dans 
revents peuvent inclure ceux spécifiés dans events, ou l'une des valeurs 
POLLERR, POLLHUP ou POLLNVAL. (Ces trois bits n'ont pas de signification dans la 
demande events, et se trouvent positionnés dans la valeur de retour revents si 
l'une des conditions correspondantes se produit.)

Si aucun événement attendu (ni aucune erreur) ne s'est déjà produit, poll() 
bloque jusqu'à ce que l'un des événements survienne. L'argument délai définit 
une limite supérieure, en millisecondes, sur le temps pendant lequel poll() 
bloquera. Définir une valeur négative pour délai signifie un délai d'attente 
infini.

Les bits qui peuvent être positionnés ou renvoyés dans events et revents sont 
définis dans <poll.h> :

    POLLIN
        Il y a des données en attente de lecture. 
    POLLPRI
        Il y a des données urgentes en attente de lecture (par exemple, des 
		données « hors bande » sur une socket TCP ; un pseudo-terminal maître en 
		mode paquet a vu l'esclave changer d'état). 
    POLLOUT
        Une écriture ne bloquera pas. 
    POLLRDHUP (depuis Linux 2.6.17)
        Le correspondant sur une socket en mode flux a fermé la connexion, ou 
		bien a été mis hors service lors de l'écriture sur la connexion. La
		macro de test de fonctionnalité _GNU_SOURCE doit être définie pour 
		obtenir cette définition. 
    POLLERR
        Condition d'erreur (uniquement en sortie). 
    POLLHUP
        Déconnexion (uniquement en sortie). 
    POLLNVAL
        Requête invalide : fd n'est pas ouvert (uniquement en sortie). 

Lorsque _XOPEN_SOURCE est définie à la compilation, les macros suivantes sont 
également définies mais n'apportent pas plus d'information que les bits 
précédents :

    POLLRDNORM
        Équivalent à POLLIN. 
    POLLRDBAND
        Des données prioritaires sont en attente de lecture (généralement pas 
		utilisé sous Linux). 
    POLLWRNORM
        Équivalent à POLLOUT. 
    POLLWRBAND
        Des données prioritaires peuvent être écrites. 

Linux connaît également POLLMSG mais ne l'utilise pas.  
ppoll()
La relation entre poll() et ppoll() est analogue à la relation entre select(2) 
et pselect(2) : de même que pselect(2), ppoll() permet à une application 
d'attendre de façon sûre que soit un descripteur de fichier devienne prêt, soit 
un signal soit capturé.

Outre la différence de l'argument délai, l'appel ppoll() suivant :


    ready = ppoll(&fds, nfds, timeout, &sigmask);

est équivalent à l'exécution atomique des appels suivants :


    sigset_t origmask;

    sigprocmask(SIG_SETMASK, &sigmask, &origmask);
    ready = poll(&fds, nfds, timeout);
    sigprocmask(SIG_SETMASK, &origmask, NULL);

Voir la description de pselect(2) pour une explication de la nécessité de ppoll().

Si l'argument sigmask est défini comme NULL, aucune manipulation de masque de 
signaux n'est effectuée (et ainsi ppoll() ne diffère de poll() que dans la 
précision de l'argument timeout).

L'argument timeout définit une limite supérieure sur le temps total pendant 
lequel ppoll() bloquera. Cet argument est un pointeur sur une structure de 
la forme :


struct timespec {
    long    tv_sec;         /* secondes */
    long    tv_nsec;        /* nanosecondes */
};

Si timeout est NULL, bloquera indéfiniment.  

## VALEUR RENVOYÉE

S'ils réussissent, ces appels renvoient une valeur positive représentant le 
nombre de structures ayant un champ revents non nul, c'est-à-dire le nombre de 
structures pour lesquels un événement attendu, ou une erreur, s'est produit. Une 
valeur de retour nulle indique un dépassement du délai d'attente et qu'aucun 
descripteur de fichier n'était prêt. S'ils échouent, ces appels renvoient -1, et 
errno contient le code d'erreur.  

## ERREURS

EBADF
    Un descripteur de fichier invalide est présent dans un ensemble. 
EFAULT
    La table fournie en argument n'est pas dans l'espace d'adressage du 
	processus appelant. 
EINTR
    Un signal a été reçu avant qu'un événement intéressant ne se produise ; 
	voir signal(7). 
EINVAL
    La valeur nfds dépasse la valeur RLIMIT_NOFILE. 
ENOMEM
    Pas assez de m

