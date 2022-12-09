
|                                               |
|-----------------------------------------------|
|  malloc,                                      |
|  free,                                        |
|  write,                                      |                                          
|  htons, htonl, ntohs, ntohl,                  |                                         
|  select,                                      |                                           
|  poll,                                        |                                         
|  epoll (epoll_create, epoll_ctl, epoll_wait), |                                                                                
|  kqueue (kqueue, kevent),                     |                   
|  socket,                                      | 
|  accept,                                      |  
|  listen,                                      |  
|  send,                                        |
|  recv,                                        |
|  bind,                                        |
|  connect,                                     |  
|  inet_addr,                                   |     
|  setsockopt,                                  |      
|  getsockname,                                 |       
|  fcntl                                        |


## htons

Name
htonl, htons, ntohl, ntohs - convert values between host and network byte order
Synopsis

´´´c++
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
´´´

Description

La fonction htonl() convertit un entier non signé hostlong depuis l'ordre des 
octets de l'hôte vers celui du réseau.

La fonction htons() convertit un entier court non signé hostshort depuis l'ordre
des octets de l'hôte vers celui du réseau.

La fonction ntohl() convertit un entier non signé netlong depuis l'ordre des 
octets du réseau vers celui de l'hôte.

La fonction ntohs() convertit un entier court non signé netshort depuis l'ordre 
des octets du réseau vers celui de l'hôte.

Sur les i386, l'ordre des octets de l'hôte est 
LSB (« Least Significant Byte first»), c'est-à-dire octet de poids faible en 
premier, alors que sur les réseaux, notamment l'Internet, l'ordre est 
MSB (« Most Significant Byte first ») octet de poids fort en premier.

Ces fonctions servent a convertir des types pour pouvoir les envoyer a travers 
le reseau sans que l'endianness de la machine corompt les donnees. Utilise les 
quand tu veux envoyer des types short, int, long, double. Tu n'as pas besoins 
de convertir un char car il fait toujours 1 octet.

Les fonction commencent par H sont pour les convertir avant de les envoye et 
ceux commencent par N sont faites pour quand tu as recu les donnees et tu les 
convertis pour TA machine.



## select

select, pselect, FD_CLR, FD_ISSET, FD_SET, FD_ZERO - 
Multiplexage d'entrées-sorties synchrones

´´´c++
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
´´´

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

### VALEUR RENVOYÉE

En cas de réussite select() et pselect() renvoient le nombre de descripteurs de 
fichier dans les trois ensembles de descripteurs retournés (c'est-à-dire, le 
nombre total de bits à 1 dans readfds, writefds, exceptfds) qui peut être nul si 
le délai de timeout a expiré avant que quoi que ce soit d'intéressant ne se 
produise. Ils retournent -1 s'ils échouent, auquel cas errno contient le code 
d'erreur ; les ensembles et timeout ne sont plus définis, ne vous fiez plus à 
leur contenu après une erreur.  

### ERREURS

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


## poll, ppoll 

Attendre un événement concernant un descripteur de fichier  

### SYNOPSIS

´´´c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int délai);

#define _GNU_SOURCE
#include <poll.h>

int ppoll(struct pollfd *fds, nfds_t nfds, 
        const struct timespec *délai, const sigset_t *sigmask);
´´´

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

### VALEUR RENVOYÉE

S'ils réussissent, ces appels renvoient une valeur positive représentant le 
nombre de structures ayant un champ revents non nul, c'est-à-dire le nombre de 
structures pour lesquels un événement attendu, ou une erreur, s'est produit. Une 
valeur de retour nulle indique un dépassement du délai d'attente et qu'aucun 
descripteur de fichier n'était prêt. S'ils échouent, ces appels renvoient -1, et 
errno contient le code d'erreur.  

### ERREURS

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

epoll_create - Ouvrir un descripteur de fichier epoll  
SYNOPSIS
#include <sys/epoll.h>

## epol

´´´
int epoll_create(int nb);  
´´´

### DESCRIPTION

