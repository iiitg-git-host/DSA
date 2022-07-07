#include <stdio.h>

int main(){
	char sent[500];
	printf("Enter the sentence:\n");
	scanf("%[^\n]%*c",sent);
	int n=0;
	int pos=1;
	int len=0;
	for (int i=0;i<499;i++){if(sent[i]==' '){
	if(pos%2==0 && len%2==1){
	int f=len/2;
	int first = i-1;
	int second=i-len;
	for(int j=0;j<f;j++){
	char temp=sent[first-j];
	sent[first-j]=sent[second+j];
	sent[second+j]=temp;}
		
}
	pos++;len=0;}else{len++;}
		
}	int i=0;
	
	printf("%s\n",sent);
	return 0;
	

}
