/*___________DETAILS___________*/
/* NAME: NANDANA ANAND         */
/* ROLL: B220424CS             */
/*Create tree from paranthesis and check if RED BLACK TREE*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct tree_elem{
    int val;
    struct tree_elem* left;
    struct tree_elem* right;
    struct tree_elem* parent;
    char colour;    
};

typedef struct tree_elem * treenode;

struct R_B_TREE{
    treenode root;
};

treenode CREATE_NODE(int val,treenode left,treenode right,treenode parent,char colour)
{
    treenode req=(treenode)malloc(sizeof(struct tree_elem));
    req->val=val;
    req->colour=colour;
    req->left=left;
    req->right=right;
    req->parent=parent;
    return req;
}

/*______________________________________________CREATE TREE__________________________________*/
treenode create_tree(char* str,int *i)
{
    (*i)++; //str[i] Should ideally be '('
    int val=0;
    char colour;
    while(str[(*i)]==' ' || str[*i]=='(')
    {
        (*i)++;
    }
    if(str[*i]==')' || str[*i]=='\n')
        return NULL;
    while(str[*i]!=' ' && str[*i]>='0' && str[*i]<='9')    //integer
    {
        val=val*10+str[(*i)++]-'0';
    }
    while(str[*i]==' ')
        (*i)++;
    colour=str[(*i)++];
    while(str[*i]==' ')
        (*i)++;
    treenode l=create_tree(str,i);
    (*i)++;
    treenode r=create_tree(str,i);
    (*i)++;
    while(str[*i]!=')' && str[*i]!='\n')
        (*i)++;
    treenode curr= CREATE_NODE(val,l,r,NULL,colour);
    if(l)
        l->parent=curr;
    if(r)
        r->parent=curr;
    return curr;
}
/*_________________________________CHECK_____________________________________*/
/*Properties:
1. Root is black
2. All nodes are either R or B
3. It is a BST
4. Red has only black children
4. Black height of all nodes in any path is same*/
char colour(treenode p)
{
    if(p==NULL)
        return 'B';
    return p->colour;
}
int bh(treenode curr)
{
    if(curr==NULL)
        return 1;
    if(curr->colour=='B')
        return 1+bh(curr->left);    //should be ideally same as left and right
    return bh(curr->left);
}
int checkRedBlackTreenode(treenode curr)
{
    if(curr==NULL)
        return 1;
    //Check prop 2: All nodes are either red or black
    if(curr->colour!='R' && curr->colour!='B')
        return 0;
    treenode left=curr->left;
    treenode right=curr->right;
    int ans=1;
    //Check prop 3: if not BST
    if(left)
    {
        if(curr->val < left->val)
            return 0;
        ans=ans * checkRedBlackTreenode(left);
    }
    if(right)
    {
        if(curr->val > right->val)
            return 0;
        ans=ans * checkRedBlackTreenode(right);
    }
    //Check for left and right
    if(ans==0)
        return 0;
    //Check Prop 4: Check if red has red child
    if(colour(curr)=='R')
    {    
        if(colour(curr->parent)=='R')
            return 0;
    }
    //Check prop 5: Check black height
    return bh(curr->left)==bh(curr->right); 
}
int checkRedBlackTree(struct R_B_TREE T)
{
    //Check prop1: Root is black
    if(T.root==NULL)
        return 1;
    else if(colour(T.root)=='R')
        return 0;
    return checkRedBlackTreenode(T.root);    
}

int main()
{
    char str[MAX];
    fgets(str,MAX,stdin);
    struct R_B_TREE T;
    T.root=NULL;
    int i=0;
    T.root=create_tree(str,&i);
    printf("%d",checkRedBlackTree(T));
    return 0;
}