Ouvre un descripteur de fichier epoll en demandant au noyau d'allouer une 
structure pour surveiller les événements pour nb descripteurs. La valeur nb 
n'est pas le nombre maximal absolu, mais juste un conseil pour le noyau, afin 
qu'il dimensionne ses structures internes. Le descripteur de fichier renvoyé 
sera utilisé pour tous les appels ultérieurs à l'interface epoll. Le descripteur 
de fichier renvoyé par epoll_create() devra être fermé avec close(2).  

### VALEUR RENVOYÉE

Lorsqu'il réussit, l'appel epoll_create() renvoie un entier non négatif 
identifiant le descripteur. Si une erreur se produit, epoll_create() renvoie -1 
et remplit errno avec le code approprié.  

### ERREURS

EINVAL size n'est pas positif.

ENFILE
    La limite du nombre total de fichiers ouverts sur le système a été atteinte. 
ENOMEM
    Il n'y a pas assez de mémoire pour que le noyau crée les objets nécessaires. 



 
## socket 

Créer un point de communication  

### SYNOPSIS

´´´
#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>

int socket(int domain, int type, int protocol);  
´´´

### DESCRIPTION

socket() crée un point de communication, et renvoie un descripteur.

Le paramètre domain indique le domaine de communication pour le dialogue ; ceci 
sélectionne la famille de protocole à employer. Elles sont définies dans le 
fichier <sys/socket.h>. Les formats actuellement proposés sont :

Nom	Utilisation	Page
PF_UNIX, PF_LOCAL 	Communication locale 	unix(7)
PF_INET 	Protocoles Internet IPv4	ip(7)
PF_INET6 	Protocoles Internet IPv6	ipv6(7)
PF_IPX 	IPX - Protocoles Novell	
PF_NETLINK 	Interface utilisateur noyau 	netlink(7)
PF_X25 	Protocole ITU-T X.25 / ISO-8208	x25(7)
PF_AX25 	Protocole AX.25 radio amateur 	
PF_ATMPVC 	Accès direct ATM PVCs	
PF_APPLETALK 	Appletalk	ddp(7)
PF_PACKET 	Interface paquet bas-niveau 	packet(7)

La socket a le type indiqué, ce qui définit la sémantique des communications. 
Les types actuellement définis sont :

SOCK_STREAM
    Support de dialogue garantissant l'intégrité, fournissant un flux de données 
	binaires, et intégrant un mécanisme pour les transmissions de données 
	hors-bande. 
SOCK_DGRAM
    Transmissions sans connexion, non garantie, de datagrammes de longueur 
	maximale fixe. 
SOCK_SEQPACKET
    Dialogue garantissant l'intégrité, pour le transport de datagrammes de 
	longueur fixe. Le lecteur doit lire le paquet de données complet à chaque 
	appel système récupérant l'entrée. 
SOCK_RAW
    Accès direct aux données réseau. 
SOCK_RDM
    Transmission fiable de datagrammes, sans garantie de l'ordre de délivrance. 
SOCK_PACKET
    Obsolète, à ne pas utiliser dans les programmes actuels. Voir packet(7). 

Certains types de sockets peuvent ne pas être implémentés par toutes les 
familles de protocoles. Par exemple, SOCK_SEQPACKET n'est pas implémenté 
pour AF_INET.

Le protocole à utiliser sur la socket est indiqué par l'argument protocol. 
Normalement, il n'y a qu'un seul protocole par type de socket pour une famille 
donnée, auquel cas l'argument protocol peut être nul. Néanmoins, rien ne 
s'oppose à ce que plusieurs protocoles existent, auquel cas il est nécessaire 
de le spécifier. Le numéro de protocole dépend du domaine de communication de la 
socket. Voir protocols(5). Voir getprotoent(3) pour savoir comment associer un 
nom de protocole à un numéro.

Une socket de type SOCK_STREAM est un flux d'octets full-duplex, similaire aux 
tubes (pipes). Elle ne préserve pas les limites d'enregistrements. Une socket 
SOCK_STREAM doit être dans un état connecté avant que des données puisse y être 
lues ou écrites. Une connexion sur une autre socket est établie par l'appel 
système connect(2). Une fois connectée, les données y sont transmises par 
read(2) et write(2) ou par des variantes de send(2) et recv(2). Quand une 
session se termine, on referme la socket avec close(2). Les données hors-bande 
sont envoyées ou reçues en utilisant send(2) et recv(2).

