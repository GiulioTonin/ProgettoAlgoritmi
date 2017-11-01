#include <fstream>

using namespace std;

// Funzioni per l'ordinamento di un vettore di interi
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

int main()
{
	int N;
	
	/* Leggo da file e mi istanzio i vettori:
	 * 
	 * inizi contiene i valori di inizio dei vari intervalli
	 * fini contiene i valori di fine dei vari intervalli
	 */
	ifstream in("input.txt");
	
	in >> N;
	
	int inizi[N], fini[N], max = 0;
	
	for(int i = 0; i < N; i++)
	{
		in >> inizi[i];
		in >> fini[i];
	}
	
	// Ordino i vettori in ordine crescente
    mergeSort(inizi, 0, N - 1);
    mergeSort(fini, 0, N - 1);
    
	int maxVuotoI = 0, maxVuotoF = 0;
    
    /* Ogni vuoto è un intervallo con i seguenti estremi:
     * 
     * Estremo sinistro: la fine di un intervallo i
     * Estremo destro: l'inizio di un intervallo j
     */
    for(int i = 0; i < N - 1; i++)
    {
		/* NB1: j, affinchè l'intervallo abbia valore
		 * 		  di inizio maggiore della fine i, deve
		 * 		  essere almeno in posizione i + 1 nel
		 * 		  vettore ordinato degli inizi; infatti
		 * 		  la fine di un intervallo k non può
		 * 		  precedere l'inizio di k.
		 */
		int j = i + 1;
		
		/* NB2: Potrebbero esserci intervalli che
		 *      iniziano durante l'intervallo i,
		 * 		  ovvero potrebbero esserci intervalli
		 * 		  k tali che inizio[i] < inizio[k] e 
		 * 		  inizio[k] < fine[i], ma questi non
		 * 		  mi interessano.
		 */
		while(inizi[j] < fini[i] && j < N)
			j++;
		
		/* NB3: Potrebbe essere che non ci siano intervalli
		 * 		  che iniziano dopo la fine di i.
		 * 		  Inoltre, potrebbe essere che un intervallo
		 * 		  finisca all'interno di questo presunto
		 * 		  vuoto, ed essendo il vettore delle fini
		 * 		  ordinato, mi basta controllare fine[i + 1];
		 * 		  infatti se fini[j + 1] < inizi[j] ho che il
		 * 		  vuoto non inizia da fine[i] ma da fine[k]
		 * 		  con k >= i + 1.
		 * 		  Infine, mi interessa soltanto se è un intervallo
		 * 		  più grande di quello che mi sono già salvato
		 * 		  come massimo temporaneo.
		 */
		if(j < N && fini[i + 1] > inizi[j] && max < inizi[j] - fini[i])
		{
			maxVuotoI = fini[i];
			maxVuotoF = inizi[j];
			max = inizi[j] - fini[i];
		}
	}
	
	// Scrivo su file gli estremi del massimo vuoto trovato
	ofstream out("output.txt");
	out << maxVuotoI << ' ' << maxVuotoF;
	
	return 0;
}
