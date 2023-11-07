#include "mathfonc.h"

int main(){
	fonctionHtml();
	char* data = getenv("QUERY_STRING");
	float a = 0, b= 0;
	char method[20];
	sscanf(data,"a=%f&b=%f&method=%s",&a,&b,method);
	if(a!=b || a!=0 && b!=0){
		fonctionresult(a,b,method);	
	}
	return 0;
}
