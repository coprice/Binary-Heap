#include <stdio.h>

#define DEFAULT_CAPACITY 8000000

class BinaryHeap {

    public:

    int *heap;
    int capacity;
    int size;
    bool is_min;

    BinaryHeap(int *arr, int sz, bool is_mn, int cap) {
        is_min = is_mn;
        capacity = cap;
        heap = new int[capacity];
        size = sz;
        for (int i = 0; i < size; i++) {
            heap[i] = arr[i];
        }
        build_heap();
    }

    int peek() {
        if (size > 0) {
            return heap[0];
        }
        printf("Heap is empty\n");
        return 0;
    }

    int delete_root() {
        if (size > 0) {
            int root = heap[0];
            heap[0] = heap[size-1];
            size--;
            heapify(0);
            return root;
        } else {
            printf("Heap is empty, cannot delete root\n");
            return 0;
        }
    }

    void insert(int v) {
        if (size == capacity) {
            printf("Heap exceeds maximum capacity\n");
            return;
        }

        heap[size] = v;
        size++;
        int i = size - 1;

        if (is_min) {
            fix_min(i);
        } else {
            fix_max(i);
        }
    }

    void increase_key(int i, int v) {
        int current = heap[i];

        if (current < v) {
            heap[i] = v;
        } else { return; }

        if (is_min) {
            heapify(i);
        } else {
            fix_max(i);
        }
    }

    void decrease_key(int i, int v) {
        int current = heap[i];

        if (current > v) {
            heap[i] = v;
        } else { return; }

        if (is_min) {
            fix_min(i);
        } else {
            heapify(i);
        }
    }

    void print_heap() {
        if (size > 0) {
            print_heap_rec(0, 0);
        }
    }

    private:

    // fixes a heap, assuming left and right children are proper heaps
    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int priority;

        if (is_min) {
            if (l != 0 && heap[l] < heap[i]) {
                priority = l;
            } else {
                priority = i;
            }

            if (r != 0 && heap[r] < heap[priority]) {
                priority = r;
            }
        } else {
            if (l != 0 && heap[l] > heap[i]) {
                priority = l;
            } else {
                priority = i;
            }

            if (r != 0 && heap[r] > heap[priority]) {
                priority = r;
            }
        }

        if (priority != i) {
            swap(i, priority);
            heapify(priority);
        }
    }

    void build_heap() {
        for (int i = (size-1)/2; i >= 0; i--) {
            heapify(i);
        }
    }

    // bubbles up a node in a min heap
    void fix_min(int i) {
        int p = parent(i);
        while (i != 0 && heap[p] > heap[i]) {
            swap(p, i);
            i = p;
            p = parent(i);
        }
    }

    // bubbles up a node in a max heap
    void fix_max(int i) {
        int p = parent(i);
        while (i != 0 && heap[p] < heap[i]) {
            swap(p, i);
            i = p;
            p = parent(i);
        }
    }

    void swap(int a, int b) {
        int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    int parent(int i) {
        if (size >= i) {
            return (i-1)/2;
        }
        return 0;
    }

    int left(int i) {
        int l = 2*i + 1;
        if (size > l) {
            return l;
        }
        return 0;
    }

    int right(int i) {
        int r = 2*i+2;
        if (size > r) {
            return r;
        }
        return 0;
    }

    void print_heap_rec(int i, int indents) {
        for (int x = 0; x < indents; x++) {
            printf(" ");
        }
        printf("%i\n", heap[i]);
        int l = left(i);
        int r = right(i);
        if (l != 0) {
            print_heap_rec(l, indents+1);
        }
        if (r != 0) {
            print_heap_rec(r, indents+1);
        }
    }
};

class MinHeap: public BinaryHeap {
    public:

    MinHeap(): BinaryHeap(NULL, 0, true, DEFAULT_CAPACITY) {}

    MinHeap(int cap): BinaryHeap(NULL, 0, true, cap) {}

    MinHeap(int *arr, int sz, int cap): BinaryHeap(arr, sz, true, cap) {}
};

class MaxHeap: public BinaryHeap {
    public:

    MaxHeap(): BinaryHeap(NULL, 0, false, DEFAULT_CAPACITY) {}

    MaxHeap(int cap): BinaryHeap(NULL, 0, false, cap) {}

    MaxHeap(int *arr, int sz, int cap): BinaryHeap(arr, sz, false, cap) {}
};

void print_array(int *arr, int size) {
    if (size == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%i]\n", arr[i]);
        } else {
            printf("%i, ", arr[i]);
        }
    }
}

int main() {

    printf("\n--- TESTING MIN HEAP ---\n\n");

    int arr[7] = {2,5,4,6,9,1,10};
    int size = 7;
    int capacity = 1000000;

    printf("creating heap from list: ");
    print_array(arr, size);
    MinHeap min_heap(arr, size, capacity);
    printf("created heap is:\n");
    min_heap.print_heap();

    min_heap.insert(0);
    printf("heap after inserting key 0:\n");
    min_heap.print_heap();

    printf("root (%i) removed. heap is now:\n", min_heap.delete_root());
    min_heap.print_heap();

    int root = min_heap.peek();
    min_heap.increase_key(0, 100);
    printf("%i change to 100. heap is now:\n", root);
    min_heap.print_heap();

    int last = min_heap.heap[min_heap.size-1];
    min_heap.decrease_key(min_heap.size-1, 0);
    printf("%i changed to 0. fixed heap is now:\n", last);
    min_heap.print_heap();

    printf("\n--- TESTING MAX HEAP ---\n\n");

    printf("creating heap from list: ");
    print_array(arr, size);
    MaxHeap max_heap(arr, size, capacity);
    printf("created heap is:\n");
    max_heap.print_heap();

    max_heap.insert(42);
    printf("Heap after inserting key 42:\n");
    max_heap.print_heap();
    printf("peek is now %i\n", max_heap.peek());

    printf("root (%i) removed. heap is now:\n", max_heap.delete_root());
    max_heap.print_heap();

    root = max_heap.peek();
    max_heap.decrease_key(0, 0);
    printf("%i change to 0. heap is now:\n", root);
    max_heap.print_heap();

    last = max_heap.heap[max_heap.size-1];
    max_heap.increase_key(max_heap.size-1, 100);
    printf("%i changed to 0. heap is now:\n", last);
    max_heap.print_heap();

    return 0;
}
