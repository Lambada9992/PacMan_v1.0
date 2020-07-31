#include "mybucket.h"

//template <typename typ>
//MyBucket<typ>::MyBucket()
//{
//    head = nullptr;
//    size = 0;
//}

//template<typename typ>
//MyBucket<typ>::~MyBucket()
//{
//    if(head!=nullptr){
//        while(head!= nullptr){
//            while(head->next!=nullptr){
//                element<typ> *pom = head;
//                head = head->next;
//                head->down = pom->down;
//                delete pom;
//            }
//            element<typ> *pom = head;
//            head = head->down;
//            delete pom;
//        }
//    }
//}

//template<typename typ>
//void MyBucket<typ>::push(typ obiekt, int key)
//{
//    element<typ> *pom = new element<typ>;
//    pom->object = obiekt;
//    pom->key = key;
//    pom->down = nullptr;
//    pom->next = nullptr;

//    if(head == nullptr){
//        head = pom;
//        size++;
//    }else{
//        element<typ> *iterator = head;
//        while(iterator!=nullptr){
//            if(iterator->key == pom->key){
//                pom->next = iterator ->next;
//                iterator->next = pom;
//                size++;
//                break;
//            }else if(iterator->down == nullptr){
//                iterator->down = pom;
//                size++;
//                break;
//            }else if(iterator->down->key > pom->key){
//                pom->down = head->down;
//                head->down = pom;
//                size++;
//                break;
//            }

//            iterator = iterator->down;
//        }
//    }


//}

//template<typename typ>
//typ MyBucket<typ>::pop()
//{
//    if(head==nullptr)throw "empty bucket";
//    typ result;
//    if(head->next!=nullptr){
//        element<typ> pom = head;
//        head=head->next;
//        head->down = pom->down;
//        result = pom.object;
//        delete pom;
//        size--;
//        return result;
//    }else{
//        element<typ> pom = head;
//        head=head->down;
//        result = pom.object;
//        delete pom;
//        size--;
//        return result;
//    }


//}

//template<typename typ>
//int MyBucket<typ>::getSize()
//{
//    return size;
//}
