#include<stdlib.h>
#include<stdio.h>
#include <fstream>
#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int trovaIndice(int vec[], int num, int f,int dim){
    for(int i=0;i<dim;i++){
        if(i%2==f)if(vec[i]==num) return i;
        //cout<<i;
    }
}
int trovaIndice(int vec[], int num,int dim){
    for(int i=0;i<dim;i++){
        if(vec[i]==num) return i;
        //cout<<i;
    }
}

int main()
{
    int N;
    ifstream in("input.txt");
    ofstream out("output.txt");
    in>>N;
    int inizi[N];
    int fini[N];
    int vec[2*N];
    for(int i=0;i<N;i++){
        in>>inizi[i];
        in>>fini[i];
        vec[2*i+1]=fini[i];
        vec[2*i]=inizi[i];
    }
    mergeSort(inizi, 0, N - 1);
    mergeSort(fini, 0, N - 1);
    int inizio=inizi[0];
    int fine=inizi[0];
    int delta=0;
    int imax=inizio;
    int fmax=fine;
    for(int i=0;i<N;i++){
        int k=0;
        delta=0;
        int f=vec[trovaIndice(vec,fini[i],1,2*N)-1];
        int fi=vec[trovaIndice(vec,inizi[i],0,2*N)+1];
        while(f<fi){
            k++;
            if(i+k>=N) break;
            else f=vec[trovaIndice(vec,fini[i+k],1,2*N)-1];
        }
        inizio=fini[i+k-1];
        fine=f;
        delta=fine-inizio;
        if(delta<0) delta=0;
        if(delta>fmax-imax) {
            imax=inizio;
            fmax=fine;
        }
        //cout<<"inizio:"<<inizio<<"fine:"<<fine<<"i:"<<i<<"d:"<<delta<<'\n';
        i=trovaIndice(inizi,inizio,N);
        //cout<<i<<'\n';
        //trovaIndice(vec,fini[i],N)

    }
    if(delta==0) out<<0;
    else out<<inizio<<' '<<fine;
/*
    for(int i=0;i<2*N;i++){
        out<<vec[i]<<' ';
    }
*/
    return 0;
}
