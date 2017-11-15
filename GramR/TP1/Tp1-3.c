#include "Outil.h"
#include "Tp1.h"

char * sMOT;
int bTp1AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L2 = bab+

Grammaire algebrique
	S -> b.U
	U -> a.V
	V -> b.V + b

Grammaire hommogene
	
	S -> U.V
	U -> B.A
	V -> W + B
	W -> B.V
	A -> a
	B -> b

*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);

int bU(int iDebut, int *piFin);
int bV(int iDebut, int *piFin);
int bW(int iDebut, int *pifin);

int bS(int iDebut, int *piFin);

void Tp1AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp1INITIALISER",bTp1AmorceR);
}//Tp1INITIALISER

void Tp1TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	Assert1("Tp1Tester",bTp1AmorceR);
	switch (iTest) {
		case 1: sMOT="bab";break;
		case 2: sMOT="ba";break;
		case 3: sMOT="babb";break;
		case 4: sMOT="babbba";break;
		default: Assert1("Tp1TESTER default",0);
	}
	bSucces = bS(0,&iFin);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;

	printf("%s : %s %s engendre par la grammaire decrite dans \"Tp1.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT),sEst(bEngendre));

}//Tp1TESTER	

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

int bU(int iDebut, int *piFin){
	// U -> B.A
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bA(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bV(int iDebut, int *piFin){
	// V -> W + B
	int iFin;
	int bSucces = bW(iDebut,&iFin) || bB(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bW(int iDebut, int *piFin){
	// W -> B.V 
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bV(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> U.V
	int iX, iFin;
	int bSucces = bU(iDebut,&iX) && bV(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
