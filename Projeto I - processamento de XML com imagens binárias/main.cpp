/// Copyright [2022] <Mauricio Konrath>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H


#include <iostream> ///ler e gravar
#include <fstream> ///arquivos
#include <sstream> ///dados
#include <tuple> ///tupla
#include <stack> ///pilha
#include <string> ///string e memória
#include <vector> ///array
#include <stdexcept> ///exceções em c++
#include <algorithm> ///intervalos
#include <utility> /// outras funções
#include <cstdint> ///std::size_t


namespace xml {
///obtem a tag
std::string get_tag(
    const std::string& source, 
    const std::string& open_tag,
    const std::string& close_tag, 
    size_t& start_index);
///obtem o valor
std::string get_value(
    const std::string& source,
    const std::string& open_tag,
    const std::string& close_tag);
bool valida(const std::string& contents); ///validar o xml

} ///namespace xml

namespace structures {
///classe LinkedStack
template<typename T>
class LinkedStack {
 public:
    LinkedStack(); ///construtor simples    
    ~LinkedStack(); ///destrutor    
    void clear(); ///limpa pilha
    void push(const T& data); /// empilha    
    T pop(); ///desempilha    
    T& top() const; ///retorna ao topo    
    bool empty() const; ///ve se está vazia   
    std::size_t size() const; ///retorna o tamanho
 
 private:
    class Node {   
     public:
        explicit Node(const T &data) {
            data_ = data;
            next_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() { /// getter: dado   
            return data_;
        }

        const T& data() const { /// getter const: dado  
            return data_;
        }

        Node* next() { /// getter: próximo
            return next_;
        }

        const Node* next() const { /// getter const: próximo
            return next_;
        }

        void next(Node* node) { /// setter: próximo  
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};
    std::size_t size_{0u};
};
}   /// namespace structures

namespace area {
    /// vai enumerar as sequencias dos pixels
    enum cor {
        /// 0 para preto
        preto,
        /// 1 para branco
        branco,
    };
    /// vai contar as areas em branco
    int area_contador(std::vector<std::vector<bool>> matrix);
    /// vai transformar uma area inteira da matriz em zeros
    void area_transformada(std::vector<std::vector<bool>>& matrix, int i, int j);
    /// vai criar uma nova matriz a partir de uma string de zeros e uns
    std::vector<std::vector<bool>> matriz_nova(const std::string& str_matrix, int width, int height);
}   /// namespace area

int main() {

    char xmlfilename[100];
    std::ifstream xmlfile;
    
    std::cin >> xmlfilename;  // entrada
    
    xmlfile.open(xmlfilename);
    /// retorna mensagem de erro e -1 caso o arquivo xml não for aberto
    if (not xmlfile.is_open()) {
        std::cout << "error";
        return -1;
    }
    
    std::stringstream stream;
  stream << xmlfile.rdbuf();
  std::string contents = stream.str();
    
    xmlfile.close();
     // retorna mensaegm de erro e -1 caso arquivo não é um xml válido
    if (not xml::valida(contents)) {
        std::cout << "error";
        return -1;
    }
    
    size_t i ={0};

    // busca a tag completa da próxima imagem dentro do arquivo
    while (i < contents.length()) {
        std::string open_tag = "<img>";
        std::string close_tag = "</img>";
        std::string image = xml::get_tag(contents, open_tag, close_tag, i);
        i += image.length() + close_tag.length();        
        // se chegar ao final das imagens ele sai do laço
        if (i > contents.length()) {
          break;
          }
        /// para buscar o conteudo de cada imagem foi utilizado a função get_value
        std::string data = xml::get_value(image, "<data>", "</data>");
        const std::string name = xml::get_value(image, "<name>", "</name>");
        const int width = std::stoi(xml::get_value(image, "<width>", "</width>"));
        const int height = std::stoi(xml::get_value(image, "<height>", "</height>"));
         /// se for uma imagem inválida, com altura e largura menores ou iguais a 0, retorna -1
        if (height <= 0|| width <= 0) {
          return -1;
        }
         // remove \n da string data
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        std::vector<std::vector<bool>> matrix = area::matriz_nova(data, width, height);

        int regions = area::area_contador(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }
}

namespace xml {
bool valida(const std::string& contents) {
    structures::LinkedStack<std::string> tags;
    size_t i = 0u;

    while (i < contents.length()) {
        /// encontra o íncio e final da próxima tag 
        size_t pos_inicial = contents.find('<', i);
        size_t pos_final = contents.find('>', pos_inicial);
        /// senão encontrar, pula para o final
        if (pos_inicial == std::string::npos) {
            break;
        }
        /// se a posição final falhar, ocorre um erro
        if (pos_final == std::string::npos) {
            return false;
        }
        
        std::string tag = contents.substr(pos_inicial, pos_final + 1 - pos_inicial);
        i = pos_final + 1;
        /// se for uma tag de abertura, vai colocar "/" no inicio da pilha
        if (tag[1] != '/') {
            tags.push(tag.insert(1, "/"));
        } else {
            /// se for uma tag de fechamento e a pilha está vazia, o arquivo vai ser invalido
            if (tags.empty()) {
                return false;
            /// se a tag de fechamento for igual ao topo da pilha, ele vai desempilhar o topo
            } else if (tags.top() == tag) {
                tags.pop();
            /// caso contrário vai dar erro
            } else {
                return false;
            }  
        }
    }
    return tags.empty();
}

std::string get_tag(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag, 
    size_t& start_index) {

    size_t pos_inicial = source.find(open_tag, start_index);
    size_t pos_final = source.find(close_tag, pos_inicial);
            
    pos_inicial += open_tag.length();
    std::string tag_contents = source.substr(pos_inicial, pos_final - pos_inicial);
    return tag_contents;
}

std::string get_value(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag) {

    std::size_t pos{0};
    return get_tag(source, open_tag, close_tag, pos);
}
}  /// namespace xml

namespace structures {
template<typename T>
LinkedStack<T>::LinkedStack() {}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::clear() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node* novo = new Node(data, top_);
    top_ = novo;
    size_++;
}

template<typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Empty Stack");
    }
    Node* aux = top_;
    T data = aux->data();
    top_ = top_->next();
    size_--;
    delete aux;
    return data;
}

template<typename T>
T& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Empty Stack");
    }
    return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

}   /// namespace structures

