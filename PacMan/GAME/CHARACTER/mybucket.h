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
    MyBucket();
    ~MyBucket();

    void push(typ obiekt,int key);
    typ pop();
    int getSize();




};

#endif // MYBUCKET_H
