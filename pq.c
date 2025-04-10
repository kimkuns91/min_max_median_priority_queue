#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500001

int maxHeap[MAX_SIZE];  // 중앙값 이하 (루트는 최대값)
int minHeap[MAX_SIZE];  // 중앙값 초과 (루트는 최소값)
int maxSize = 0;
int minSize = 0;

int delete_min();
int delete_max();
int delete_median();
int find_min();
int find_max();
int find_median();

// ---------- Heap Functions ----------
void swap(int *a, int *b) {
    int temp = *a; *a = *b; *b = temp;
}

// Max-Heapify (Up and Down)
void max_heapify_up(int *heap, int index) {
    while (index > 1 && heap[index / 2] < heap[index]) {
        swap(&heap[index], &heap[index / 2]);
        index /= 2;
    }
}

void max_heapify_down(int *heap, int size, int index) {
    int largest = index;
    int left = 2 * index, right = 2 * index + 1;

    if (left <= size && heap[left] > heap[largest]) largest = left;
    if (right <= size && heap[right] > heap[largest]) largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        max_heapify_down(heap, size, largest);
    }
}

// Min-Heapify (Up and Down)
void min_heapify_up(int *heap, int index) {
    while (index > 1 && heap[index / 2] > heap[index]) {
        swap(&heap[index], &heap[index / 2]);
        index /= 2;
    }
}

void min_heapify_down(int *heap, int size, int index) {
    int smallest = index;
    int left = 2 * index, right = 2 * index + 1;

    if (left <= size && heap[left] < heap[smallest]) smallest = left;
    if (right <= size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        min_heapify_down(heap, size, smallest);
    }
}

// ---------- Core Operations ----------

void insert(int element) {
    // 첫 번째 요소이거나 중앙값보다 작은 경우 최대 힙에 삽입
    if (maxSize == 0 || element <= maxHeap[1]) {
        maxHeap[++maxSize] = element;
        max_heapify_up(maxHeap, maxSize);
    } else {
        // 중앙값보다 큰 경우 최소 힙에 삽입
        minHeap[++minSize] = element;
        min_heapify_up(minHeap, minSize);
    }

    // 힙 균형 맞추기
    if (maxSize > minSize + 1) {
        // 최대 힙에서 최소 힙으로 이동
        int move = maxHeap[1]; // 최대 힙의 루트(최대값)를 이동
        maxHeap[1] = maxHeap[maxSize--]; // 루트 제거
        max_heapify_down(maxHeap, maxSize, 1); // 힙 재구성
        
        minHeap[++minSize] = move; // 최소 힙에 추가
        min_heapify_up(minHeap, minSize); // 힙 재구성
    } 
    else if (minSize > maxSize) {
        // 최소 힙에서 최대 힙으로 이동
        int move = minHeap[1]; // 최소 힙의 루트(최소값)를 이동
        minHeap[1] = minHeap[minSize--]; // 루트 제거
        min_heapify_down(minHeap, minSize, 1); // 힙 재구성
        
        maxHeap[++maxSize] = move; // 최대 힙에 추가
        max_heapify_up(maxHeap, maxSize); // 힙 재구성
    }
}

int delete_min() {
    // 두 힙이 모두 비어있는 경우
    if (maxSize == 0 && minSize == 0) return -1;
    
    // 최소 힙이 비어있거나 최대 힙의 최소값이 최소 힙의 최소값보다 작은 경우
    if (minSize == 0 || (maxSize > 0 && maxHeap[maxSize] < minHeap[1])) {
        // 최대 힙에서 최소값 찾기 (힙의 마지막 요소)
        int result = maxHeap[maxSize];
        maxSize--;
        
        // 힙 균형 맞추기
        if (minSize > maxSize && minSize > 0) {
            int move = minHeap[1];
            minHeap[1] = minHeap[minSize--];
            if (minSize > 0) min_heapify_down(minHeap, minSize, 1);
            maxHeap[++maxSize] = move;
            max_heapify_up(maxHeap, maxSize);
        }
        
        return result;
    } else {
        // 최소 힙에서 최소값 찾기 (힙의 루트)
        int result = minHeap[1];
        minHeap[1] = minHeap[minSize--];
        if (minSize > 0) min_heapify_down(minHeap, minSize, 1);
        
        return result;
    }
}

