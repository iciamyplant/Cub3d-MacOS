# Parsing & Map error

## Ce qui est demandé

Votre programme doit prendre en premier argument un fichier de description de scène avec pour extension **.cub**

1. La map doit être composée d’uniquement ces 4 caractères : 
**0** pour les espaces vides
**1** pour les murs
**2** pour un objet
**N,S,E** ou **W** la position de départ du joueur et son orientation.</br>
Cette simple map doit être valide :
```
111111
100101
102001
1100N1
111111
```
2. La map doit être fermée/entourée par des **1** (murs).

3. La *description* de la map en elle meme sera **toujours en dernier dans le fichier**, le reste des éléments peut être dans n’importe quel ordre.

4. **Sauf pour la map elle-même**, les informations de chaque élément peuvent être séparées par **un ou plusieurs espace(s)**, et chaque type d’élément peut être séparée par une ou plusieurs **lignes vides**. Les espaces sont une partie valable de la carte.

5. Pour chaque élement, le premier caractère est **l’identifiant (un ou deux caractères)**, suivi de toutes les informations spécifiques à l’élément dans **un ordre strict** tel que :

```c
# Resolution :
R 1920 1080

# Texture nord :
NO ./path_to_the_north_texture

# South texture :
SO ./path_to_the_south_texture

# West texture :
WE ./path_to_the_west_texture

# East texture :
EA ./path_to_the_east_texture

# Sprite texture :
S ./path_to_the_sprite_texture

# Couleur du sol :
F 220,100,0

# Couleur du plafond :
C 225,30,0
```

6. Si un problème de configuration de n’importe quel type est rencontré dans
le fichier, le programme doit quitter et renvoyer "Error\n" suivi d’un message
d’erreur explicite de votre choix.

## Liste *non exhaustive* de cas d'erreur de map.cub

### Le fichier

- [ ] Le fichier n'a pas la bonne extention .cub (pas valide) ```map00```
- [ ] Le fichier .cub est vide ou contient juste un /n ```map01```

### La map elle-meme

- [ ] La map n'est pas entourée par des 1 ```map01e*```
- [ ] La map est avant les éléments dans le fichier ```map02e*```
- [ ] Un ou plusieurs élément(s) est après la map dans le fichier ```map03e*```
- [ ] La map est séparee par une ligne vide ```map04e*```
- [ ] Il y a plusieurs maps ```map05e*```
- [ ] La map contient un ou plusieurs espaces à l'interieur ```map06e*```
- [ ] Il n'y a pas de N,S,E ou W  dans la map (pas de joueur) ```map07e*``` ```map01e4``` ```map01e6```
- [ ] Il y a plus d'un joueur dans la map ```map08e*```
- [ ] Il y a d'autres caracteres que 0, 1, 2, N,S, E, W ```map09e*```
- [ ] Il n'y a pas de map apres la description ```map01e6```

### Les éléments

- [ ] Le premier caractere d'un élément n'est pas un identifiant ```map10e*```
- [ ] L'identifint a plus de deux caracteres ```map11e*```
- [ ] Apres R on a plus de deux nombres ```map12e*```
- [ ] Apres R on a qu'un seul nombre ```map13e*```
- [ ] Apres F ou C on a qu'un seul nombre, que deux nombres, plus de trois nombres, un nb plus grand que 255 ```map14e*```
- [ ] Le path d'une texture est mauvais ```map15e*```
- [ ] Il n'y a aucun caractere (couleur, resolution ou path) apres un identifiant ```map16e*```
- [ ] Apres R on a 0 0 ```map17e01```