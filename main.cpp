#include <iostream>
#include "RBTree.h"
using namespace std;
int main() {
    int a[] = {10,40,30,60,90,70,20,50 ,80};
    
    int check_insert = 0;   //插入动作开关(0:关闭，1打开)
    int check_remove = 0;   //删除动作开关(0:关闭，1打开)
    int i;
    int ilen = sizeof(a)/(sizeof(int));
    cout<<ilen<<endl;
    RBTree<int> * tree = new RBTree<int>();
    
//    cout<<"==原始数据: ";
    for (int j = 0; j <ilen ; ++j) {
        cout<<a[j]<<" ";
    }
    cout<<endl;

    for (int k = 0; k <ilen ; ++k) {
       tree->insert(a[k]);

       if(check_insert=1){
           cout<<"==添加节点: "<<a[k]<<endl;
           cout<<"==树的详细信息: "<<endl;
           tree->print();
           cout<<endl;
       }
    }
    cout<<"==前序遍历";
    tree->preOrder();

    cout<<"\n==中序遍历";
    tree->inOrder();

    cout<<"\n后序遍历";
    tree->postOrder();
    cout<<endl;

    cout<<"==最小值: "<<tree->mininum()<<endl;
    cout<<"==最大值: "<<tree->maxinum()<<endl;
    cout<<"==树的详细信息: "<<endl;

    if(check_remove=1){
        for (int j = 0; j < ilen; ++j) {
            tree->remove(a[j]);
            cout<<"==删除节点: "<<a[j]<<endl;
            cout<<"==树的详细信息: "<<endl;
            tree->print();
            cout<<endl;
        }
    }
    tree->destroy();

    return 0;


}