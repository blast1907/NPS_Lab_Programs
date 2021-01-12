#include<stdio.h>

int main()
{
	printf("Hamming Code for Error Detection and Correction(useful upto max 1 bit error)\n");
	int sent[8],recv[8];
	printf("Please Enter the four bit Data word in binary\n");
	scanf("%d %d %d %d",&sent[7],&sent[6],&sent[5],&sent[3]);
	sent[1] = sent[3] ^ sent[5] ^ sent[7];
	sent[2] = sent[3] ^ sent[6] ^ sent[7];
	sent[4] = sent[5] ^ sent[6] ^ sent[7];
	printf("Hamming Code for inputted 4 bit Data word is :");
	for(int i=7;i>=1;i--)
		printf("%d ",sent[i]);
	printf("\n");

	for(int i=7;i>=1;i--)
		scanf("%d",&recv[i]);

	recv[1] = recv[1] ^ recv[3] ^ recv[5] ^ recv[7];
	recv[2] = recv[2] ^ recv[3] ^ recv[6] ^ recv[7];
	recv[4] = recv[4] ^ recv[5] ^ recv[6] ^ recv[7];

	int ind=1*recv[1] + 2*recv[2] + 4*recv[4];

	if(ind==0){
		printf("No errors in transmission\n");
		printf("Data word is %d %d %d %d",recv[7],recv[6],recv[5],recv[3]);
	}
	else{
		printf("Error at %dth bit\n",ind);
		recv[ind] = (recv[ind]+1)%2;
		printf("Data word is %d %d %d %d\n",recv[7],recv[6],recv[5],recv[3]);
	}






	return 0;
}
