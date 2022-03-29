/// Copyright [2022] <Mauricio Konrath>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();  // limpar lista

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem

    T& at(std::size_t index);  // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const;  // versão const do acesso ao indice

    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover dado específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // lista contém determinado dado?
    std::size_t find(const T& data) const;  // posição de um item na lista

    std::size_t size() const;  // tamanho da lista

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

        T& data() {  /// Getter: dado
            return data_;
        }
        const T& data() const {  /// Getter const: dado
            return data_;
        }
        Node* next() {  /// Getter: próximo
            return next_;
        }
        const Node* next() const {  /// Getter const: próximo
            return next_;
        }
        void next(Node* node) {  /// Setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::CircularList<T>::CircularList() {
    head = new Node(0);
    size_ = 0;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
    delete head;
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (size_> 0) {
        pop_front();
    }
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    insert(data, size_);
}
template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node *new_value = new Node(data);
    if (new_value == nullptr) {
        throw std::out_of_range("lista cheia");
    } else {
        if (empty()) {
            new_value->next(head);
        } else {
            new_value->next(head->next());
        }
        head->next(new_value);
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node *new_value = new Node(data);
        if (new_value == nullptr) {
            throw std::out_of_range("lista cheia");
        } else {
            Node *previous = head->next();
            for (std::size_t i = 0; i < index - 1; i++) {
                previous = previous->next();
            }
            new_value->next(previous->next());
            previous->next(new_value);
            size_++;
        }
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *current = head->next();
        std::size_t position = 0;
        while (current->next() != head && data > current->data()) {
            current = current->next();
            position++;
        }
        if (data > current->data()) {
            insert(data, position + 1);
        } else {
            insert(data, position);
        }
    }
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        Node *current = head->next();
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        Node *current = head->next();
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else if (index == 0) {
        return pop_front();
    } else {
        Node *previous = head->next();
        for (std::size_t i = 0; i < index - 1; i++) {
            previous = previous->next();
        }
        Node *eliminate = previous->next();
        T info_back = eliminate->data();
        previous->next(eliminate->next());
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node *eliminate = head->next();
        T info_back = eliminate->data();
        head->next(eliminate->next());
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    Node* current = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (data == current->data()) {
            return i;
        }
        current = current->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
