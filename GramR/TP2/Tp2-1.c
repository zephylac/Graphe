#include "Outil.h"
#include "Tp2.h"

char * sMOT;
int bTp2AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L1 = a( a*b + b*a )
		 = a( a+b + b+a + b + a )
		 = ab + aa + a.a+b + ab+a  
		 = aa + a+b + ab+a

Grammaire algebrique
	S -> T + U + V 
	T -> aa
	U -> a.U + ab 
	V -> a.W
	W -> b.W + ba 
	
 

Grammaire hommogene
	
	S -> V + U + T
	T -> AA

	U -> X + Y
	X -> A.U
	Y -> A.B
 
	V -> A.W
	W -> F + G
	F -> B.W
	G -> B.A

	A -> a
	B -> b

*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bF(int idebut, int *pifin);
int bG(int idebut, int *pifin);
int bT(int idebut, int *pifin);
int bU(int idebut, int *pifin);
int bV(int idebut, int *pifin);
int bW(int idebut, int *pifin);
int bX(int idebut, int *pifin);
int bY(int idebut, int *pifin);
int bS(int iDebut, int *piFin);

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp1INITIALISER",bTp2AmorceR);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	Assert1("Tp2Tester",bTp2AmorceR);
	switch (iTest) {
		case 1: sMOT="aa";break;
		case 2: sMOT="ab";break;
		case 3: sMOT="aab";break;
		case 4: sMOT="abbba";break;
		case 5: sMOT="aaabbb";break;
		case 6: sMOT="ba";break;
		case 7: sMOT="bba";break;
		case 8: sMOT="bab";break;
		case 9: sMOT="bbaa";break;
		case 10: sMOT="";break;
		default: Assert1("Tp2TESTER default",0);
	}
	bSucces = bS(0,&iFin);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;

	printf("%s : %s %s engendre par la grammaire decrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT),sEst(bEngendre));

}//Tp2TESTER	

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

int bT(int iDebut, int *piFin){
	// T -> A.A
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bA(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bU(int iDebut, int *piFin){
	// U -> X + Y
	int iFin;
	int bSucces = bX(iDebut,&iFin) || bY(iDebut,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bV(int iDebut, int *piFin){
	// V -> A.W
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bW(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bW(int iDebut, int *piFin){
	// W -> F + G
	int iFin;
	int bSucces = bF(iDebut,&iFin) || bG(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bX(int iDebut, int *piFin){
	// X -> U.A
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bU(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bY(int iDebut, int *piFin){
	// Y -> A.B
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bF(int iDebut, int *piFin){
	// F -> W.B
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bW(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bG(int iDebut, int *piFin){
	// F -> B.A
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bA(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> V + U + T 
	int iFin;
	int bSucces = bV(iDebut,&iFin) || bU(iDebut,&iFin) || bT(iDebut,&iFin)	;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
