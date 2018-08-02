
class BinaryHeap(object):
  def __init__(self, lst=[], isMin=True):
    self.heap = lst
    self.isMin = isMin
    self.__buildHeap__()

  # fixes a heap (assumes left and right children are proper heaps)
  def __heapify__(self, n):
    l, r, priority = self.left(n), self.right(n), None

    if self.isMin:
      if l is not None and self.heap[l] < self.heap[n]:
        priority = l
      else:
        priority = n
      if r is not None and self.heap[r] < self.heap[priority]:
        priority = r
    else:
      if l is not None and self.heap[l] > self.heap[n]:
        priority = l
      else:
        priority = n
      if r is not None and self.heap[r] > self.heap[priority]:
        priority = r

    if priority != n:
      self.__swap__(n, priority)
      self.__heapify__(priority)

  def __buildHeap__(self):
    for i in range((len(self.heap)-1)/2, -1, -1):
      self.__heapify__(i)

  def __swap__(self, a, b):
    temp = self.heap[a]
    self.heap[a] = self.heap[b]
    self.heap[b] = temp

  # bubbles up a node in a min heap
  def __fixMin__(self, n):
    while n != 0 and self.heap[self.parent(n)] > self.heap[n]:
        parent = self.parent(n)
        self.__swap__(parent, n)
        n = parent

  # bubbles up a node in a max heap
  def __fixMax__(self, n):
    while n != 0 and self.heap[self.parent(n)] < self.heap[n]:
      parent = self.parent(n)
      self.__swap__(parent, n)
      n = parent

  def printHeap(self, n=0, indents=0):
    for _ in range(indents):
      print "",
    print self.heap[n]
    l, r = self.left(n), self.right(n)
    if l is not None:
      self.printHeap(l, indents+1)
    if r is not None:
      self.printHeap(r, indents+1)

  def parent(self, i):
    return (i-1)/2 if len(self.heap) >= i else None

  def left(self, i):
    l = 2*i+1
    return l if len(self.heap) > l else None

  def right(self, i):
    r = 2*i+2
    return r if len(self.heap) > r else None

  def peek(self):
    try:
      return self.heap[0]
    except:
      return None

  def deleteRoot(self):
    try:
      root = self.heap[0]
      self.heap[0] = self.heap.pop()
      self.__heapify__(0)
      return root
    except:
      return None

  def insert(self, v):
    self.heap.append(v)
    n = len(self.heap)-1

    if self.isMin:
      self.__fixMin__(n)
    else:
      self.__fixMax__(n)

  def increaseKey(self, n, v):
    current = self.heap[n]

    if current < v:
      self.heap[n] = v
    else: return

    if self.isMin:
      self.__heapify__(n)
    else:
      self.__fixMax__(n)

  def decreaseKey(self, n, v):
    current = self.heap[n]

    if current > v:
      self.heap[n] = v
    else: return

    if self.isMin:
      self.__fixMin__(n)
    else:
      self.__heapify__(n)

class MinHeap(BinaryHeap):
  def __init__(self, lst=[]):
    BinaryHeap.__init__(self, lst)

class MaxHeap(BinaryHeap):
  def __init__(self, lst=[]):
    BinaryHeap.__init__(self, lst, isMin=False)
