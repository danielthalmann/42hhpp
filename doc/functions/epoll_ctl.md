
# epoll_ctl

Interface de contrôle pour un descripteur epoll  


## SYNOPSIS

```c
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);  
```

## DESCRIPTION

Contrôle le descripteur epoll epfd, en demandant que l'opération op soit réalisée sur le descripteur de fichier cible fd. La structure event décrit l'objet lié au descripteur de fichier fd. La structure epoll_event est définie ainsi :

```c
typedef union epoll_data {
    void *ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;

struct epoll_event {
    __uint32_t events;    /* Événement epoll      */
    epoll_data_t data;    /* Variable utilisateur */
};
```

Le membre events est un masque de bits composé à partir des événements disponibles suivants :

**EPOLLIN**

> Le descripteur associé est disponible pour un appel read(2). 

**EPOLLOUT**

> Le descripteur associé est disponible pour un appel write(2). 

**EPOLLRDHUP** (depuis Linux 2.6.17)

> Le pair de la socket en mode flux a fermé la connexion, ou bien a été mis hors service en cours d'écriture sur la connexion. (Cet attribut est particulièrement utile pour écrire du code simple afin de détecter la mise hors service du pair lors de l'utilisation de la surveillance « Edge Triggered ».) 

**EPOLLPRI**

> Il y a des données urgentes disponibles pour un appel read(2). 

**EPOLLERR**

> Une erreur s'est produite sur le descripteur de fichier associé. epoll_wait(2) attendra toujours cet événement ; il n'est pas nécessaire de l'indiquer dans events. 

**EPOLLHUP**

> Une déconnexion s'est produite sur le descripteur associé. epoll_wait(2) attendra toujours cet événement ; il n'est pas nécessaire de l'indiquer dans events. 

**EPOLLET**

> Définir le comportement en détection de changement d'état sur le descripteur. Par défaut epoll fonctionne en détection de niveau. Voir epoll(7) pour plus de détails sur les comportements en détection de niveau et de changements d'état. 

**EPOLLONESHOT** (depuis Linux 2.6.2)

> Définir le comportement « coup unique » (Ndt : one-shot) pour le descripteur de fichier associé. Cela signifie qu'après qu'un événement n'ait été retiré avec epoll_wait(2), le descripteur de fichier est désactivé de manière interne et aucun autre événement ne sera rapporté par l'interface epoll. L'utilisateur doit appeler epoll_ctl() avec EPOLL_CTL_MOD pour réactiver le descripteur de fichier avec le nouveau masque d'événement. 

L'interface epoll supporte tous les descripteurs de fichier supportés par poll(2). Les valeurs valides pour le paramètre op sont :

**EPOLL_CTL_ADD**

> Ajouter le descripteur de fichier fd dans le descripteur epoll epfd et associe l'événement event avec le fichier représenté par fd. 

**EPOLL_CTL_MOD**

> Changer l'événement event associé au descripteur de fichier fd. 

**EPOLL_CTL_DEL**

> Supprimer le descripteur de fichier fd du descripteur epoll epfd. Le paramètre event est ignoré et peut être NULL (mais voir la section BOGUES plus loin). 

 
## VALEUR RENVOYÉE

Lorsqu'il réussit, l'appel epoll_ctl() renvoie zéro. Si une erreur se produit, epoll_ctl() renvoie -1 et errno contient le code approprié.  
ERREURS

**EBADF**
>    epfd ou fd n'est pas un descripteur valide. 

**EEXIST**
>    op était EPOLL_CTL_ADD, et le descripteur de fichier fd fourni est déjà dans epfd. 

**EINVAL**
>    epfd n'est pas un descripteur epoll, ou fd est le même que epfd, ou l'opération demandée op n'est pas supportée par cette interface. 

**ENOENT**
>    op était EPOLL_CTL_MOD ou EPOLL_CTL_DEL, et fd n'est pas dans epfd. 

**ENOMEM**
>    Pas assez de mémoire dans le noyau pour traiter l'opération op. 

**EPERM**
>    Le fichier cible fd ne supporte pas epoll. 

 
## CONFORMITÉ

epoll_ctl() est spécifique à Linux et a été introduit dans Linux 2.5.44.  

## BOGUES

Dans les noyaux antérieurs à la version 2.6.9, l'opération EPOLL_CTL_DEL nécessitait un pointeur non-NULL pour event, même si cet argument était ignoré. Depuis Linux 2.6.9, event peut être NULL lors d'une opération EPOLL_CTL_DEL. Les applications qui doivent être portables vers les noyaux antérieurs à la version 2.6.9 doivent indiquer un pointeur non-NULL dans event.  
