/// Copyright [2022] <Mauricio Konrath>
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H


#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
    BinaryTree() = default;
    ~BinaryTree();
    void insert(const T& data);
    void remove(const T& data);
    bool contains(const T& data) const;
    bool empty() const;
    std::size_t size() const;
    ArrayList<T> pre_order() const;
    ArrayList<T> in_order() const;
    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
        }

        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        Node* remove(const T& data_) {
            if (data_ < data) {
                if (left != nullptr) {
                    left = left->remove(data_);
                    return this;
                } else {
                    return nullptr;
                }
            } else if (data_ > data) {
                if (right != nullptr) {
                    right = right->remove(data_);
                    return this;
                } else {
                    return nullptr;
                }
            } else {
                if (right != nullptr && left != nullptr) {
                    Node* temp = right->minimum();
                    data = temp->data;
                    right = right->remove(data);
                    return this;
                } else if (right != nullptr) {
                    Node* temp = right;
                    delete this;
                    return temp;
                } else if (left != nullptr) {
                    Node* temp = left;
                    delete this;
                    return temp;
                } else {
                    delete this;
                    return nullptr;
                }
            }
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data && left != nullptr) {
                return left->contains(data_);
            } else if (data_ > data && right != nullptr) {
                return right->contains(data_);
            } else {
                return false;
            }
        }

        void pre_order(ArrayList<T>& v) const {
            // Raiz.
            v.push_back(data);

            if (left != nullptr) {
                left->pre_order(v);
            }

            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }

            v.push_back(data);

            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }

            if (right != nullptr) {
                right->post_order(v);
            }

            v.push_back(data);
        }

        Node* minimum() {
            if (left == nullptr) {
                return this;
            } else {
                return left->minimum();
            }
        }

        T data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root{nullptr};
    std::size_t size_{0};
};

}  // namespace structures

#endif

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    if (root != nullptr) {
        structures::ArrayList<T> list_nodes = pre_order();
        while (!list_nodes.empty()) {
            remove(list_nodes.pop_back());
        }
    }
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (!contains(data)) {
        if (root != nullptr) {
            root->insert(data);
        } else {
            root = new Node(data);
        }
        size_++;
    } else {
        throw std::out_of_range("Elemento existente");
    }
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (root != nullptr) {
        if (contains(data)) {
            root->remove(data);
            size_--;
        } else {
            throw std::out_of_range("Elemento invalido");
        }
    } else {
        throw std::out_of_range("Árvore nao existe");
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->post_order(v);
    }
    return v;
}

