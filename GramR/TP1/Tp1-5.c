#include "Outil.h"
#include "Tp1.h"

char * sMOT;
int bTp1AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L4 = ba + ab + bab+

Grammaire algebrique
	S -> U + V + W
	U -> b.a
	V -> a.b
	W -> U.X
	X -> b.X + b

Grammaire hommogene
	
	S -> W + U + V
	U -> B.A
	V -> A.B
	W -> U.X
	X -> Y + B
	Y -> B.X	
	A -> a
	B -> b

*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bU(int idebut, int *pifin);
int bV(int idebut, int *pifin);
int bW(int idebut, int *pifin);
int bX(int idebut, int *pifin);
int bY(int idebut, int *pifin);
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
		case 4: sMOT="baba";break;
		case 5: sMOT="ab";break;
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
	// V -> A.B
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}


int bW(int iDebut, int *piFin){
	// W -> U.X
	int iX, iFin;
	int bSucces = bU(iDebut,&iX) && bX(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bX(int iDebut, int *piFin){
	// X -> Y + B
	int iFin;
	int bSucces = bY(iDebut,&iFin) || bB(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bY(int iDebut, int *piFin){
	// Y -> B.X
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bX(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
 	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> W + U + V 
	int iFin;
	int bSucces = bW(iDebut,&iFin) || bU(iDebut,&iFin) || bV(iDebut,&iFin)	;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
