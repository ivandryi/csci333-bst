#include "BST.h"
#include <iostream>
#include <list>
template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  postOrderDelete(root);
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {  // using in-rder successor
  Node<T>** curr = &root;
  while(curr != 0 && (*curr)->getValue() != v) {
    if(v > (*curr)->getValue())
      curr = &((*curr)->getRightChild());
    else 
      curr = &((*curr)->getLeftChild());
  }
  if(curr != 0) {
    Node<T>* nodeToRemove = *curr;
    if(nodeToRemove->getLeftChild() == 0 && nodeToRemove->getRightChild() == 0) {
      delete nodeToRemove;
      *curr = 0;
    } else if (nodeToRemove->getLeftChild() == 0) {
      *curr = nodeToRemove->getRightChild();
      delete nodeToRemove;
    } else if (nodeToRemove->getRightChild() == 0) {
      *curr = nodeToRemove->getLeftChild();
      delete nodeToRemove;
    } else {
      Node<T>* ios = nodeToRemove->getRightChild();
      while(ios->getLeftChild() != 0) {
	ios = ios->getLeftChild();
      }
      ios->setLeftChild(*(nodeToRemove->getLeftChild()));
      *curr = nodeToRemove->getRightChild();
      delete nodeToRemove;
    }
  }
}


template<typename T>
void BST<T>::postOrderDelete(Node<T>* t) {
  if (t != 0) {
    postOrderDelete(t->getLeftChild());
    postOrderDelete(t->getRightChild());
    delete t;
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {

    traversalPrint(root->getLeftChild());

    traversalPrint(root->getRightChild());
    std::cout << root->getValue() << std::endl;
  }
}

template <typename T>
void BST<T>::printTree() {
  std::list<Node<T>* > queue;
  queue.push_front(root);
  int count = 1;
  while(!queue.empty()){
    std::cout << std::endl;
    Node<T>* val = queue.front();
    std::cout << val->getValue();
    queue.pop_front();
    
    if(val->getLeftChild()!=0 || val->getRightChild()!=0){
      count++;
    }
    if(val->getLeftChild()!=0)
    queue.push_back(val->getLeftChild());
    if(val->getRightChild()!=0)
    queue.push_back(val->getRightChild());

  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
