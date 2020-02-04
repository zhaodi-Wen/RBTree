//
// Created by WZD06 on 2019.11.04.
//
#include <stack>
#include <iostream>
#include <iomanip>
using namespace std;
#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H
enum RBTColor{RED,BLACK};
template <class T>
class RBTNode{
public:
    RBTColor color;
    T key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    RBTNode(T value,RBTColor c,RBTNode *p,RBTNode *l,RBTNode *r):
        key(value),color(c),left(l),right(r),parent(p){}
};
template <class T>
class RBTree{
private:
    RBTNode<T> *mRoot;
public:
    RBTree();
    ~RBTree();
    //前序遍历
    void preOrder();
    //中序遍历
    void inOrder();
    //后序遍历
    void  postOrder();

    //递归实现查找key值的节点
    RBTNode<T> *search(T key);
    //非递归查找key值的节点
    RBTNode<T> *iterativeSearch(T key);

    //查找最小节点，返回键值
    T mininum();
    //查找最大节点,返回键值
    T maxinum();

    //找节点(x)的后继节点,即查找大于该节点的最小节点
    RBTNode<T> *successor(RBTNode<T> *x);
    //找节点(x)的前驱节点,即查找小于该节点的最大节点
    RBTNode<T> *predecessor(RBTNode<T> *x);

    //将节点(key为键值)插入红黑树
    void insert(T key);
    //删除节点(key为键值)
    void remove(T key);
    //销毁红黑树
    void destroy();

    //打印红黑树
    void print();

private:
    //前序遍历"红黑树"
    void preOrder(RBTNode<T> *tree) const ;
    //中序遍历"红黑树"
    void inOrder(RBTNode<T> *tree) const ;
    //后序遍历"红黑树"
    void postOrder(RBTNode<T> *tree) const ;

    //递归查找红黑树键值为key的节点
    RBTNode<T> *search(RBTNode<T> *x,T key)const ;
    //非递归查找键值为key的节点
    RBTNode<T> *iterativeSearch(RBTNode<T> *x,T key)const ;

    //查找最小节点,返回tree为根节点的红黑树的最小节点
    RBTNode<T> *minimum(RBTNode<T> *tree);
    //查找最大节点,返回tree为根节点的红黑树的最大节点
    RBTNode<T> *maximum(RBTNode<T> *tree);

    //左旋转
    void leftRotate(RBTNode<T> * &root,RBTNode<T> *x);
    //右旋转
    void rightRotate(RBTNode<T> *&root,RBTNode<T> *x);
    //插入函数
    void insert(RBTNode<T> *&root,RBTNode<T> * node);
    //插入修正函数
    void insertFixUp(RBTNode<T> *&root,RBTNode<T> *node);
    //删除函数
    void remove(RBTNode<T> *&root,RBTNode<T> *node);
    //删除修正函数
    void removeFixUp(RBTNode<T> *&root,RBTNode<T> *node,RBTNode<T> *parent);
    //销毁红黑树
    void  destroy(RBTNode<T> * &tree);
    //打印红黑树
    void print(RBTNode<T> * &tree, T key,int direction);

#define rb_parent(r)       ((r)->parent)
#define rb_color(r)        ((r)->color)
#define rb_is_red(r)       ((r)->color==RED)
#define rb_is_black(r)     ((r)->color==BLACK)
#define rb_set_black(r)    do{ (r)->color==BLACK;} while(0)
#define rb_set_red(r)      do{ (r)->color==RED;}while(0)
#define rb_set_parent(r,p) do{(r)->parent==(p);}while(0)
#define rb_set_color(r,c)  do{(r)->color==c;}while(0)
};
template <class T>
RBTree<T>::RBTree():mRoot(nullptr) {
    mRoot = nullptr;
}
template <class T>
void RBTree<T>::preOrder(RBTNode<T> *tree) const {
    stack <RBTNode<T> *> s;
    RBTNode<T> * root = tree;
    while (root||s.empty()){
        while (root) {
            cout << root->key << " ";
            s.push(root);
            root = root->left;
        }
        if(!s.empty()){
            root = s.top();
            s.pop();
            root = root->right;
        }
    }
}
template <class T>
void RBTree<T>::preOrder() {
    preOrder(mRoot);
}

