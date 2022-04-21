#include "Index.h"

using namespace std;

void Node::setKeyLeft(shared_ptr<std::string> leftkey) {
  this->keyLeft = leftkey;
}
void Node::setKeyRight(shared_ptr<std::string> rightkey) {
  this->keyRight = rightkey;
}
void Node::setKeyTemp(shared_ptr<std::string> tempkey) { this->mid = tempkey; }
void Node::setValueLeft(int leftvalue) { this->valueLeft = leftvalue; }
void Node::setValueRight(int rightvalue) { this->valueRight = rightvalue; }
void Node::setValueTemp(int tempvalue) { this->valueMid = tempvalue; }

shared_ptr<std::string> Node::getKeyLeft() { return keyLeft; }
shared_ptr<std::string> Node::getKeyRight() { return keyRight; }
shared_ptr<std::string> Node::getKeyTemp() { return mid; }

int Node::getValueLeft() { return this->valueLeft; }
int Node::getValueRight() { return this->valueRight; }
int Node::getValueTemp() { return this->valueMid; }

std::shared_ptr<Node> Node::getLeft() { return this->left; }
std::shared_ptr<Node> Node::getRight() { return this->right; }
std::shared_ptr<Node> Node::getLeftMid() { return this->leftMid; }
std::shared_ptr<Node> Node::getRightMid() { return this->rightMid; }
std::shared_ptr<Node> Node::getParent() { return this->parent; }

void Node::setParent(std::shared_ptr<Node> parent) { this->parent = parent; }
void Node::setLeftMid(std::shared_ptr<Node> leftmid) {
  this->leftMid = leftmid;
}
void Node::setRightMid(std::shared_ptr<Node> rightmid) {
  this->rightMid = rightmid;
}
void Node::setLeft(std::shared_ptr<Node> left) { this->left = left; }
void Node::setRight(std::shared_ptr<Node> right) { this->right = right; }

bool Node::isFull() {
  return (keyLeft != nullptr && keyRight != nullptr && mid != nullptr);
}
bool Node::isLeaf() const { return !left && !right && !leftMid; }

bool Node::isTwoNode() {
  if (keyLeft && !keyRight)
    return true;
  else
    return false;
}
bool Node::isThreeNode() const {
  return (keyLeft && keyRight);
}

// public constructor
Index::Index() { root = nullptr; }

Index::~Index() { root.reset(); }

int Index::compare(std::shared_ptr<std::string> left,
                   std::shared_ptr<std::string> right) {
  if (left == nullptr || right == nullptr) {
    cout << "error";
  }
  return left->compare(*right);
}

void Index::Insert(shared_ptr<string> key, int value) {
  if (root == nullptr) {
    root = make_shared<Node>();
    add(root, key, value);
  } else {
    shared_ptr<Node> curr1 = root;
    shared_ptr<Node> curr = findNode(curr1, key);
    add(curr, key, value);

    if (curr->isFull()) {
      split(curr);
    }
  }
}

void Index::add(shared_ptr<Node> curr, shared_ptr<string> key, int value) {
  if (curr->isTwoNode()) {
    if (compare(curr->getKeyLeft(), key) < 0) {
      curr->setKeyRight(key);
      curr->setValueRight(value);
    } else if (compare(curr->getKeyLeft(), key) > 0) {
      curr->setKeyRight(curr->getKeyLeft());
      curr->setValueRight(curr->getValueLeft());
      curr->setKeyLeft(key);
      curr->setValueLeft(value);
    } else {
      curr->setKeyLeft(key);
      curr->setValueLeft(value);
    }
  } else if (curr->isThreeNode()) {
    if (compare(curr->getKeyLeft(), key) > 0 &&
        compare(curr->getKeyRight(), key) > 0) {
      curr->setKeyTemp(curr->getKeyLeft());
      curr->setValueTemp(curr->getValueLeft());
      curr->setKeyLeft(key);
      curr->setValueLeft(value);
    } else if (compare(curr->getKeyRight(), key) < 0) {
      curr->setKeyTemp(curr->getKeyRight());
      curr->setValueTemp(curr->getValueRight());
      curr->setKeyRight(key);
      curr->setValueRight(value);
    } else if (compare(curr->getKeyRight(), key) == 0) {
      curr->setKeyRight(key);
      curr->setValueRight(value);
    } else if (compare(curr->getKeyLeft(), key) == 0) {
      curr->setKeyLeft(key);
      curr->setValueLeft(value);
    } else {
      curr->setKeyTemp(key);
      curr->setValueTemp(value);
    }
  } else {
    curr->setKeyLeft(key);
    curr->setValueLeft(value);
  }
}
shared_ptr<Node> Index::findNode(std::shared_ptr<Node> root,
                                 std::shared_ptr<std::string> keyFind) {
  if (root->isLeaf())
    return root;
  if (root->isThreeNode()) {
    if (compare(keyFind, root->getKeyLeft()) == 0 || compare(keyFind, root->getKeyRight()) == 0) {
      return root;
    } else if (compare(keyFind, root->getKeyLeft()) > 0 &&
               compare(keyFind, root->getKeyRight()) < 0) {
      return findNode(root->getLeftMid(), keyFind);
    }
  }
  if (compare(keyFind, root->getKeyLeft()) == 0) {
    return root;
  } else if (compare(keyFind, root->getKeyLeft()) < 0 && root->getLeft() !=
  nullptr) {
    return findNode(root->getLeft(), keyFind);
  } else {
    return findNode(root->getRight(), keyFind);
  }
}

