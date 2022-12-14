# recv(2) 

Recevoir un message sur une socket


Other Alias
recvfrom, recvmsg

## SYNOPSIS

```c
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

## DESCRIPTION

Les appels système recv(), recvfrom() et recvmsg() sont utilisés pour recevoir des messages depuis une socket, et peuvent servir sur une socket orientée connexion ou non. Cette page décrit dans un premier temps les fonctionnalités communes de ces trois appels système, puis précise ensuite ce qui les différencie.

Ces trois appels renvoient la longueur du message s'ils réussissent. Si un message est trop long pour tenir dans le tampon, les octets supplémentaires peuvent être abandonnés suivant le type de socket utilisé.

Si aucun message n'est disponible sur la socket, les fonctions de réception se mettent en attente, à moins que la socket soit non bloquante (voir fcntl(2)) auquel cas la valeur -1 est renvoyée, et errno est positionnée à EAGAIN ou EWOULDBLOCK. Les fonctions de réception renvoient normalement les données disponibles sans attendre d'avoir reçu le nombre exact réclamé.

Une application peut avoir recours à select(2), poll(2), ou epoll(7) pour savoir si des données supplémentaires sont disponibles dans la socket.
L'argument flags
L'argument flags est constitué d'un OU binaire entre une ou plusieurs des valeurs suivantes :

MSG_CMSG_CLOEXEC (recvmsg() uniquement ; depuis Linux 2.6.23)
    Positionne l'attribut « close-on-exec » pour le descripteur de fichier reçu via un descripteur de fichier de domaine UNIX en utilisant l'opération SCM_RIGHTS (décrite dans unix(7)). Cet attribut est utile pour les mêmes raisons que l'attribut O_CLOEXEC de open(2). 
MSG_DONTWAIT (depuis Linux 2.2)
    Activer les opérations non bloquantes. Si l'opération devait bloquer, l'appel échouera avec l'erreur EAGAIN ou EWOULDBLOCK (on peut aussi activer ce comportement avec l'option O_NONBLOCK de la fonction F_SETFL de fcntl(2)). 
MSG_ERRQUEUE (depuis Linux 2.2)
    Cet attribut demande que les erreurs soient reçues depuis la file d'erreur de la socket. Les erreurs sont transmises dans un message annexe dont le type dépend du protocole (IP_RECVERR pour IPv4). Il faut alors fournir un tampon de taille suffisante. Consultez cmsg(3) et ip(7) pour plus de détails. Le contenu du paquet original qui a causé l'erreur est passé en tant que données normales dans msg_iovec. L'adresse de destination originale du datagramme ayant causé l'erreur est fournie dans msg_name. 
    Pour les erreurs locales, aucune adresse n'est passée (ceci peut être vérifié dans le membre cmsg_len de cmsghdr). À la réception d'une erreur, MSG_ERRQUEUE est placé dans msghdr. Après réception d'une erreur, l'erreur en attente sur la socket est régénérée en fonction de la prochaine erreur dans la file, et sera transmise lors de l'opération suivante sur la socket.

    L'erreur est contenue dans une structure sock_extended_err :

    #define SO_EE_ORIGIN_NONE    0
    #define SO_EE_ORIGIN_LOCAL   1
    #define SO_EE_ORIGIN_ICMP    2
    #define SO_EE_ORIGIN_ICMP6   3
    struct sock_extended_err
    {
        uint32_t ee_errno;   /* numéro d'erreur */
        uint8_t  ee_origin;  /* origine de l'erreur */
        uint8_t  ee_type;    /* type */
        uint8_t  ee_code;    /* code */
        uint8_t  ee_pad;     /* remplissage */
        uint32_t ee_info;    /* données supplémentaires */
        uint32_t ee_data;    /* autres données */
        /* Des données supplémentaires peuvent suivre */
    };
    struct sockaddr *SO_EE_OFFENDER(struct sock_extended_err *);

    ee_errno contient le code errno de l'erreur en file. ee_origin est le code d'origine de l'erreur. Les autres champs sont spécifiques au protocole. La macro SOCK_EE_OFFENDER renvoie un pointeur sur l'adresse de l'objet réseau ayant déclenché l'erreur, à partir d'un pointeur sur le message. Si l'adresse n'est pas connue, le membre sa_family de la structure sockaddr contient AF_UNSPEC et les autres champs de la structure sockaddr sont indéfinis. Le contenu du paquet ayant déclenché l'erreur est transmis en données normales. 
    Pour les erreurs locales, aucune adresse n'est passée (ceci peut être vérifié dans le membre cmsg_len de cmsghdr). À la réception d'une erreur, MSG_ERRQUEUE est placé dans msghdr. Après réception d'une erreur, l'erreur en attente sur la socket est régénérée en fonction de la prochaine erreur dans la file, et sera transmise lors de l'opération suivante sur la socket. 
MSG_OOB
    Cette option permet la lecture des données hors-bande qui ne seraient autrement pas placées dans le flux de données normales. Certains protocoles placent ces données hors-bande en tête de la file normale, et cette option n'a pas lieu d'être dans ce cas. 
MSG_PEEK
    Cette option permet de lire les données en attente dans la file sans les enlever de cette file. Ainsi une lecture ultérieure renverra à nouveau les mêmes données. 
MSG_TRUNC (depuis Linux 2.2)
    Pour les socket en mode brut (AF_PACKET), datagramme Internet (depuis Linux 2.4.27/2.6.8), netlink (depuis Linux 2.6.22) et datagramme UNIX (depuis Linux 3.4) : renvoyer la taille réelle du paquet ou datagramme, même quand il est plus grand que le tampon fourni.

    Pour une utilisation avec des sockets en mode flux, consultez tcp(7). 
MSG_WAITALL (depuis Linux 2.2)
    Cette option demande que l'opération de lecture soit bloquée jusqu'à ce que la requête complète soit satisfaite. Toutefois, la lecture peut renvoyer quand même moins de données que prévu si un signal est reçu, ou si une erreur ou une déconnexion se produisent. 

recvfrom()
recvfrom() enregistre le message reçu dans le tampon buf. Le processus appelant doit préciser la taille de ce tampon dans len.

Si src_addr n'est pas NULL, et si le protocole sous-jacent fournit l'adresse de la source, celle-ci y est insérée dans le tampon sur désigné par src_addr. Dans ce cas, addrlen est un paramètre-résultat. Avant l'appel, il doit recevoir la valeur de la taille du tampon associé à src_addr. En retour, addrlen est mis à jour avec la valeur réelle de l'adresse source. Cette adresse est tronquée si le buffer fourni n'a pas une taille suffisante ; dans ce cas addrlen renvoie un valeur supérieure à celle fournie lors de l'appel.

Si le processus appelant n'est pas intéressé par l'adresse de la source, src_addr doit avoir la valeur NULL, et addrlen doit valoir 0.
recv()
L'appel recv() est normalement utilisé sur une socket connectée (voir connect(2)). Il est équivalent à l'appel :


    recvfrom(fd, buf, len, flags, NULL, 0));
recvmsg()
L'appel recvmsg() utilise une structure msghdr pour minimiser le nombre de paramètres à fournir directement. Cette structure est définie dans <sys/socket.h> comme ceci :

struct iovec {                    /* dispersion/assemblage
                                     d'éléments de tableaux */
    void *iov_base;               /* Adresse de début */
    size_t iov_len;               /* Nombre d'octets à transférer */
};
struct msghdr {
    void         *msg_name;       /* adresse optionnelle */
    socklen_t     msg_namelen;    /* taille de l'adresse */
    struct iovec *msg_iov;        /* tableau scatter/gather */
    size_t        msg_iovlen;     /* # éléments dans msg_iov */
    void         *msg_control;    /* métadonnées, voir ci-dessous */
    size_t        msg_controllen; /* taille du tampon de métadonnées */
    int           msg_flags;      /* attributs du message reçu */
};

Ici msg_name et msg_namelen spécifient l'adresse d'origine si la socket n'est pas connectée ; msg_name peut être un pointeur nul si le nom n'est pas nécessaire. msg_iov et msg_iovlen décrivent les tampons de réception comme décrit dans readv(2). msg_control, de longueur msg_controllen, pointe sur un tampon utilisé pour les autres messages relatifs au protocole, ou à d'autres données annexes. Lorsqu'on invoque recvmsg, msg_controllen doit contenir la longueur disponible dans le tampon msg_control ; au retour il contiendra la longueur de la séquence de message de contrôle.

Les messages ont la forme

struct cmsghdr {
    socklen_t     cmsg_len;     /* nombre d'octets de données, y compris l'en-tête */
    int           cmsg_level;   /* protocole d'origine */
    int           cmsg_type;    /* type dépendant du protocole */
/* suivi de
    unsigned char cmsg_data[]; */
};

Les données de service ne doivent être manipulées qu'avec les macros de cmsg(3).

À titre d'exemple, Linux utilise ce mécanisme pour transmettre des erreurs étendues, des options IP, ou des descripteurs de fichier sur des sockets de domaine UNIX.

Le champ msg_flags du msghdr est rempli au retour de recvmsg(). Il peut contenir plusieurs attributs :

MSG_EOR
    indique une fin d'enregistrement, les données reçues terminent un enregistrement (utilisé généralement avec les sockets du type SOCK_SEQPACKET). 
MSG_TRUNC
    indique que la portion finale du datagramme a été abandonnée car le datagramme était trop long pour le tampon fourni. 
MSG_CTRUNC
    indique que des données de contrôle ont été abandonnées à cause d'un manque de place dans le tampon de données annexes. 
MSG_OOB
    indique que des données hors-bande ont été reçues. 
MSG_ERRQUEUE
    indique qu'aucune donnée n'a été reçue, sauf une erreur étendue depuis la file d'erreurs. 

## VALEUR RENVOYÉE

Ces fonctions renvoient le nombre d'octets reçus si elles réussissent, ou -1 si elles échouent. Dans ce dernier cas, errno permettra d'identifier la cause de l'erreur.

Lorsque le partenaire d'une socket de flux se ferme proprement, la valeur renvoyée est 0 (c'est-à-dire la valeur habituellement renvoyée lorsqu'on arrive à la fin d'un fichier).

Les sockets de datagrammes autorisent des datagrammes de longueur nulle dans différents domaines (par exemple, les domaines UNIX et Internet). Lorsque de tels datagrammes sont reçus, la valeur renvoyée est 0.

La valeur 0 peut aussi être renvoyée lorsque le nombre d'octets demandé en réception d'une socket de flux est égal à 0.

## ERREURS

Il y a des erreurs standards déclenchées par le niveau socket, et des erreurs supplémentaires spécifiques aux protocoles. Consultez leurs pages de manuel.

EAGAIN ou EWOULDBLOCK
    La socket est non bloquante et aucune donnée n'est disponible, ou un délai de timeout a été indiqué, et il a expiré sans que l'on ait reçu quoi que ce soit. POSIX.1-2001 permet de renvoyer l'une ou l'autre des erreurs dans ce cas et n'exige pas que ces constantes aient la même valeur. Une application portable devrait donc tester les deux possibilités. 
EBADF
    Le paramètre sockfd n'est pas un descripteur correct. 
ECONNREFUSED
    Un hôte distant a refusé la connexion réseau (généralement parce qu'il n'offre pas le service demandé). 
EFAULT
    Un tampon pointe en dehors de l'espace d'adressage accessible. 
EINTR
    Un signal a interrompu la lecture avant que des données soient disponibles ; consultez signal(7). 
EINVAL
    Un paramètre non valable a été fourni. 
ENOMEM
    Pas assez de mémoire pour recvmsg(). 
ENOTCONN
    La socket est associée à un protocole orienté connexion et n'a pas encore été connectée (consultez connect(2) et accept(2)). 
ENOTSOCK
    Le paramètre sockfd ne correspond pas à une socket. 

## CONFORMITÉ

BSD 4.4 (ces fonctions sont apparues dans BSD 4.2), POSIX.1-2001.

POSIX.1-2001 décrit seulement les drapeaux MSG_OOB, MSG_PEEK, et MSG_WAITALL. 