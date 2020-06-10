#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <vector>
using namespace std;


template <class T>
class Vector{

public:
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _eos(nullptr)
	{	}

	size_t size() const{
		return _finish - _start;
	}

	size_t capacity() const{
		return _eos - _start;
	}

	void pushBack(const T& val){
		// 检查容量，当_finsh == _eos ， 满
		if (_finish == _eos){
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		// 插入，尾插
		*_finish = val;
		// 更新_size
		++_finish;
	}

	void reserve(size_t n){
		//只增加容量
		if (n > capacity()){
			size_t oldSize = size();
			// 开空间
			T* tmp = new T[n];
			// 拷贝
			// 会出现浅拷贝问题
			//memcpy(tmp, _start, sizeof(T)*size());

			// 深拷贝，调用T类型的赋值运算符
			for (int i = 0; i < size(); i++){
				tmp[i] = _start[i];
			}
			//释放原有空间
			delete[] _start; // 释放空值针也不会报错

			// 更新容量
			// 空间的指向

			// 此处如果只更新_start则不对，因为增容之后位置会改变，所以必须要对_start,_finish进行更新，否则size()也不对
			_start = tmp;
			// 不能在当前加一个size(),因为此时_finish还没有更新，为零，只能将原来的_size给保存下来
			_finish = _start + oldSize;
			_eos = _start+n;
		}
	}

	// 方括号遍历的操作
	// operator[] : 可读可写的遍历
	T& operator[](size_t pos){
		if (pos < size()){
			return _start[pos];
		}
	}

	const T& operator[](size_t pos) const{
		if (pos < size()){
			return _start[pos];
		}
	}

	// 迭代器
	// 可读可写
	typedef T* iterator;
	// 只读
	typedef const T* const_iterator;

	iterator begin(){
		//第一个元素的位置
		return _start;
	}
	iterator end(){
		//最后一个元素的下一个位置，也就是最后一个元素的结束位置
		return _finish;
	}

	const_iterator begin() const{
		return _start;
	}

	const_iterator end() const{
		return _finish;
	}
	// val默认值：内置类型：0值，自定义类型：调用无参构造
	void resize(size_t n, const T& val = T()){
		if (n > capacity()){
			reserve(n);
		}
		if (n > size()){
			while (_finish != _start + n){
				*_finish++ = val;
			}
		}
		// 更新size
		_finish += n;
	}
	/*
		插入的时候可能会产生迭代器失效，需要更新迭代器
	*/
	void insert(iterator pos, const T& val){
		if (pos >= _start && pos <= _finish){
			// 检查容量,注意增容之后pos迭代器失效
			if (_finish == _eos){
				// 增容会导致迭代器失效，如果发生了增容，更新迭代器
				// 保存原始位置,当前位置与起始位置的偏移量
				size_t len = pos - _start;
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				// 增容之后pos的位置应该发生改变，否则无法比较

				// 更新迭代器
				pso = _start + len;
			}
			// 移动元素
			iterator end = _finish;
			while (end > pos){ // 不更新pos就会产生越界操作
				*end = *(end - 1);
				--end;
			}

			// 插入
			*pos = val;
			// 更新size
			++_finish;
		}
	}
	//删除
	// 返回迭代器：执行当前被删除元素的下一个元素位置
	iterator erase(iterator pos){
		// 保证有元素
		if (pos >= _start && pos < _finish){
			// 移动元素
			// 此处需要注意删除 end() -1 位置上的元素时候测越界野指针错误
			iterator begin = pos+1;
			while (begin != _finish){
				*(begin-1) = *begin;
				++begin;
			}
			// 更新size
			--_finish;
		}
		// 以防删除错位
		// 删除之后还在当前位置，但是元素已经发生改变
		return pos;
	}
private:
	T* _start;
	T* _finish;
	T* _eos; // end of storage
};

void test(){
	Vector<int> v;
	Vector<char> vc;
	Vector<string> vs;

	size_t size = v.size();
}
template <class T>
void print(Vector<T> v){
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "size=" << v.size() << endl;
	cout << "cap=" << v.capacity() << endl;
}

// 只读的操作
template<class T>
void printVector(const Vector<T>& v){
	int i = 0;
	for (; i < v.size(); i++)
	{
		cout << v[i] << " ";
		// 不可调用只读，const类型
		//v[i] = 'a';
	}
	cout << endl;

	Vector<T>::const_iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test1(){
	Vector<int> vi;
	size_t size = vi.size();
	size_t cap = vi.capacity();
	print(vi);
	vi.pushBack(1);
	size = vi.size();
	cap = vi.capacity();
	print(vi);
	vi.pushBack(2);
	size = vi.size();
	cap = vi.capacity();
	print(vi);

	vi.pushBack(3);
	size = vi.size();
	print(vi);
	cap = vi.capacity();
	vi.pushBack(4);
	size = vi.size();
	print(vi);
	cap = vi.capacity();
	vi.pushBack(5);
	size = vi.size();
	print(vi);
	cap = vi.capacity();
	vi.pushBack(2);
	size = vi.size();
	print(vi);
	cap = vi.capacity();
	vi.pushBack(4);
	size = vi.size();
	print(vi);
	cap = vi.capacity();
}
void test2(){
	Vector<int> vi;// 1,2,3,4,5,6,7
		
	Vector<int>::iterator it = vi.begin();
	while (it != vi.end()){
		if (*it % 2 == 1){ // 
			it = vi.erase(it);
		}else
			++it;
	}
}
int main(void){
	test1();
	//test();
	cout << "end of process" << endl;
	while (1);
}