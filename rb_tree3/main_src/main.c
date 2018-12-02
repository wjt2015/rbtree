/*
main.c
*/
#include"rb_tree.h"

int main(){
  char filename[] = "../data/rbtree.txt";
  FILE* fp = fopen(filename,"r");
  RBTree* tree = rb_build(fp);
  fclose(fp);
  fp = fopen("../data/rb_tree_out.txt","w");
  rb_print(tree,fp);
  int height = rb_height(tree);
  int n = printf("height=%d\n",height);
  rb_free(tree);

  fclose(fp);
  n =printf("\nint main() finish!\n");

}
