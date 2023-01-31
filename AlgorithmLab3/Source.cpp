#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;


double get_execution_time(int (*function)(int * arr, int n), int * a, int N)
{

	int start_time = clock();
	function(a, N);
	int end_time = clock();
	
	double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	return execution_time;
}

void Swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}


int bubble_sort_count(int* arr, int n)
{
	int i, j;
	int countr = 0;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			countr++;
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);

			}
		}
	}
	return countr;
}

int interstion_sort_count(int* arr, int n)
{
	int i, key, j;
	int countr = 0;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		countr++;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
			if (j > -1)
			{
				countr++;
			}

		}
		arr[j + 1] = key;
	}
	return countr;
}

int selection_sort_count(int * arr, int n)
{
	int i, j, min_idx;
	int countr = 0;
	for ( i = 0; i < n-1; i++)
	{
		min_idx = i;
		for ( j = i+1; j < n; j++)
		{
			countr++;
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}
		if (min_idx != i)
		{
			Swap(&arr[min_idx], &arr[i]);
		}
	}
	return countr;
}

int heapify(int * arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int countr = 0;

	if (l < n)
	{
		countr++;
	}
	
	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n)
	{
		countr++;
	}
	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		Swap(&arr[i], &arr[largest]);

		countr = countr + heapify(arr, n, largest);
	}

	return countr;
}

int build_heap(int * arr, int n)
{
	int countr = 0;
	for (int i = n/2 - 1; i >= 0; i--)
	{
		countr = countr + heapify(arr, n, i);
	}
	return countr;
}

int heap_sort_count(int * arr, int n)
{
	int countr = 0;
	countr = build_heap(arr, n);

	for (int i = n-1; i >= 0; i--)
	{
		Swap(&arr[0], &arr[i]);
		countr = countr + heapify(arr, i, 0);
	}
	return countr;
}

