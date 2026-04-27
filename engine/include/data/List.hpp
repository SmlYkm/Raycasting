#pragma once

// If possible, avoid using this class, it's somewhat computationally expensive

namespace engine {
    namespace data {
        template <class T>

        class List {
        private:
            template <class Type> 

            class Node {
            private:
                Type        data_m;
                Node<Type>* next_m;
                Node<Type>* prev_m;

            public:
                Node(Type data, Node<Type>* prev = nullptr, Node<Type>* next = nullptr)
                    : data_m(data)
                    , prev_m(prev)
                    , next_m(next) {
                }

                Node()
                    : data_m(Type())
                    , prev_m(nullptr)
                    , next_m(nullptr) {
                }

                ~Node() {
                    next_m = nullptr;
                    prev_m = nullptr;
                }

                void set_prev(Node<Type>* prev) {
                    prev_m = prev;
                }

                Node<Type>* prev() const {
                    return prev_m;
                }

                void set_next(Node<Type>* next) {
                    next_m = next;
                }

                Node<Type>* next() const {
                    return next_m;
                }

                void set_data(const Type data) {
                    data_m = data;
                }

                const Type data() const {
                    return data_m;
                }
            };

        private:
            Node<T>* head_m;
            Node<T>* tail_m;
            int      length_m;

        public:
            class Iterator {
            private:
                Node<T>* current_m;

            public:
                Iterator(Node<T>* head = nullptr)
                    : current_m(head) {
                }

                ~Iterator() {
                    current_m = nullptr;
                }

                T operator*() {
                    return current_m->data();
                }

                Iterator& operator++() {
                    if(current_m)
                        current_m = current_m->next();
                    return *this;
                }

                const bool operator==(const Iterator& other) const {
                    return current_m == other.current_m;
                }

                const bool operator!=(const Iterator& other) const {
                    return current_m != other.current_m;
                }

                Node<T>* current() const {
                    return current_m;
                }
            };
        
        public:
            List()
                : head_m(nullptr)
                , tail_m(nullptr)
                , length_m(0) {
            }

            ~List() {
                clear();
            }

            void clear() {
                while(head_m) {
                    Node<T>* temp = head_m->next();
                    delete head_m;
                    head_m = temp;
                    --length_m;
                }
                head_m = nullptr;
                tail_m = nullptr;
            }

            void insert_at_ending(const T data) {
                if(!head_m) {
                    tail_m = new Node<T>(data);
                    head_m = tail_m;
                    ++length_m;
                    return;
                }
                Node<T>* temp = new Node<T>(data);
                temp->set_prev(tail_m);
                tail_m->set_next(temp);
                tail_m = temp;
                ++length_m;
            }

            void insert_at_beginning(const T data) {
                if(!tail_m) {
                    head_m = new Node<T>(data);
                    tail_m = head_m;
                    ++length_m;
                    return;
                }
                Node<T>* temp = new Node<T>(data);
                temp->set_next(head_m);
                head_m->set_prev(temp);
                head_m = temp;
                ++length_m;
            }

            void remove_from_beginning() {
                if(!tail_m)
                    return;
                Node<T>* temp = head_m->next();
                if(temp)
                    temp->set_prev(nullptr);
                else
                    tail_m = nullptr;
                delete head_m;
                head_m = temp;
                --length_m;
            }

            void remove_from_ending() {
                if(!tail_m)    
                    return;
                Node<T>* temp = tail_m->prev();
                if(temp)
                    temp->set_next(nullptr);
                else
                    head_m = nullptr;
                delete tail_m;
                tail_m = temp;
                --length_m;
            }

            Iterator begin() {
                return Iterator(head_m);
            }

            Iterator end() {
                return Iterator(nullptr);
            }

            const int length() const {
                return length_m;
            }

            Iterator erase(Iterator& it) {
                if(!head_m || it == end())
                    return end();

                Node<T>* temp = it.current();

                if(temp->prev())
                    temp->prev()->set_next(temp->next());
                else
                    head_m = temp->next();
                if(temp->next())
                    temp->next()->set_prev(temp->prev());
                else
                    tail_m = temp->prev();
                Iterator proxIt(temp->next());
                delete temp;
                --length_m;
                return proxIt;
            }
        };
    }
}