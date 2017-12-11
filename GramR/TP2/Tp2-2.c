#include "Outil.h"
#include "Tp2.h"

char * sMOT;
int bTp2AmorceR=kF;//ie ce module a effectivement été amorcé


/*Langage
	L2 = a^n.b^n.a  avec n >= 0
		 = a + a^n.b^n.a avec n > 0

Grammaire algebrique
	S -> a + U.a    
	U -> a.U.b + a.b
	
 

Grammaire hommogene
	
	S -> U + A  
	U -> X.A
	X -> V + W
	V -> A.X.B 
	W -> A.B
 
*/

int bA(int iDebut, int *piFin);
int bB(int iDebut, int *piFin);
int bU(int idebut, int *piFin);
int bV(int idebut, int *piFin);
int bW(int idebut, int *piFin);
int bX(int idebut, int *piFin);
int bS(int iDebut, int *piFin);

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
		case 1: sMOT="aba";break;
		case 2: sMOT="aabba";break;
		case 3: sMOT="aaabbba";break;
		case 4: sMOT="a";break;
		case 5: sMOT="aaabba";break;
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

int bU(int iDebut, int *piFin){
	// U -> X.A
	int iX, iFin;
	int bSucces = bX(iDebut,&iX) && bA(iX,&iFin) ;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bV(int iDebut, int *piFin){
	// V -> A.U.B
	int iX, iY, iFin;
	int bSucces = bA(iDebut,&iX) && bX(iX,&iY) && bB(iY,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bW(int iDebut, int *piFin){
	// W -> A.B
	int iX, iFin;
	int bSucces = bA(iDebut,&iX) && bB(iX,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}

int bX(int iDebut, int *piFin){
	// X -> V + W
	int iFin;
	int bSucces = bV(iDebut,&iFin) || bW(iDebut,&iFin);
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}


int bS(int iDebut, int *piFin){
	// S -> U + A 
	int iFin;
	int bSucces = bU(iDebut,&iFin) || bA(iDebut,&iFin)	;
	*piFin = (bSucces) ? iFin : iDebut;
	return(bSucces);
}
