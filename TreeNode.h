#pragma once
template <typename T>
struct TreeNode{
    TreeNode(const T& v,TreeNode<T>* l = nullptr,TreeNode<T>* r = nullptr)
        : value(v)
        , left(l)
        , right(r)
        {}
    TreeNode<T>* left;
    TreeNode<T>* right;
    T value;
};