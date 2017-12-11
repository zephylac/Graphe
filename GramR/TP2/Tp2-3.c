#include "Outil.h"
#include "Tp2.h"

char * sMOT;
int bTp2AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L3 = ab + a^n.b^n.a*.b  avec n >= 0
		 = ab + a^n.b^n.a*.b + a*.b avec n > 0
		 = a^n.b^n(a+.b + b) + a+.b + b  avec n > 0

Grammaire algebrique
	S -> F + I + b
	F -> G.H
	G -> a.G.b + ab
	H -> I + b	
	I -> a.I + ab
	 

Grammaire hommogene

	S -> F + I + B
	F -> G.H
	G -> K + L
	K -> A.G.B
	L -> A.B
	H -> I + B	
	I -> M + L
	M -> A.I

*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bF(int idebut, int *piFin);
int bG(int idebut, int *piFin);
int bH(int idebut, int *piFin);
int bI(int idebut, int *piFin);
int bJ(int iDebut, int *piFin);
int bK(int idebut, int *piFin);
int bL(int idebut, int *piFin);
int bM(int idebut, int *piFin);
int bS(int idebut, int *piFin);

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp2INITIALISER",bTp2AmorceR);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	Assert1("Tp2Tester",bTp2AmorceR);
	switch (iTest) {
		case 1: sMOT="ab";break;
		case 2: sMOT="b";break;
		case 3: sMOT="aaab";break;
		case 4: sMOT="abab";break;
		case 5: sMOT="abb";break;
		case 6: sMOT="aabbb";break;
		case 7: sMOT="aaabbbaaab";break;
		case 8: sMOT="aabab";break;
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

int bF(int iDebut, int *piFin){
	// F -> G.H
	int iX, iFin;
	int bSucces = bG(iDebut,&iX) && bH(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bG(int iDebut, int *piFin){
	// G -> K + L
	int iFin;
	int bSucces = bK(iDebut,&iFin) || bL(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bK(int iDebut, int *piFin){
	// K -> A.G.B
	int iX, iY, iFin;
	int bSucces = bA(iDebut,&iX) && bG(iX,&iY) && bB(iY,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bL(int iDebut, int *piFin){
	// L -> A.B
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bH(int iDebut, int *piFin){
	// H -> I + B
	int iFin;
	int bSucces = bI(iDebut,&iFin) || bB(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bI(int iDebut, int *piFin){
	// I -> M + L
	int iFin;
	int bSucces = bM(iDebut,&iFin) || bL(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bM(int iDebut, int *piFin){
	// M -> A.I
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bI(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> F + I + B 
	int iFin;
	int bSucces = bF(iDebut,&iFin) || bI(iDebut,&iFin) || bB(iDebut,&iFin)	;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
