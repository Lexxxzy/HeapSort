#include <iostream>
#include <ctime>
#include <numbers>
#include "windows.h"
#include <locale.h>


using namespace std;

//дек
class deq
{

private:
    //структура для хранения элементов в деке
    struct Node
    {
          int val;
          Node* Next;
          Node* Prev;
          Node(int n) :Next(0), Prev(0), val(n) {}; //конструктор структуры

    };
    Node* Head;
    Node* Tail;

public:
    // Счетчик колличества операций
    unsigned long long int N_op = 0;

    void pushFront(int n);
    void pushBack(int n);
    int popFirst();
    int popLast();
    void Print();
    bool isEmpty();
    int size();

    int count = 0; //количество элементов

    deq() { Head = NULL;Tail = NULL; } //конструктор дека
};

void deq::pushFront(int n) //вставка в начало
{
    Node* Elem = new Node(n);
    Elem->Prev = NULL;
    count++;

    if (Head != NULL) //проверка на то есть ли голова (добавление первого элемента)
    {
        Elem->Next = Head;
        Head->Prev = Elem; //установка указателя ГОЛОВЫ(которая сейчас) на предыдущий элемент 
        Head = Elem;
    }
    else
    {
        Elem->Next = NULL;
        Head = Tail = Elem;
    }
}

void deq::pushBack(int n) //вставка в конец
{
    Node* Elem = new Node(n);
    Elem->Next = NULL;
    count++;

    if (Tail != NULL)
    {
        Elem->Prev = Tail;
        Tail->Next = Elem;
        Tail = Elem;
    }
    else
    {
        Elem->Next = NULL;
        Tail = Head = Elem;
    }
}

int deq::popFirst() //удаление из начала
{

    if (count != 0) {
        if (Head->Next) {          //если в деке больше одного элемента 
            Node* element = Head; //указываем на то, что будем использовать голову
            int ret = element->val;

            Head = Head->Next; //присваиваем статус головы следующему за бывшей головой элементу 
            Head->Prev = nullptr;  //указываем на то, что перед головой пусто
            delete element;     //удаляем бывшую голову

            count--;   //уменьшаем размер дека

            return ret;  //возвращаем значение удаленного элемента
        }
        else if (Head == Tail) { //если элемент один в деке
            Node* element = Head;
            int ret = element->val;

            Head->Next = nullptr;  //указываем, что за головой пусто
            Head = nullptr;       //указываем на то, что голова тоже пуста
            delete Head;        //удаляем единственный элемент

            count = 0;        //присваиваем ноль размеру дека

            return ret;       //возвращаем значение удаленного элемента
        }
    }
    else cout << "error" << endl;
} 

int deq::popLast() //удаление из конца
{
    if (count != 0) {               //если дек не пустой
        //cout << Tail->val << endl;
        if (count > 1) {         //если в деке находится больше одного элемента
            Node* element = Tail;     //указываем на то, что будет использоваться хвост
            Tail = Tail->Prev; //присваиваем статус хвоста предыдущему элементу
            Tail->Next = NULL;
            int ret = element->val;//указываем на то, что за элементом пусто
            delete element;     //удаляем бывший хвост
            count--;
            return ret; //уменьшаем размер дека
        }
        else { //если в деке находится всего один элемент
            Node* element = Tail;
            int ret = element->val;
            Head = Tail = 0;        //присваиваем ему значение ноль
            count--;    //уменьшаем размер дека
            return ret;
        }
    }
    else cout << "error" << endl;
}

int deq::size() //возвращает размер дека
{
    return count;
}

bool deq::isEmpty() 
{
   return Head == NULL ? true : false;
}

void deq::Print()
{
    Node* p = Head;
    while (p != NULL)
    {
        cout << p->val << "  ";
        p = p->Next;
    }
    cout << "\n";
}


