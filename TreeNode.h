template <typename T>
struct TreeNode{
public:
    TreeNode(T v,TreeNode<T>* l = nullptr,TreeNode<T>* r = nullptr)
    : value(v)
    , left_child(l)
    , right_child(r)
    {};
private:
    TreeNode<T>* left_child;
    TreeNode<T>* right_child;
    T value;
};