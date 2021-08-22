# 堆

## 1. 数据结构

数组(从`0`开始)中下标为 `i` 的节点，对应的父结点、左子结点和右子结点如下：

```c
iParent(i) = (i - 1) / 2;
iLeftChild(i) = 2 * i + 1;
iRightChild(i) = 2 * i + 2;
```

假设节点 `i` 在第 `L` 层，第 `L` 层最后一个元素 `last(L)` 的下标为 $2^{L+1}-2$，令 `L` 层 `i` 节点后面有 `j` 个节点，有
$$i = 2^{L+1} - i - 2$$ $$iRightChild(i) = last(L+1)-2j = 2 * i + 2$$

## 2. 建堆

一种方法是从空堆开始，不断插入新值。更优的方法是：从最后一个非叶节点(最后一个节点的父节点) 开始，向下堆化。

简单证明：如果左子树和右子树都是堆，通过向下堆化可以使整棵树保持堆的性质。

## 3. 插入

插入到数组最后，然后 `up-heap`。

## 3. 删除

将最后元素与待删除元素交换，然后 `down-heap`。

## 4. 其他

* 稳定性
同选择排序一样，由于其中交换位置的操作，所以是不稳定的排序算法。

* 时间复杂度
堆排序的最优时间复杂度、平均时间复杂度、最坏时间复杂度均为$\mathbb{O}(n \log{n})$。

* 空间复杂度
而由于可以在输入数组上建立堆，所以是原地算法。

## 5. 参考代码

```c
void sift_down(int arr[], int start, int end) {
  // 建立父结点指标和子结点指标
  int dad = start;
  int son = dad * 2 + 1;
  while (son <= end) {  // 子结点指标在范围内才做比较
    if (son + 1 <= end && arr[son] < arr[son + 1])  // 先比较两个子结点大小，选择最大的
      son++;
    if (arr[dad] >= arr[son])  // 如果父结点比子结点大，代表调整完毕，直接跳出函数
      return;
    else {  // 否则交换父子内容，子结点再和孙结点比较
      swap(arr[dad], arr[son]);
      dad = son;
      son = dad * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // 从最后一个节点的父节点开始sift down以完成堆化(heapify)
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}
```
