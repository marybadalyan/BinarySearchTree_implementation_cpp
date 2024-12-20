
#include <iostream>
#include "TreeNode.h"

#include "stack"
#include "queue"
template <typename T>
class BinarySearchTree{

public:
    BinarySearchTree(TreeNode<T>* r = nullptr): tree_root(r){}

    ~BinarySearchTree(){
        clearRecursive();
    }

    bool isEmpty() const{
        return tree_root == nullptr;
    }
    void insertIterative(const T& val){
        if (!tree_root){
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
   
    int findMax(){
        return findMaxNodeIterative()->value;
    }
    int findMin(){
        return findMinNodeIterative()->value;
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
                TreeNode<T>* min = findMinNodeRecursiveHelper(curr->right);
                curr->value = min->value;
                prev = curr;
                curr = curr->right;  // Let's find the minimum node and delete it.   
            }
        }
    }

    void clearIterative(){
        if(isEmpty()) return;

        std::queue<TreeNode<T>*> q;
        q.push(tree_root);

        while(!q.empty()){
            TreeNode<T>* tmp = q.front();
            q.pop();
            if(tmp->left)
                q.push(tmp->left);
            if(tmp->right)
                q.push(tmp->left);

            delete tmp;
            tmp = nullptr;
        }
        tree_root = nullptr;
    }
    
    TreeNode<T>* findMaxRecursive() const{
        return findMaxNodeRecursiveHelper(tree_root);
    }
    void preorederIterative() const{
        if(isEmpty()) return;
        std::stack<TreeNode<T>*> s;
        TreeNode<T>* tmp = tree_root;
        while(true){
            while(tmp){
                std::cout << tmp->val << " ";
                if(tmp->right){
                    s.push(tmp->right);
                }
                tmp = tmp->left;
            }
            if(s.empty()){
                break;
            }

            tmp = s.top();
            s.pop();
        }
    }
    void inorderIterative() const{
        if(isEmpty()) return;

        std::stack<TreeNode<T>*> s;
        TreeNode<T>* tmp = tree_root;
        while(true){
            while(tmp){
                s.push(tmp);
                tmp = tmp->left;
            }

            if(s.empty()) return;

            tmp = s.top();
            s.pop();
            std::cout << tmp->value << " ";
            tmp = tmp->right;  //line 156 will be  pushing it to the stack  
        }
    }
    void postorderIterative() const{
        if(isEmpty()) return;

        std::stack<TreeNode<T>*> s;
        TreeNode<T>* tmp = tree_root;
        while(true){

            while(tmp){

                if(tmp->right){
                    s.push(tmp->right);
                }
                s.push(tmp);
                tmp = tmp->left;

            }

            if(s.empty()) return;

            tmp = s.top();
            s.pop();

            if(tmp->right && !s.empty() && s.top() == tmp->right){
                s.pop();
                s.push(tmp);
                tmp = tmp->right;
            }
            else{
                std::cout << tmp->value << " ";
                tmp = nullptr;
            }
        }
    }
   
    int heightRecursive(){
        return heightRecursiveHelper(tree_root);
    }
    int heightIterative(){
        std::queue<TreeNode<T>*> q;
        int height = 0;
        q.push(tree_root);

        int levelSize = q.size();

        while(!q.empty()){

            for(int i = 0; i < levelSize;++i){
                TreeNode<T>* tmp = q.front();
                q.pop();

                if(tmp->left){
                    q.push(tmp->left);
                }
                if(tmp->right){
                    q.push(tmp->right);
                }
            }
            ++height; 
        }
        return height;
    }
    void clearRecursive(){
        clearRecursiveHelper(tree_root);
        tree_root = nullptr;
    }
    void clearRecursiveHelper(TreeNode<T>* root){
        if(!root) return;

        clearRecursiveHelper(root->left);
        clearRecursiveHelper(root->right);

        delete root;
        root = nullptr;
    }
    void preorderRecursive() const{
        preorderRecursive(tree_root);
    }
    void postorederRecursive() const{
        postorederRecursiveHelper(tree_root);
    }
    
    void inorderRecursive() const{
        inorderRecursiveHelper(tree_root);
    }

