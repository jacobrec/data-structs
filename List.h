#ifndef _JACOB_LIST_H_
#define  _JACOB_LIST_H_

#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <time.h>

template <class T>
class List {
private:
    int  length;
    int  size;
    T *  array;
    bool sorted;

    void resize(int amount) {
        length += amount;
        if (length == size || (length < size / 5, amount < 0)) {
            array = (T *)realloc(array, (length * 2 + 1) * sizeof(T));
            size  = length * 2 + 1;
        }
        sorted = false;
    }

    int binarySearch(T item) {
        int left  = 0;
        int right = length - 1;
        int mid;

        while (left <= right) {
            mid = (left + right) / 2;
            if (array[mid] < item) {
                left = mid + 1;
            }
            else if (array[mid] > item) {
                right = mid - 1;
            }
            else{
                return(mid);
            }
        }
        return(-1);
    }

    void quickSort(int left, int right) {
        int i = left, j = right;
        int tmp;
        int pivot = array[(left + right) / 2];


        while (i <= j) {
            while (array[i] < pivot) {
                i++;
            }
            while (array[j] > pivot) {
                j--;
            }
            if (i <= j) {
                swap(i, j);
                i++;
                j--;
            }
        }


        if (left < j) {
            quickSort(left, j);
        }

        if (i < right) {
            quickSort(i, right);
        }
    }

    unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
        //http://burtleburtle.net/bob/hash/doobs.html
        a = a - b;  a = a - c;  a = a ^ (c >> 13);
        b = b - c;  b = b - a;  b = b ^ (a << 8);
        c = c - a;  c = c - b;  c = c ^ (b >> 13);
        a = a - b;  a = a - c;  a = a ^ (c >> 12);
        b = b - c;  b = b - a;  b = b ^ (a << 16);
        c = c - a;  c = c - b;  c = c ^ (b >> 5);
        a = a - b;  a = a - c;  a = a ^ (c >> 3);
        b = b - c;  b = b - a;  b = b ^ (a << 10);
        c = c - a;  c = c - b;  c = c ^ (b >> 15);
        return(c);
    }

public:
    int getLength() const {
        return(length);
    }

    void init(int num) {
        array = (T *)realloc(array, num * sizeof(T));
    }

    List() {
        array  = (T *)calloc(5, sizeof(T));
        size   = 5;
        length = 0;
        sorted = false;
    }

    void add(T item) {
        array[length] = item;
        resize(1);
    }

    void insert(T item, int index) {
        assert(index <= length);
        for (int i = length; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = item;
        resize(1);
    }

    T remove(int index) {
        assert(index < length);
        T temp = array[index];
        for (int i = index; i < length; i++) {
            array[i] = array[i + 1];
        }
        resize(-1);
        return(temp);
    }

    T pop() {
        assert(length > 0);
        resize(-1);
        return(array[length]);
    }

    int indexOf(T item) {
        if (sorted) {
            return(binarySearch(item));
        }
        else{
            for (int i = 0; i < length; i++) {
                if (array[i] == item) {
                    return(i);
                }
            }
            return(-1);
        }
    }

    void swap(int indexA, int indexB) {
        int temp = array[indexA];

        array[indexA] = array[indexB];
        array[indexB] = temp;
    }

    void sort() {
        sorted = true;
        this->quickSort(0, length - 1);
    }

    void shuffle() {
        sorted = false;
        srand(mix(clock(), time(NULL), clock()));
        for (int i = length - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(i, j);
        }
    }

    void reverse() {
        sorted = false;
        for (int i = 0; i < length / 2; i++) {
            swap(i, length - 1 - i);
        }
    }

    List <T> getFrom(int inclusive, int exclusive) {
        List <T> newlist;
        newlist.init(exclusive - inclusive);
        for (int i = inclusive; i < exclusive; i++) {
            newlist.length++;
            newlist[i - inclusive] = array[i];
        }

        return(newlist);
    }

    T& operator[](const int index) const {
        assert(index < length);
        return(array[index]);
    }

    List <T> operator[](const char *s) {
        int left  = 0;
        int right = 0;
        int colon = 0;

        char *leftstr  = (char *)malloc(10);
        char *rightstr = (char *)malloc(10);
        bool  isRight  = false;
        char *inp      = (char *)s;


        while (true) {
            char c = inp[left + right + colon];

            if (c == '\0') {
                break;
            }
            else if (c == ':') {
                colon++;
                isRight = true;
            }
            else{
                if (isRight) {
                    rightstr[right++] = c;
                }
                else{
                    leftstr[left++] = c;
                }
            }
        }
        left  = atoi(leftstr);
        right = atoi(rightstr);
        if (right < 0) {
            right += length + 1;
        }
        if (left < 0) {
            left += length + 1;
        }

        return(getFrom(left, right));
    }

    List <T>& operator+=(const List <T> other) {
        for (int i = 0; i < other.getLength(); i++) {
            this->add(other[i]);
        }
        return(*this);
    }

    List <T>& operator+=(const T other) {
        this->add(other);
        return(*this);
    }

    friend List <T> operator+(const List <T> lhs, const List <T> rhs) {
        List <T> newlist;
        newlist.init(lhs.getLength() + rhs.getLength());
        for (int j = 0; j < lhs.getLength(); j++) {
            newlist.length++;
            newlist[j] = lhs[j];
        }
        for (int j = 0; j < rhs.getLength(); j++) {
            newlist.length++;
            newlist[j + lhs.getLength()] = rhs[j];
        }
        return(newlist);
    }

    bool operator==(const List <T>& rhs) {
        if (this->getLength() != rhs.getLength()) {
            return(false);
        }
        for (int i = 0; i < this->getLength(); i++) {
            if (rhs[i] != (*this)[i]) {
                return(false);
            }
        }
        return(true);
    }

    bool operator!=(const List <T>& rhs) {
        return(!(*this == rhs));
    }
};

#endif
