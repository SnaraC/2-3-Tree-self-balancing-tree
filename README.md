# 2-3-Tree

C++ implementation of functionalities (insertion, deletion, search) of 2-3-Tree (self-balancing tree). 

Made by: Sovannara Chou

This is one of my projects in Data Structures, Algorithms, and Discrete Mathematics II (CSS 343) at UWB. 

Project goal: creating a 2-3tree to build balancing tree working up to 100k input values. PASS TEST!

**Description:**

** Search**
  - Search function will return the value that we search for.
  
** Insert**
  - Use find helper function to find the node then insert data/value.
  - Use split helper function to split the node if tree node is full(3 node) for balancing purpose. 


**- Remove** 
  - Use find function to find the node then use remove function to remove data/value.
  - Use Merge function to merge the node if tree node is empty for balancing purpose.
