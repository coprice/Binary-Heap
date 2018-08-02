from binaryHeap import MinHeap, MaxHeap

print "\n--- TESTING MIN HEAP ---\n"

lst = [2,5,4,6,9,1,10]

print "creating heap from list: {}".format(lst)
heap = MinHeap(lst)
print "created heap is:"
heap.printHeap()

heap.insert(0)
print "Heap after inserting key 0:"
heap.printHeap()
print "peek is now {}".format(heap.peek())

root = heap.deleteRoot()
print "root ({}) removed. heap is now:".format(root)
heap.printHeap()

root = heap.peek()
heap.increaseKey(0, 100)
print "{} changed to 100. fixed heap is now:".format(root)
heap.printHeap()

last = heap.heap[(len(heap.heap)-1)]
heap.decreaseKey(len(heap.heap)-1, 0)
print "{} change to 0. fixed heap is now:".format(last)
heap.printHeap()

print "\n--- TESTING MAX HEAP ---\n"
lst = [2,5,4,6,9,1,10]

print "creating heap from list: {}".format(lst)
heap = MaxHeap(lst)
print "created heap is"
heap.printHeap()

heap.insert(42)
print "Heap after inserting key 42:"
heap.printHeap()
print "peek is now {}".format(heap.peek())

root = heap.deleteRoot()
print "root ({}) removed. heap is now {}".format(root, heap.heap)
heap.printHeap()

root = heap.peek()
heap.decreaseKey(0, 0)
print "{} changed to 0. fixed heap is now".format(root)
heap.printHeap()

last = heap.heap[(len(heap.heap)-1)]
heap.increaseKey(len(heap.heap)-1, 100)
print "{} change to 100. fixed heap is now:".format(last)
heap.printHeap()
