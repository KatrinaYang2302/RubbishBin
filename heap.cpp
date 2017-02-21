#include <iostream>
#include <stdio.h>
using namespace std;

template <class T>
class heap{
public:
	int capacity;
	int size;
	T *ele;
	inline int left(int i){return 2*i+1;}
	inline int right(int i){return 2*i+2;}
	inline int parent(int i){return (i-1)/2;}
	inline int pair(int i){

		//-1 if don't have pair, else return paired num
		if(i==0 || (i==size-1 && i%2)) return -1;
		return (i%2)?(i+1):(i-1);
	}
	T getMin();
	T extractMin();
	void push(T);
	bool empty();
	bool full();
	void print();
	heap(int capacity = 65536):capacity(capacity), size(0){
		ele = new T[capacity];
	}
	~heap(){
		delete [] ele;
	}
};

template <class T>
T heap<T>::getMin(){
	return ele[0];
}

template <class T>
bool heap<T>::empty(){
	return size==0;
}
template <class T>
bool heap<T>::full(){
	return size==capacity;
}

template <class T>
T heap<T>::extractMin(){
	//must ensure heap not empty. otherwise return value is not predictable
	//analogous for push
	if(empty()) return (T)NULL;
	int cur = size-1;
	T outer = ele[size-1];
	while(cur > 0){
		int paired = pair(cur);
		int prt = parent(cur);
		if(paired == -1){
			outer = ele[prt];
			ele[prt] = ele[cur];
			cur = prt;
		}
		else{
			if(outer > ele[paired]){
				T tmp = ele[paired];
				ele[paired] = outer;
				outer = tmp;
			}
			T newOuter = ele[prt];
			ele[prt] = outer;
			outer = newOuter;
			cur = prt;
		}
	}
	size--;
	return outer;
}

template <class T>
void heap<T>::push(T e){
	if(full()) return;
	size++;
	ele[size-1] = e;
	int cur = size-1;
	while(cur > 0){
		int prt = parent(cur);
		if(ele[cur] >= ele[prt]) break;
		T tmp = ele[cur];
		ele[cur] = ele[prt];
		ele[prt] = tmp;
		cur= prt;
	}
}

template <class T>
void heap<T>::print(){
	cout << "size: " << size << endl;
	for(int i = 0; i < size; i++) cout << ele[i] << " ";
	cout << endl;
}

int main() {
	heap<int> hp;
	int test[8] = {2, 2333, 23333, 233, 233333, 23, 23333333, 2333333};
	for(int i = 0; i < 8; i++){
		hp.push(test[i]);
		hp.print();
	}
	for(int i = 0; i < 8; i++){
		cout << hp.extractMin() << endl;
		hp.print();
	}
	return 0;
}
