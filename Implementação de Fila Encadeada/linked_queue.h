/// Copyright [2021] <Mauricio Konrath>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H
#include <cstdint>

namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

 private:
    class Node{
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (size_ > 0) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *new_value = new Node(data, tail);
    if (new_value == nullptr) {
        throw std::out_of_range("fila cheia");
    }
    if (empty()) {
        head = new_value;
    } else {
        tail->next(new_value);
    }
    tail = new_value;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        Node *eliminate = head;
        T info_back = eliminate->data();
        head = eliminate->next();
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
