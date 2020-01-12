#include <iostream>


template <typename T>
class Array final
{
	class Iterator
	{
		friend class Array<T>;
	public:
		Iterator(Array<T>& arr);
		const T& get() const;
		void set(const T& value);
		void insert(const T& value);
		void remove();
		void next();
		void prev();
		void toIndex(int index);
		bool hasNext() const;
		bool hasPrev() const;
	private:
		int index;
		Array<T>& arr;
	};
public:

	Array();
	Array(int capacity);
	~Array();
	void insert(const T& value);
	void insert(int index, const T& value);
	void remove(int index);
	int size();
	int capacity();
	const T& operator[](int index) const;
	T& operator[](int index);
	Iterator iterator() {
		Iterator iterator(*this);
		return iterator;
	}
	const Iterator iterator() const {
		Iterator iterator(*this);
		return iterator;
	}
	

private:
	int currentSize;
	int count;
	T* arr;
	void growSize();
};

template <typename T>
Array<T>::Array() {
	arr = new T[8];
	count = 0;
	currentSize = 8;
}
template <typename T>
Array<T>::Array(int capacity) {
	arr = new T[capacity];
	count = 0;
	currentSize = capacity;
}
template <typename T>
Array<T>::~Array() {
	delete arr;
}

template <typename T>
void Array<T>::insert(const T& value) {
	if (count == currentSize) {
		growSize();
	}

	arr[count] = value;
	count++;
}
template <typename T>
void Array<T>::insert(int index, const T& value) {
	if (index > count) {
		throw std::out_of_range("out of range insert");
	}
	if (count == currentSize) {
		growSize();
	}
	std::copy(arr + index, arr + count , arr + index+1);
	arr[index] = value;
	count++;
}
template <typename T>
void Array<T>::remove(int index) {
	if (index > currentSize) {
		throw std::out_of_range("out of range");
	}
	if (count > 0) {
		std::copy(arr + index+1, arr + count, arr + index);
		arr[count - 1] = 0;
		count--;
	}
}
template<typename T>
int Array<T>::size()
{
	return count;
}
template<typename T>
int Array<T>::capacity()
{
	return currentSize;
}
template <typename T>
T& Array<T>::operator[](int index) {
	
	if (index < 0 || index >= currentSize) {
		throw std::out_of_range("out of range []");
	}
	return arr[index];
}
template<typename T>
const T& Array<T>::operator[](int index) const
{
	if (index < 0 || index >= currentSize) {
		throw std::out_of_range("out of range []");
	}
	return arr[index];
}

template<typename T>
void Array<T>::growSize()
{
	T* temp = NULL;
	if (count == currentSize) {
		temp = new T[currentSize * 2];
		std::move(arr, arr+count, temp);
	}
	delete arr;
	arr = temp;
	currentSize = currentSize * 2;
}


template<typename T>
Array<T>::Iterator::Iterator(Array<T>& arr) : arr(arr)
{
	index = 0;
}

template<typename T>
const T& Array<T>::Iterator::get() const
{
	return arr[index];
}

template<typename T>
void Array<T>::Iterator::set(const T& value)
{
	arr[index] = value;
}

template<typename T>
void Array<T>::Iterator::insert(const T& value)
{
	arr.insert(index, value);
}

template<typename T>
void Array<T>::Iterator::remove()
{
	arr.remove(index);
}

template<typename T>
void Array<T>::Iterator::next()
{
	index++;
}

template<typename T>
void Array<T>::Iterator::prev()
{
	index--;
}

template<typename T>
void Array<T>::Iterator::toIndex(int index)
{
	this->index = index;
}

template<typename T>
bool Array<T>::Iterator::hasNext() const
{
	return index < arr.count - 1;
}

template<typename T>
bool Array<T>::Iterator::hasPrev() const
{
	return index >1;
}

