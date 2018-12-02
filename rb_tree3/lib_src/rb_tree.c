/*
rb_tree.c
*/
#include"rb_tree.h"
/*
关键字对比;
*/
int compare(char bufA[],char bufB[]){
  int iret = strcmp(bufA,bufB);
  return iret;
}

/*
左旋,x必须有右子;
*/
void leftRotate(RBTree* tree,RBNode* x){
  RBNode* y = x->rchild;
  if(x == tree->root){
    tree->root = y;
  }else if(x == x->parent->lchild){
    x->parent->lchild = y;
  }else{
    x->parent->rchild = y;
  }
  y->parent = x->parent;

  y->lchild->parent = x;
  x->rchild = y->lchild;
  y->lchild = x;
  x->parent = y;
}
/*
右旋,y必须有左子;
*/
void rightRotate(RBTree* tree,RBNode* y){
  RBNode* x = y->lchild;
  if(y == tree->root){
    tree->root = x;
  }else if(y == y->parent->lchild){
    y->parent->lchild = x;
  }else{
    y->parent->rchild = x;
  }
  x->parent = y->parent;

  x->rchild->parent = y;
  y->lchild = x->rchild;
  y->parent = x;
  x->rchild = y;
}
/*
插入节点后修正红黑树;
*/
void rb_insert_fixup(RBTree* rbTree,RBNode* z){
  RBNode* y = NULL;
  while(z->parent->color == _RED_){
    if(z->parent == z->parent->lchild){
      y = z->parent->parent->rchild;
      if(y->color==_RED_){
        y->color = z->parent->color = _BLACK_;
        y->parent->color = _RED_;
        z = y->parent;
      }else{
        if(z == z->parent->lchild){
          z=z->parent;
          leftRotate(rbTree,z);
        }
        z->parent->color = _BLACK_;
        y->parent->color = _RED_;
        rightRotate(rbTree,y->parent);
        z = rbTree->root;
      }
    }else{
      y = z->parent->parent->lchild;
      if(y->color == _RED_){
        y->color = z->parent->color = _BLACK_;
        y->parent->color = _RED_;
        z = y->parent;
      }else{
        if(z == z->parent->lchild){
          z = z->parent;
          rightRotate(rbTree,z);
        }
        y->parent->color = _RED_;
        z->parent->color = _BLACK_;
        leftRotate(rbTree,y->parent);
        z = rbTree->root;
      }
    }
  }
  rbTree->root->color = _BLACK_;
}

void transplant(RBTree* tree,RBNode* y,RBNode* x){
    if(y == tree->root){
        tree->root = x;
    }else if(y == y->parent->lchild){
        y->parent->lchild = x;
    }else{
        y->parent->rchild = x;
    }
    x->parent = y->parent;
}
/*
插入新节点;
*/
void rb_insert(RBTree* rbTree,RBNode* z){
  RBNode* y = &(rbTree->nil);
  RBNode* x = rbTree->root;
  int iret = 0;
  while(x != &(rbTree->nil)){
    y = x;
    iret = compare(z->buf,x->buf);
    if(iret <= 0){
      x = x->lchild;
    }else{
      x = x->rchild;
    }
  }
  iret = compare(z->buf,y->buf);
  if(y == &(rbTree->nil)){
    rbTree->root = z;
  }else if(iret < 0){
    y->lchild = z;
  }else{
    y->rchild = z;
  }
  z->parent = y;
  z->lchild = z->rchild = &(rbTree->nil);
  z->color = _RED_;
  rb_insert_fixup(rbTree,z);
}

