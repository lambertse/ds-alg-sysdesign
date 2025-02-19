#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define MAX_LEVEL 33

namespace util {
int randomLevel();
} // namespace util

template <class ValueType> class Node {
public:
  Node(ValueType value, size_t level) : value(value), level(level) {
    next = std::vector<Node *>{level, nullptr};
  }
  ValueType value;
  int level;
  std::vector<Node *> next;
};

template <class ValueType> class SkipList {
public:
  using NodeValue = Node<ValueType>;
  SkipList() {
    _head = new NodeValue(ValueType(), MAX_LEVEL);
    std::srand(std::time(0)); // Initialize random seed once
  }

  ~SkipList() {
    NodeValue *current = _head;
    while (current) {
      NodeValue *next = current->next[0];
      delete current;
      current = next;
    }
  }

  bool contain(ValueType value) {
    NodeValue *curNode = _head;
    int level = MAX_LEVEL - 1;
    for (; level >= 0; level--) {
      while (curNode->next[level] && curNode->next[level]->value <= value) {
        if (curNode->next[level]->value == value)
          return true;
        curNode = curNode->next[level];
      }
    }
    return false;
  }

  bool insert(ValueType value) {
    NodeValue *curNode = _head;
    std::vector<NodeValue *> pre{MAX_LEVEL, _head};
    int level = MAX_LEVEL - 1;
    for (; level >= 0; level--) {
      while (curNode->next[level] && curNode->next[level]->value <= value) {
        if (curNode->next[level]->value == value) {
          return false;
        }
        curNode = curNode->next[level];
      }
      pre[level] = curNode;
    }

    int maxLevel = util::randomLevel();
    auto newNode = new NodeValue(value, maxLevel);

    for (level = 0; level < maxLevel; level++) {
      NodeValue *preNext = pre[level]->next[level];
      pre[level]->next[level] = newNode;
      newNode->next[level] = preNext;
    }
    return true;
  }

  bool deleteValue(ValueType value) {

    std::vector<NodeValue *> pre{MAX_LEVEL, _head};
    int level = MAX_LEVEL - 1;
    NodeValue *curNode = _head;
    NodeValue *foundNode = nullptr;
    for (; level >= 0; level--) {
      while (curNode->next[level] && curNode->next[level]->value <= value) {
        if (curNode->next[level]->value == value) {
          foundNode = curNode->next[level];
          break;
        }
        curNode = curNode->next[level];
      }
      pre[level] = curNode;
    }
    if (!foundNode)
      return false;

    for (level = 0; level < foundNode->level; level++) {
      pre[level]->next[level] = foundNode->next[level];
    }

    delete foundNode;
    return true;
  }

private:
  Node<ValueType> *_head;
};

namespace util {
int randomLevel() {
  int level = 1;
  while ((std::rand() % 2) == 0 && level < MAX_LEVEL) {
    level++;
  }
  return level;
}

} // namespace util
