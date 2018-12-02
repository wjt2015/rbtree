/*
rb_tree.h
*/
#ifndef _RB_TREE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//-------
#define _RED_ 0
#define _BLACK_ 1
//---
#define _BUFSIZE_ 1024
//---
#define _RBNODE_SIZE_ sizeof(RBNode)
//-------
typedef struct xRBNode{
  int color;
  struct xRBNode* lchild;
  struct xRBNode* rchild;
  struct xRBNode* parent;
  char buf[_BUFSIZE_];
}RBNode;
//---
typedef struct xRBTree{
  RBNode nil;
  RBNode* root;
}RBTree;
//-------

void rb_insert(RBTree* rbTree,RBNode* z);
void rb_print(RBTree* rbTree,FILE* fp);
void rb_free(RBTree* rbTree);
RBTree* rb_build(FILE* fp);
int rb_height(RBTree* tree);
//-------
#endif
//-------
