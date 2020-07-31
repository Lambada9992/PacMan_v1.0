#ifndef MYBUCKET_H
#define MYBUCKET_H

template <typename T>
struct element{
    T object;
    element *next;
    element *down;
    int key;
};


template <typename typ>
class MyBucket
{
private:
    element<typ> *head;
    int size;

public:
    MyBucket(){
        head = nullptr;
        size = 0;
    }
    ~MyBucket(){
        if(head!=nullptr){
            while(head!= nullptr){
                while(head->next!=nullptr){
                    element<typ> *pom = head;
                    head = head->next;
                    head->down = pom->down;
                    delete pom;
                }
                element<typ> *pom = head;
                head = head->down;
                delete pom;
            }
        }
    }

    void push(typ obiekt,int key){
        element<typ> *pom = new element<typ>;
        pom->object = obiekt;
        pom->key = key;
        pom->down = nullptr;
        pom->next = nullptr;

        if(head == nullptr){
            head = pom;
            size++;
        }else{
            element<typ> *iterator = head;
            while(iterator!=nullptr){
                if(iterator->key == pom->key){
                    pom->next = iterator ->next;
                    iterator->next = pom;
                    size++;
                    break;
                }else if(iterator->down == nullptr){
                    iterator->down = pom;
                    size++;
                    break;
                }else if(iterator->down->key > pom->key){
                    pom->down = head->down;
                    head->down = pom;
                    size++;
                    break;
                }

                iterator = iterator->down;
            }
        }


    }
    typ pop(){
        if(head==nullptr)throw "empty bucket";
        typ result;
        if(head->next!=nullptr){
            element<typ> *pom = head;
            head=head->next;
            head->down = pom->down;
            result = pom->object;
            delete pom;
            size--;
            return result;
        }else{
            element<typ> *pom = head;
            head=head->down;
            result = pom->object;
            delete pom;
            size--;
            return result;
        }


    }

    int getSize(){
        return size;
    }



};

#endif // MYBUCKET_H
