#ifndef _INDEX_
#define _INDEX_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Node {
private:
  std::shared_ptr<std::string> keyLeft;
  std::shared_ptr<std::string> keyRight;
  std::shared_ptr<std::string> mid;
  int valueMid, valueLeft, valueRight;
  std::shared_ptr<Node> left, right, leftMid, rightMid, parent;

public:
  // constructor
  Node()
      : left(nullptr), right(nullptr), leftMid(nullptr), rightMid(nullptr),
        parent(nullptr) {
    keyLeft = nullptr;
    keyRight = nullptr;
    mid = nullptr;
    valueMid = valueLeft = valueRight = 0;
  }
  Node(std::shared_ptr<Node> temp)
      : left(nullptr), right(nullptr), leftMid(nullptr), rightMid(nullptr),
        parent(nullptr) {
    keyLeft = temp->getKeyLeft();
    keyRight = temp->getKeyRight();
    mid = nullptr;
    valueMid = 0;
    valueLeft = temp->getValueLeft();
    valueRight = temp->getValueRight();
  }

  void setKeyLeft(std::shared_ptr<std::string> leftkey);
  void setKeyRight(std::shared_ptr<std::string> rightkey);
  void setValueLeft(int leftvalue);
  void setValueRight(int rightvalue);
  void setValueTemp(int tempvalue);
  void setKeyTemp(std::shared_ptr<std::string> tempkey);

  std::shared_ptr<std::string> getKeyRight();
  std::shared_ptr<std::string> getKeyLeft();
  std::shared_ptr<std::string> getKeyTemp();

  int getValueLeft();
  int getValueRight();
  int getValueTemp();

  std::shared_ptr<Node> getLeft();
  std::shared_ptr<Node> getRight();
  std::shared_ptr<Node> getLeftMid();
  std::shared_ptr<Node> getRightMid();
  std::shared_ptr<Node> getParent();

  void setParent(std::shared_ptr<Node> parent);
  void setLeftMid(std::shared_ptr<Node> leftmid);
  void setRightMid(std::shared_ptr<Node> rightmid);
  void setLeft(std::shared_ptr<Node> left);
  void setRight(std::shared_ptr<Node> right);

  bool isLeaf() const;
  bool isTwoNode();
  bool isThreeNode() const;
  bool isFull();
  bool isEmpty();
};

class Index {
private:
  std::shared_ptr<Node> root;

public:
  // public constructor
  Index();
  // Insert an element in the index, associate the integer value with the
  // element
  void Insert(std::shared_ptr<std::string> key, int value);

  void add(std::shared_ptr<Node> curr, std::shared_ptr<std::string> key,
           int value);

  // Find an element in the index
  int Find(std::shared_ptr<std::string> key);
  // Remove an element from the index
  void Remove(std::shared_ptr<std::string> key);
  // Destructor
  ~Index();
  // set root
  void setRoot(std::shared_ptr<Node> curr);
  // compare
  int compare(std::shared_ptr<std::string> left,
              std::shared_ptr<std::string> right);
  // split
  void split(std::shared_ptr<Node> curr);
  // findNode
  std::shared_ptr<Node> findNode(std::shared_ptr<Node> root1,
                                 std::shared_ptr<std::string> keyFind);
  // search if contain value in node
  bool contains(std::shared_ptr<Node> curr, std::shared_ptr<std::string> key);
  // remove helper function
  std::shared_ptr<Node> deleteHelper(std::shared_ptr<Node> currtemp,
                                     std::shared_ptr<std::string> key);
  // merge function
  void merge(std::shared_ptr<Node> curr);

  int getRoot() { return root->getValueRight(); }
};

#endif