void Index::setRoot(std::shared_ptr<Node> curr) { this->root = curr; }
void Index::split(std::shared_ptr<Node> curr) {
  shared_ptr<Node> p;

  if (curr != root) {
    p = curr->getParent();
  } else {
    p = make_shared<Node>();
    setRoot(p);
  }

  shared_ptr<Node> n1 = make_shared<Node>();
  shared_ptr<Node> n2 = make_shared<Node>();

  n1->setParent(p);
  n2->setParent(p);
  n1->setKeyLeft(curr->getKeyLeft());
  n1->setValueLeft(curr->getValueLeft());
  n2->setValueLeft(curr->getValueRight());
  n2->setKeyLeft(curr->getKeyRight());

  if (p->isThreeNode()) {
    if (curr == p->getLeft()) {
      p->setRightMid(p->getLeftMid());
      p->setLeft(n1);
      p->setLeftMid(n2);
    } else if (curr == p->getRight()) {
      p->setRightMid(n1);
      p->setRight(n2);
    } else if (curr == p->getLeftMid()) {
      p->setLeftMid(n1);
      p->setRightMid(n2);
    }
  } else if (p->isTwoNode()) {
    if (curr == p->getLeft()) {
      p->setLeftMid(n2);
      p->setLeft(n1);
    } else {
      p->setLeftMid(n1);
      p->setRight(n2);
    }
  } else {
    if (p == root) {
      p->setLeft(n1);
      p->setRight(n2);
    }
  }

  if (!curr->isLeaf()) {
    n1->setLeft(curr->getLeft());
    n1->setRight(curr->getLeftMid());
    n1->getLeft()->setParent(n1);
    n1->getRight()->setParent(n1);
    n2->setLeft(curr->getRightMid());
    n2->setRight(curr->getRight());
    n2->getLeft()->setParent(n2);
    n2->getRight()->setParent(n2);
  }

  add(p, curr->getKeyTemp(), curr->getValueTemp());

  if (p->isFull()) {
    split(p);
  }
}

int Index::Find(std::shared_ptr<std::string> key) {
  if(root == nullptr)
    return -1;
  shared_ptr<Node> find = findNode(root, key);
  if (find->getKeyLeft() != nullptr && compare(find->getKeyLeft(), key) == 0) {
    return find->getValueLeft();
  } else if (find->getKeyRight() != nullptr &&
             compare(find->getKeyRight(), key) == 0) {
    return find->getValueRight();
  } else
    return -1;
}

// Remove an element from the index
void Index::Remove(std::shared_ptr<std::string> key) {
  shared_ptr<Node> curr = findNode(root, key);
  curr = deleteHelper(curr, key);
  
  if (curr->isEmpty()) {
    merge(curr);
  }
}

bool Index::contains(shared_ptr<Node> curr, std::shared_ptr<std::string> key) {
  return (curr->getKeyLeft() != nullptr && (curr->getKeyLeft(), key) == 0 ||
          curr->getKeyRight() != nullptr && (curr->getKeyRight(), key) == 0);
}

