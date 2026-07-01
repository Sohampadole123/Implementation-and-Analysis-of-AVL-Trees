# Implementation-and-Analysis-of-AVL-Trees

This repository contains a complete implementation of an AVL Tree data structure in C++. The project provides a menu-driven console application that supports insertion, deletion, searching, updating, and traversal operations while automatically maintaining tree balance using AVL rotations.

AVL Trees are self-balancing Binary Search Trees (BSTs) that guarantee efficient search, insertion, and deletion operations with logarithmic time complexity.

## Features

- Insert new elements
- Delete existing elements
- Search for elements
- Update existing values
- Display Inorder Traversal
- Display Preorder Traversal
- Display Postorder Traversal
- Display Level Order Traversal
- Find Minimum Element
- Find Maximum Element
- Find Predecessor
- Find Successor
- Display Tree Statistics
- Count Total Nodes
- Clear Complete Tree

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Update | O(log n) |
| Minimum | O(log n) |
| Maximum | O(log n) |
| Predecessor | O(log n) |
| Successor | O(log n) |
| Traversals | O(n) |
| Clear Tree | O(n) |

---

## Menu

After running the program, the following menu appears.

```
1. Insert
2. Delete
3. Search
4. Display Inorder
5. Display Preorder
6. Display Postorder
7. Display Level Order
8. Count Elements
9. Minimum
10. Maximum
11. Predecessor
12. Successor
13. Update Value
14. Tree Statistics
15. Clear Tree
16. Exit
```

---

## Demonstration

### Insert Elements

```
Choice: 1
Enter value: 30

Inserted Successfully

Choice: 1
Enter value: 20

Inserted Successfully

Choice: 1
Enter value: 40

Inserted Successfully

Choice: 1
Enter value: 10

Inserted Successfully

Choice: 1
Enter value: 25

Inserted Successfully

Choice: 1
Enter value: 35

Inserted Successfully

Choice: 1
Enter value: 50

Inserted Successfully
```

---

### Display Inorder

```
Choice: 4

Inorder:
10 20 25 30 35 40 50
```

---

### Display Level Order

```
Choice: 7

Level Order:
30 20 40 10 25 35 50
```

---

### Search

```
Choice: 3

Enter value: 35

Found
```

---

### Minimum and Maximum

```
Choice: 9

Minimum: 10
```

```
Choice: 10

Maximum: 50
```

---

### Find Predecessor

```
Choice: 11

Enter key: 35

Predecessor: 30
```

---

### Find Successor

```
Choice: 12

Enter key: 35

Successor: 40
```

---

### Update a Value

```
Choice: 13

Old Value: 25

New Value: 27

Updated
```

---

### Delete Element

```
Choice: 2

Enter value: 40

Deleted Successfully
```

---

### Tree Statistics

```
Choice: 14

Tree Statistics

---------------
Node Count : 6
Height     : 3
```

---

### Clear Tree

```
Choice: 15

Tree cleared successfully.
```

---

### Exit

```
Choice: 16

Thank You
```

---

## Concepts Used

- AVL Tree
- Binary Search Tree
- Self Balancing Trees
- Tree Rotations (LL, RR, LR, RL)
- Recursion
- Queue (Level Order Traversal)
- Object-Oriented Programming (OOP)
- Dynamic Memory Allocation

---

## Language

- C++17

---

## Compiler

```
g++ -std=c++17 main.cpp -o avl
```

Run:

```
./avl
```