#include "../List.h"
#include <cstdio>
#include <cassert>


void testInsert() {
    List <char> i;
    i.insert('a', 0);
    i.insert('d', 1);
    i.insert('c', 1);
    i.insert('b', 1);
    i.insert('e', 4);

    for (int j = 0; j < i.getLength(); j++) {
        assert(i[j] == ('a' + j));
    }
}

void testAdd() {
    List <int> i;
    i.add(0);
    i.add(1);
    i.add(2);
    i.add(3);
    i.add(4);

    for (int j = 0; j < i.getLength(); j++) {
        assert(i[j] == (j));
    }
}

void testRemove() {
    List <char> i;
    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }
    i.remove(25); // z
    i.remove(20); // u
    i.remove(12); // m
    i.remove(0);  // a

    assert(i.getLength() == 22);


    for (int j = 0; j < i.getLength(); j++) {
        assert(i[j] != 'a');
        assert(i[j] != 'm');
        assert(i[j] != 'u');
        assert(i[j] != 'z');
    }
}

void testPop() {
    List <char> i;
    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }
    for (int j = i.getLength(); j > 0; j--) {
        i.pop();
    }
    assert(i.getLength() == 0);

    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }
    for (int j = 0; j < 5; j++) {
        i.pop();
    }
    for (int j = 0; j < i.getLength(); j++) {
        assert(i[j] < 'v');
    }
}

void testSort() {
    List <char> i;
    i.add('e');
    i.add('g');
    i.add('b');
    i.add('d');
    i.add('f');
    i.add('c');
    i.add('a');

    i.sort();

    for (int j = 0; j < i.getLength(); j++) {
        assert(('a' + j) == i[j]);
    }
}

void testShuffle() {
    List <char> i;
    for (char j = ' '; j <= 'z'; j++) { // adds almost 100 ascii characters in order
        i.add(j);
    }

    List <char> l;
    for (char j = ' '; j <= 'z'; j++) {
        l.add(j);
    }

    bool notallsame = false;

    i.shuffle();
    l.shuffle();


    for (int j = 0; j < i.getLength(); j++) {
        if (i[j] != l[j]) {
            notallsame = true;
        }
    }
    assert(notallsame);
    // the odds of these two arrays being the same after shuffleing is
    // 1/(100!) which is basically zero
}

void testSearch() {
    List <char> i;
    i.add('e');
    i.add('g');
    i.add('b');
    i.add('d');
    i.add('f');
    i.add('c');
    i.add('a');

    // tests the linear search
    assert(i.indexOf('a') == 6);
    assert(i.indexOf('b') == 2);
    assert(i.indexOf('c') == 5);
    assert(i.indexOf('d') == 3);
    assert(i.indexOf('e') == 0);
    assert(i.indexOf('f') == 4);
    assert(i.indexOf('g') == 1);


    i.sort();

    // tests the binary search
    assert(i.indexOf('a') == 0);
    assert(i.indexOf('b') == 1);
    assert(i.indexOf('c') == 2);
    assert(i.indexOf('d') == 3);
    assert(i.indexOf('e') == 4);
    assert(i.indexOf('f') == 5);
    assert(i.indexOf('g') == 6);
}

void testReverse() {
    List <char> i;
    List <char> l;
    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
        l.add(j);
    }

    i.reverse();

    for (int j = 0; j < i.getLength(); j++) {
        assert(i[j] == l[l.getLength() - 1 - j]);
    }
}

void testSlice() {
    List <char> i;
    List <char> l1;
    List <char> l2;
    List <char> l3;
    List <char> l4;
    List <char> l5;
    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }

    for (char j = 'a'; j <= ('a' + 9); j++) {
        l1.add(j);
    }
    for (char j = 'a'; j <= ('z'); j++) {
        l2.add(j);
    }
    for (char j = 'a'; j <= ('z'); j++) {
        l3.add(j);
    }
    for (char j = 'a'; j <= ('z'); j++) {
        l4.add(j);
    }
    for (char j = ('z' - 5); j <= ('z'); j++) {
        l5.add(j);
    }
}

void testAppend() {
    List<char> i;
    i += 'a';
    i += 'b';
    i += 'c';

    List<char> l1;
    for (char j = 'a'; j <= 'c'; j++) {
        l1.add(j);
    }

    assert(i == l1);

    i += 'd';
    i += 'e';
    i += 'f';

    List<char> l2;
    for (char j = 'd'; j <= 'f'; j++) {
        l2.add(j);
    }

    l1 += l2;

    assert(i == l1);

}

void testAddition() {
    List <char> i;
    List <char> l1;
    List <char> l2;

    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }

    for (char j = 'a'; j < 'n'; j++) {
        l1.add(j);
    }

    for (char j = 'n'; j <= 'z'; j++) {
        l2.add(j);
    }

    assert(i == (l1 + l2));
}

void testEqual() {
    List <char> i;
    for (char j = 'a'; j <= 'z'; j++) {
        i.add(j);
    }

    List <char> l;
    for (char j = 'a'; j <= 'z'; j++) {
        l.add(j);
    }
    assert(i == l);

    l[14] = '-';

    assert(i != l);
}

void testAssign(){
    List<char> i;
    i += 'a';
    i += 'b';
    i += 'c';
    // TODO Assignment in these forms
    //List<char> l('a','b','c');
    //List<char> l = {'a','b','c'};

    //assert(i == l);
}

void testList() {
    printf("--- Starting List Tests ---\n");


    printf("Insert Test\n");
    testInsert();
    printf("Add Test\n");
    testAdd();
    printf("Remove Test\n");
    testRemove();
    printf("Pop Test\n");
    testPop();

    printf("Sort Test\n");
    testSort();
    printf("Shuffle Test\n");
    testShuffle();
    printf("Reverse Test\n");
    testReverse();

    printf("Search Test\n");
    testSearch();


    printf("Equality Test\n");
    testEqual();
    printf("Slice Test\n");
    testSlice();
    printf("Append Test\n");
    testAppend();
    printf("Add Test\n");
    testAddition();
    // printf("Assignment Test");
    // testAssign();

    printf("--- Ending List Tests ---\n");
}
