#include "TreeNode.h"

template <typename T>
class BinarySearchTree{
public:
    BinarySearchTree(TreeNode<T>* r = nullptr): tree_root(r){};
    ~BinarySearchTree(){
        clear();
    }
    void insertIterative(T value){
        if (tree_root == nullptr){
            tree_root = new TreeNode<T>(value);
            return;
        }

        TreeNode<T>* tmp = tree_root;
        while(tmp != nullptr)
        {
            if(value > tmp->value){
                if(tmp->right == nullptr)
                {
                    tmp->right = new TreeNode<T>(value);
                    return;
                }
                else tmp = tmp->right;
            }
            else if(value < tmp->value){
                if(tmp->left == nullptr)
                {
                    tmp->left = new TreeNode<T>(value);
                    return;
                }
                else tmp = tmp->left;
            }
            else break;  //don't allow duplicates break in case there is more to be executed 
        }
    }
    void insertRHelper(){
        insertRecursive(tree_root);
    }
    TreeNode<T>* insertRecursive(TreeNode<T>*root,T value){
        if(root == nullptr){
           return new TreeNode<T>(value);
        }
        if(value < root->value){
            root->left= insertRecursive(root->left,value);
        }
        else if(value > root->value){
            root->right = insertRecursive(root->right,value)
        }
        else return;
        return root;
    }
private:
    TreeNode<T>* tree_root;
};