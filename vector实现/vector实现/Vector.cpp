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
		// �����������_finsh == _eos �� ��
		if (_finish == _eos){
			size_t newC = capacity() == 0 ? 1 : 2 * capacity();
			reserve(newC);
		}
		// ���룬β��
		*_finish = val;
		// ����_size
		++_finish;
	}

	void reserve(size_t n){
		//ֻ��������
		if (n > capacity()){
			size_t oldSize = size();
			// ���ռ�
			T* tmp = new T[n];
			// ����
			// �����ǳ��������
			//memcpy(tmp, _start, sizeof(T)*size());

			// ���������T���͵ĸ�ֵ�����
			for (int i = 0; i < size(); i++){
				tmp[i] = _start[i];
			}
			//�ͷ�ԭ�пռ�
			delete[] _start; // �ͷſ�ֵ��Ҳ���ᱨ��

			// ��������
			// �ռ��ָ��

			// �˴����ֻ����_start�򲻶ԣ���Ϊ����֮��λ�û�ı䣬���Ա���Ҫ��_start,_finish���и��£�����size()Ҳ����
			_start = tmp;
			// �����ڵ�ǰ��һ��size(),��Ϊ��ʱ_finish��û�и��£�Ϊ�㣬ֻ�ܽ�ԭ����_size����������
			_finish = _start + oldSize;
			_eos = _start+n;
		}
	}

	// �����ű����Ĳ���
	// operator[] : �ɶ���д�ı���
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

	// ������
	// �ɶ���д
	typedef T* iterator;
	// ֻ��
	typedef const T* const_iterator;

	iterator begin(){
		//��һ��Ԫ�ص�λ��
		return _start;
	}
	iterator end(){
		//���һ��Ԫ�ص���һ��λ�ã�Ҳ�������һ��Ԫ�صĽ���λ��
		return _finish;
	}

	const_iterator begin() const{
		return _start;
	}

	const_iterator end() const{
		return _finish;
	}
	// valĬ��ֵ���������ͣ�0ֵ���Զ������ͣ������޲ι���
	void resize(size_t n, const T& val = T()){
		if (n > capacity()){
			reserve(n);
		}
		if (n > size()){
			while (_finish != _start + n){
				*_finish++ = val;
			}
		}
		// ����size
		_finish += n;
	}
	/*
		�����ʱ����ܻ����������ʧЧ����Ҫ���µ�����
	*/
	void insert(iterator pos, const T& val){
		if (pos >= _start && pos <= _finish){
			// �������,ע������֮��pos������ʧЧ
			if (_finish == _eos){
				// ���ݻᵼ�µ�����ʧЧ��������������ݣ����µ�����
				// ����ԭʼλ��,��ǰλ������ʼλ�õ�ƫ����
				size_t len = pos - _start;
				size_t newC = capacity() == 0 ? 1 : 2 * capacity();
				reserve(newC);
				// ����֮��pos��λ��Ӧ�÷����ı䣬�����޷��Ƚ�

				// ���µ�����
				pso = _start + len;
			}
			// �ƶ�Ԫ��
			iterator end = _finish;
			while (end > pos){ // ������pos�ͻ����Խ�����
				*end = *(end - 1);
				--end;
			}

			// ����
			*pos = val;
			// ����size
			++_finish;
		}
	}
	//ɾ��
	// ���ص�������ִ�е�ǰ��ɾ��Ԫ�ص���һ��Ԫ��λ��
	iterator erase(iterator pos){
		// ��֤��Ԫ��
		if (pos >= _start && pos < _finish){
			// �ƶ�Ԫ��
			// �˴���Ҫע��ɾ�� end() -1 λ���ϵ�Ԫ��ʱ���Խ��Ұָ�����
			iterator begin = pos+1;
			while (begin != _finish){
				*(begin-1) = *begin;
				++begin;
			}
			// ����size
			--_finish;
		}
		// �Է�ɾ����λ
		// ɾ��֮���ڵ�ǰλ�ã�����Ԫ���Ѿ������ı�
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

// ֻ���Ĳ���
template<class T>
void printVector(const Vector<T>& v){
	int i = 0;
	for (; i < v.size(); i++)
	{
		cout << v[i] << " ";
		// ���ɵ���ֻ����const����
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