namespace area {
///metodo que vai transformar uma area que é conexa inteira em uma matriz de zeros, ou seja em pretos
void area_transformada(std::vector<std::vector<bool>>& matrix, int i, int j) {
    structures::LinkedStack<std::tuple<int, int>> stack;

    int largura = matrix[0].size();
    int altura = matrix.size();
    stack.push(std::make_tuple(i, j));

    while (!stack.empty()) {
        std::tuple<int, int> aux = stack.pop();
        
        i = std::get<0>(aux);
        j = std::get<1>(aux);
        matrix[i][j] = 0;
        /// analisa os elementos da esquerda para ver se existe e sé branco
        if (j > 0 && matrix[i][j - 1]) {
            stack.push(std::make_tuple(i, j - 1));     
        }
        /// analisa os elementos da direita para ver se existe e sé branco
        if (j < (largura - 1) && matrix[i][j + 1]) {
            stack.push(std::make_tuple(i, j + 1));
        }
        /// analisa os elementos acima para ver se existe e sé branco
        if (i > 0 && matrix[i - 1][j]) {
            stack.push(std::make_tuple(i - 1, j));
        }
        /// analisa os elementos abaixo para ver se existe e sé branco
        if (i < (altura - 1) && matrix[i + 1][j]) {
            stack.push(std::make_tuple(i + 1, j));
        }
    }

} 
/// método que vai contar as áreas conexas de 1's, e quando encontra ele incrementa um contador, 
///e depois ele prenche com 0's esses elementos
int area_contador(std::vector<std::vector<bool>> matrix) {
    int cont = 0;    
    for (int i = 0; i < (int) matrix.size(); i++) {
        for (int j = 0; j < (int) matrix[0].size(); j++) {
            if (matrix[i][j] == cor::branco) {
                cont++;
                area_transformada(matrix, i, j);
            }
        }
    }
    return cont;
}

/// metodo que vai criar uma nova matriz apartir dos 0's e 1's
std::vector<std::vector<bool>> matriz_nova(const std::string& str_matrix, int width, int height) {
    std::vector<std::vector<bool>> matrix;

    for (int i = 0u; i < height; i++) {
        std::vector<bool> line;
        for (int j = 0; j < width; j++) {
            line.push_back(str_matrix[i * width + j] == '1');
        }
        matrix.push_back(line);
    } 
    return matrix;
}
}   /// namespace area

#endif