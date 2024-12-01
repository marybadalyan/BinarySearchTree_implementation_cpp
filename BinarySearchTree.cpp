#include "TreeNode.h"

template <typename T>
class BinarySearchTree{

public:
    BinarySearchTree(TreeNode<T>* r = nullptr): tree_root(r){}

    ~BinarySearchTree(){
        clear();
    }

    bool isEmpty(){
        return tree_root == nullptr;
    }
    void insertIterative(const T& value){
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
    void insertRecursive(const T& value){
        tree_root = insertRecursive(tree_root,value);
    }
    
    void eraseIterative(const T& v){
        if (isEmpty()) {
            throw std::underflow_error("Cannot erase from an empty tree.");
            return;
        }
        //the easierst is deleteing a leaf 
        TreeNode<T>* prev = nullptr;
        TreeNode<T>* curr = tree_root;
        T value = v; //this might change

        while(curr != nullptr){

            if(value < curr->value){
                prev = curr;
                curr = curr->left;
            }
            else if(value > curr->value){
                prev = curr;
                curr = curr->right;
            }
            else{
                if(curr->left == nullptr && curr->right == nullptr){
                    if(curr->value > prev->value){
                        prev->right = nullptr;
                    }
                    else{
                        prev->left = nullptr
                    }
                    delete curr;
                    curr = nullptr;
                    return;
                }
                if(curr->right == nullptr){ // means curr->left isnt null cus the previous condition would have been right
                    if(curr->value < prev->value){
                        prev->left = curr->left;
                    }
                    else{
                        prev->right = curr->left;
                    }

                    delete curr;
                    curr = nullptr;
                    return;
                } 
                if(curr->left == nullptr){
                    if(curr->value > prev->value){
                        prev->right = curr->right;
                    }
                    else{
                        prev->left = curr->right;
                    }
                }

                TreeNode<T>* min = FindMinNode(curr->right);
                curr->value = min->value;
                value = min->value;
                prev = curr;
                curr = curr->right;  //lets find the minimum node and delete it   
            }
        }
    }


private:
    TreeNode<T>* insertRecursiveHelper(TreeNode<T>*root, constr T& value){ // or you can pass a poiner by reference  without returning every root 
        if(root == nullptr){
           return new TreeNode<T>(value);
        }
        if(value < root->value){
            root->left= insertRecursiveHelper(root->left,value);
        }
        else if(value > root->value){
            root->right = insertRecursiveHelper(root->right,value);
        }

        return root;
    }
  
private:
    TreeNode<T>* tree_root;
};