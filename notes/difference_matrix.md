# Difference Matrix

## Motivation

Offline range sum query in matrix with range updates.

## Technique

Let matrix A be the source matrix with size NxM. Let there is matrix D such that A is prefix sum matrix of D.
One can update matrix A by adding value X to A in range [x1,x2) and [y1,y2) just by adding X to D[y1][x1] and D[y2][x2] and subtracting X to D[y1][x2] and D[y2][x1].

For generating matrix A again, we can just simply compute prefix sum of matrix D.