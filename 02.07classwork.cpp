#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
#define MIN 0
#define MAX 100

template<typename T>
T** make2DArray(T **is, int sizei, int sizej);
template<typename T>
void printArray(T *ar, int size);
template<typename T>
void printArray(T **ar, int sizei, int sizej);
template<typename T>
void delete2DArray(T **ar, int sizei, int sizej);
template<typename T>
void fillArray(T *ar, int size);
template<typename T>
void fillArray(T **ar, int sizei, int sizej);
template<typename T>
T findMax(T *ar, int size);
template<typename T>
T findMax(T **ar, int sizei, int sizej);
template<typename T>
T findMin(T *ar, int size);
template<typename T>
T findMin(T **ar, int sizei, int sizej);
template<typename T>
void multiplyByMin(T **ar, int sizei, int sizej);
template<typename T>
void swap(T *p1, T *p2);
template<typename T>
void orderMainDiagonal(T **sq, int size);
template<typename T>
long long productNE(T **sq, int size);

int main() {
	srand(time(NULL));
	int **a { };
	a = make2DArray(a, 5, 5);
	fillArray(a, 5, 5);
	printArray(a, 5, 5);
	cout << findMax(a, 5, 5) << endl;
	//multiplyByMin(a, 5, 4);
	cout << productNE(a, 5) << endl;
	//orderMainDiagonal(a, 5);
	//printArray(a, 5, 5);
	//mainDiagonal(a, 5);
	delete2DArray(a, 5, 5);

	return 0;
}

//Создание массива
template<typename T>
T** make2DArray(T **is, int sizei, int sizej) {
	is = new T*[sizei];
	for (int i = 0; i < sizei; i++) {
		*(is + i) = new T[sizej];
	}
	return is;
}

//Вывод массива
template<typename T>
void printArray(T *ar, int size) {
	for (int i = 0; i < size; i++) {
		cout << *(ar + i) << " ";
	}
	cout << endl;
}

template<typename T>
void printArray(T **ar, int sizei, int sizej) {
	for (int i = 0; i < sizei; i++) {
		printArray(*(ar + i), sizej);
	}

}

//Удаление массива
template<typename T>
void delete2DArray(T **ar, int sizei, int sizej) {
	for (int i = 0; i < sizei; i++) {
		delete[] *(ar + i);
	}
	delete[] ar;
}

//Заполнение массива случайными числами
template<typename T>
void fillArray(T *ar, int size) {
	for (int i = 0; i < size; i++) {
		*(ar + i) = rand() / (double) RAND_MAX * (MAX - MIN);
	}
}

template<typename T>
void fillArray(T **ar, int sizei, int sizej) {
	for (int i = 0; i < sizei; i++) {
		fillArray(*(ar + i), sizej);
	}
}

//Нахождение максимума
template<typename T>
T findMax(T *ar, int size) {
	T max = *ar;
	for (int i = 1; i < size; i++)
		if (*(ar + i) > max)
			max = *(ar + i);
	return max;
}

template<typename T>
T findMax(T **ar, int sizei, int sizej) {
	T max = **ar;
	for (int i = 1; i < sizei; i++)
		if (findMax(*(ar + i), sizej) > max)
			max = findMax(*(ar + i), sizej);
	return max;
}

//Нахождение минимума
template<typename T>
T findMin(T *ar, int size) {
	T min = *ar;
	for (int i = 1; i < size; i++)
		if (*(ar + i) < min)
			min = *(ar + i);
	return min;
}

template<typename T>
T findMin(T **ar, int sizei, int sizej) {
	T min = **ar;
	for (int i = 1; i < sizei; i++)
		if (findMin(*(ar + i), sizej) < min)
			min = findMin(*(ar + i), sizej);
	return min;
}

/*
 * Создать динамические массивы, используя указатели. Дан
 * двумерный массив a, размером (n×m). Найти минимальный элемент в
 * каждой строке матрицы. Затем каждую строку матрицы умножить на
 * минимальный элемент строки.
 */
template<typename T>
void multiplyByMin(T **ar, int sizei, int sizej) {
	T m { };
	for (int i = 0; i < sizei; i++) {
		m = findMin(*(ar + i), sizej);
		for (int j = 0; j < sizej; j++) {
			ar[i][j] *= m;
		}
	}
}

/*
 * Дан двумерный массив a, размером (n×n)(или квадратная матрица а). Найти произведение
 * минимального и максимального элементов её главной диагонали.
 */
template<typename T>
void mainDiagonal(T **sq, int size) {
	T max { **sq }, min { **sq };
	for (int i = 0; i < size; i++) {
		if (sq[i][i] > max)
			max = sq[i][i];
		if (sq[i][i] < min)
			min = sq[i][i];
	}
	cout << "max == " << max << endl;
	cout << "min == " << min << endl;
	cout << "max * min == " << max * min << endl;
}

/*
 * Создать динамические массивы, используя указатели. Дан двумерный массив a, размером (n×n).
 * Упорядочить по возрастанию элементы главной диагонали
 */
template<typename T>
void swap(T *p1, T *p2) {
	T t { };
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

template<typename T>
void orderMainDiagonal(T **sq, int size) {
	bool sorted { 0 };
	while (!sorted) {
		sorted = 1;
		for (int i = 1; i < size; i++) {
			if (sq[i][i] < sq[i - 1][i - 1]) {
				swap(sq[i][i], sq[i - 1][i - 1]);
				sorted = 0;
			}
		}
	}
}

/*
 * Создать динамические массивы, используя указатели. Дан двумерный массив a, размером (n×n) (или квадратная матрица а).
 * Найти произведение элементов, расположенных в верхней треугольной матрице, расположенной выше побочной диагонали,
 * включая саму побочную диагональ.
 */
// К сожалению, результат даже в long long не всегда влезает
template<typename T>
long long productNE(T **sq, int size) {
	long long p { 1 };
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i + j <= size-1)
				p *= sq[i][j];
	return p;
}
