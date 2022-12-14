# getsockname

 Obtenir le nom d'une socket  

## SYNOPSIS

```c
#include <sys/socket.h>

int getsockname(int s, struct sockaddr *name, socklen_t *namelen)
```

 
## DESCRIPTION

getsockname() renvoie le nom name de la socket indiquée. Le paramètre namelen doit être initialisé pour indiquer la taille de la zone mémoire pointée par name. En retour, il contiendra la taille effective (en octets) du nom renvoyé.  

## VALEUR RENVOYÉE

Cet appel système renvoie 0 s'il réussit, ou -1 s'il échoue, auquel cas errno est renseignée en conséquence.  

## ERREURS

EBADF
    L'argument s n'est pas un descripteur valide. 
EFAULT
    name pointe en dehors de l'espace d'adressage accessible. 
EINVAL
    namelen n'est pas valide (par exemple, est négatif). 
ENOBUFS
    Les ressources système disponibles sont insuffisantes pour effectuer l'opération. 
ENOTSOCK
    L'argument s est un fichier, pas une socket. 