shared_ptr<Node> Index::deleteHelper(shared_ptr<Node> currtemp,
                                     shared_ptr<std::string> key) {
  shared_ptr<Node> curr = currtemp;
  if(curr == root)
  {
    setRoot(make_shared<Node>());
  }
  if (!curr->isLeaf()) {
    if (curr->isThreeNode()) {
      if (compare(curr->getKeyLeft(), key) == 0) {
        curr = curr->getLeftMid();
      } else {
        curr = curr->getRight();
      }
    } else
      curr = curr->getRight();
    while (!curr->isLeaf()) {
      curr = curr->getLeft();
    }

    if (curr->isThreeNode()) {
      if (compare(curr->getKeyLeft(), key) > 0) {
        if (compare(currtemp->getKeyLeft(), key) == 0) {
          currtemp->setKeyLeft(curr->getKeyLeft());
          currtemp->setValueLeft(curr->getValueLeft());
        } else {
          currtemp->setKeyRight(curr->getKeyLeft());
          currtemp->setValueRight(curr->getValueLeft());
        }
        curr->setKeyLeft(curr->getKeyRight());
        curr->setValueLeft(curr->getValueRight());
        curr->setKeyRight(nullptr);
        curr->setValueRight(-1);
      } else if (compare(curr->getKeyLeft(), key) < 0) {
        if (compare(currtemp->getKeyLeft(), key) == 0) {
          currtemp->setKeyLeft(curr->getKeyRight());
          currtemp->setValueLeft(curr->getValueRight());
        } else {
          currtemp->setKeyRight(curr->getKeyRight());
          currtemp->setValueRight(curr->getValueRight());
        }
        curr->setKeyRight(nullptr);
        curr->setValueRight(-1);
      }
    } else if (curr->isTwoNode()) {
      if (compare(curr->getKeyLeft(), key) > 0) {
        if (compare(currtemp->getKeyLeft(), key) == 0) {
          currtemp->setKeyLeft(curr->getKeyLeft());
          currtemp->setValueLeft(curr->getValueLeft());
          curr->setKeyLeft(nullptr);
          curr->setValueLeft(-1);
        } else {
          currtemp->setKeyRight(curr->getKeyLeft());
          currtemp->setValueRight(curr->getValueLeft());
          curr->setKeyLeft(nullptr);
          curr->setValueLeft(-1);
        }
      }
    }
  } else if (curr->isLeaf()) {
    if(curr == root)
    {
      setRoot(make_shared<Node>());
    }
    if (curr->isThreeNode()) {
      if (compare(curr->getKeyLeft(), key) == 0) {
        curr->setKeyLeft(curr->getKeyRight());
        curr->setValueLeft(curr->getValueRight());
        curr->setKeyRight(nullptr);
        curr->setValueRight(-1);
      } else if (compare(curr->getKeyRight(), key) == 0) {
        curr->setKeyRight(nullptr);
        curr->setValueRight(-1);
      }
    } else if (curr->isTwoNode()) {
      if (compare(curr->getKeyLeft(), key) == 0) {
        curr->setKeyLeft(nullptr);
        curr->setValueLeft(-1);
      }
    }
  }
  return curr;
}