    void levelorderIterative() const{
        std::queue<TreeNode<T>*> q;

        q.push(tree_root);
        while(!q.empty()){
            TreeNode<T>* tmp = q.front();
            q.pop();
            std::cout << tmp->value << " ";

            if(tmp->left){
                q.push(tmp->left);
            }
            if(tmp->right){
                q.push(tmp->right);
            }
        }
    }
    int countOfLeavesRecursive() const{
        return countOfLeavesRecursiveHelper(tree_root);
    }
    int countOfNodesRecursive() const{
        return countOfNodesRecursiveHelper(tree_root);
    }
    int countOfNodesIterative(){
        if(isEmpty()) return 0;

        int count = 0;
        std::queue<TreeNode<T>*> q;
        q.push(tree_root);
        while(!q.empty()){
            TreeNode<T>* tmp =  q.front();
            q.pop();
            ++count; //we cannot increment using the level count of nodes cuz the q has  nodes form multiple levels

            if(tmp->left){
                q.push(tmp->left);
            }
            if(tmp->right){
                q.push(tmp->right);
            }
        }
        return count;
    }
    int countOfLeavesIterative(){
        if(isEmpty()) return 0;
        std::stack<TreeNode<T>*> s;
        int count = 0;

        s.push(tree_root);

        while(!s.empty()){
            TreeNode<T>* tmp = s.top();
            s.pop();


            if(!tmp->left && !tmp->right){
                ++count;
            }

            if(tmp->left){
                s.push(tmp->left);
            }
            if(tmp->right){
                s.push(tmp->right);
            }
        }
        return count;
    }
    int widthRecursive(){
        int width = 0;
        int height = heightIterative();
        for(int i = 1; i <= height; ++i){
            width = std::max(width,widthRecursiveHelper(tree_root,i));
        }
        return width;
    }
    int widthIterative(){
        if (isEmpty()) return 0;

        int height = heightRecursive();
        int width = 0;
        std::queue<TreeNode<T>*> q;
        q.push(tree_root);
        for(int i = 0; i < height; ++i){
            int size = q.size();

            for(int j = 0; j < size;++j){
                TreeNode<T>* tmp = q.front();
                q.pop();
                if(tmp->left)
                    q.push(tmp->left);
                if(tmp->right)
                    q.push(tmp->right);
            }
            width = std::max(width,size);
        }
        return width;
    }
private:
    int widthRecursiveHelper(TreeNode<T>* root,int level){
        if(!root)
            return 0;

        if(level == 1) 
            return 1;
    
        return widthRecursiveHelper(root->left,level-1) + widthRecursiveHelper(root->right,level-1);
    } 
    int heightRecursiveHelper(TreeNode<T>* root){
        if(!root) return 0;

        return 1 + std::max(heightRecursiveHelper(root->left),heightRecursiveHelper(root->right));
    }
    int countOfNodesRecursiveHelper(TreeNode<T>* root) const{
        if(!root) return 0;

        return 1 + countOfNodesRecursiveHelper(root->left) + countOfNodesRecursiveHelper(root->right);
    }

    int countOfLeavesRecursiveHelper(TreeNode<T>* root) const{
        if(!root) return 0;
        if(!root->left && !root->right) return  1;
        
        return countOfLeavesRecursiveHelper(root->left) + countOfLeavesRecursiveHelper(root->right);
    }
    
    void inorderRecursiveHelper(TreeNode<T>* root) const{
        if(!root) return;

        inorderRecursiveHelper(root->left);
        std::cout << root->value << " ";
        inorderRecursiveHelper(root->right);
    }
    void postorederRecursiveHelper(TreeNode<T>* root) const{
        if(!root) return;

        postorederRecursiveHelper(root->left);
        postorederRecursiveHelper(root->right);
        std::cout << root->value << " ";
    }

    void preorderRecursiveHelper(TreeNode<T>* root) const{
        if (!root) return;
        std::cout << root->value <<" ";
        preorderRecursiveHelper(root->left);
        preorderRecursiveHelper(root->right);
    }

    TreeNode<T>* findMaxNodeIterative() const{
        TreeNode<T>* tmp = tree_root;
        while(tmp && tmp->right){
            tmp =  tmp->right;
        }
        return tmp;
    }
    TreeNode<T>* findMaxNodeRecursiveHelper(TreeNode<T>* root) const{
        if(root == nullptr) {
            return nullptr; //if not checked will return a segmentation fault on line 136
        }
        if(root->right == nullptr){
            return root;
        }

        return findMaxNodeRecursiveHelper(root->right);
    }
    TreeNode<T>* findMinNodeIterative() const{
        TreeNode<T>* tmp = tree_root;
        while(tmp && tmp->left){
            tmp = tmp->left;
        }
        return tmp;
    }
    
    TreeNode<T>* findMinNodeRecursive() const{
        return findMinNodeRecursiveHelper(tree_root);
    }

    TreeNode<T>* insertRecursiveHelper(const T& val,TreeNode<T>* root){ 
        // Or you can pass a pointer by reference without returning the  root each time.
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

            TreeNode<T>* min = findMinNodeRecursiveHelper(root->right);
            root->value = min->value;
            root->right = eraseRecursiveHelper(min->value, root->right);
        }
        
        return root;
    }

    TreeNode<T>* findMinNodeRecursiveHelper(TreeNode<T>* root) const{
        if(root == nullptr)
            return nullptr;
        if(root->left == nullptr){
            return root;
        }
        
        return findMinNodeRecursiveHelper(root->left);
    }
private:
    TreeNode<T>* tree_root;
};



int main(){
    BinarySearchTree<int>* tree = new BinarySearchTree<int>();

    tree->insertIterative(13);
    tree->insertIterative(15);
    tree->insertIterative(9);
    tree->insertIterative(12);
    tree->insertIterative(11);
    tree->insertIterative(5);

  
    std:: cout<< tree->countOfNodesIterative();

    std::cout << tree->widthRecursive();
    std::cout << tree->widthIterative();

}


