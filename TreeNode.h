template <typename T>
struct TreeNode{
public:
    TreeNode(T v,TreeNode<T>* l = nullptr,TreeNode<T>* r = nullptr)
    : value(v)
    , left(l)
    , right(r)
    {};
private:
    TreeNode<T>* left;
    TreeNode<T>* right;
    T value;
};