#include "mathfonc.h"

///Styles pour la mise en forme
void styles() {
    printf("<style>\n");
    printf("body { background-color: #333; color: #fff; font-family: Arial, sans-serif; }\n");
    printf("h1 { color: #ff6600; }\n");
    printf("form { border: 1px solid #777; background-color: #555; padding: 10px; }\n");
	printf("input,select{margin: 1vw;padding: 0.5vw;letter-spacing: 0.2vw;color: rgb(75, 71, 71);width: 20vw;outline: none;font-size: 1.0vw;}");
    printf("table { border-collapse: collapse; width: 100%%; }\n");
    printf("th, td { border: 1px solid #777; padding: 8px; text-align: center; }\n");
    printf("thead { background-color: #555; color: #ff6600; }\n");
    printf("</style>\n");
}

///Formulaire pour les données pour la resolution de la fonction
void fonctionHtml(){
	printf("content-type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
	printf("<html>");
		printf("<head>");
		    printf("<meta charset='UTF-8'>");
			printf("<title>Resolution</title>\n");
        	styles(); 
    		printf("</head>\n");
		printf("<body>");
			printf("<div><h1 align='center'>f(x)=1-log(x)</h1></div>"); 
			printf("<form action=\"http://localhost/cgi-bin/fonction.cgi\" method=\"get\">");
				printf("<input type=\"number\" step=\"0.0001\" name=\"a\" placeholder=\"de A\" required>");
				printf("<input type=\"number\" step=\"0.0001\" name=\"b\" placeholder=\"à B\" required>");	
				printf("<select name=\"method\">");
					printf("<option value=\"descartes\">Methode de Descarte</option>");
					printf("<option value=\"dicho\">Dichotomie</option>");
					printf("<option value=\"newton\">Methode de Newton</option>");
				printf("<input type='submit' value='Entrer'>");
			printf("</form><br>");
}

///Formulaire pour entrer les données pour l'intégrale
void integralHtml(){
	printf("content-type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
	printf("<html>");
		printf("<head>");
		    printf("<meta charset='UTF-8'>");
			printf("<title>Integrale</title>\n");
        	styles(); 
    		printf("</head>\n");
		printf("<body>");
			printf("<div><h1 align='center'>f(x)=log(x)-1</h1></div>"); 
			printf("<form action ='integrale.cgi' method='GET'>");
				printf("<input type=\"number\" step=\"0.0001\" name=\"a\" placeholder=\"de A\" required>");
				printf("<input type=\"number\" step=\"0.0001\" name=\"b\" placeholder=\"à B\" required>");
				printf("<input type=\"number\" step=\"0.0001\" name=\"eps\" placeholder=\"pour une incremenation de \"required>");
				printf("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='submit' value='Entrer'>");
			printf("</form><br>");
}

///Fonction à étudier
float fonction(float x){
	float y=(float)(-log(x) + 1);
	return y;
}
float fonc(float x){
	float y=(float)(((float)log(x))-1.0);
	return y;
}

/// Dichotomie
float dichotomie(float a,float b){
	float a1 = 0.0;
	while(fabs(fonction(a)-fonction(b)) > 0.00001){
		a1 = (a+b)/2;
		printf("<tr>\n");
		printf("<td>%f</td>\n",a);
		printf("<td>%f</td>\n",b);
		printf("<td>%f</td>\n",a1);
		printf("<td>%f</td>\n",fonction(a1));
		printf("</tr>\n");
		if(fonction(a)*fonction(a1) <= 0){
			b = a1;
		}
		else{
			a = a1;
		}
	}
	return a1;
}

/// Méthode sécante
float* coeff(float x1,float y1,float x2,float y2){
	float* c = malloc(2*sizeof(float));
	c[0] = (y1 - y2)/(x1 - x2);
 	c[1] = y1 - c[0]*x1;
 	return c;
}
float ptSecante(float a, float b){
	return (-b/a);
}
float ssecante(float a, float b){
	float tmp = 0.0;
	while(fabs(fonction(b)) > 0.00001 && a!=b){
 		float* c = coeff(a,fonction(a),b,fonction(b));
 		tmp = b;
		b = ptSecante(c[0],c[1]);
		printf("<tr>\n");
		printf("<td>%f</td>\n",a);
		printf("<td>%f</td>\n",tmp);
		printf("<td>%f</td>\n",b);
		printf("<td>%f</td>\n",fonction(b));
		printf("</tr>\n");
 	}
	return b;
}

/// Méthode tangente
float fprim(float xo){
	return -1/xo;
}
float pttangente(float xo){
	return (-fonction(xo)/fprim(xo)) + xo;
}
float stangente(float a){
	float tmp = 0.0;
	while(fabs(fonction(a)) > 0.00001){
		tmp = a;
		a = pttangente(a);
		printf("<tr>\n");
		printf("<td>%f</td>\n",tmp);
		printf("<td>%f</td>\n",a);
		printf("<td>%f</td>\n",fonction(a));
		printf("</tr>\n");
	}
	return a;
}

///Affichage des resulats de l'intégrale
void integraleresult(char* a, char* b, char* eps){
	float* integrT;
	float* integrR;
	int borne=0;
		
	integrT=integraleTrapeze(atof(a),atof(b),atof(eps),&borne);
	integrR=integraleRectangle(atof(a),atof(b),atof(eps));
			
	printf("<table>\n");
		printf("<thead >\n");
			printf("<th>ITERATION</th>\n");
			printf("<th>METHODE RECTANGLE</th>\n");
			printf("<th>METHODE TRAPEZE</th>\n");
		printf("</thead>\n");
		printf("<tbody>\n");
		for(int i=0;i<borne;i++){
			printf("<tr>");
			printf("<td>%d</td>\n",i);
			printf("<td>%f</td>\n",integrR[i]);
			printf("<td>%f</td>\n",integrT[i]);
			printf("</tr>");
		}		
		printf("</tbody>\n");
	printf("</table>\n");	
	printf("</body></html>");
}
///Affichage du résulat pour la resolution du fonction
void fonctionresult(float a,float b,char* method){
	if(fonction(a)*fonction(b) < 0){
		if(strcmp(method,"dicho")==0){
			printf("<table>\n");
				printf("<thead >\n");
					printf("<th>a</th>\n");
					printf("<th>b</th>\n");
					printf("<th>X1 :[a;b]</th>\n");
					printf("<th>f(X1)</th>\n");
				printf("</thead>\n");
				dichotomie(a,b);
			printf("</table>\n");
		}
		else if(strcmp(method,"newton")==0){
			printf("<table>\n");
				printf("<thead>\n");
					printf("<th>a</th>\n");
					printf("<th>Intersections de T(a)</th>\n");
					printf("<th>f(t)</th>\n");
				printf("</thead>\n");
				stangente(a);
			printf("</table>\n");
		}
		else if(strcmp(method,"descartes")==0){
			printf("<table>\n");
				printf("<thead>\n");
					printf("<th>a</th>\n");
					printf("<th>b</th>\n");
					printf("<th>Intersection de (ab)</th>\n");
					printf("<th>f(d)</th>\n");
			printf("</thead>\n");
			ssecante(a,b);
			printf("</table>\n");
		}
	}
	else {
		printf("<h1 id=\"pasSolution\">Pas de solution dans l'intervalle [%f ; %f]</h1>\n",a,b);
	}	
	printf("</body></html>");
}

/// Resolution de l'integrale
float* integraleTrapeze(float a,float b,float eps,int* bor){
	int borne= (int)( (float)((b-a)/eps) )+1;
	float* result=(float*)malloc(sizeof(float)*borne);
	float rep=0.0;
	int k=0;

	for(float i=a;i<b;i+=eps){
		if( fabs(fonc(i))>fabs(fonc(i+eps)) ){
			rep+=( fonc(i)*eps )-fabs( ((fonc(i)-fonc(i+eps))*eps)/2 );
		}
		else if( fabs(fonc(i))<=fabs(fonc(i+eps)) ){
			rep+=( fonc(i)*eps )+fabs( ((fonc(i)-fonc(i+eps))*eps)/2 );
		}
		result[k]=rep;
		k++;
	}
	*bor=k;
	return result;
}
float* integraleRectangle(float a,float b,float eps){
	int borne= (int)( (float)((b-a)/eps) )+1;
	float* result=(float*)malloc(sizeof(float)*borne);
	float rep=0.0;
	int k=0;

	for(float i=a;i<b;i+=eps){
		k++;
		rep+=( fonc(i)*eps );
		if( fabs(fonc(i))>fabs(fonc(i+eps)) ){
			rep-=( (fonc(i)-fonc(i+eps))*eps );
		}
		result[k]=rep;
	}
	return result;
}
