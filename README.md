### ⚠️  Ne pas oublier de ```make fclean``` avant de ```git push``` ⚠️

gcc ./src/parsing.c ./src/parsing_map.c ./src/parsing_color_resolution_texture.c ./src/parsing_utils.c ./src/get_next_line.c ./src/get_next_line_utils.c ./inc/cub3d.h libmlx.dylib src/raycasting.c src/minimap.c src/keys.c&& ./a.out description.cub

# Cub3D
A 3D game using raycasting.

Start
```
make && ./Cub3D description.cub
```
Supprimer tout
```
make fclean
```

## INTRODUCTION 🤓

Sujet -> [EN](https://github.com/tinaserra/Cub3D/blob/master/links/cub3d_en.pdf) | [FR](https://github.com/tinaserra/Cub3D/blob/master/links/cube3d_fr.pdf)

## RAYCASTING 😎

**Raycasting** est une technique de rendu permettant de créer une perspective 3D dans une carte 2D. Le jeu le plus connu qui utilise cette technique est bien sûr **Wolfenstein 3D**.

### Raycasting & Raytracing

***Raycasting n'est pas la même chose que raytracing!***</br></br>
Le raycasting est **une technique semi-3D rapide** qui fonctionne en temps réel même sur des calculatrices graphiques à 4 MHz.</br>
Le raytracing est **une technique de rendu réaliste** qui prend en charge les reflets et les ombres dans de vraies scènes 3D, et ce n'est que récemment que les ordinateurs sont devenus assez rapides pour le faire en temps réel pour un niveau raisonnablement élevé. résolutions et scènes complexes.

### Le principe du raycasting

Tuto :</br>
[How to become a Raycasting Master <3](https://lodev.org/cgtutor/raycasting.html)

Envoyer des rayons de gauche à droite depuis la position du joueur.
Plus le rayon met du temps à atteindre le mur, plus il est loin.
Plus il est loin plus la colonne de pixels est petite.
La couleur dépend aussi de la distance : plus c’est loin plus c’est foncé plus c’est près plus c’est clair.


## USEFUL LINKS 🤙🏼
* [Raycasting tutorial video](https://courses.pikuma.com/courses/take/raycasting/lessons/7485598-introduction-and-learning-outcomes)
* [Lodev raycasting tutorial in english](https://lodev.org/cgtutor/raycasting.html)
* [Le raycasting en francais](http://projet-moteur-3d.e-monsite.com/pages/raycasting/raycasting.html)
* [Images in MLX](https://github.com/keuhdall/images_example)

# Comment utiliser Git en multi ?

Pour lister les branches existantes dans le repository local:
```js
git branch
```
Pour créer une branche en local, il suffit de faire:
```js
git branch [nom-de-la-branche]
```
Pour basculer sur une branche donnée et travailler dessus:
```js
git checkout [nom-de-la-branche]
```
Pour pusher la branche actuelle vers le repository distant:
```js
git push origin [nom-de-la-branche]
```
Pour lister les branches distantes:
```js
git remote show origin
```
Pour un autre développeur qui voudrait utiliser la branche nom-de-la-branche
```js
git fetch origin
git checkout origin/[nom-de-la-branche]
```
La première commande met à jour le repository local avec les changements présents dans le repository ditant. La deuxième crée un branche locale « nom-de-la-branche » câblée sur la branche distante.

Pour appliquer les changements de la branche master distante sur une branche locale spécifique: ```rebase```
```c
// on se positionne sur notre branche master
git checkout master

// on la met à jour par rapport au repository distant
git pull

// on se positionne sur la branche [nom-de-la-branche]
git checkout [nom-de-la-branche]

// on tente d'appliquer les changements fait dans master
git rebase master

// en cas de conflit, les résoudre et faire  "git rebase --continue"
```

Git: [pense-bête](http://www.letuyau.net/2012/09/git-pense-bete/)
