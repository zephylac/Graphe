#include "Outil.h"
#include "Tp3.h"

char * sMOT;
int bTp3AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L3 = a^n.b^n avec n qui est un carre non nul
	L3' = a^n.b^n
Grammaire algebrique

	S -> K
	K -> T.U 
	T -> a.T.b 
	U -> a.b

Grammaire hommogene
 	S -> K
	K -> T.U 
	T -> A.T.B
	U -> A.B

Grammaire attributs
 
	S(n) -> K(n).(n est un carre)
	K(n) -> T(n) + U(n) 
	T(n+1) -> A.T(n).B
	U(1) -> A.B	
*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bK(int iDebut, int *piFin, int * paN);
int bT(int idebut, int *piFin, int * paN);
int bU(int idebut, int *piFin, int * paN);
int bS(int idebut, int *piFin, int * paN);

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp3INITIALISER",bTp3AmorceR);
}//Tp3INITIALISER

void Tp3TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	int paN;
	Assert1("Tp3Tester",bTp3AmorceR);
	switch (iTest) {
		case 1: sMOT="ab";break;
		case 2: sMOT="aabb";break;
		case 3: sMOT="aaabbb";break;
		case 4: sMOT="aaaabbbb";break;
		case 5: sMOT="abbaa";break;
		case 6: sMOT="aaabbbaaa";break;
		case 7: sMOT="abbaba";break;
		case 8: sMOT="aabbaba";break;
		case 9: sMOT="bababbaba";break;
		case 10: sMOT="";break;
		default: Assert1("Tp3TESTER default",0);
	}
	bSucces = bS(0,&iFin,&paN);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;

	printf("%s : %s %s engendre par la grammaire decrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT),sEst(bEngendre));

}//Tp3TESTER	

int estUnCarre(int n){
	return((int)sqrt(n) == sqrt(n));
}

int bA(int iDebut, int *piFin){
	// A -> a
	int bSucces = sMOT[iDebut] == 'a';
	*piFin = (bSucces) ? iDebut+1 : iDebut;
	return(bSucces);
}

int bB(int iDebut, int *piFin){
	// B -> b
	int bSucces = sMOT[iDebut] == 'b';
	*piFin = (bSucces) ? iDebut+1 : iDebut;
	return(bSucces);
}

int bT(int iDebut, int *piFin, int * paN){
	// T(n+1) -> A.K(n).B
	int iX, iY, iFin;
	int aA = 0;
	int bSucces = bA(iDebut,&iX) && bK(iX,&iY,&aA) && bB(iY,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA + 1;
	return(bSucces);
}

int bU(int iDebut, int *piFin, int * paN){
	// U(1) -> A.B.
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = 1;
	return(bSucces);
}

int bK(int iDebut, int *piFin, int * paN){
	//	K(n) -> T(n) + U(n)  
	int iFin;
	int aA = 0;
	int bSucces = bT(iDebut,&iFin,&aA) || bU(iDebut,&iFin,&aA);
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	return(bSucces);
}
int bS(int iDebut, int *piFin, int * paN){
	// S(n) -> K(n).(n est un carre)
	int iFin;
	int aA = 0;
	int bSucces = bK(iDebut,&iFin,&aA) && (estUnCarre(aA));
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	return(bSucces);
}
