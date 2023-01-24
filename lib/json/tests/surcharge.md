Dans le cadre du projet que je suis en train de faire avec Tiago, il m'est apparut un problème
assez étrange que je n'arrive pas à m'expliquer. 
Je vous expose les fait et peut-être que vous avez une explication à tout cela.

Pour une partie du code, j'ai utilisé la surcharge de fonction. Malheureusement pour moi, cela n'a pas 
fonctionné du premier coup.

Voici un exemple de code avec le résultat obtenu ci-dessous qui fonctionne correctement


```cpp

#include <iostream>
#include <string>

void set(const std::string s) {
    std::cout << " value '" << s << "' : je suis un string" << std::endl;
}

void set(const int i) {
    std::cout << " value '" << i << "'\t : je suis un int" << std::endl;
}

int main()
{
    set(1);
    set("text");
    set(std::string("text"));
}

```

résultat obtenu :

```bash
 value '1'       : je suis un int
 value 'text' : je suis un string
 value 'text' : je suis un string
```

On peut constater que la ```set("text")``` et ```set(std::string("text"))``` utilisent tout deux 
la fonction ```void set(const std::string s)```

et maintenant si j'ajoute la fonction suivante :

```cpp

void set(const bool b) {
    std::cout << " value '" << b << "'\t : je suis un boolean" << std::endl;
}

```

j'obtiens :

```bash
 value '1'       : je suis un int
 value '1'       : je suis un boolean
 value 'text' : je suis un string
```

on voit ici que la fonction boolean a été utilisé pour la chaine de caractère constante.
Je n'ai pas trouvé la raison de ce comportement. pourquoi, uniquement avec le type bool, 
la sélection de la fonction surchargé est fause.

J'ai essayé avec des autres type numérique comme float, double, seul le type bool se comporte de
cette manière.

étrange, non ?

