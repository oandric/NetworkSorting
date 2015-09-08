#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <MaxCompilerRT.h>
#include <string.h>


#define ARRAY_SIZE 64			// Size of array to be sorted (N)
//#define STREAM_SIZE 1			// Number of arrays that are consecutively sent to CPU and Maxeler inside one cycle -defined later
#define CYCLES 1				// Number of sorting repeats on CPU and Maxeler (for statistics)
#define TESTS 1				// Number of tests with different stream sizes (max = 19)
#define DATA_BITS 16			// Bit length of data to be sorted
#define ALG_SEQ "QuickSort"		// Sequential algorithm present in tests
#define ALG_NETWORK "Bubble"	// Network algorithm present in tests
#define COMPARATOR 1			// ID of comparator used on Maxeler board

int izpis = 1;		// Shows results in terminal window

int simSeqCPU = 0;	// Run sequential sorting algorithm on CPU
int simNetCPU = 1;	// Run/Simulate network sorting algorithm on CPU
int simNetMAX = 1;	// Run/Simulate sequential sorting algorithm on Maxeler

int comp (const void * elem1, const void * elem2) {
    int f = *((uint16_t*)elem1);
    int s = *((uint16_t*)elem2);
    if (f > s) return -1;
    if (f < s) return 1;
    return 0;
}

unsigned long sec(struct timespec t1, struct timespec t2){
    return t2.tv_nsec>t1.tv_nsec?t2.tv_sec-t1.tv_sec:t2.tv_sec-t1.tv_sec-1;
}

unsigned long nsec(struct timespec t1, struct timespec t2){
    return t2.tv_nsec>t1.tv_nsec?t2.tv_nsec-t1.tv_nsec:t2.tv_nsec-t1.tv_nsec + 1000000000;
}