int delete_max() {
    // 두 힙이 모두 비어있는 경우
    if (maxSize == 0 && minSize == 0) return -1;
    
    // 최대 힙이 비어있거나 최소 힙의 최대값이 최대 힙의 최대값보다 큰 경우
    if (maxSize == 0 || (minSize > 0 && minHeap[minSize] > maxHeap[1])) {
        // 최소 힙에서 최대값 찾기 (힙의 마지막 요소)
        int result = minHeap[minSize];
        minSize--;
        
        // 힙 균형 맞추기
        if (maxSize > minSize + 1 && maxSize > 0) {
            int move = maxHeap[1];
            maxHeap[1] = maxHeap[maxSize--];
            if (maxSize > 0) max_heapify_down(maxHeap, maxSize, 1);
            minHeap[++minSize] = move;
            min_heapify_up(minHeap, minSize);
        }
        
        return result;
    } else {
        // 최대 힙에서 최대값 찾기 (힙의 루트)
        int result = maxHeap[1];
        maxHeap[1] = maxHeap[maxSize--];
        if (maxSize > 0) max_heapify_down(maxHeap, maxSize, 1);
        
        return result;
    }
}

int delete_median() {
    if (maxSize == 0) return -1;

    int result = maxHeap[1];
    maxHeap[1] = maxHeap[maxSize--];
    max_heapify_down(maxHeap, maxSize, 1);
    return result;
}

int find_min() {
    // 두 힙이 모두 비어있는 경우
    if (maxSize == 0 && minSize == 0) return -1;
    
    // 최소 힙이 비어있으면 최대 힙에서 최소값 찾기
    if (minSize == 0) {
        // 최대 힙에서 가장 작은 값 찾기
        int min_val = maxHeap[1];
        for (int i = 2; i <= maxSize; i++) {
            if (maxHeap[i] < min_val) {
                min_val = maxHeap[i];
            }
        }
        return min_val;
    }
    
    // 최대 힙이 비어있으면 최소 힙에서 최소값 찾기
    if (maxSize == 0) {
        return minHeap[1]; // 최소 힙의 루트
    }
    
    // 최대 힙의 최소값 찾기
    int min_val_max = maxHeap[1];
    for (int i = 2; i <= maxSize; i++) {
        if (maxHeap[i] < min_val_max) {
            min_val_max = maxHeap[i];
        }
    }
    
    // 최소 힙의 최소값과 비교
    return (min_val_max < minHeap[1]) ? min_val_max : minHeap[1];
}

int find_max() {
    // 두 힙이 모두 비어있는 경우
    if (maxSize == 0 && minSize == 0) return -1;
    
    // 최대 힙이 비어있거나 최소 힙의 최대값이 최대 힙의 최대값보다 큰 경우
    if (maxSize == 0) {
        return minHeap[minSize]; // 최소 힙의 마지막 요소 (최대값)
    } else if (minSize == 0) {
        return maxHeap[1]; // 최대 힙의 루트 (최대값)
    } else {
        // 두 힙의 최대값 비교
        return (minHeap[minSize] > maxHeap[1]) ? minHeap[minSize] : maxHeap[1];
    }
}

int find_median() {
    // 두 힙이 모두 비어있는 경우
    if (maxSize == 0 && minSize == 0) return -1;
    
    // 중앙값은 항상 max heap의 루트에 있음
    if (maxSize > 0) {
        return maxHeap[1];
    } else {
        // max heap이 비어있으면 min heap의 루트가 중앙값
        return minHeap[1];
    }
}

// ---------- Main Function ----------
int main() {
    FILE *in = fopen("pq.in", "r");
    FILE *out = fopen("pq.out", "w");
    if (!in || !out) {
        fprintf(stderr, "File error\n");
        return 1;
    }

    int N;
    fscanf(in, "%d", &N);

    char cmd[5];
    int val;
    for (int i = 0; i < N; i++) {
        fscanf(in, "%s", cmd);
        if (strcmp(cmd, "I") == 0) {
            fscanf(in, "%d", &val);
            insert(val);
        } else if (strcmp(cmd, "D") == 0) {
            fscanf(in, "%s", cmd);
            if (cmd[0] == 'M') delete_min();
            else if (cmd[0] == 'X') delete_max();
            else delete_median();
        } else if (strcmp(cmd, "F") == 0) {
            fscanf(in, "%s", cmd);
            int result = -1;
            if (cmd[0] == 'M') result = find_min();
            else if (cmd[0] == 'X') result = find_max();
            else result = find_median();

            if (result == -1)
                fprintf(out, "NULL\n");
            else
                fprintf(out, "%d\n", result);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
