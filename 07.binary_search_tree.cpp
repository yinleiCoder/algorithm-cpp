#include <iostream>
#include <queue>
#include "SortTestHelper.h"

using namespace std;

template<typename Key, typename Value>
class BST {
 private:
  struct Node {
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node(Key key, Value value){
      this->key = key;
      this->value = value;
      this->left = this->right = NULL;
    }
    Node(Node *node){
      this->key = node->key;
      this->value = node->value;
      this->left = node->left;
      this->right = node->right;
    }
  };
  Node *root;
  int count;
 public:
  BST(){
    root = NULL;
    count = 0;
  }
  void insert(Key key, Value value){
    root = insert(root, key, value);
  }
  bool contain(Key key) {
    return contain(root, key);
  }
  Value* search(Key key) {
    return search(root, key);
  }
  void preOrder() {
    preOrder(root);
  }
  void inOrder() {
    inOrder(root);
  }
  void postOrder() {
    postOrder(root);
  }
  // 以node为根的二叉搜索树进行层序遍历
  void levelOrder(){
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
      Node *node = q.front();
      q.pop();
      cout << node->key<<endl;
      if(node->left){
        q.push(node->left);
      }
      if(node->right){
        q.push(node->right);
      }
    }
  }
  // 寻找最小的键值
  Key minimum() {
    assert(count != 0);
    Node* minNode = minimum(root);
    return minNode->key;
  }
  // 寻找最大的键值
  Key maxmum() {
    assert(count != 0);
    Node* maxNode = maximum(root);
    return maxNode->key;
  }
  // 删除最小值所在节点
  void removeMin() {
    if(root){
      root = removeMin(root);
    }
  }
  void removeMax() {
    if(root){
      root = removeMax(root);
    }
  }
  /**
   * 删除任意节点(删除只有一个孩子是简单的，但是对于左右都有孩子的节点则可以考虑Hubbard Deletion)
   * 1.删除左右都有孩子的节点d，找到代替节点s=min(d->right)[即右孩子的左孩子]
   * 2.s是d的后继，将s节点删除掉s-right = delMin(d->right);
   * 3.s->left=d->left,删除d，s是新的子树的根
   * @param key
   */
  void remove(Key key) {
    root = remove(root, key);
  }

  int size() {
    return count;
  }
  bool isEmpty() {
    return count == 0;
  }
  ~BST(){
    destroy(root);
  }
 private:
  // 向以node为根的二叉搜索树中，插入节点(key, value)，返回插入新节点后的二叉搜索树的根
  Node* insert(Node *node, Key key, Value value){
    if(node == NULL) {
      count++;
      return new Node(key, value);
    }
    if(key == node->key) {
      node->value = value;
    } else if(key < node->key) {
      node->left = insert(node->left, key, value);
    } else {
      node->right = insert(node->right, key, value);
    }
    return node;
  }
  bool contain(Node* node, Key key) {
    if(node == NULL){
      return false;
    }
    if(key == node->key) {
      return true;
    } else if(key < node->key) {
      return contain(node->left, key);
    } else{
      return contain(node->right, key);
    }
  }
  //以node为根的二叉搜索树中查找key所对应的value
  Value* search(Node* node, Key key) {
    if(node == NULL) {
      return NULL;
    }
    if(key == node->key) {
      return &(node->value);
    } else if(key < node->key) {
      return contain(node->left, key);
    } else {
      return contain(node->right, key);
    }
  }
  //以node为根的二叉搜索树进行前序遍历
  void preOrder(Node* node) {
    if(node != NULL) {
      cout << node->key << endl;
      preOrder(node->left);
      preOrder(node->right);
    }
  }
  //以node为根的二叉搜索树进行中序遍历
  void inOrder(Node* node) {
    if(node != NULL) {
      inOrder(node->left);
      cout << node->key << endl;
      inOrder(node->right);
    }
  }
  //以node为根的二叉搜索树进行中序遍历
  void postOrder(Node* node) {
    if(node != NULL) {
      postOrder(node->left);
      postOrder(node->right);
      cout << node->key << endl;
    }
  }
  void destroy(Node* node) {
    if(node != NULL) {
      destroy(node->left);
      destroy(node->right);
      delete node;
      count--;
    }
  }
  // 在以node为根的二叉搜索树中，返回最小键值的节点
  Node* minimum(Node* node){
    if(node->left == NULL){
      return node;
    }
    return minimum(node->left);
  }
  // 在以node为根的二叉搜索树中，返回最大键值的节点
  Node* maximum(Node* node){
    if(node->right == NULL){
      return node;
    }
    return maximum(node->right);
  }
   // 在以node为根的二叉搜索树中，删除最小节点，返回删除节点后新的二叉搜索树的根
  Node* removeMin(Node* node){
    if(node->left == NULL){
      Node* rightNode = node->right;// 右孩子也是二叉搜索树，代替掉原来父节点成为根
      delete node;
      count--;
      return rightNode;
    }
     node->left = removeMin(node->left);
    return node;
  }
  // 在以node为根的二叉搜索树中，删除最大节点，返回删除节点后新的二叉搜索树的根
  Node* removeMax(Node* node){
    if(node->right == NULL){
      Node* leftNode = node->left;// 左孩子也是二叉搜索树，代替掉原来父节点成为根
      delete node;
      count--;
      return leftNode;
    }
     node->right = removeMin(node->right);
    return node;
  }
  // 删除以node为根的二分搜索树中键值为key的节点
  Node* remove(Node* node, Key key){
    if(node == NULL){
      return NULL;
    }
    if(key < node->key) {
      node->left = remove(node->left, key);
      return node;
    }else if(key > node->key){
      node->right = remove(node->right, key);
      return node;
    } else {
      if(node->left == NULL) {
        Node *rightNode = node->right;
        delete node;
        count--;
        return rightNode;
      }
      if(node->right == NULL) {
        Node *leftNode = node->left;
        delete node;
        count--;
        return leftNode;
      }
      // 左右孩子都不为空
      Node *delNode = node;
      Node *successor = new Node(minimum(node->right));
      count++;
      successor->right = removeMin(node->right);
      successor->left = node->left;
      delete delNode;
      count--;
      return successor;
    }
  }

};


/**
 * 二分搜索树/二叉排序树(logn):
 * 1，每个节点的键值>左孩子，<右孩子
 * 2. 以左右孩子为根的子树仍然为二分搜索树
 * 3. 不一定是完全二叉树
 * 通常用于实现查找表——字典数据结构
 * 平衡二叉树可以考虑红黑树
 * @return
 */
int main() {
  return 0;
}