int main(int argc, char* argv[])
{
	char *device_name = (argc==2 ? argv[1] : NULL);
	max_maxfile_t* maxfile;
	max_device_handle_t* device;
	uint16_t *in_array;
	uint16_t *out_array;

	// Array to be sorted
	uint16_t a[]={87,35,77,74,121,65,99,14,28,92,42,21,46,127,98,27,65,114,44,65,121,7,99,36,119,57,35,15,98,111,22,65,65,7,95,99,39,21,9,85,60,52,18,107,89,109,65,64,127,114,117,13,66,46,126,80,64,41,83,64,29,83,44,45};

	// Stream sizes
	unsigned long streams[]={1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000,100000,200000,500000,1000000};

	uint16_t b[ARRAY_SIZE];
	uint16_t x[ARRAY_SIZE];
	uint16_t y[ARRAY_SIZE];

	unsigned long STREAM_SIZE;	// Number of arrays that are consecutively sent to CPU and Maxeler inside one cycle

	int i,j,k,m,n,p;
	int status = 0;

	struct timespec t1, t2, t3, t4, t5;

	unsigned long s = 0;
	unsigned long ns = 0;
	unsigned long s_cpu_seq[CYCLES];		// sorting time for sequential algorithm on CPU
	unsigned long ns_cpu_seq[CYCLES];
	unsigned long s_cpu_network[CYCLES];	// sorting time for network algorithm on CPU
	unsigned long ns_cpu_network[CYCLES];
	unsigned long s_maxeler[CYCLES];		// sorting time on Maxeler card
	unsigned long ns_maxeler[CYCLES];
	FILE *result;

	printf("Opening and configuring FPGA.\n");
	maxfile = max_maxfile_init_DramLoopback();
	device = max_open_device(maxfile, device_name);
	max_set_terminate_on_error(device);

	// Create a file for writing results
	char str[80];
	sprintf(str, "Result_%s_Bit%d_Comp%d_N%d_C%d.txt",ALG_NETWORK,DATA_BITS,COMPARATOR,ARRAY_SIZE,CYCLES);

	result = fopen(str,"w");


	for(p=0; p<TESTS; p++){
		STREAM_SIZE = streams[p];

	//====================================================================================================
	//	QuickSort
	//====================================================================================================

	if (simSeqCPU){

		printf("\nPocinje racunanje sekvenčnog sort algoritma na CPU:\n");


	//	clock_gettime(CLOCK_REALTIME, &t4);
		for(m=0 ; m<CYCLES ; m++){
			s = 0;
			ns = 0;
			for(n=0 ; n<STREAM_SIZE ; n++){

				for(i = 0; i < ARRAY_SIZE; i++) {
					b[i] = a[i];
				}

				clock_gettime(CLOCK_REALTIME, &t1);
				//===========================================================
				qsort (b, sizeof(b)/sizeof(*b), sizeof(*b), comp);
				//===========================================================
				clock_gettime(CLOCK_REALTIME, &t2);

				s = s + sec(t1, t2) + (ns + nsec(t1,t2)) / 1000000000;
				ns = (ns + nsec(t1,t2)) % 1000000000;
			}
			s_cpu_seq[m] = s;
			ns_cpu_seq[m] = ns;

		s = 0;
		ns = 0;
		}
		for(m=0 ; m<CYCLES ; m++){
			s = s + s_cpu_seq[m];
			ns = ns + ns_cpu_seq[m];
		}
		s = s + ns / 1000000000;
		ns = ns % 1000000000;


	//	clock_gettime(CLOCK_REALTIME, &t5);

	//	printf("\n\nObrada na CPU zavrsena.\nVrijeme obrade: %lu s, %lu ns \n\n", sec(t4, t5), nsec(t4,t5));
		printf("QuickSort na CPU zavrsen.\nVrijeme obrade: %lu s, %lu ns \n\n", s, ns);
		if (izpis){
			for(i = 0; i < ARRAY_SIZE; i++) {
					printf("[%d]\ta: %d\n", i, b[i]);
			}
		}
	}			// end if

	//====================================================================================================
	//	Bitonic Merge Network on CPU
	//====================================================================================================

	if (simNetCPU){

		printf("\nPocinje racunanje mrežnog sort algoritma na CPU:\n");

	//	clock_gettime(CLOCK_REALTIME, &t4);
		for(m=0 ; m<CYCLES ; m++){
			s = 0;
			ns = 0;
			for(n=0 ; n<STREAM_SIZE ; n++){

				for(i = 0; i < ARRAY_SIZE; i++) {
					x[i] = a[i];
				}

				clock_gettime(CLOCK_REALTIME, &t1);
				//===========================================================

				for (int j = 0; j <1; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 2; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <2; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 3; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <3; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 4; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <4; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 5; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <5; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 6; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <6; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 7; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <7; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 8; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <8; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 9; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <9; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 10; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <10; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 11; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <11; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 12; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <12; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 13; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <13; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 14; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <14; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 15; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <15; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 16; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <16; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 17; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <17; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 18; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <18; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 19; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <19; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 20; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <20; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 21; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <21; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 22; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <22; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 23; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <23; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 24; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <24; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 25; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <25; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 26; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <26; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 27; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <27; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 28; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <28; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 29; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <29; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 30; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <30; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 31; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <31; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 32; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <32; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 33; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <33; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 34; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <34; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 35; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <35; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 36; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <36; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 37; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <37; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 38; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <38; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 39; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <39; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 40; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <40; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 41; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <41; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 42; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <42; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 43; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <43; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 44; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <44; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 45; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <45; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 46; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <46; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 47; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <47; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 48; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <48; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 49; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <49; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 50; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <50; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 51; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <51; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 52; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <52; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 53; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <53; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 54; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <54; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 55; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <55; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 56; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <56; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 57; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <57; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 58; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <58; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 59; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <59; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 60; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <60; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 61; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <61; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 62; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <62; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 63; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <63; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 64; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <62; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 63; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <61; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 62; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <60; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 61; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <59; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 60; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <58; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 59; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <57; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 58; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <56; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 57; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <55; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 56; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <54; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 55; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <53; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 54; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <52; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 53; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <51; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 52; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <50; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 51; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <49; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 50; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <48; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 49; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <47; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 48; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <46; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 47; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <45; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 46; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <44; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 45; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <43; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 44; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <42; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 43; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <41; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 42; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <40; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 41; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <39; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 40; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <38; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 39; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <37; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 38; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <36; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 37; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <35; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 36; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <34; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 35; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <33; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 34; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <32; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 33; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <31; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 32; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <30; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 31; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <29; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 30; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <28; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 29; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <27; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 28; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <26; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 27; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <25; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 26; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <24; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 25; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <23; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 24; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <22; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 23; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <21; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 22; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <20; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 21; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <19; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 20; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <18; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 19; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <17; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 18; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <16; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 17; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <15; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 16; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <14; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 15; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <13; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 14; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <12; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 13; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <11; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 12; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <10; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 11; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <9; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 10; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <8; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 9; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <7; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 8; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <6; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 7; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <5; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 6; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <4; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 5; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <3; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 4; j < 64; j++){y[j]=x[j];}
				x[0]=y[0];
				for (int j = 1; j <2; j+=2){x[j]=y[j]>y[j+1]?y[j]:y[j+1];x[j+1]=y[j]>y[j+1]?y[j+1]:y[j];}
				for (int j = 3; j < 64; j++){x[j]=y[j];}
				for (int j = 0; j <1; j+=2){y[j]=x[j]>x[j+1]?x[j]:x[j+1];y[j+1]=x[j]>x[j+1]?x[j+1]:x[j];}
				for (int j = 2; j < 64; j++){y[j]=x[j];}

				//===========================================================
				clock_gettime(CLOCK_REALTIME, &t2);

				s = s + sec(t1, t2) + (ns + nsec(t1,t2)) / 1000000000;
				ns = (ns + nsec(t1,t2)) % 1000000000;
			}
			s_cpu_network[m] = s;
			ns_cpu_network[m] = ns;

		s = 0;
		ns = 0;
		}
		for(m=0 ; m<CYCLES ; m++){
			s = s + s_cpu_network[m];
			ns = ns + ns_cpu_network[m];
		}
		s = s + ns / 1000000000;
		ns = ns % 1000000000;


	//	clock_gettime(CLOCK_REALTIME, &t5);

	//	printf("\nObrada na CPU zavrsena.\nVrijeme obrade: %lu s, %lu ns \n\n", sec(t4, t5), nsec(t4,t5));
		printf("Bitonic Merge Network na CPU zavrsen.\nVrijeme obrade: %lu s, %lu ns \n\n", s, ns);
		if (izpis){
			for(i = 0; i < ARRAY_SIZE; i++) {
					printf("[%d]\ta: %d\n", i, y[i]);
			}
		}
	}			// end if


	//====================================================================================================
	//	Bitonic Merge Network on Maxeler
	//====================================================================================================

	if (simNetMAX){

		printf("Generating data to send to FPGA.\n");

		// To send the arrays to the FPGA we pack them together
		out_array = malloc(ARRAY_SIZE * STREAM_SIZE * sizeof(uint16_t));
		in_array = malloc(ARRAY_SIZE * STREAM_SIZE * sizeof(uint16_t));

		if(!in_array || !out_array) {
			fprintf(stderr, "Failed to allocate memory for data I/O.\n");
			return 1;
		}

		// Creating the stream of arrays to be sent to Maxeler
		for(i = 0; i < ARRAY_SIZE * STREAM_SIZE; i++) {
			out_array[i] = 0;
			in_array[i] = a[i % ARRAY_SIZE];
		}

		printf("\nStreaming data to/from FPGA.\n");
		printf("Pocinje racunanje mrežnog sort algoritma na MAX Kartici:\n");

		s = 0;
		ns = 0;
		//clock_gettime(CLOCK_REALTIME, &t4);

		for(k=0 ; k<CYCLES ; k++){

			clock_gettime(CLOCK_REALTIME, &t1);

			max_run(device,
			max_input("inX", in_array, ARRAY_SIZE * STREAM_SIZE * sizeof(uint16_t)),
			max_output("oData", out_array, ARRAY_SIZE * STREAM_SIZE * sizeof(uint16_t)),
			max_runfor("DramLoopbackKernel", STREAM_SIZE),
			max_end());

			clock_gettime(CLOCK_REALTIME, &t2);

			s_maxeler[k] = sec(t1, t2);
			ns_maxeler[k] = nsec(t1,t2);

			s = s + sec(t1, t2) + (ns + nsec(t1,t2)) / 1000000000;
			ns = (ns + nsec(t1,t2)) % 1000000000;


		}
		//clock_gettime(CLOCK_REALTIME, &t5);

		//printf("\nObrada na kartici zavrsena.\nVrijeme obrade: %lu s, %lu ns \n\n", sec(t4, t5), nsec(t4,t5));
		printf("\nObrada na kartici zavrsena.\nVrijeme obrade: %lu s, %lu ns \n", s, ns);
		printf("\nSTREAM SIZE: %lu \n\n", STREAM_SIZE);

		printf("Checking data read from FPGA.\n");

		if (izpis){
			for(i = 0; i < ARRAY_SIZE * STREAM_SIZE; i++) {
			printf("[%d]\tout_array: %d\n", i, out_array[i]);
			if(out_array[i]>out_array[i-1]){
			//				printf("PROBLEM!!!");
						}
			}
		}
	}			// end if

	//====================================================================================================
	// Writing the current test results to a file
	//====================================================================================================

		for(k=0 ; k<CYCLES ; k++){
			if (simSeqCPU){fprintf(result,"%s \t %u \t %u \t CPU \t %u \t %u \t %u \t %lu \t %lu \n",ALG_SEQ,DATA_BITS,COMPARATOR, ARRAY_SIZE,STREAM_SIZE,CYCLES, s_cpu_seq[k], ns_cpu_seq[k]);}
			if (simNetCPU){fprintf(result,"%s \t %u \t %u \t CPU \t %u \t %u \t %u \t %lu \t %lu \n",ALG_NETWORK,DATA_BITS,COMPARATOR, ARRAY_SIZE,STREAM_SIZE,CYCLES, s_cpu_network[k], ns_cpu_network[k]);}
			if (simNetMAX){fprintf(result,"%s \t %u \t %u \t MAX \t %u \t %u \t %u \t %lu \t %lu \n",ALG_NETWORK,DATA_BITS,COMPARATOR, ARRAY_SIZE,STREAM_SIZE,CYCLES, s_maxeler[k], ns_maxeler[k]);}
		}

	}

	// Close the file with results
	fclose(result);

	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");
	//}
	printf("Shutting down\n");
	max_close_device(device);
	max_destroy(maxfile);

	return status;

}