void test_comparisons()
{
	cout << "test comparisons" << endl;
	cout << "Random Arrays" << endl;
	
	//random arrays
	int* hr[30];
	int* br[30];
	int* sr[30];
	int* inr[30];
	for (int i = 1; i < 31; i++)
	{
		
		hr[i-1] = new int[i];
		br[i-1] = new int[i];
		sr[i-1] = new int[i];
		inr[i - 1] = new int[i];
		for (int j = 0; j < i; j++)
		{
			hr[i - 1][j] = j;
			br[i - 1][j] = j;
			sr[i - 1][j] = j;
			inr[i - 1][j] = j;
		}
		for (int j = 0; j < i; j++)
		{
			int r = rand() % i;
			Swap(&hr[i - 1][j], &hr[i - 1][r]);
			Swap(&br[i - 1][j], &br[i - 1][r]);
			Swap(&sr[i - 1][j], &sr[i - 1][r]);
			Swap(&inr[i - 1][j], &inr[i - 1][r]);
		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile1("Comparisons Random Arrays.csv");

	for (int i = 0; i < 30; i++)
	{
		int h1 = heap_sort_count(hr[i], i + 1);
		int i1 = interstion_sort_count(inr[i], i + 1);
		int s1 = selection_sort_count(sr[i], i + 1);
		int b1 = bubble_sort_count(br[i], i + 1);
		cout << i + 1 << "       " << h1 << "               " << i1 << "                " << s1
			 << "               " << b1 << "     " << endl;
		outFile1 << i+1 << "," << h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	outFile1.close();
	for (int i = 0; i < 30; i++)
	{
		delete[] hr[i];
		delete[] br[i];
		delete[] sr[i];
		delete[] inr[i];
	}
	cout << endl << endl << endl;
	//sorted arrays
	cout << "Sorted Arrays" << endl;
	int* hs[30];
	int* bs[30];
	int* ss[30];
	int* ins[30];
	for (int i = 1; i < 31; i++)
	{
		hs[i - 1] = new int[i];
		bs[i - 1] = new int[i];
		ss[i - 1] = new int[i];
		ins[i - 1] = new int[i];
		for (int j = 0; j < i; j++)
		{
			hs[i - 1][j] = j;
			bs[i - 1][j] = j;
			ss[i - 1][j] = j;
			ins[i - 1][j] = j;
		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile2(" Comparisons Sorted Arrays.csv");
	for (int i = 0; i < 30; i++)
	{
		int h1 = heap_sort_count(hs[i], i + 1);
		int i1 = interstion_sort_count(ins[i], i + 1);
		int s1 = selection_sort_count(ss[i], i + 1);
		int b1 = bubble_sort_count(bs[i], i + 1);
		cout << i + 1 << "       " << h1 << "               " << i1 << "               " << s1 << "               " << b1 << "     " << endl;
		outFile2 << i+1 << "," <<h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	for (int i = 0; i < 30; i++)
	{
		delete[] hs[i];
		delete[] bs[i];
		delete[] ss[i];
		delete[] ins[i];

	}
	cout << endl << "Inversly sorted" << endl;
	//inversly sorted arrays
	int* hi[30];
	int* bi[30];
	int* si[30];
	int* ii[30];
	for (int i = 1; i < 31; i++)
	{
		hi[i - 1] = new int[i];
		bi[i - 1] = new int[i];
		si[i - 1] = new int[i];
		ii[i - 1] = new int[i];
		for (int j = i-1, k = 0; j >= 0; j--, k++)
		{
			hi[i - 1][k] = j;
			bi[i - 1][k] = j;
			si[i - 1][k] = j;
			ii[i - 1][k] = j;
		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile3("Comparisons Inveresely sorted.csv");
	for (int i = 0; i < 30; i++)
	{
		int h1 = heap_sort_count(hi[i], i + 1);
		int i1 = interstion_sort_count(ii[i], i + 1);
		int s1 = selection_sort_count(si[i], i + 1);
		int b1 = bubble_sort_count(bi[i], i + 1);
		cout << i + 1 << "       " << h1 << "               " << i1 << "               " << s1 << "               " << b1 << "     " << endl;
		outFile3 << i+1 << "," << h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	for (int i = 0; i < 30; i++)
	{
		delete[] hi[i];
		delete[] bi[i];
		delete[] si[i];
		delete[] ii[i];
	}
}

void test_time()
{
	int scaler = 1000;
	cout << "Test time" << endl;
	
	cout << "Random Arrays" << endl;
	//random arrays
	int* hr[30];
	int* br[30];
	int* sr[30];
	int* inr[30];
	for (int i = 1; i < 31; i++)
	{
		int new_size = i * scaler;
		hr[i - 1] = new int[new_size];
		br[i - 1] = new int[new_size];
		sr[i - 1] = new int[new_size];
		inr[i - 1] = new int[new_size];
		for (int j = 0; j < new_size; j++)
		{
			hr[i - 1][j] = j;
			br[i - 1][j] = j;
			sr[i - 1][j] = j;
			inr[i - 1][j] = rand() % new_size;
		}
		for (int j = 0; j < i; j++)
		{
			int r = rand() % i;
			Swap(&hr[i - 1][j], &hr[i - 1][r]);
			Swap(&br[i - 1][j], &br[i - 1][r]);
			Swap(&sr[i - 1][j], &sr[i - 1][r]);
			Swap(&inr[i - 1][j], &inr[i - 1][r]);


		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile1("Time - Random Arrays.csv");
	for (int i = 1; i <= 30; i++)
	{
		double h1 = get_execution_time(heap_sort_count, hr[i-1], i * scaler );
		double i1 = get_execution_time(interstion_sort_count, inr[i-1], i * scaler );
		double s1 = get_execution_time(selection_sort_count, sr[i-1], i * scaler );
		double b1 = get_execution_time(bubble_sort_count, br[i-1], i * scaler );
		cout << i*scaler << "       " << h1 << "               " << i1 << "                " << s1 << "               " << b1 << "     " << endl;
		outFile1 << i * scaler << "," << h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	cout << endl << endl << endl;
	for (int i = 0; i < 30; i++)
	{
		delete[] hr[i];
		delete[] br[i];
		delete[] sr[i];
		delete[] inr[i];

	}
	//sorted arrays
	cout << "Sorted Arrays" << endl;
	int* hs[30];
	int* bs[30];
	int* ss[30];
	int* ins[30];
	for (int i = 1; i < 31; i++)
	{
		int new_size = i * scaler;
		hs[i - 1] = new int[new_size];
		bs[i - 1] = new int[new_size];
		ss[i - 1] = new int[new_size];
		ins[i - 1] = new int[new_size];
		for (int j = 0; j < new_size; j++)
		{
			hs[i - 1][j] = j;
			bs[i - 1][j] = j;
			ss[i - 1][j] = j;
			ins[i - 1][j] = j;
		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile2("Time - Sorted Arrays.csv");
	for (int i = 1; i <= 30; i++)
	{
		double h1 = get_execution_time(heap_sort_count, hs[i-1], i * scaler );
		double i1 = get_execution_time(interstion_sort_count, ins[i-1], i * scaler );
		double s1 = get_execution_time(selection_sort_count, ss[i-1], i * scaler );
		double b1 = get_execution_time(bubble_sort_count, bs[i-1], i * scaler );
		cout << i * scaler  << "       " << h1 << "               " << i1 << "                " << s1 << "               " << b1 << "     " << endl;
		outFile2 << i * scaler << "," << h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	for (int i = 0; i < 30; i++)
	{
		delete[] hs[i];
		delete[] bs[i];
		delete[] ss[i];
		delete[] ins[i];

	}
	cout << endl << "Inversly sorted" << endl;
	//inversly sorted arrays
	int* hi[30];
	int* bi[30];
	int* si[30];
	int* ii[30];
	for (int i = 1; i < 31; i++)
	{
		int new_size = i * scaler;
		hi[i - 1] = new int[new_size];
		bi[i - 1] = new int[new_size];
		si[i - 1] = new int[new_size];
		ii[i - 1] = new int[new_size];
		for (int j = new_size - 1, k = 0; j >= 0; j--, k++)
		{
			hi[i - 1][k] = j;
			bi[i - 1][k] = j;
			si[i - 1][k] = j;
			ii[i - 1][k] = j;
		}
	}
	cout << "n" << "     " << "Heapsort" << "     " << "Insertion sort" << "      " << "selection sort" << "      " << "Bubble sort" << endl;
	ofstream outFile3("Time - Inversely sorted.csv");
	for (int i = 1; i <= 30; i++)
	{
		double h1 = get_execution_time(heap_sort_count, hi[i-1], i * scaler );
		double i1 = get_execution_time(interstion_sort_count, ii[i-1], i * scaler);
		double s1 = get_execution_time(selection_sort_count, si[i-1], i * scaler );
		double b1 = get_execution_time(bubble_sort_count, bi[i-1], i * scaler);
		cout << i * scaler  << "       " << h1 << "               " << i1 << "                " << s1 << "               " << b1 << "     " << endl;
		outFile3 << i * scaler  << "," << h1 << "," << i1 << "," << s1 << "," << b1 << endl;
	}
	for (int i = 0; i < 30; i++)
	{
		delete[] hi[i];
		delete[] bi[i];
		delete[] si[i];
		delete[] ii[i];
	}
}


int main()
{
	srand(time(0));
	test_comparisons();
	cout << endl << endl << endl;
	test_time();
	system("pause");
	return 0;
}