#ifndef TREE_H
#define TREE_H

template <typename T>
class Tree {
    private:
        Tree<T>* left;
        Tree<T>* right;
        T data;
    public:
        Tree<T>* getLeftTree() {
            return left;
        }

        Tree<T>* getRightTree() {
            return right;
        }

        T getRoot() {
            return data;
        }

        void setLeftTree(Tree<T> &tree) {
            left = tree;
        }

        void setRightTree(Tree<T> &tree) {
            right = tree;
        }

        void setRootData(T n) {
            data = n;
        }
};


#endif // TREE_H
