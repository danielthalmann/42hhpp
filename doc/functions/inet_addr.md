# inet_addr

inet_aton, inet_addr, inet_network, inet_ntoa, inet_makeaddr, inet_lnaof, inet_netof - Routines de manipulation d'adresses Internet  

## SYNOPSIS

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int inet_aton(const char *cp, struct in_addr *inp);

in_addr_t inet_addr(const char *cp);

in_addr_t inet_network(const char *cp);

char *inet_ntoa(struct in_addr in);

struct in_addr inet_makeaddr(int net, int host);

in_addr_t inet_lnaof(struct in_addr in);

in_addr_t inet_netof(struct in_addr in);
```


Exigences de macros de test de fonctionnalités pour la glibc (voir feature_test_macros(7)) :

inet_aton(), inet_ntoa() : _BSD_SOURCE || _SVID_SOURCE  

## DESCRIPTION

inet_aton() convertit l'adresse Internet de l'hôte cp depuis la notation IPv4 décimale pointée vers une forme binaire (dans l'ordre d'octet du réseau), et la stocke dans la structure pointée par inp. inet_aton() renvoie une valeur non nulle si l'adresse est valide, et zéro sinon. L'adresse fournie à cp peut avoir l'une des formes suivantes :

a.b.c.d
    Chacune des quatre parties numériques représente un octet de l'adresse ; ces octets sont assignés de gauche à droite pour produire l'adresse binaire. 
a.b.c
    Les parties a et b représentent les deux premiers octets de l'adresse binaire. La partie c est interprétée comme une valeur 16 bits définissant les deux octets les plus à droite de l'adresse binaire. Cette notation est pertinente pour indiquer (démodé) des adresses de réseaux de classe B. 
a.b
    La partie a représente le premier octet de l'adresse binaire. La partie b est interprétée comme une valeur 24 bits définissant les trois octets les plus à droite de l'adresse binaire. Cette notation est pertinente pour indiquer (démodé) des adresses de réseaux de classe C. 
a
    La valeur a est interprétée comme une valeur 24 bits directement enregistrée dans l'adresse binaire, sans aucun réajustement d'octet. 

Dans toutes les formes précédentes, les éléments d'une adresse en notation pointée peuvent être indiqués sous forme décimale, octale (avec un 0 devant) ou hexadécimale (avec un 0X devant). La terminologie des adresses sous ces formes est appelée notation numérique pointée IPV4. La forme qui utilise exactement quatre nombres décimaux est appelée notation décimale pointée IPV4 (ou quelques fois : notation quatre points IPv4).

La fonction inet_addr() convertit l'adresse Internet de l'hôte cp depuis la notation numérique pointée IPV4 en une donnée binaire dans l'ordre des octets du réseau. Si l'adresse est invalide, INADDR_NONE (généralement -1) est renvoyé. L'utilisation de cette fonction pose problème car -1 est une adresse valide (255.255.255.255). Évitez-la au profit de inet_aton(), inet_pton(3) ou getaddrinfo(3) qui fournissent un renvoi d'erreur plus propre.

La fonction inet_network() convertit cp, une chaîne en notation numérique pointée IPV4 en un nombre dans l'ordre des octets de l'hôte pertinent pour être utilisé comme adresse de réseau Internet. a string in IPv4 numbers-and-dots notation, Si elle réussit, cette fonction renvoie l'adresse convertie. Si l'adresse est invalide, -1 est renvoyé.

La fonction inet_ntoa() convertit l'adresse Internet de l'hôte in donne dans l'ordre des octets du réseau en une chaîne de caractères dans la notation numérique pointée. La chaîne est renvoyée dans un tampon alloué statiquement, qui est donc écrasé à chaque appel.

La fonction inet_lnaof() renvoie la partie adresse locale extraite d'une adresse Internet in. La valeur est renvoyée dans l'ordre des octets de l'hôte.

La fonction inet_netof() renvoie la partie adresse réseau extraite d'une adresse Internet in. La valeur est renvoyée dans l'ordre des octets de l'hôte.

La fonction inet_makeaddr() est la réciproque des fonctions inet_netof() et inet_lnaof(). Elle renvoie une adresse d'hôte Internet dans l'ordre des octets du réseau, en combinant le numéro du réseau net et l'adresse locale host, chacun d'eux étant donné dans l'ordre des octets de l'hôte.

La structure in_addr utilisée dans inet_ntoa(), inet_makeaddr(), inet_lnaof() et inet_netof() est définie ainsi dans <netinet/in.h> :

```c
typedef uint32_t in_addr_t;

struct in_addr {
    in_addr_t s_addr;
};
```

 
## CONFORMITÉ

BSD 4.3. inet_addr() et inet_ntoa() sont spécifiées dans POSIX.1-2001. inet_aton() n'est pas spécifiée dans POSIX.1-2001 mais est disponible sur la plupart des systèmes.  
NOTES
Notez que l'ordre des octets des i386 est LSB (poids faible en premier ou petit boutiste), alors que l'ordre des octets sur l'Internet est MSB (poids fort en premier ou gros boutiste).

inet_lnaof(), inet_netof() et inet_makeaddr() sont des fonctions héritées qui supposent qu'elles traitent des adresses de classes canoniques. Les sous-réseaux de classes canoniques divisent la partie réseau et la partie hôte des adresses IPv4 sur des limites d'octets comme suit :

Classe A
    Ce type d'adresse est indiqué par la valeur 0 du bit de poids fort (dans l'ordre des octets du réseau) de l'adresse. L'adresse du réseau est contenue dans l'octet de poids fort et l'adresse de l'hôte dans les trois octets restants. 
Classe B
    Ce type d'adresse est indiqué par la valeur binaire 10 dans les deux bits de poids fort de l'adresse. L'adresse du réseau est contenue dans les deux octets de poids fort et l'adresse de l'hôte dans les deux octets restants. 
Classe C
    Ce type d'adresse est indiqué par la valeur binaire 110 dans les trois bits de poids fort de l'adresse. L'adresse du réseau est contenue dans les trois octets de poids fort et l'adresse de l'hôte dans l'octet restant. 

La classification des adresses réseaux est aujourd'hui obsolète, supplantée par le « Classless Inter-Domain Routing (CIDR) », qui scinde les adresses en éléments réseau et hôte sur une frontière arbitraire en bit (plutôt qu'en octet)  

## EXEMPLE

Ci-dessous, un exemple de l'utilisation de inet_aton() et de inet_ntoa(). Voici des exemples d'exécution :

```

$ ./a.out 226.000.000.037   # Le dernier octet est en octal
226.0.0.31
$ ./a.out 0x7f.1            # Le premier octet est en hexadécimal
127.0.0.1
```


```c
#define _BSD_SOURCE
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    struct in_addr addr;

    if (argc != 2) {
        fprintf(stderr, "%s <dotted-address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (inet_aton(argv[1], &addr) == 0) {
        perror("inet_aton");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", inet_ntoa(addr));
    exit(EXIT_SUCCESS);
}
```

