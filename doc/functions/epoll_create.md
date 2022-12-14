# epoll

epoll_create - Ouvrir un descripteur de fichier epoll  

## SYNOPSIS

```c
#include <sys/epoll.h>

int epoll_create(int nb);  
```

## DESCRIPTION

Ouvre un descripteur de fichier epoll en demandant au noyau d'allouer une 
structure pour surveiller les événements pour nb descripteurs. La valeur nb 
n'est pas le nombre maximal absolu, mais juste un conseil pour le noyau, afin 
qu'il dimensionne ses structures internes. Le descripteur de fichier renvoyé 
sera utilisé pour tous les appels ultérieurs à l'interface epoll. Le descripteur 
de fichier renvoyé par epoll_create() devra être fermé avec close(2).  

## VALEUR RENVOYÉE

Lorsqu'il réussit, l'appel epoll_create() renvoie un entier non négatif 
identifiant le descripteur. Si une erreur se produit, epoll_create() renvoie -1 
et remplit errno avec le code approprié.  

## ERREURS

EINVAL size n'est pas positif.

ENFILE
    La limite du nombre total de fichiers ouverts sur le système a été atteinte. 
ENOMEM
    Il n'y a pas assez de mémoire pour que le noyau crée les objets nécessaires. 



 