void Index::merge(std::shared_ptr<Node> curr) {
  shared_ptr<Node> p;
  if (curr == root) {
    if(curr->isEmpty() && curr->isLeaf())
    {
      return;
    }
    else if (!curr->getLeft()->isEmpty() && curr->getRight()->isEmpty()) {
      setRoot(curr->getLeft());
      return;
    } else if (!curr->getRight()->isEmpty() && curr->getLeft()->isEmpty()) {
      setRoot(curr->getRight());
      return;
    }
  } else if (curr != root) {
    p = curr->getParent();
  }
  
  if(!p->isEmpty() && p->isTwoNode()) {
    if (curr == p->getLeft()) {
      if (p->getRight()->isTwoNode()) {
        p->getRight()->setKeyRight(p->getRight()->getKeyLeft());
        p->getRight()->setValueRight(p->getRight()->getValueLeft());
        p->getRight()->setKeyLeft(p->getKeyLeft());
        p->getRight()->setValueLeft(p->getValueLeft());
        
        if (!curr->isLeaf()) {
          p->getRight()->setLeftMid(p->getRight()->getLeft());
          if(curr->getRight()->isEmpty())
          {
            p->getRight()->setLeft(curr->getLeft());
            p->getRight()->getLeft()->setParent(p->getRight());
          }
          else
          {
            p->getRight()->setLeft(curr->getRight());
            p->getRight()->getLeft()->setParent(p->getRight());
          }  
        }
        p->setKeyLeft(nullptr);
        p->setValueLeft(-1);
      } else if (p->getRight()->isThreeNode()) {
        curr->setKeyLeft(p->getKeyLeft());
        curr->setValueLeft(p->getValueLeft());
        if (!curr->isLeaf()) {
          if (curr->getLeft()->isEmpty()) {
            curr->setLeft(curr->getRight());
          }
          curr->setRight(p->getRight()->getLeft());
          curr->getRight()->setParent(curr);
          p->getRight()->setLeft(p->getRight()->getLeftMid());
          p->getRight()->setLeftMid(make_shared<Node>());
        }
        p->setKeyLeft(p->getRight()->getKeyLeft());
        p->setValueLeft(p->getRight()->getValueLeft());
        p->getRight()->setKeyLeft(p->getRight()->getKeyRight());
        p->getRight()->setValueLeft(p->getRight()->getValueRight());
        p->getRight()->setKeyRight(nullptr);
        p->getRight()->setValueRight(-1);
      }
    } else if (curr == p->getRight()) {
      if (p->getLeft()->isThreeNode()) {
        curr->setKeyLeft(p->getKeyLeft());
        curr->setValueLeft(p->getValueLeft());
    
        if (!curr->isLeaf()) {
          if(curr->getRight()->isEmpty())
          {
            curr->setRight(curr->getLeft());
          }    
          curr->setLeft(p->getLeft()->getRight());
          curr->getLeft()->setParent(curr);
          p->getLeft()->setRight(p->getLeft()->getLeftMid());
          p->getLeft()->setLeftMid(make_shared<Node>());
        }
        p->setKeyLeft(p->getLeft()->getKeyRight());
        p->setValueLeft(p->getLeft()->getValueRight());
        p->getLeft()->setKeyRight(nullptr);
        p->getLeft()->setValueRight(-1);
      } else if (p->getLeft()->isTwoNode()) {
        
        p->getLeft()->setKeyRight(p->getKeyLeft());
        p->getLeft()->setValueRight(p->getValueLeft());
        if (!curr->isLeaf()) {
          p->getLeft()->setLeftMid(p->getLeft()->getRight());
          p->getLeft()->getLeftMid()->setParent(p->getLeft());
          if(curr->getLeft()->isEmpty())
          {
            p->getLeft()->setRight(curr->getRight());
            p->getLeft()->getRight()->setParent(p->getLeft());
            curr->setRight(make_shared<Node>());
          }   
          else
          {
            p->getLeft()->setRight(curr->getLeft());
            p->getLeft()->getRight()->setParent(p->getLeft());
          }
        }
        p->setKeyLeft(nullptr);
        p->setValueLeft(-1);
      }
    }
  }
  else if (p->isThreeNode()) {
    if (curr == p->getLeft()) {
      if (p->getLeftMid()->isThreeNode()) {
        curr->setKeyLeft(p->getKeyLeft());
        curr->setValueLeft(p->getValueLeft());

        p->setKeyLeft(p->getLeftMid()->getKeyLeft());
        p->setValueLeft(p->getLeftMid()->getValueLeft());

        p->getLeftMid()->setKeyLeft(p->getLeftMid()->getKeyRight());
        p->getLeftMid()->setValueLeft(p->getLeftMid()->getValueRight());

        p->getLeftMid()->setKeyRight(nullptr);
        p->getLeftMid()->setValueRight(-1);
        if (!curr->isLeaf()) {
          if (curr->getLeft()->isEmpty()) {
            curr->setLeft(curr->getRight());
          }
          curr->setRight(p->getLeftMid()->getLeft());
          curr->getRight()->setParent(curr);
          p->getLeftMid()->setLeft(p->getLeft()->getLeftMid());
          p->setLeftMid(make_shared<Node>());
        }
      } else if (p->getLeftMid()->isTwoNode()) {
        curr->setKeyLeft(p->getKeyLeft());
        curr->setValueLeft(p->getValueLeft());
        
        curr->setKeyRight(p->getLeftMid()->getKeyLeft());
        curr->setValueRight(p->getLeftMid()->getValueLeft());
      
        if (!curr->isLeaf()) {
          if (curr->getLeft()->isEmpty()) {
            curr->setLeft(curr->getRight());
          }
          curr->setLeftMid(p->getLeftMid()->getLeft());
          curr->setRight(p->getLeftMid()->getRight());
          curr->getLeftMid()->setParent(curr);
          curr->getRight()->setParent(curr);
        }
        p->setLeftMid(make_shared<Node>());
        p->setKeyLeft(p->getKeyRight());
        p->setValueLeft(p->getValueRight());
        p->setValueRight(-1);
        p->setKeyRight(nullptr);
      }
    } else if (curr == p->getLeftMid()) {
      if (p->getLeft()->isThreeNode()) {
        curr->setKeyLeft(p->getKeyLeft());
        curr->setValueLeft(p->getValueLeft());

        p->setKeyLeft(p->getLeft()->getKeyRight());
        p->setValueLeft(p->getLeft()->getValueRight());

        p->getLeft()->setKeyRight(nullptr);
        p->getLeft()->setValueRight(-1);

        if (!curr->isLeaf()) {
          if (curr->getRight()->isEmpty()) {
            curr->setRight(curr->getLeft());
          }
          curr->setLeft(p->getLeft()->getRight());
          curr->getLeft()->setParent(curr);
          p->getLeft()->setRight(p->getLeft()->getLeftMid());
          p->getLeft()->setLeftMid(make_shared<Node>());
        }
      } else if (p->getLeft()->isTwoNode()) {
        p->getLeft()->setKeyRight(p->getKeyLeft());
        p->getLeft()->setValueRight(p->getValueLeft());
        p->setKeyLeft(p->getKeyRight());
        p->setValueLeft(p->getValueRight());
        if (!curr->isLeaf()) {
          p->getLeft()->setLeftMid(p->getLeft()->getRight());
          if (curr->getLeft()->isEmpty()) {
            p->getLeft()->setRight(curr->getRight());
            p->getLeft()->getRight()->setParent(p->getLeft());
            curr->setRight(nullptr);
          } else {
            p->getLeft()->setRight(curr->getLeft());
            p->getLeft()->getRight()->setParent(p->getLeft());
            curr->setLeft(make_shared<Node>());
          }
        }
        p->setKeyRight(nullptr);
        p->setValueTemp(-1);
      }
    } else if (curr == p->getRight()) {
      curr->setKeyLeft(p->getKeyRight());
      curr->setValueLeft(p->getValueRight());
      p->setKeyRight(nullptr);
      p->setValueRight(-1);
      if (p->getLeftMid()->isThreeNode()) {
        p->setKeyRight(p->getLeftMid()->getKeyRight());
        p->setValueRight(p->getLeftMid()->getValueRight());
        p->getLeftMid()->setKeyRight(nullptr);
        p->getLeftMid()->setValueRight(-1);
        if (!curr->isLeaf()) {
          if (curr->getRight()->isEmpty()) {
            curr->setRight(curr->getLeft());
          }
          curr->setLeft(p->getLeftMid()->getRight());
          curr->getLeft()->setParent(curr);
          p->getLeftMid()->setRight(p->getLeftMid()->getLeftMid());
          p->getLeftMid()->setLeftMid(make_shared<Node>());
        }
      } else if (p->getLeftMid()->isTwoNode()) {
        curr->setKeyRight(curr->getKeyLeft());
        curr->setValueRight(curr->getValueLeft());
        curr->setKeyLeft(p->getLeftMid()->getKeyLeft());
        curr->setValueLeft(p->getLeftMid()->getValueLeft());
        if (!curr->isLeaf()) {
          if (curr->getRight()->isEmpty()) {
            curr->setRight(curr->getLeft());
          }
          curr->setLeft(p->getLeftMid()->getLeft());
          curr->setLeftMid(p->getLeftMid()->getRight());
          curr->getLeft()->setParent(curr);
          curr->getLeftMid()->setParent(curr);
        }    
        p->setLeftMid(make_shared<Node>());
      }
    }
  }

  if (p->isEmpty()) {
    merge(p);
  }
}

bool Node::isEmpty() {
  return (keyLeft && keyRight);
}