int getValue(deq* d, int n)
{
    int i;
    deq* temp = new deq();;
    int ret;

    if (n <= d->size() / 2) //если искомый элемент находиться ближе к началу списка
    {
        for (i = 0; i < n; i++)
        {
            temp->pushBack(d->popFirst()); //удаляем из основного дека и переписываем в temp до n-ого элемента
        }
        ret = d->popFirst(); //удаляем искомый элемент из основного и получаем его значение
        temp->pushBack(ret); //добавляем в конец чтобы получить начальное расположение
        for (i = 0;!temp->isEmpty(); i++)
        {
            d->pushFront(temp->popLast());//убираем с конца temp списка и добавляем в начало основного (возвращаем все как было)
        }
        return ret;
    }
    else //если ближе к концу
    {
        if (n != d->size() - 1) //если не последний элемент
        {
            for (i = 0; i < d->size() - n; i++)
            {
                temp->pushFront(d->popLast());
            }
        }
        ret = d->popLast(); //удаляем искомый элемент из конца основного и получаем его значение
        temp->pushFront(ret); //добавляем в начало чтобы получить начальное расположение

        for (i = 0;!temp->isEmpty(); i++)
        {
            d->pushBack(temp->popFirst()); //убираем с начала temp списка и добавляем в начало основного (возвращаем все как было)
        }
        return ret;
    }

    delete temp;
}

void setValue(deq* d, int n, int val)
{
    int i;
    deq* temp = new deq();
    int ret;

    if (n <= d->size() / 2)
    {
        for (i = 0; i < n; i++)
        {
            temp->pushBack(d->popFirst());
        }
        ret = d->popFirst(); //удаляем искомый элемент из основного дека
        temp->pushBack(val); //добавляем в конец чтобы получить начальное расположение
        for (i = 0;!temp->isEmpty(); i++)
        {
            
            d->pushFront(temp->popLast()); //убираем с конца temp списка и добавляем в начало основного дека(возвращаем все как было)
        }
        
    }
    else
    {
        if (n != d->size()-1) //если не последний элемент
        {
            for (i = 0; i < d->size() - n; i++)
            {
                temp->pushFront(d->popLast()); //перекидываем элементы их конца основного дека в начало temp
            }
        }

        ret = d->popLast(); //удаляем искомый элемент из конца основного 
        temp->pushFront(val); //добавляем в начало чтобы получить начальное расположение

        for (i = 0;!temp->isEmpty(); i++)
        {
            d->pushBack(temp->popFirst()); //убираем с начала temp списка и добавляем в начало основного (возвращаем все как было)
        }
    }
    delete temp;
}

//создание max heap
void heapify(deq* d,int n, int i)
{
    int largest = i; //Инициализируем корень поддерева как наибольшие элемент
    int l = 2 * i + 1; // левый ребенок= 2*i + 1
    int r = 2 * i + 2; // правый ребенок= 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && getValue(d,l) > getValue(d,largest))
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && getValue(d,r) > getValue(d,largest))
        largest = r;

    // Если самый большой элемент оказался не корень
    if (largest != i)
    {
        int temp = getValue(d,i);
        setValue(d, i, getValue(d,largest));
        setValue(d, largest, temp);
        //swap(i, largest);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(d, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(deq* d,int n)
{
    // Построение кучи (перегруппируем дек)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(d, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--)
    {
        // Перемещаем текущий корень в начало
        int temp = getValue(d, 0);
        setValue(d, 0, getValue(d, i));
        setValue(d, i, temp);
        //swap(0, i);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(d, i, 0);
    }
}

int main()

{

    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    // Эксперимента
    // Инициализация очереди и заполнение хранилища ключей
    int i, start, end;
    // Хранилище 3000 элементов
    int Key[3000];
    int N = 300;//начальное количество
    deq list;

    for (i = 0; i < 300; i++)
    {
        // Заполнение хранилища ключей случайными числами до 1000
        Key[i] = rand() % 999;
    }

    for (i = 0; i < 1; i++)
    {
        for (int z = N - 300; z < N; z++)
        {
            list.pushFront(Key[z]);
        }
        cout << "Начальный дек: ";
        list.Print();
        //list.N_op = 0;
        start = GetTickCount64();
        //сортируем
        heapSort(&list, list.size());
        end = GetTickCount64();
        cout << "Отсортированный дек: ";
        list.Print();
        cout << "\n\n\n";

        cout << "Номер сортировки: " << i + 1 << " Колличество отсортированных элементов: " << N << " Время сортировки (ms): " << end - start << " Колличество операций (N_op): " << endl;
        N = N + 300;//шаг в 300

    }


    //deq elements;

    ////добавляем элементы в дек
    //elements.pushFront(15);
    //elements.pushFront(1);
    //elements.pushFront(3);
    //elements.pushFront(7);
    //elements.pushFront(9);
    //elements.pushBack(4);
    //elements.pushBack(6);
    //elements.Print();

    ////сортируем
    //heapSort(&elements, elements.size());

    //elements.Print();

    //int end = clock();
    //cout << end;

}