#include <iostream>
#include <algorithm>

template<class T>
class AVLNode {
public:
    AVLNode(const T &value) : data_(value), left_(NULL), right_(NULL), parent_(NULL) {}

    ~AVLNode() {}

    const T &GetValue() const { return data_; }

    void SetLeft(AVLNode *left) { left_ = left; }

    AVLNode *GetLeft() const { return left_; }

    void SetRight(AVLNode *right) { right_ = right; }

    AVLNode *GetRight() const { return right_; }

    void SetParent(AVLNode *parent) { parent_ = parent; }

    AVLNode *GetParent() const { return parent_; }

    void Print() const { std::cout << data_ << std::endl; }

private:
    AVLNode();

    T data_;
    AVLNode *left_;
    AVLNode *right_;
    AVLNode *parent_;
};

template<class T>
class AVLTree {
public:
    AVLTree() : root_(NULL) {}

    ~AVLTree();

    bool Insert(const T &value);
    AVLNode<T> *GetRoot() const { return root_; }
    AVLNode<T> *Find(AVLNode<T> *root, const T &value) const;
    int Height(AVLNode<T> *root) const;
    int BalanceFactor(AVLNode<T> *root) const;
    void RotateLeft(AVLNode<T> *root);
    void RotateRight(AVLNode<T> *root);

    void PrintPreOrder(AVLNode<T> *root) const; // Parent, Left, Right
    void PrintInOrder(AVLNode<T> *root) const; // Left, Parent, Right
    void PrintPostOrder(AVLNode<T> *root) const; // Left, Right, Parent

    void PrintBreadthSearchFirst() const;

private:
    void InsertAVLNode(AVLNode<T> *root, AVLNode<T> *ins);

    void DeleteAVLNode(AVLNode<T> *node);

    AVLNode<T> *root_;
};

template<class T>
AVLTree<T>::~AVLTree() {
    if (root_) {
        DeleteAVLNode(root_);
    }
}

template<class T>
void AVLTree<T>::DeleteAVLNode(AVLNode<T> *node) {
    if (node) {
        DeleteAVLNode(node->GetLeft());
        DeleteAVLNode(node->GetRight());
        delete node;
    }
}

template<class T>
bool AVLTree<T>::Insert(const T &value) {
    AVLNode<T> *new_node = new(std::nothrow) AVLNode<T>(value);

    if (!new_node)
        return true;

    if (!root_)
        root_ = new_node;
    else
        InsertAVLNode(root_, new_node);

    return false;
}

template<class T>
void AVLTree<T>::InsertAVLNode(AVLNode<T> *root, AVLNode<T> *ins) {
    if (ins->GetValue() <= root->GetValue()) {
        if (root->GetLeft())
            InsertAVLNode(root->GetLeft(), ins);
        else {
            root->SetLeft(ins);
            ins->SetParent(root);
        }
    } else {
        if (root->GetRight())
            InsertAVLNode(root->GetRight(), ins);
        else {
            root->SetRight(ins);
            ins->SetParent(root);
        }
    }

    int balance = BalanceFactor(root);
    if (balance > 1) {
        if (BalanceFactor(root->GetLeft()) < 0)
            RotateLeft(root->GetLeft());
        RotateRight(root);
    } else if (balance < -1) {
        if (BalanceFactor(root->GetRight()) > 0)
            RotateRight(root->GetRight());
        RotateLeft(root);
    }
}

template<class T>
void AVLTree<T>::PrintPreOrder(AVLNode<T> *root) const {
    if (root) {
        root->Print();
        PrintPreOrder(root->GetLeft());
        PrintPreOrder(root->GetRight());
    }
}

template<class T>
void AVLTree<T>::PrintInOrder(AVLNode<T> *root) const {
    if (root) {
        PrintInOrder(root->GetLeft());
        root->Print();
        PrintInOrder(root->GetRight());
    }
}

template<class T>
void AVLTree<T>::PrintPostOrder(AVLNode<T> *root) const {
    if (root) {
        PrintPostOrder(root->GetLeft());
        PrintPostOrder(root->GetRight());
        root->Print();
    }
}

template<class T>
AVLNode<T> *AVLTree<T>::Find(AVLNode<T> *root, const T &value) const {
    if (root) {
        if (root->GetValue() == value)
            return root; // Found
        else if (value < root->GetValue())
            return Find(root->GetLeft(), value);
        else
            return Find(root->GetRight(), value);
    }

    return NULL;
}

template<class T>
int AVLTree<T>::Height(AVLNode<T> *root) const {
    int height = 0;
    if (root) {
        int left = Height(root->GetLeft());
        int right = Height(root->GetRight());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}

template<class T>
int AVLTree<T>::BalanceFactor(AVLNode<T> *root) const {
    int balance = 0;
    if (root) {
        balance = Height(root->GetLeft()) - Height(root->GetRight());
    }
    return balance;
}

template<class T>
void AVLTree<T>::RotateLeft(AVLNode<T> *root) {
    AVLNode<T> *newroot = root->GetRight();
    root->SetRight(newroot->GetLeft());
    newroot->SetLeft(root);

    if (root->GetParent() == NULL) {
        root_ = newroot;
        newroot->SetParent(NULL);
    } else {
        if (root->GetParent()->GetLeft() == root) {
            root->GetParent()->SetLeft(newroot);
        } else {
            root->GetParent()->SetRight(newroot);
        }
        newroot->SetParent(root->GetParent());
    }
    root->SetParent(newroot);
}

template<class T>
void AVLTree<T>::RotateRight(AVLNode<T> *root) {
    AVLNode<T> *newroot = root->GetLeft();
    root->SetLeft(newroot->GetRight());
    newroot->SetRight(root);

    if (root->GetParent() == NULL) {
        root_ = newroot;
        newroot->SetParent(NULL);
    } else {
        if (root->GetParent()->GetLeft() == root) {
            root->GetParent()->SetLeft(newroot);
        } else {
            root->GetParent()->SetRight(newroot);
        }
        newroot->SetParent(root->GetParent());
    }

    root->SetParent(newroot);
}

std::ostream &operator<<(std::ostream &os, const std::pair<int, int> &pair) {
    os << pair.first << ' ' << pair.second;
    return os;
}

int main() {
    AVLTree<int> tree_int;
    tree_int.Insert(12);
    tree_int.Insert(11);
    tree_int.Insert(112);
    tree_int.Insert(122);

    tree_int.PrintInOrder(tree_int.GetRoot());

    AVLTree<std::pair<int, int>> tree_pair;
    tree_pair.Insert(std::pair<int, int>(12, 22));
    tree_pair.Insert(std::pair<int, int>(11, 221));
    tree_pair.Insert(std::pair<int, int>(10, 252));
    tree_pair.Insert(std::pair<int, int>(9, 222));


    tree_pair.PrintInOrder(tree_pair.GetRoot());
    return 0;
}