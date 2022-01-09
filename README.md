# data-structures
Collection of idfferent data structures implemented in c++
## Data Structures Implemented
* Hashing
* Red Black Tree
## Description
### Hashing
A hashing algorithm is a mathematical algorithm that converts an input data array of a certain type and arbitrary length to an output bit string of a fixed length. 
Hashing algorithms take any input and convert it to a uniform message by using a hashing table.
#### Conflict Resolve
Conflicts were resolved in two ways
* Linear Probing
* Separate Chaining
##### Linear Probing
Along with quadratic probing and double hashing, linear probing is a form of open addressing. 
In these schemes, each cell of a hash table stores a single key–value pair.
When the hash function causes a collision by mapping a new key to a cell of the hash table that is already occupied by another key, 
linear probing searches the table for the closest following free location and inserts the new key there. Lookups are performed in the same way, 
by searching the table sequentially starting at the position given by the hash function, until finding a cell with a matching key or an empty cell.
##### Separate Chaining
The idea is to make each cell of hash table point to a linked list of records that have same hash function value. 
#### Output
![output_hashing](images/output_hashing.png)
### Red Black Tree
In computer science, a **red–black tree** is a kind of self-balancing binary search tree. Each node stores an extra bit representing "color" (**"red"** or **"black"**), used to ensure that the tree remains balanced during insertions and deletions.

When the tree is modified, the new tree is rearranged and "repainted" to restore the coloring properties that constrain how unbalanced the tree can become in the worst case. The properties are designed such that this rearranging and recoloring can be performed efficiently.


