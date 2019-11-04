
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int N;


double qsort(double *Mas, int first, int last)
{
	double mid, buf;
	int f = first, l = last;
	mid = Mas[(l + f) / 2];
	while(f<l)
	{
		while (Mas[f] < mid) f++;
		while (Mas[l] > mid) l--;
		if (f<=l)
		{
			buf = Mas[f];
			Mas[f] = Mas[l];
			Mas[l] = buf;
			l--;
			f++;
		}
	}
	if (first < l) qsort(Mas, first, l);
	if (f < last) qsort(Mas, f, last);
	return 0;
}

void mergesort(double* Mas, int l, int r)
{
	if (l == r) return;
	int mid = (l + r) / 2;
	mergesort(Mas, l, mid);
	mergesort(Mas, mid + 1, r);
	int i = l;
	int j = mid + 1;
	double* tmp = (double*)malloc((r - l + 1) * sizeof(double));
	for (int step = 0; step < r - l + 1; step++) 
	{
		if ((j > r) || ((i <= mid) && (Mas[i] < Mas[j])))
		{
			tmp[step] = Mas[i];
			i++;
		}
		else
		{
			tmp[step] = Mas[j];
			j++;
		}
	}
	for (int s = 0; s < r - l + 1; s++)
		Mas[s + l] = tmp[s];
	free(tmp);
}




void halfsort(double* Mas)
{
	double* tmp = (double*)malloc(N / 2 * sizeof(double));
	double* tmp1 = (double*)malloc((N - N / 2) * sizeof(double));
	int i, j, k;
	k = 0;
	double x;
	int lsize = N / 2;
	int rsize = N - lsize;
	for (i = 0; i < lsize; i++)
	{
		x = Mas[i];
		j = i;
		while (j > 0 && tmp[j - 1] > x)
		{
			tmp[j] = tmp[j - 1];
			j--;
		}
		tmp[j] = x;
	}

	for (i = lsize; i < N; i++)
	{
		x = Mas[i];
		j = i - lsize;
		while (j > 0 && tmp1[j - 1] > x)
		{
			tmp1[j] = tmp1[j - 1];
			j--;
		}
		tmp1[j] = x;
	}

	i = j = 0;
	
	while ((i < rsize) && j < lsize)
	{


		if (tmp1[i] < tmp[j])
		{
			Mas[k] = tmp1[i];
			i++;
		}

		else
		{
			Mas[k] = tmp[j];
			j++;
		}
		k++;
	}	
	for (i; i < rsize; i++)
	{
		Mas[k] = tmp1[i];
		k++;
	}
	for (j; j < lsize; j++)
	{
		Mas[k] = tmp[j];
		k++;
	}
	
	free(tmp);
	free(tmp1);
}



double insertsort(double* Mas)
{
	int i, j;
	double x;
	for (i = 0; i < N; i++)
	{
		x = Mas[i];
		j = i;
		while (j > 0 & Mas[j-1] > x)
		{
			Mas[j] = Mas[j - 1];
			j--;
		}
		Mas[j] = x;
	}
	return 0;
}


int main()
{
	int i;
	double time1;
	
	FILE* fp = fopen("results.txt", "wt");

	int aNs[] = { 5000, 10000, 15000 , 20000, 25000, 50000, 100000, 200000, 250000, 300000, 400000};

	for (int nstep = 0; nstep < sizeof(aNs) /sizeof(aNs[0]); nstep++)
	{
		N = aNs[nstep];
		double* mas = (double*)malloc(N * sizeof(double));
		double* old = (double*)malloc(N * sizeof(double));
		printf("%d\n", N);
		
		for (i = 0; i < N; i++) //gererating//
		{
			mas[i] = (double)rand() / RAND_MAX;
		}

		//for (i = 0; i < N; i++) //printf generated array//
		//{
		//	printf("%lf ", mas[i]);
		//}

		//printf("\n");
		time1 = double(clock()) / CLOCKS_PER_SEC;
		//printf("%lf\n", time1);

		for (int step = 0; step < N; step++)
			old[step] = mas[step];
		insertsort(mas);                          // insertsort
		//for (i = N/2; i < N/2+10; i++) 
			//{
			//	printf("%lf ", mas[i]);
		//	}
		//printf("\n");
		double t1 = double(clock()) / CLOCKS_PER_SEC - time1;
		printf("%lf\n", t1);

		for (int step = 0; step < N; step++)
			mas[step] = old[step];
		time1 = double(clock()) / CLOCKS_PER_SEC;
		halfsort(mas);                         //splitted insertsort
		//for (i = 0; i < N; i++) 
		//{
		//	printf("%lf ", mas[i]);
		//}
		//printf("\n");
		double t2 = double(clock()) / CLOCKS_PER_SEC - time1;
		printf("%lf\n", t2);


		for (int step = 0; step < N; step++)
			mas[step] = old[step];
		time1 = double(clock()) / CLOCKS_PER_SEC;
		mergesort(mas, 0, N - 1);                       //mergesort
		//for (i = N/2; i < N/2+10; i++) 
		//{
		//	printf("%lf ", mas[i]);
		//}
		//printf("\n");
		double t3 = double(clock()) / CLOCKS_PER_SEC - time1;
		printf("%lf\n", t3);

		fprintf(fp, "%d\t%lf\t%lf\t%lf\n", N, t1, t2, t3);

		free(old);
		free(mas);
	}

	fclose(fp);


	return 0;
}