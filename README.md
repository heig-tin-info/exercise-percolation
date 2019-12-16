# Percolation

Une entreprise vaudoise vous mandate pour étudier un modèle de percolation en milieu poreux. Le milieu est modélisé par une matrice aléatoire d'entiers qui détermine les sites qui peuvent être envahis par l'eau et ceux qui sont imperméables.

Une matrice percole s'il existe un chemin d'eau allant de la ligne supérieure vers la ligne inférieure.

La matrice suivante ne percole pas car l'eau ne pénètre pas jusqu'en bas.

```console
1 1 2 1 2 2 1 2 2 1
2 1 1 2 2 1 1 1 2 1
2 2 2 2 2 2 1 1 2 2
2 2 1 2 2 1 1 2 2 1
1 1 0 1 2 2 2 2 2 2
0 0 1 1 1 2 2 1 1 1
0 0 1 0 1 1 1 0 0 1
0 1 1 1 1 1 0 1 0 0
1 0 1 1 0 1 1 0 0 0
0 1 0 0 0 0 0 0 0 1
```

La convention est `0` pour un vide ou pore, `1` pour un obstacle imperméable et `2` pour l'eau.

L'eau ne peut circuler que horizontalement et verticalement, pas par les diagonales.

## Cahier des charges

1. Créer une matrice de 20 par 20
2. La remplire avec des valeurs aléatoires (`0` ou `1`)
3. Tester la percolation
4. Afficher la matrice
5. Dire si oui ou non la matrice percole