/*
删除红黑树的一个节点;
*/
void rb_delete_fixup(RBTree* tree,RBNode* x){
    while(x != tree->root && (x->color == _BLACK_)){
        RBNode* w;
        RBNode* y;
        if(x == x->lchild){
            w = x->parent->rchild;
            if(w->color == _RED_){
                w->color = _BLACK_;
                x->color = _RED_;
                leftRotate(tree,x->parent);
                w = x->parent->rchild;
            }
            if(w->lchild->color == _BLACK_ && w->rchild->color == _BLACK_){
                w->color = _RED_;
                x = x->parent;
            }else{
                if(w->rchild->color == _BLACK_){
                    w->color = _RED_;
                    w->lchild->color = _BLACK_;
                    rightRotate(tree,w);
                    w = x->parent->rchild;
                }
                w->color = w->parent->color;
                w->parent->color = w->rchild->color = _BLACK_;
                leftRotate(tree,x->parent);
                x = tree->root;
            }
        }else{
            w = x->parent->lchild;
            if(w->color == _RED_){
                x->parent->color = _RED_;
                w->color = _BLACK_;
                rightRotate(tree,x->parent);
                w = x->parent->lchild;
            }
            if(x->lchild->color == _BLACK_ && x->rchild->color == _BLACK_){
                x->parent->color = _RED_;
                x = x->parent;
            }else{
                if(w->lchild->color == _BLACK_){
                    w->color = _RED_;
                    w->rchild->color = _BLACK_;
                    leftRotate(tree,w);
                    w = x->parent->lchild;
                }
                w->color = w->parent->color;
                w->lchild->color = w->parent->color = _BLACK_;
                rightRotate(tree,w->parent);
                x = tree->root;
            }
        }
    }
    x->color = _BLACK_;
}
/*
最小子节点;
root必须是有效节点;
*/
RBNode* rb_minimum(RBTree* tree,RBNode* root){
    RBNode* minNode;
    for(minNode = root;minNode->lchild != &(tree->nil);minNode = minNode->lchild){
        ;
    }
    return minNode;
}
/*删除*/
void rb_delete(RBTree* tree,RBNode* z){
    RBNode* y = z;
    RBNode* x;
    int y_original_color = y->color;
    if(z->lchild == &(tree->nil)){
        x = y->rchild;
        transplant(tree,z,z->rchild);
    }else if(z->rchild == &(tree->nil)){
        x = y->lchild;
        transplant(tree,z,z->lchild);
    }else{
        y = rb_minimum(tree,z->rchild);
        x = y->rchild;
        y_original_color = y->color;
        x = y->rchild;
        if(y->parent != z){
            transplant(tree,y,x);
            y->rchild = z->rchild;
            z->rchild->parent = y;
        }
        transplant(tree,z,y);
        y->lchild = z->lchild;
        z->lchild->parent = y;
        y->color = z->color;
    }
    if(y_original_color == _BLACK_){
        rb_insert_fixup(tree,x);
    }
}
/*
遍历红黑树;
*/
void rbnode_print_internal(RBTree* rbTree,RBNode* r,FILE* fp){
  if(r != &(rbTree->nil)){
    int n = fprintf(fp,"\t(%s;%s)\n\n",r->buf,(r->color == _RED_?"red":"black"));
    rbnode_print_internal(rbTree,r->lchild,fp);
    rbnode_print_internal(rbTree,r->rchild,fp);
  }
}
void rb_print(RBTree* rbTree,FILE* fp){
  int n = fprintf(fp,"\t(key,color):\n\n");
  rbnode_print_internal(rbTree,rbTree->root,fp);
}
/*
销毁红黑树
*/
void rbnode_free_internal(RBTree* rbTree,RBNode* rbNode){
  if(rbNode != &(rbTree->nil)){
    RBNode* lchild = rbNode->lchild;
    RBNode* rchild = rbNode->rchild;
    free(rbNode);
    rbnode_free_internal(rbTree,lchild);
    rbnode_free_internal(rbTree,rchild);
  }
}
void rb_free(RBTree* rbTree){
  rbnode_free_internal(rbTree,rbTree->root);
  free(rbTree);
}
/*
构造红黑树;
*/
RBTree* rb_build(FILE* fp){
  RBTree* rbTree = (RBTree*)malloc(sizeof(RBTree));
  rbTree->root = &(rbTree->nil);
  rbTree->nil.color = _BLACK_;
  rbTree->nil.parent = rbTree->nil.lchild = rbTree->nil.rchild = &(rbTree->nil);
  memset(rbTree->nil.buf,0,_BUFSIZE_);

  char buf[_BUFSIZE_];
  int n = 0;
  while((n = fscanf(fp,"%s",buf)) >= 1){
    RBNode* z = (RBNode*)malloc(_RBNODE_SIZE_);
    memset(z->buf,0,_BUFSIZE_);
    memcpy(z->buf,buf,strlen(buf));
    rb_insert(rbTree,z);
  }
  return rbTree;
}
/*计算红黑树的高度*/
int rb_height_internal(RBTree* tree,RBNode* root){
    int n = 0;
    if(root != &(tree->nil)){
        int lheight = rb_height_internal(tree,root->lchild);
        int rheight = rb_height_internal(tree,root->rchild);
        n += (lheight < rheight?rheight:lheight) + 1;
    }
    return n;
}
int rb_height(RBTree* tree){
    int height = rb_height_internal(tree,tree->root);
    return height;
}
//----
