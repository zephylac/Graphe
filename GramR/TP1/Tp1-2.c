#include "Outil.h"
#include "Tp1.h"

char * sMOT;
int bTp1AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L1 = ba + bab

Grammaire algebrique
	S -> U + V
	U -> b.a.b
  V -> b.a

Grammaire hommogene
	
	S -> U + V
	U -> B.A.B
	V -> B.A
	A -> a
	B -> b

*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);

int bU(int iDebut, int *piFin);
int bV(int iDebut, int *piFin);

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
		case 3: sMOT="aaba";break;
		case 4: sMOT="baba";break;
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
	// U -> B.A.B
	int iX, iY, iFin;
	int bSucces = bB(iDebut,&iX) && bA(iX,&iY) && bB(iY, &iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}


int bV(int iDebut, int *piFin){
	// V -> B.A
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bA(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> U + V
	int iFin;
	int bSucces = bU(iDebut,&iFin) || bV(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