/**
 * 中序遍历*
 * */
 template <class T>
 void RBTree<T>::inOrder(RBTNode<T> * tree)const {
     stack<RBTNode<T> *> s;
     RBTNode<T> * root = tree;
     while (root||!s.empty()){
         while (root) {
             s.push(root);
             root = root->left;
         }
         if(!s.empty()){
             root = s.top();
             cout<<root->key<<" ";
             s.pop();
             root = root->right;
         }
     }
 }
 template <class T>
 void RBTree<T>::inOrder() {
     inOrder(mRoot);
 }
 /**
  * 后序遍历*
  * */
  template <class T>
  void RBTree<T>::postOrder(RBTNode<T> *tree) const {
//      stack<RBTNode<T> *> s;
//      RBTNode<T> *root = tree;
//      RBTNode<T> * temp = nullptr;
//      while (root){
//          s.push(root);
//          root = root->left;
//      }
//
//      while (!s.empty()){
//          //非空
//          //访问根节点
//          root = s.top();
//          if(root->right== nullptr || root->right==temp){
//              //访问他
//              cout<<root->key<<" ";
//              temp = root;
//              s.pop();
//          } else{
//              //访问右节点
//              root = root->right;
//              while (root){
//                  s.push(root);
//                  root = root->left;
//              }
//          }
//      }
    stack<RBTNode<T> *> s;
    //开辟两个新的常量
    RBTNode<T> *temp = nullptr;
    RBTNode<T> *root = tree;

    //压栈
    while (root)
    {
        s.push(root);
        root = root->left;
    }
    while (!s.empty()){
        root = s.top();
        //如果没有右子树或者右子树被访问过，就访问该节点
        if(root->right== nullptr || root->right==temp){
            cout<<root->key<<" ";
            s.pop();
            temp = root;//表明被访问过了
        } else{
            root = root->right;//
            while (root){
                s.push(root);
                root = root->left;
            }
        }
    }
  }
  template <class T>
  void RBTree<T>::postOrder() {
      postOrder(mRoot);
  }

  /**
   * 递归查找红黑树中键值为key的节点
   * */
  template <class T>
  RBTNode<T>* RBTree<T>::search(RBTNode<T> *x, T key) const {
      if(x == nullptr || x->key == key)
          return  x;
      if(key< x->key)
          return search(x->left,key);
      else
          return search(x->right,key);
  }
  template <class T>
  RBTNode<T>* RBTree<T>::search(T key) {
      search(mRoot,key);
  }
  /**
   * 非递归查找键值为为x的key的节点
   * */
   template <class T>
   RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T> *x, T key) const {
       while ((x!=nullptr) && (x->key!=key)){
           if(key<x->key)
               x = x->left;
           else
               x  = x->right;

       }
      return x;
   }
   template<class T>
   RBTNode<T>* RBTree<T>::iterativeSearch(T key) {
       iterativeSearch(mRoot,key);
   }
 /***
  * 查找最小节点,返回红黑树的最小节点
  * */
 template <class T>
 RBTNode<T>* RBTree<T>::minimum(RBTNode<T> *tree) {
     if(tree == nullptr)
         return tree;
     while (tree->left!=nullptr)
         tree = tree->left;
     return tree;
 }
 template <class T>
 T RBTree<T>::mininum() {

     RBTNode<T> *p = minimum(mRoot);
     if(p!= nullptr)
        return p->key;
     return long(nullptr);
 }
 /**
  * 查找最大节点
  * */
 template <class T>
 RBTNode<T>* RBTree<T>::maximum(RBTNode<T> *tree) {
     if(tree == nullptr)
         return tree;
     while (tree->right){
         tree = tree->right;
     }
     return tree;
 }
 template <class T>
 T RBTree<T>::maxinum()  {
     RBTNode<T>* p = maximum(mRoot);
     if(p!=nullptr)
         return p->key;
    bool is_type = std::is_same<int,T>::value;
    cout<<"is_type "<<is_type<<endl;


     return long(nullptr);
 }

 /**
  * 找节点(x)的后继节点,即查找"红黑树中数值大于该节点的最小节点"
  * ?
  */
  template <class T>
  RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x) {
      if(x->right!= nullptr)
          return mininum(x->right);

      RBTNode<T> *y = x->parent;
      while ((y!= nullptr) && (x==y->right)){
          x = y;
          y = y->parent;
      }
     return y;
  }
/**
 * 找节点x的前驱节点，即查找"红黑树中数值小于改节点的最大节点"
 * */
 template <class T>
 RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x) {
     if(x->left)
         return maximum(x->left);
     RBTNode<T> *y = x->parent;
     while ((y!= nullptr ) &&(x == y->left)){
         x = y;
         y = y->parent;
     }
    return y;
 }
