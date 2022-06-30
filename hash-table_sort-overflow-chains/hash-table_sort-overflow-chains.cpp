#include <iostream>
using namespace std;
#include <string>
typedef int T;

struct Node
{
    string data;
    Node* next;
    Node(string data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class HashTable
{
private:
    Node** hash_table;
    int copasaty;
    int hash_table_size_el;

    int hashString(string str)
    {
        int h = 0;
        int str_size = str.size();
        for (int p = 0; p < str_size; p++)
        {
            //h = h * this->hash_table_mul + (int)str[p];//char код
            h += (int)str[p];
        }
        return h % this->copasaty;
    }
public:

    //конструктор+
    HashTable(int size)
    {
        this->hash_table = new Node * [size];
        this->copasaty = size;
        hash_table_size_el = 0;
        for (int i = 0; i < size; i++)
        {
            this->hash_table[i] = nullptr;
        }
    }

    //конструктор копирования
    HashTable(const HashTable& A) : HashTable(A.copasaty)
    {
        /*copasaty = A.copasaty;
        hash_table_size_el = 0;
        this->hash_table = new Node * [copasaty];
        for (int i = 0; i < copasaty; i++)
        {
            this->hash_table[i] = nullptr;
        }*/
        for (int i = 0; i < copasaty; i++)
        {
            //if (A.hash_table[i] == nullptr)
            //    this->hash_table[i] = nullptr;
            //else
            //{
            Node* current = A.hash_table[i];
            while (current)
            {
                insert_2(current->data);
                current = current->next;
            }
            //}
        }
    }

    //вставка сразу в нужное место верс 1
    //void insert(string str)
    //{
    //    int hashcode = hashString(str);
    //    Node* current = this->hash_table[hashcode];
    //    Node* new_el = new Node(str);
    //    if (current==nullptr)
    //    {
    //        this->hash_table[hashcode] = new_el;
    //        hash_table_size_el++;
    //        return;
    //    }
    //        if (current->data == str)
    //        {
    //            delete new_el;
    //            return;
    //        }
    //        Node* current_2 = current->next;
    //        while (current_2)
    //        {
    //            //if (current->data == str)
    //            //{
    //            //    delete new_el;
    //            //    return;
    //            //}
    //            //else
    //                if (current->data < str && str < current_2->data)
    //                {
    //                    current->next = new_el;
    //                    new_el->next = current_2;
    //                    hash_table_size_el++;
    //                    return;
    //                }
    //            current = current->next;
    //            current_2 = current_2->next;
    //        }
    //        current->next = new Node(str);
    //        hash_table_size_el++;
    //}

    void insert_after(Node* el, Node* before)
    {
        el->next = before->next;
        before->next = el;
    }

    bool insert_after(string value, Node* before, Node* after)
    {
        if (!before)
            return  value < after->data;
        if (!after)
            return before->data < value;
        return before->data < value&& value < after->data;
    }

    //вставка в нужное верс 2
    void insert_2(string str)
    {
        if (find(str))
        {
            return;
        }
        hash_table_size_el += 1;
        int hashcode = hashString(str);
        Node* current = this->hash_table[hashcode];
        Node* new_elem = new Node(str);
        Node* previous = nullptr;
        while (current)
        {
            if (insert_after(str, previous, current))
            {
                if (!previous)
                {
                    this->hash_table[hashcode] = new_elem;
                    new_elem->next = current;
                }
                else
                    insert_after(new_elem, previous);
                return;
            }
            previous = current;
            current = current->next;
        }
        if (!previous)
            this->hash_table[hashcode] = new_elem;
        else
            insert_after(new_elem, previous);
        return;
    }

    ////удаление верс 1
    //bool remove(string str)
    //{
    //    int hashcode = hashString(str);
    //    Node* current = this->hash_table[hashcode];
    //    if (current == nullptr)
    //    {
    //        return false;
    //    }
    //    else
    //    {
    //        if (current->data == str)
    //        {
    //            this->hash_table[hashcode] = current->next;
    //            delete current;
    //            hash_table_size_el--;
    //            return true;
    //        }
    //        else
    //        {
    //            Node* current_2 = current->next;
    //            while (current_2)
    //            {
    //                if (current_2->data == str)
    //                {
    //                    Node* del_el = current_2;
    //                    current = current_2->next;
    //                    delete del_el;
    //                    hash_table_size_el--;
    //                    return true;
    //                }
    //                else
    //                    if (current->data < str && str < current_2->data)
    //                    {
    //                        return false;
    //                    }
    //                current = current->next;
    //                current_2 = current_2->next;
    //            }
    //            return false;
    //        }
    //    }
    //}

    //удаление верс 2
    bool remove_2(string str)
    {
        if (!find(str))
        {
            return false;
        }
        hash_table_size_el--;
        int hashcode = hashString(str);
        Node* current = this->hash_table[hashcode];
        Node* previous = nullptr;
        while (current)
        {
            if (current->data == str)
            {
                if (!previous)
                {
                    this->hash_table[hashcode] = current->next;
                    delete current;
                }
                else
                    delete_after(previous);
                return true;
            }
            previous = current;
            current = current->next;
        }
    }

    void delete_after(Node* before)
    {
        Node* del_elem = before->next;
        before->next = del_elem->next;
        delete del_elem;
    }

    //поиск
    bool find(string str)
    {
        int hashcode = hashString(str);
        Node* current = this->hash_table[hashcode];
        while (current)
        {
            if (current->data == str)
                return true;
            current = current->next;
        }
        return false;
    }

    //деструктор
    ~HashTable()
    {
        for (int i = 0; i < copasaty; i++)
        {
            Node* current = this->hash_table[i];
            if (current)
            {
                while (current->next != nullptr)
                {
                    Node* del_el = current;
                    current = current->next;
                    delete del_el;
                }
                delete current;
                this->hash_table[i] = nullptr;
            }
        }
        delete[] hash_table;
        copasaty = 0;
        hash_table_size_el = 0;
    }

    //присваивание
    HashTable& operator = (const HashTable& A)
    {
        this->~HashTable();
        copasaty = A.copasaty;
        this->hash_table = new Node * [copasaty];
        for (int i = 0; i < copasaty; i++)
        {
            if (A.hash_table[i] == nullptr)
                this->hash_table[i] = nullptr;
            else
            {
                Node* current = A.hash_table[i];
                while (current)
                {
                    insert_2(current->data);
                    current = current->next;
                }
            }
        }
        return *this;
    }

    ////объединение верс_1
    //HashTable unification(const HashTable& A)
    //{
    //    HashTable rez(*this);
    //    for (int i = 0; i < copasaty; i++)
    //    {
    //        if (A.hash_table[i] == nullptr)
    //            rez.hash_table[i] = nullptr;
    //        else
    //        {
    //            Node* current = A.hash_table[i];
    //            while (current)
    //            {
    //                rez.insert_2(current->data);
    //                current = current->next;
    //            }
    //        }
    //    }
    //    return rez;
    //}

    //объединение верс_2
    HashTable unification_2(const HashTable& A)
    {
        HashTable rez(A.copasaty);
        for (int i = 0; i < copasaty; i++)
        {
            if (A.hash_table[i] != nullptr || this->hash_table[i] != nullptr)
            {
                Node* current = A.hash_table[i];
                Node* current_2 = this->hash_table[i];
                int n = 0;
                rez.hash_table[i] = SortedMerge(current, current_2, &n);
                rez.hash_table_size_el += n;
            }
            else
            {
                rez.hash_table[i] = nullptr;
            }
        }
        return rez;
    }

    void add_el_inlist(Node* tail, Node* a)
    {
        tail->next = new Node(a->data);
        tail = tail->next;
        a = a->next;
    }

    void copy_list(Node* tail, Node* a, int* n)
    {
        Node* q = a;
        while (q)
        {
            tail->next = new Node(q->data);
            tail = tail->next;
            q = q->next;
            (*n)++;
        }
    }

    Node* SortedMerge(Node* a, Node* b, int* n)
    {
        Node add_list("");
        Node* tail = &add_list;
        Node* aa = a;
        Node* bb = b;
        while (aa || bb)
        {
            if (!aa)
            {
                copy_list(tail, bb, n);
                break;
            }
            if (!bb)
            {
                copy_list(tail, aa, n);
                break;
            }
            if (aa->data < bb->data)
                add_el_inlist(tail, aa);
            else
                if (aa->data > bb->data)
                    add_el_inlist(tail, bb);
                else
                {
                    add_el_inlist(tail, bb);
                    aa = aa->next;
                }
            (*n)++;
        }
        return add_list.next;
    }

    /*tail->next = new Node(bb->data);
tail = tail->next;
bb = bb->next;*/

//преобразование в массив
    string* to_array(int& n)
    {
        /*if (str_arr != nullptr)
            delete str_arr;   */
        n = hash_table_size_el;
        if (n == 0)
            return nullptr;
        else
        {
            string* rez = new string[n];
            for (int i = 0; i < n; i++)
                rez[i] = "";
            int k = 0;
            for (int i = 0; i < copasaty; i++)
            {
                if (hash_table[i] != nullptr)
                {
                    Node* current = hash_table[i];
                    while (current != nullptr)
                    {
                        rez[k] = current->data;
                        k++;
                        current = current->next;
                    }
                }
            }
            return rez;
        }
    }

    //кол-во эл-тов в таблице
    int get_hash_table_size()
    {
        return hash_table_size_el;
    }

    //печать
    void print_hash_table()
    {
        for (int i = 0; i < copasaty; i++)
        {
            if (hash_table[i] != nullptr)
            {
                Node* current = hash_table[i];
                while (current)
                {
                    cout << current->data << " , ";
                    current = current->next;
                }
            }
        }
    }
};

int main()
{
    HashTable A(3);

    string B = "name1";
    string C = "name2";
    A.insert_2(B);
    cout << A.find(B) << endl;
    HashTable D(A);
    cout << D.find(B) << endl;
    D.insert_2(C);
    cout << A.find(C) << endl;
    cout << D.find(C) << endl;

    HashTable E = A.unification_2(D);
    cout << E.find(B) << endl;
    cout << E.find(C) << endl;
    cout << "size A -> " << A.get_hash_table_size() << "\n";
    cout << "size D -> " << D.get_hash_table_size() << "\n";
    cout << "size E -> " << E.get_hash_table_size() << "\n";
    D.insert_2(B);
    D.insert_2(B);
    D.insert_2(B);
    cout << "D -> " << "\n";
    D.print_hash_table();
    cout << "size D -> " << D.get_hash_table_size() << "\n";
    //string* arr;
    //string** ptr_arr = &arr;
    int n = 0;
    //cout << E.to_array(arr, n);

    cout << "E -> " << "\n";
    E.print_hash_table();
    cout << "size E -> " << E.get_hash_table_size() << "\n";
    string* arr = E.to_array(n);

    cout << "\nsize -> " << n << "\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << "\n";
    return 0;

}