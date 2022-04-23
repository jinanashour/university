#include<iostream>
#include<vector>
#include<thread>
#include <ctime>
#include <climits> 
#include <cstdlib>
using namespace std;


void MergeSortedIntervals(vector<int>& v, int s, int m, int e);
void MergeSort(vector<int>& v, int s, int e);
int Partition(vector<int>& v, int start, int end);
void Quicksort(vector<int>& v, int start, int end);
void insertionSort(vector<int> data, int n);
void counting_sort(vector<int>& A, int R);

int main() {
	//getting the input from the user
	//getting sets size
	vector<int>inputSets(5);
	for (int i = 0; i < 5; i++) {
		cout << "Enter the size of set #" << i + 1;
		cin >> inputSets[i];
	}
	//getting sets content
	for (int i = 0; i < 5; i++) {
		vector<int>elements(inputSets[i]);
		srand(time(0));
		for (int j = 0; j < elements.size(); j++) {
			elements[j] = rand();
		}

		//merge sort
		float start_s1 = clock();
		thread mergeSort(MergeSort, elements, 0, elements.size());
		float stop_s1 = clock();
		cout << "time1 mergeSort: "
			<< (stop_s1 - start_s1) / double(CLOCKS_PER_SEC) * 1000 << endl;


		//insertion sort
		start_s1 = clock();
		thread insertionSort(insertionSort, elements, elements.size());
		stop_s1 = clock();
		cout << "time1 insertionSort : "
			<< (stop_s1 - start_s1) / double(CLOCKS_PER_SEC) * 1000 << endl;



		//quick sort
		start_s1 = clock();
		thread quickSort(Quicksort, elements, 0, elements.size());
		stop_s1 = clock();
		cout << "time1 quickSort: "
			<< (stop_s1 - start_s1) / double(CLOCKS_PER_SEC) * 1000 << endl;


		//counting sort
		start_s1 = clock();
		thread countingSort(counting_sort, elements, elements.size());
		stop_s1 = clock();
		cout << "time1 countingSort: "
			<< (stop_s1 - start_s1) / double(CLOCKS_PER_SEC) * 1000 << endl;

	}




	return 0;
}





void MergeSortedIntervals(vector<int>& v, int s, int m, int e) {

	// temp is used to temporary store the vector obtained by merging
	// elements from [s to m] and [m+1 to e] in v
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void MergeSort(vector<int>& v, int s, int e) {

	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}


int Partition(vector<int>& v, int start, int end) {

	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (v[i] < v[pivot]) {
			swap(v[i], v[j]);
			++j;
		}
	}
	swap(v[j], v[pivot]);
	return j;

}

void Quicksort(vector<int>& v, int start, int end) {

	if (start < end) {
		int p = Partition(v, start, end);
		Quicksort(v, start, p - 1);
		Quicksort(v, p + 1, end);
	}

}


void insertionSort(vector<int> data, int n)
{
	int i, j, tmp;

	for (i = 1; i < n; i++)
	{
		j = i;
		tmp = data[i];
		while (j > 0 && tmp < data[j - 1])
		{
			data[j] = data[j - 1];
			j--;
		}
		data[j] = tmp;
	}
}

void counting_sort(vector<int>& A, int R)
{

	vector <int> B;//create vector temps
	B.clear();// clear vectors before use
	vector <int> C;
	C.clear();
	int min = 0;
	int max = R;

	for (int i = 0; i < A.size(); i++)
		C[A[i]] = C[A[i]] + 1;

	for (int i = 1; i <= R; i++)
		C[i] = C[i] + C[i - 1];

	for (int i = A.size() - 1; i >= 0; i--)
	{
		B[C[A[i]] - 1] = A[i];
		C[A[i]] = C[A[i]] - 1;
	}

	for (int i = 0; i < A.size(); i++)
	{
		A[i] = B[i];
	}
}