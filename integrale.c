#include "mathfonc.h"

int main(){
	integralHtml();
	char* data=getenv("QUERY_STRING");
	char a[100],b[100],eps[100];
	sscanf(data,"a=%[^&]&b=%[^&]&eps=%[^\n]\n",a,b,eps);
	if(strcmp(eps,"")!=0){
		integraleresult(a,b,eps);
	}
	return 0;
}
