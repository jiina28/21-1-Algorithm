#include <iostream>
#include <string.h>

#define MAX_SIZE 30
using namespace std;

char printMenu();

typedef struct Heap {
    char name[10];
    float score;
}Heap;

class Myqueue {
public:
    int count;  //size (role of index)
    void insertQueue(Heap *heap);       //insert element in priority queue
    void deleteQueue(Heap *heap);       //delete root
    void decreaseKey(Heap *heap);       //decrease element key
    void printQueue(Heap *heap);        //print all of elements in priority queue
    void minHeapify(Heap *heap, int index);     //keep shape of min heap and heapify
};

int main() {
    Myqueue myqueue;
    Heap heap[MAX_SIZE];
    char menu_char;     //selected menu
    myqueue.count = 1;      //the first element index is 1

    while(1) { 
        menu_char = printMenu();
        if(menu_char == 'I')
            myqueue.insertQueue(heap);
        else if(menu_char == 'D')
            myqueue.deleteQueue(heap);
        else if(menu_char == 'C')
            myqueue.decreaseKey(heap);
        else if(menu_char ==  'P')
            myqueue.printQueue(heap);
        else        //if you select Q, then exit
        {
            cout << "Thank you for using this program..\nHave a good day :) Bye!\n";
            break;
        }
        
        if(myqueue.count > 3)       //if elements are more than 3, then do minHeapify()
            myqueue.minHeapify(heap, 1);
    }
    return 0;
}

void Myqueue :: insertQueue(Heap *heap) {
    cout << "Enter name of element > ";
    cin >> heap[count].name;
    if(count>30)        //is_full check
        cout << "There are no spaces in heap!!\n";
    do {
        if(count>30)
            break;
        cout << "Enter key value of element > ";
        cin >> heap[count].score;
    }while(heap[count].score < 0.0 || heap[count].score > 100.0);   //if the key is not in boundary(0.0~100.0), then keep asking
    count++;

    cout << "New element [" << heap[count-1].name << ", " << heap[count-1].score << "] is inserted.\n\n\n";
}

void Myqueue :: deleteQueue(Heap *heap) {
    Heap to_delete = heap[1];       //move root element to temp
    if(!count)      //is_empty check
        cout << "nothing to delete!!\n";
    else {
        heap[1] = heap[count-1];        //move last element to root
        Heap last = heap[count--];      //decrease priority queue size
    }
    cout << "[" << to_delete.name << ", " << to_delete.score << "] is deleted\n\n\n";
}

void Myqueue :: decreaseKey(Heap *heap) {
    Heap temp;
    int index;
    float new_key;
    cout << "Enter index of element > ";
    cin >> index;
    int parent = index/2;       //parent index is (current(child) index / 2)
    do {
        cout << "Enter new key value > ";
        cin >> new_key;
    }while(new_key < 0.0 || new_key > 100.0);       //if the key is not in boundary(0.0~100.0), then keep asking
    if(heap[index].score < new_key) {       //if new key is bigger than the key of current index, then do not change key
        cout << "new key is bigger than current key\n";
    }
    else {
        heap[index].score = new_key;        //assign new key to key of current index in priority queue
        while(index>1 && heap[parent].score>heap[index].score) {    //if parent key is bigger than key of current index, then swap
            temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            index = parent;
        }
    }
}

void Myqueue :: printQueue(Heap *heap) {
    int i;
    for(i=1;i<count;i++) {
        printf("[%s, %.1f] ", heap[i].name, heap[i].score);
    }
    cout << "\n";
}

char printMenu() {
    const char *menu = "- * - * - * - * MENU - * - * - * - *\nI : Insert new element into queue.\nD : Delete element with smallest key from queue.\nC : Decrease key of element in queue.\nP : Print out all elements in queue.\nQ : Quit.\n";
    char menu_char;

    cout << menu << "\n";
    //if you enter wrong menu, keep asking
    do {
        cout << "Choose menu > ";
        cin >> menu_char;
        if(menu_char == 'I' || menu_char == 'D'|| menu_char == 'C' || menu_char == 'P' || menu_char == 'Q') {
            break;
        }
    } while(1);

    return menu_char;
}

void Myqueue::minHeapify(Heap *heap, int index) {
    Heap temp;
    int min = index;        //current index
    int left=0, right=0;
    left = index * 2;       //left child index
    right = index * 2 + 1;      //right child index

    if((left <= count) && (heap[left].score < heap[min].score)) {   //if the key of left child index is smaller than the key of current index, then make min index to left child index
        min = left;
    }
    if((right <= count) && (heap[right].score < heap[min].score)) {     //if the key of right child index is smaller than the key of current index, then make min index to right child index
        min = right;
    }
    if(min != index) {      //if current min index and current index that first came in as a argument are different, then swap
        temp = heap[min];
        heap[min] = heap[index];
        heap[index] = temp;

        minHeapify(heap, min);      //recursive minHeapify
    }
}