/**
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 **/
template <class T>
void RBTree<T>::leftRotate(RBTNode<T> *&root, RBTNode<T> *x) {
    //设置右孩子为y
    RBTNode<T> *y = x->right;
    /**
     * 将y的左孩子设置为x的有孩子
     * 将如果y的左孩子非空,将其父亲节点设置为x**/
     x->right = y->left;
     if(y->left){
         y->left->parent = x;
     }
     y->parent = x->parent;
     if(x->parent== nullptr){
         root = y;
     } else{
         if(x->parent->left==x)
             x->parent->left = y;
         else
             x->parent->right = y;
     }
     //将"x"设置为y的左孩子
     y->left = x;
     //"x"的父节点设置为y
     x->parent = y;
}

/**
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 **/
 template <class T>
 void RBTree<T>::rightRotate(RBTNode<T> *&root, RBTNode<T> *y) {
     //设置左孩子
     RBTNode<T> *x = y->left;
     //"x"的右孩子变成y的左孩子
     y->left = x->right;
     if(x->right)
         x->right->parent = y;
     //将"y"的父亲设置为x的父亲
     x->parent = y->parent;
     if(y->parent== nullptr)
         root = x;
     else {
         if(y==y->parent->left){
             y->parent->right = x;//如果y是其父节点的右孩子，那么将x设置为其父节点的右孩子
         } else
             y->parent->left = x;//如果y是其父节点的左孩子,那么将x设置为其父节点的左孩子
     }
     x->right = y;
     y->parent = x;
 }

/**
* 将结点插入到红黑树中
*
* 参数说明：
*     root 红黑树的根结点
*     node 插入的结点        // 对应《算法导论》中的node
**/
template <class T>
void RBTree<T>::insert(RBTNode<T> *&root, RBTNode<T> *node) {
    RBTNode<T> *y = nullptr;
    RBTNode<T> *x = root;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x!= nullptr){
        y = x;
        if(node->key<x->key){
            x = x->left;
        } else
            x = x->right;
    }
    node->parent = y;
    if(y){
        if(node->key<y->key){
            y->left = node;
        } else
            y->right = node;
    } else
        root = node;
    //设置节点的颜色为红色
    node->color = RED;
    //将他重新修正为一颗二叉查找树
    insertFixUp(root,node);
}

/**
 * 将结点(key为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 插入结点的键值
 **/
 template <class T>
 void RBTree<T>::insert(T key) {
     RBTNode<T> *z = nullptr;
     if((z=new RBTNode<T>(key,BLACK, nullptr, nullptr, nullptr))== nullptr)
         return;

     insert(mRoot,z);
 }
