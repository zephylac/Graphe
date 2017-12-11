#include "Outil.h"
#include "Tp2.h"

char * sMOT;
int bTp2AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L3 = autant de a que de b

Grammaire algebrique

  S -> aU + bT
	T -> a + aS + bSS
  U -> b + bS + aUU

Grammaire hommogene

	S -> T + U 
	T -> A.W
	U -> B.V
	
	V -> A + G + H
	G -> A.S
	H -> B.V.V

	W -> B + I + J
	I -> B.S
	J -> a.W.W	
*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bG(int idebut, int *piFin);
int bH(int idebut, int *piFin);
int bI(int idebut, int *piFin);
int bJ(int idebut, int *piFin);
int bT(int idebut, int *piFin);
int bU(int idebut, int *piFin);
int bV(int idebut, int *piFin);
int bW(int idebut, int *piFin);
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
		case 2: sMOT="ba";break;
		case 3: sMOT="aabb";break;
		case 4: sMOT="ababab";break;
		case 5: sMOT="abbaabba";break;
		case 6: sMOT="aaabb";break;
		case 7: sMOT="abbaba";break;
		case 8: sMOT="aabbaba";break;
		case 9: sMOT="bababbaba";break;
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

int bG(int iDebut, int *piFin){
	// G -> A.S
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bS(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bH(int iDebut, int *piFin){
	// H -> B.V.V
	int iX, iY, iFin;
	int bSucces = bB(iDebut,&iX) && bV(iX,&iY) && bV(iY,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bI(int iDebut, int *piFin){
	// I -> B.S
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bS(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bJ(int iDebut, int *piFin){
	// J -> A.W.W
	int iX, iY, iFin;
	int bSucces = bA(iDebut,&iX) && bW(iX,&iY) && bW(iY,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bT(int iDebut, int *piFin){
	// T -> A.W
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bW(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bU(int iDebut, int *piFin){
	// U -> B.V
	int iX, iFin;
	int bSucces = bB(iDebut,&iX) && bV(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bV(int iDebut, int *piFin){
	// V -> A + G + H
	int iFin;
	int bSucces = bH(iDebut,&iFin) || bG(iDebut,&iFin) || bA(iDebut,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bW(int iDebut, int *piFin){
	// W -> B + I + J 
	int iFin;
	int bSucces = bJ(iDebut,&iFin) || bI(iDebut,&iFin) || bB(iDebut,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bS(int iDebut, int *piFin){
	// S -> V + W + Vide 
	int iFin;
	int bSucces = bT(iDebut,&iFin) || bU(iDebut,&iFin)	;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
