# General

ConvexHullMaker is little program to create convex hulls.

It tries to effectively solve the dynamic convex hull problem.

![appIcon](appIcon.png)

WARNING: Lining up the hull results in undefined behavior!

# Algorithms

n - total number of points on scene

m - number of points in hull

## I. AddPoint

1. Check whether we are inside the polygon using logarithmic complexity.

2. If this is not the case, check which hull points are visible and which are not.

3. Replace visible points (excluding boundary ones) with a new point

### Complexity

T(addPoint) = O(log(m)), if interior of the hull containts point

T(addPoint) = O(m), otherwise

## II.  RemovePoint

1. Check whether the hull contains target point.

2. If it's our case delete triangle (p-1), (p), (p+1).

3. Find all points in deleted triangle.

4. Build convex polygon from this points.

5. Merge hull and new polygon.

### Complexity

T(removePoint) = O(nlog(n)), if the hull contains point

T(removePoint) = O(m), otherwise

# Usage

# Shortcuts

| Keys  | Actions |
|-------|---------|
X | Clear scene
R | check/unchek rewrite option
P | open save file dialog
Ctrl + S | save hull
Ctrl + Z | undo
Ctrl + Shift + Z | redo
Ctrl + Y | also redo