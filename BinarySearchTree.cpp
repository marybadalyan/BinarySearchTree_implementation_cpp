#pragma once

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
    void insertIterative(const T& val){
        if (tree_root == nullptr){
            tree_root = new TreeNode<T>(val);
            return;
        }

        TreeNode<T>* tmp = tree_root;
        while(tmp != nullptr)
        {
            if(val > tmp->value){
                if(tmp->right == nullptr)
                {
                    tmp->right = new TreeNode<T>(val);
                    return;
                }
                else tmp = tmp->right;
            }
            else if(val < tmp->value){
                if(tmp->left == nullptr)
                {
                    tmp->left = new TreeNode<T>(val);
                    return;
                }
                else tmp = tmp->left;
            }
            else {
                throw std::underflow_error("Duplicates aren't allowed.");
                return;
            }  // Don't allow duplicates. Break in case there is more to be executed.
        }
    }
    void insertRecursive(const T& val){
        tree_root = insertRecursiveHelper(val,tree_root);
    }
    
    void eraseRecursive(const T& val){
        tree_root = eraseRecursiveHelper(val, tree_root);
    }
   
    void eraseIterative(const T& val){
        if (isEmpty()) {
            throw std::underflow_error("Cannot erase from an empty tree.");
            return;
        }
        // The easiest case is deleting a leaf node.
        TreeNode<T>* prev = nullptr;
        TreeNode<T>* curr = tree_root;

        while(curr != nullptr){

            if(val < curr->value){
                prev = curr;
                curr = curr->left;
            }
            else if(val > curr->value){
                prev = curr;
                curr = curr->right;
            }
            else{ // Found the node.
                if(curr->left == nullptr && curr->right == nullptr){
                    if(prev == nullptr){ // We need to delete the root.
                        tree_root = nullptr;
                    }
                    else if(curr->value > prev->value){
                        prev->right = nullptr;
                    }
                    else{
                        prev->left = nullptr;
                    }
                    delete curr;
                    curr = nullptr;
                    return;
                }
                if(curr->right == nullptr){ // Means curr->left isn't null because the previous condition would have been true.
                    if(prev == nullptr){
                        tree_root = curr->left; //if we need to delete the root that happens to have a left child
                    }
                    else if(curr->value < prev->value){
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
                    if(prev == nullptr){
                        tree_root = curr->right;
                    }
                    else if(curr->value > prev->value){
                        prev->right = curr->right;
                    }
                    else{
                        prev->left = curr->right;
                    }
                }
                // Root is handled here. It'll just get replaced as in case of both, so no other checks need to be made.
                TreeNode<T>* min = findMinNodeIterative(curr->right);
                curr->value = min->value;
                val = min->value;
                prev = curr;
                curr = curr->right;  // Let's find the minimum node and delete it.   
            }
        }
    }
    
    TreeNode<T>* findMinNodeIterative(){
        TreeNode<T>* tmp = tree_root;
        while(tmp != nullptr && tmp->left != nullptr){
            tmp = tmp->left;
        }
        return tmp;
    }
    TreeNode<T>* findMinNodeRecursive(){
        findMinNodeRecursiveHelper(tree_root);
    }
    TreeNode<T>* findMinNodeRecursiveHelper(TreeNode<T>* root){
        if(root == nullptr)
            return nullptr;
        if(root->left == nullptr){
            return root;
        }
        
        return findMinNodeRecursiveHelper(root->left);
    }
private:
    TreeNode<T>* insertRecursiveHelper(const T& val,TreeNode<T>* root){ 
        // Or you can pass a pointer by reference without returning the root each time.
        if(root == nullptr){
           return new TreeNode<T>(val);
        }
        if(val < root->value){
            root->left = insertRecursiveHelper(val,root->left);
        }
        else if(val > root->value){
            root->right = insertRecursiveHelper(val,root->right);
        }

        return root;
    }
    
    TreeNode<T>* eraseRecursiveHelper(const T& val, TreeNode<T>* root){
        if(root == nullptr) return nullptr;

        if(val > root->value){
            root->right = eraseRecursiveHelper(val, root->right);
        }
        else if(val < root->value){
            root->left = eraseRecursiveHelper(val, root->left);
        }
        else{
            if(root->left == nullptr && root->right == nullptr){
                delete root;
                return nullptr;
            }
            if(root->right == nullptr){
                TreeNode<T>* tmp = root->left;
                delete root;
                return tmp;
            }
            if(root->left == nullptr){
                TreeNode<T>* tmp = root->right;
                delete root;
                return tmp;
            }

            TreeNode<T>* min = findMinNodeRecursive(root->right);
            root->value = min->value;
            root->right = eraseRecursiveHelper(min->val, root->right);
        }
        
        return root;
    }

private:
    TreeNode<T>* tree_root;
};
