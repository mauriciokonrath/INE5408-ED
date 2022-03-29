// Copyright [2021] <Mauricio Konrath>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template <typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template <typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}
// excluindo o conteúdo
template <typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}
// verifique se a fila está cheia
template <typename T>
void structures::ArrayQueue<T>::enqueue(const T &data) {
    if (full()) {
        throw std::out_of_range("fila cheia!");
    } else {
        end_ = (end_+1) % max_size();
        contents[end_] = data;
        size_++;
        }
}
// verifique se a fila está vazia, retira um valor e os move
template <typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia!");
    } else {
        T aux;
        aux = contents[begin_];
        begin_ = (begin_+1) % max_size();
        size_--;
        return aux;
        }
}
//  verifica se a fila está vazia, senao retorna o valor de contents
template <typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[end_];
    }
}
// limpa a fila
template <typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}
// tamanho da fila
template <typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}
//  tamanho maximo da fila
template <typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}
// verifica se a fila esta vazia
template <typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size() == 0);
}
// verifica se a fila está cheia pelo seu tamanho máximo e o tamanho
template <typename T>
bool structures::ArrayQueue<T>::full() {
    return (size() == max_size());
}
