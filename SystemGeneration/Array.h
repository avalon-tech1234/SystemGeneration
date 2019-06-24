#pragma once

class MyArray
{
public:
	

	template <class _T>
	static void AllocateArray(_T *** arr, int sz) {
		(*arr) = new _T*[sz];
		for (int i = 0; i < sz; i++) {
			(*arr)[i] = new _T[sz];
			memset((*arr)[i], 0, sizeof(_T) * sz);
		}
	};

	template <class _T>
	static void DestroyArray(_T ** arr, int sz) {
		for (int i = 0; i < sz; i++) {
			delete[] arr[i];
		}
	}

};