/**
* 红黑树插入修正函数
*
* 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 插入的结点        // 对应《算法导论》中的z
**/
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T> *&root, RBTNode<T> *node) {
    RBTNode<T> *parent,*gparent;
    /**若父节点存在，且父节点的颜色是红色**/
    while ((parent==rb_parent(node))&&rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若父节点是祖父节点的左孩子
        if(parent==gparent->left) {
            //case1 :叔叔节点是红色
            RBTNode<T> *uncle = gparent->right;
            if (uncle && rb_is_red(uncle)) {
                rb_set_black(uncle);
                rb_set_black(parent);
                rb_is_red(gparent);
                node = gparent;
                continue;
            }

            //Case2 :叔叔是黑色且当前节点是右孩子
            if (parent->right == node) {
                RBTNode<T> *tmp;
                leftRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            //Case3:叔叔是黑色,且当前节点是左孩子
            rb_set_black(parent);
            rb_set_red(gparent);
            rightRotate(root, gparent);
        } else{
            //case1:叔叔节点是红色
            RBTNode<T> *uncle = gparent->left;
            if(uncle&&rb_is_red(uncle)){
                rb_set_black(uncle);
                rb_set_black(parent);
                rb_set_red(gparent);
                node = gparent;
                continue;
            }
            //case2：叔叔是黑色，且当前节点是左孩子
            if(parent->left ==node){
                RBTNode<T> *tmp;
                rightRotate(root,parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            //case3:叔叔是黑色，且当前节点是右孩子
            rb_set_black(parent);
            rb_set_red(gparent);
            leftRotate(root,gparent);
        }
    }
    rb_set_black(root);
}
/**
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
 **/
template <class T>
void RBTree<T>::remove(RBTNode<T> *&root, RBTNode<T> *node) {
    RBTNode<T> *child ,*parent;
    RBTColor  color;

    //被删除节点左右孩子都不为空
    if((node->left!= nullptr)&&(node->right!= nullptr)){
        //被删除节点的后继节点(称为取代节点)
        RBTNode<T> *replace = node;
        //获取后继节点
        replace = node->right;
        while (replace->left){
            replace = replace->left;
        }
        //node节点不是根节点的时候
        if(rb_parent(node)){
            if((rb_parent(node)->left==node))
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } else
            root = replace;
        //child是"取代节点"的右节点,也是需要"调整的节点"
        //"取代节点"肯定不存在左孩子,因为他是一个后继节点
        child = replace->right;
        parent = rb_parent(replace);
        color = rb_color(replace);
        //被"删除节点"是"他的后继节点的父节点"
        if(parent==node){
            parent = replace;
        } else{
            //child不为空
            if(child){
                rb_set_parent(child,parent);
            }
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right,replace);
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if(color==BLACK)
            removeFixUp(root,child,parent);
        delete node;
        return;
    }
    if(node->left)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;
    if(parent)//node不是根节点
        if(parent->left==node)
            parent->left = child;
        else
            parent->right = child;
    else
        root = child;//变成根节点

    if(color==BLACK)
        removeFixUp(root,child,parent);
    delete node;
}

/**
 * 删除红黑树中键值为key的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 **/
 template <class T>
 void RBTree<T>::remove(T key) {
     RBTNode<T> *node;
     if((node=search(mRoot,key))!= nullptr)
         remove(mRoot,node);
 }

/**
* 红黑树删除修正函数
*
* 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 待修正的节点
**/
template <class T>
void RBTree<T>::removeFixUp(RBTNode<T> *&root, RBTNode<T> *node, RBTNode<T> *parent) {
    RBTNode<T> *other;

    while ((!node||rb_is_black(node)) &&node!=root){
        if(parent->left==node){
            other= parent->right;
            if(rb_is_red(other)){
                //case1:x的兄弟w是红色
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root,parent);
                other = parent->right;
            }
            if((!other->left||rb_is_black(other->left))&&
              (!other->right||rb_is_black(other->right))){
                //case2:x的兄弟w是黑色，且w的两个孩子节点也是黑色
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if(!other->right||rb_is_black(other->right)){
                    //case3:x的兄弟w是黑色的，并且w的左孩子是红色的，右孩子是黑色的
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root,other);
                    other = parent->right;
                }
                //case4:x的兄弟w是黑色的，并且w的右还在是红色的，左孩子任意颜色
                rb_set_color(other,rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root,parent);
                node = root;
                break;
            }
        } else{
            other = parent->left;
            if(rb_is_red(other)){
                //case1://x的兄弟节点w是红色
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root,parent);
                other = parent->left;
            }
            if((!other->left||rb_is_black(other->left))&&
                (!other->right||rb_is_black(other->right))){
                //x的兄弟节点w是黑色,并且w的左右也是黑色
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if(!node->left||rb_is_black(node->left)){
                    //case3:x的兄弟节点w是黑色的，并且w的左孩子是红色，右孩子是黑色的
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root,other);
                    other = parent->left;
                }
                //case4:x的兄弟节点w是黑色的，并且w的右孩子是红色的，左孩子的任意颜色
                rb_set_color(other,rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root,parent);
                node = root;
                break;
            }
        }
    }
    if(node)
        rb_set_black(node);
}
/*销毁红黑树 **/
template <class T>
void RBTree<T>::destroy(RBTNode<T> *&tree) {
    if(tree== nullptr)
        return;
    if(tree->left)
        return destroy(tree->left);
    if(tree->right)
        return destroy(tree->right);
    delete tree;
    tree = nullptr;
}
template <class T>
void RBTree<T>::destroy() {
    destroy(mRoot);
}

/*打印二叉查找树
 * key   --节点的键值
 * direction --
 ***/
 template <class T>
 void RBTree<T>::print(RBTNode<T> *&tree, T key, int direction) {
    if(tree){
        if(direction==0){
            cout<<setw(2)<<tree->key<<"B is root\n";
        }
        else
            cout<<setw(2)<<tree->key<<(rb_is_red(tree)?"(R)":"B")<<" is"<<setw(2)<<key<<"'s"<<setw(12)<<(direction==1?"right child :":"left child")<<endl;
        print(tree->left,tree->key,-1);
        print(tree->right,tree->key,-1);
    }
 }
 template <class T>
 void RBTree<T>::print() {
     if(mRoot)
         print(mRoot,mRoot->key,0);
 }

#endif //RBTREE_RBTREE_H
