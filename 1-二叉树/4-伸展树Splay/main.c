//
//  main.c
//  SplayTree
//
//  Created by Matthew Lu on 14/03/2014.
//  Copyright (c) 2014 Matthew Lu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node Tree;
typedef int KEY_TYPE;
int size;  // size is not a must, just use to recode the height of the tree

struct tree_node
{
    Tree *left, *right;
    KEY_TYPE item;
};


// search the tree and rotate the tree to put i to the root
Tree * splay(KEY_TYPE i,Tree *t)
{
    Tree N,*l,*r,*y;
    if (t == NULL) {
        return t;
    }
    N.left = N.right = NULL;
    l= r= &N;
    
    for (; ; ) {
        if (i < t->item) {
            
            if (t->left == NULL) {
                break;
            }
            
            if (i < t->left ->item) {
                // rotate right
                y = t->left;
                t->left = y->right;
                y->right = t;
                t= y;
                
                if (t->left == NULL) {
                    break;
                }
                
            }
            
            r->left = t;  // link right
            r=t;
            t=t->left;
            
        }
        else if (i > t->item)
        {
            if (t->right == NULL) {
                break;
            }
            
            if (i>t->right->item) {
                y = t->right;    //rotate left
                t->right = y->left;
                y->left = t;
                t=y;
                
                if (t->right == NULL) {
                    break;
                }
            }
            
            l->right =t;  // link left
            l=t;
            t=t->right;
        }
        else
        {
            break;
        }
    }
    
    l->right = t->left;  // assemble
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
}


Tree * insert(KEY_TYPE i, Tree *t)
{
    //insert i into the tree t, unless it's already there
    //Return a pointer to the resulting tree
    
    Tree *new = (Tree*)malloc(sizeof(Tree));
    
    if (new == NULL) {
        printf("Ran out of space\n");
        exit(1);
    }
    
    new->item = i;
    
    if (t==NULL) {
        new->left = new ->right = NULL;
        size = 1;
        return new;
    }
    
    t = splay(i, t);
    
    if (i<t->item) {
        new ->left = t->left;
        new->right = t;
        t->left = NULL;
        size++;
        return new;
    }
    else if (i > t->item)
    {
        new->right = t->right;
        new->left = t;
        t->right = NULL;
        size++;
        return new;
    }
    else
    {
        //we get here if it's already in the tree
        // dont add it again
        free(new);
        return t;
    }
    
}


Tree *delete(KEY_TYPE i,Tree *t)
{
    //Deletes i from the tree if it's there
    // Return a pointer to the resulting tree
    
    Tree *x;
    if (t==NULL) {
        return NULL;
    }
    
    t=splay(i, t);
    
    if (i == t->item) {
        //found it
        if (t->left == NULL) {
            x = t->right;
        }
        else
        {
            x = splay(i, t->left);
            x->right = t->right;
        }
        size--;
        free(t);
        return x;
    }
    return  t; // it was not here
}



int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Hello, World!\n");
    
    Tree *root;
 
    root  = NULL;
    size = 0;
    

    root = insert(1, root);
    root = insert(2, root);
    root = insert(3, root);
    root = insert(4, root);
    root = insert(5, root);
    root = insert(6, root);
    
    printf("size = %d\n",size);
    
    root = delete(3, root);

    
    printf("size = %d\n",size);
    
    Tree *find = splay(4, root);
    
    printf("find item = %d\n",find->item);
    
    return 0;
}

