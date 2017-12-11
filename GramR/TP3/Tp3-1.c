#include "Outil.h"
#include "Tp3.h"

char * sMOT;
int bTp3AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L3 = a^n.b^n.a^n avec n>0
	L3' = a^n.b^n.a+
Grammaire algebrique

	S -> K
	K -> T.U 
	T -> a.T.b + a.b
	U -> aU + a

Grammaire hommogene
 	S -> K
	K -> T.U 
	T -> X + Y
	X -> A.T.B
	Y -> A.B
	U -> V + A
	V -> A.U

Grammaire attributs
 
	S(n,p) -> K(n,p).(n est egal a p)
	K(n,p) -> T(n,p).U(n,p) 
	T(n,p) -> X(n,p) + Y(n,p)
	X(n+1,p) -> A.T(n,p).B
	Y(n,0) -> A.B.(n = 1)
	U(n,p) -> V(n,p) + W(n,p)
	V(n,p+1) -> A.U(n,p)
	W(0,p) -> A.(p = 1)	
*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bK(int iDebut, int *piFin, int * paN, int * paP);
int bT(int idebut, int *piFin, int * paN, int * paP);
int bU(int idebut, int *piFin, int * paN, int * paP);
int bV(int idebut, int *piFin, int * paN, int * paP);
int bW(int idebut, int *piFin, int * paN, int * paP);
int bS(int idebut, int *piFin, int * paN, int * paP);
int bX(int idebut, int *piFin, int * paN, int * paP);
int bY(int idebut, int *piFin, int * paN, int * paP);



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
	int paN, paP;
	Assert1("Tp3Tester",bTp3AmorceR);
	switch (iTest) {
		case 1: sMOT="aba";break;
		case 2: sMOT="aabbaa";break;
		case 3: sMOT="aabba";break;
		case 4: sMOT="aabaa";break;
		case 5: sMOT="abbaa";break;
		case 6: sMOT="aaabbbaaa";break;
		case 7: sMOT="abbaba";break;
		case 8: sMOT="aabbaba";break;
		case 9: sMOT="bababbaba";break;
		case 10: sMOT="";break;
		default: Assert1("Tp3TESTER default",0);
	}
	bSucces = bS(0,&iFin,&paN,&paP);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;

	printf("%s : %s %s engendre par la grammaire decrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT),sEst(bEngendre));

}//Tp3TESTER	

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

int bT(int iDebut, int *piFin, int * paN, int * paP){
	// T(n,p) -> X(n,p) + Y(n,p)
	int iFin;
	int aA = 187,aB = 188;
	int bSucces = bX(iDebut,&iFin,&aA,&aB) ||  bY(iDebut,&iFin,&aA,&aB) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	*paP = aB;

	return(bSucces);
}

int bX(int iDebut, int *piFin, int * paN, int * paP){
	// X(n+1,p) -> A.K(n,p).B
	int iX, iY, iFin;
	int aA = 0, aB = 0;
	int bSucces = bA(iDebut,&iX) && bT(iX,&iY,&aA,&aB) && bB(iY,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA + 1;
	*paP = aB;
	return(bSucces);
}

int bY(int iDebut, int *piFin, int * paN, int * paP){
	// Y(n,0) -> A.B.(n = 1)
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = 1;
	*paP = 0;
	return(bSucces);
}

int bU(int iDebut, int *piFin, int * paN, int * paP){
	// U(n,p) -> V(n,p) + W(n,p)
	int iFin;
	int aA = 0, aB = 0;
	int bSucces = bV(iDebut,&iFin,&aA,&aB) || bW(iDebut,&iFin,&aA,&aB) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	*paP = aB;
	return(bSucces);
}

int bV(int iDebut, int *piFin, int * paN, int * paP){
	// V(n,p+1) -> A.U(n,p)
	int iX, iFin;
	int aA = 0, aB = 0;
	int bSucces = bA(iDebut,&iX) && bU(iX,&iFin,&aA,&aB) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	*paP = aB + 1;
	return(bSucces);
}

int bW(int iDebut, int *piFin, int * paN, int * paP){
	// W(0,p) -> A.(p = 1)	
	int iFin;
	int bSucces = bA(iDebut,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = 0;
	*paP = 1; 
	return(bSucces);
}

int bK(int iDebut, int *piFin, int * paN, int * paP){
	//	K(n,p) -> T(n,p).U(n,p)  
	int iX, iFin;
	int aA = 0, aB = 0, aC=0, aD = 0;
	int bSucces = bT(iDebut,&iX,&aA,&aB) && bU(iX,&iFin,&aC,&aD);
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA + aC;
	*paP = aB + aD;
	return(bSucces);
}
int bS(int iDebut, int *piFin, int * paN, int * paP){
	// S(n,p) -> K(n,p).(n est egal a p)
	int iFin;
	int aA = 0, aB = 0;
	int bSucces = bK(iDebut,&iFin,&aA,&aB) && (aA == aB);
	*piFin = (bSucces) ? iFin : iDebut;
	*paN = aA;
	*paP = aB;
	d2(*paN,*paP);
	return(bSucces);
}
