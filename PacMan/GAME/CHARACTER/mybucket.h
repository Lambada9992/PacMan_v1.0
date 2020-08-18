#ifndef MYBUCKET_H
#define MYBUCKET_H

template <typename T>
/**
 * @brief The element struct struktura wykorzystywana do przetrzymywania elementow
 */
struct element{
    /**
     * @brief object przetrzymywany element
     */
    T object;
    /**
     * @brief next wskaznik na nastepny strukture o tej samej wartosci klucza
     */
    element *next;
    /**
     * @brief down wskaznik na strukture o nizszej wartosci klucza
     */
    element *down;
    /**
     * @brief key wartosc priorytetu struktury
     */
    int key;
};


template <typename typ>
/**
 * @brief The MyBucket class struktura danych realizujaca zdanie kolejki priorytetowej na zasadzie dzialania sortowania kubelkowego
 */
class MyBucket
{
private:

    element<typ> *head;
    int size;

public:
    MyBucket();
    ~MyBucket();

    /**
     * @brief push dodanie elementu do kolejki priorytetowej
     * @param obiekt dodawany element
     * @param key klucz priorytetowy dodawanego elementu
     */
    void push(typ obiekt,int key);
    /**
     * @brief pop wyjecie ze struktury elementu o najnizszym kluczu(zwrocenie go oraz usuniecie ze struktury)
     * @return element o najnizszym kluczu
     */
    typ pop();
    /**
     * @brief getSize ilosc elementow w strukturze danych
     * @return ilosc elementow
     */
    int getSize();




};

#endif // MYBUCKET_H
