
#include <iostream>
#include <array>
#include <tuple>

template<typename T>
void swap(T* a, T* b)
{
	auto temp = *a;
	*a = *b;
	*b = temp;
}

template<typename T, typename Compare> 
T setMedianPivotToMiddle(T* start, T* end, Compare compare) {
	auto a = start;
	auto b = (start + ((end - start) / 2));
	auto c = end;
	if ((compare(*a , *b) && compare(*b , *c)) || (compare(*c , *b) && compare(*b , *a)))
		return *b;
	else if ((compare(*b , *a) && compare(*a , *c)) || (compare(*c , *a) && compare(*a , *b)))
		swap(a, b);
	else
		swap(b, c);
	return *b;

}

template<typename T, typename Compare>
std::pair<T*,T*> partition(T* start, T* end, Compare compare) {
	auto pivot = setMedianPivotToMiddle(start,end,compare);
	auto left_it = start;
	auto right_it = end;
	while (left_it <= right_it) {
		while (compare(*left_it, pivot)) {
			left_it++;
		}
		while (compare(pivot, *right_it)) {
			right_it--;
		}
		if (left_it <= right_it) {
			swap(left_it, right_it);
			left_it++;
			right_it--;
		};
	}
	return std::make_pair(left_it, right_it);

}
template<typename T, typename Compare>
void insert_sort(T* start, T* end, Compare compare) {
	auto iterator = start;
	T* j, key;
	while (iterator <= end) {
		key = *iterator;
		j = iterator-1;
		while (j >= start && compare(key,*j)) {
			*(j + 1) = *j;
				j--;
		}
		*(j + 1) = key;
		iterator++;
	}
}

template<typename T, typename Compare>
void quick_sort(T* start, T* end, Compare compare) {
	if (end - start < 16) {
		insert_sort(start, end, compare);
		return;
	}

	T* right_start;
	T* left_end;

	while (start <= end) {
		std::tie(right_start, left_end) = partition(start, end, compare);
		if (left_end - start < end - right_start) {
			quick_sort(start, left_end, compare);
				start = right_start;
		}
		else {
			quick_sort(right_start, end, compare);
				end = left_end;
		}
	}

};


template<typename T>
bool comp(const T& a, const T& b);

