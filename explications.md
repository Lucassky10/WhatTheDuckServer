# Explications C++

## Intéraction avec le terminal

**cout** : sortie standard
**cin** : entrée standard
**endl** : end of line

## Les références

```c++

int age(35);

int& referenceVersAge(age);

```

Une référence doit être du même type que la variable à laquelle est est accrochée.

C'est comme un lien vers la valeur d'une autre variable.

## Les fonctions

### Passage de paramètre par référence

```c++
void f1(string texte);  //Implique une copie coûteuse de 'texte' 
{
}

void f2(string& texte);  //Implique que la fonction peut modifier 'texte' 
{
}
```

En utilisant un passage par référence, la variable n'est pas copiée.

Cette façon de faire a un défaut : elle autorise la modification de l'argument.

Pour éviter ce problème, il est possible de faire un **passage par référence constante**.

```c++
void f1(string const& texte);  //Pas de copie et pas de modification possible
{
}
```

## Manipuler des tableaux dynamiques

Si besoin : https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1896212-manipulez-les-tableaux#/id/r-1896142

## Les pointeurs

### Afficher l'adresse d'une variable

```c++
int age(16);

cout << &age << endl;
```

## Déclarer un pointer

Ce code déclare un pointeur qui peut contenir l'adresse d'une varaible de type `int`.

```c++

int *pointeur;

```

On peut maintenant stocker l'adresse d'une variable dans un pointeur : 

```c++

int age(25);
int *ptr;

ptr = &age;

// ptr : adresse
// *ptr : valeur

```

## Allocation dynamique 

Si besoin : https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1896772-declarez-les-pointeurs#/id/r-1896722

### Libérer la mémoire

`delete ptr;`

## La programmation orientée objet




