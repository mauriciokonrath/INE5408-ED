/// Copyright [2021] <Mauricio Konrath>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H
#include <cstdint>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        // getter: info
        T& data() {
            return data_;
        }
        // getter-constante: info
        const T& data() const {
            return data_;
        }
        // getter: próximo
        Node* next() {
            return next_;
        }
        // getter-constante: próximo
       const Node* next() const {
            return next_;
        }
        // setter: próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures
#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (size_ > 0) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *new_value = new Node(data, top_);
    if (new_value == nullptr) {
        throw std::out_of_range("pilha cheia");
    }
    top_ = new_value;
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        Node *eliminate = top_;
        T info_back = eliminate->data();
        top_ = top_->next();
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        return top_->data();
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
