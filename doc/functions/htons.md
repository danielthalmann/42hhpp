
# htons

Name
htonl, htons, ntohl, ntohs - convert values between host and network byte order

## Synopsis

```c++
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

## Description

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

