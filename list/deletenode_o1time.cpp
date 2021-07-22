/*
题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点
思路：要求在O(1)时间内删除结点，则可以这样考虑：将给定结点后继结点的值赋给给定结点，
然后删除给定结点的后继结点即可
上面的思路还有一个问题：如果删除的结点位于链表的尾部，没有下一个结点，怎么办？
我们仍然从链表的头结点开始，顺便遍历得到给定结点的前序结点，并完成删除操作。
这个时候时间复杂度是O(n)。那题目要求我们需要在O(1)时间完成删除操作，我们的算法
是不是不符合要求？实际上，假设链表总共有n个结点，我们的算法在n-1总情况下时间复杂度是O(1)，
只有当给定的结点处于链表末尾的时候，时间复杂度为O(n)。那么平均时间复杂度为
[(n-1)*O(1)+O(n)]/n，仍然为O(1)。
*/

#include <iostream>
using namespace std;

typedef struct LNode{
  int data;
  LNode *next;
}LNode, *List;

void InsertList(List &l, int data)//头插入节点
{
  List head;
  LNode *p=new LNode;
  p->data=data;
  if(NULL==l)
    p->next=NULL;
  else
    p->next=l;
  l=p;
}

void PrintList(List l)//打印链表
{
  LNode *p=l;
  while(p)
  {
    cout<<p->data<<" ";
    p=p->next;
  }
  cout<<endl;
}

void DeleteNode(List &l, LNode *toBeDeleted)//删除链表l中的toBeDeleted节点
{
  LNode *p;
  if(!l || !toBeDeleted)
    return;

  if(l==toBeDeleted)//若删除的节点时表头
  {
    p=l->next;
    delete toBeDeleted ;
    l=p;
  }
  else
  {
    if(toBeDeleted->next==NULL)//若删除的节点时最后一个节点
    {
      p=l;
      while(p->next!=toBeDeleted)
        p=p->next;
      p->next=NULL;
      delete toBeDeleted;
    }
    else//删除节点时中间节点
    {
      p=toBeDeleted->next;
      toBeDeleted->data=p->data;
      toBeDeleted->next=p->next;
      delete p;

    }

  }

}

int main()
{
  List l=NULL;
  LNode *p;
  int n;
  InsertList(l, 3);
  InsertList(l, 7);
  InsertList(l, 12);
  InsertList(l, 56);
  InsertList(l, 33);
  InsertList(l, 78);
  InsertList(l, 20);
  InsertList(l, 89);

  PrintList(l);
  cout<<"请输入要删除的节点：";
  cin>>n;

  p=l;
  while(p && p->data != n)
    p=p->next;

  if(!p)
  {
    cout << "不存在这样的节点！" << endl;
    return 0;
  }
  else
    DeleteNode(l, p);

  cout<<"删除后的链表：";
  PrintList(l);
}