Les protocoles de communication qui implémentent les sockets SOCK_STREAM 
garantissent qu'aucune donnée n'est perdue ou dupliquée. Si un bloc de données, 
pour lequel le correspondant a suffisamment de place dans son tampon, n'est pas 
transmis correctement dans un délai raisonnable, la connexion est considérée 
comme inutilisable. Si l'option SO_KEEPALIVE est activée sur la socket, le 
protocole vérifie, d'une manière qui lui est spécifique, si le correspondant 
est toujours actif. Un signal SIGPIPE est envoyé au processus tentant d'écrire 
sur une socket inutilisable, forçant les programmes ne gérant pas ce signal à se 
terminer. Les sockets de type SOCK_SEQPACKET emploient les mêmes appels système 
que celles de types SOCK_STREAM, à la différence que la fonction read(2) ne 
renverra que le nombre d'octets requis, et toute autre donnée restante dans le 
paquet sera éliminée. De plus, les frontières des messages seront préservées.

Les sockets de type SOCK_DGRAM ou SOCK_RAW permettent l'envoi de datagrammes aux 
correspondants indiqués dans l'appel système sendto(2). Les datagrammes sont 
généralement lus par la fonction recvfrom(2), qui fournit également l'adresse du 
correspondant.

Les sockets SOCK_PACKET sont obsolètes. Elles servent à recevoir les paquets 
bruts directement depuis le gestionnaire de périphérique. Utilisez plutôt 
packet(7).

L'opération F_SETOWN de fcntl(2) permet de préciser un processus ou groupe de 
processus qui recevront un signal SIGURG lors de l'arrivée de données 
hors-bande, ou le signal SIGPIPE lorsqu'une connexion sur une socket SOCK_STREAM 
se termine inopinément. Cette fonction permet également de définir le processus 
ou groupe de processus qui recevra une notification asynchrone des événements 
d'entrées-sorties par le signal SIGIO. L'utilisation de F_SETOWN est équivalent 
à un appel ioctl(2) avec l'argument FIOSETOWN ou SIOCSPGRP.

Lorsque le réseau indique une condition d'erreur au module du protocole (par 
exemple l'utilisation d'un message ICMP au lieu d'IP), un drapeau signale une 
erreur en attente sur la socket. L'opération suivante sur cette socket renverra 
ce code d'erreur. Pour certains protocoles, il est possible d'activer une file 
d'attente d'erreurs par socket. Pour plus de détails, voir IP_RECVERR dans ip(7).

Les opérations sur les sockets sont contrôlées par des options du niveau socket. 
Ces options sont définies dans <sys/socket.h>. Les fonctions setsockopt(2) et 
getsockopt(2) sont utilisées respectivement pour fixer ou lire les options.  
VALEUR RENVOYÉE
Cet appel système renvoie un descripteur référençant la socket créée s'il 
réussit. S'il échoue, il renvoie -1 et errno contient le code d'erreur.  

### ERREURS

EACCES
    La création d'une telle socket n'est pas autorisée. 
EAFNOSUPPORT
    L'implémentation ne supporte pas la famille d'adresses indiquée. 
EINVAL
    Protocole inconnu, ou famille de protocole inexistante. 
EMFILE
    La table des fichiers est pleine. 
ENFILE
    La limite du nombre total de fichiers ouverts sur le système a été atteinte. 
ENOBUFS ou ENOMEM
    Pas suffisamment d'espace pour allouer les tampons nécessaires. La socket ne 
	peut être créée tant que suffisamment de ressources ne seront pas libérées. 
EPROTONOSUPPORT
    Le type de protocole, ou le protocole lui-même n'est pas disponible dans ce 
	domaine de communication. 

D'autres erreurs peuvent être dues aux modules de protocoles sous-jacents.
