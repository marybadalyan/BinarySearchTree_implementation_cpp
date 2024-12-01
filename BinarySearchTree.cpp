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
            else break;  // Don't allow duplicates. Break in case there is more to be executed.
        }
    }
    void insertRecursive(const T& value){
        tree_root = insertRecursiveHelper(tree_root, value);
    }
    
    void eraseRecursive(const T& val){
        tree_root = eraseRecursiveHelper(val, tree_root);
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

            TreeNode<T>* min = findMinNode(root->right);
            root->value = min->value;
            root->right = eraseRecursiveHelper(root->value, root->right);
        }
        
        return root;
    }
    void eraseIterative(const T& val){
        if (isEmpty()) {
            throw std::underflow_error("Cannot erase from an empty tree.");
            return;
        }
        // The easiest case is deleting a leaf node.
        TreeNode<T>* prev = nullptr;
        TreeNode<T>* curr = tree_root;
        T value = val; // This might change.

        while(curr != nullptr){

            if(value < curr->value){
                prev = curr;
                curr = curr->left;
            }
            else if(value > curr->value){
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
                    if(prev == nullptr){ // We need to delete the root.
                        tree_root = nullptr;
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
                    if(prev == nullptr){ // We need to delete the root.
                        tree_root = nullptr;
                    }
                    else if(curr->value > prev->value){
                        prev->right = curr->right;
                    }
                    else{
                        prev->left = curr->right;
                    }
                }
                // Root is handled here. It'll just get replaced as in case of both, so no other checks need to be made.
                TreeNode<T>* min = findMinNode(curr->right);
                curr->value = min->value;
                value = min->value;
                prev = curr;
                curr = curr->right;  // Let's find the minimum node and delete it.   
            }
        }
    }

private:
    TreeNode<T>* insertRecursiveHelper(TreeNode<T>* root, const T& value){ 
        // Or you can pass a pointer by reference without returning the root each time.
        if(root == nullptr){
           return new TreeNode<T>(value);
        }
        if(value < root->value){
            root->left = insertRecursiveHelper(root->left, value);
        }
        else if(value > root->value){
            root->right = insertRecursiveHelper(root->right, value);
        }

        return root;
    }

private:
    TreeNode<T>* tree_root;
};
