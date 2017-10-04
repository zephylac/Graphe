#include "Outil.h"
#include "Graphe.h"
#include "Tp1.h"
int bTp1AmorceR;//ie ce module a effectivement été amorcé

void DistancierCalculeR(graf *pgSimple,int bAfficher){//(O(S3)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int aK,sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgSimple->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances,supposées être des entiers ou des réels déjà ramenés à des entiers
	
	int k = 0;
	int j = 0;
	int i = 0;
	int pere[1+nSommet][1+nSommet];//matrice des peres
	int chemin[1+nSommet][1+nSommet];//matrice contenant les résultats

	Assert1("DistancierCalculeR",bGrapheSimple(pgSimple));
	//générer la matrice d'incidence sommet-sommet dM qui décrit le graphe simple pgSimple
		//dM:=0
			for (uL=1;uL<=nSommet;uL++)
				for (uC=1;uC<=nSommet;uC++)
					dM[uL][uC]=0;
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgSimple->aHed[sX];aK<pgSimple->aHed[sX+1];aK++){
				sY=pgSimple->sSuk[aK];
				dM[sX][sY]=pgSimple->coulh[aK];//distance (sX,sY)
			}
	//exécuter l'algorithme de Floyd sur dM
	//code à compléter...
    	
	// Init
	for (uL=1;uL<=nSommet;uL++){
		for (uC=1;uC<=nSommet;uC++){
	        	chemin[uL][uC] = INFINI;
	    		pere[uL][uC]= 0;
	  	}
	}
	
	for (uL=1;uL<=nSommet;uL++){
		chemin[uL][uL] = 0;
	}

       	for (sX=1; sX <= nSommet; sX++ ){
		//pere[sX][sX]; //Superflu car redondance
          	for(sY=1 ; sY <= nSommet; sY++ ){
            		if( dM[sX][sY] != 0 && sX != sY ){
              			chemin[sX][sY] = dM[sX][sY];
	      			pere[sX][sY] = sX;
          		}
		}
	}
	for (k = 1; k <= nSommet; k++){
		for (i = 1; i <= nSommet; i++){
			for (j = 1; j <= nSommet; j++){
				if(chemin[i][j] > chemin[i][k] + chemin[k][j] && chemin[i][k] != INFINI && chemin[k][j] != INFINI){
					chemin[i][j] = chemin[i][k] + chemin[k][j];
					pere[i][j] = pere[k][j];
				}
			}
		}
	}
	if (bAfficher){//afficher le distancier dM
		//code à compléter...
		for(i = 1; i <= nSommet; i++){
			for(j = 1; j <= nSommet; j++){
				if(chemin[i][j] == INFINI){
					printf("        I");
				}
				else{
					printf("%9i",chemin[i][j]);
				}
			}
			printf("\n");
		}
	}
}//DistancierCalculeR

void GrapheAllouerInitialiseR(int nGraphe,int bAfficher,graf **ppgSimple){
	//alloue et décrit dans ppgSimple le graphe de rang1 nGraphe
	//pour simplifier la saisie,les sommets vont de A à Z puis de a à z et les données sont supposées être des entiers dans [0..9] 
    char ksGros[]="AB1AD1AE2BC3BG2CJ2CK1DM1DN2EF2EQ1FG2FR1GS1HI2HT1IJ1IV1JX3KY2LM2LZ1Ma1NO1Nb3OP2Oc3Pe1Qe2Qf2Rf2Rg2ST2Sg2TU2UV1Uh3VW2WX1Yj1Zj2ab2ak3bm1cd1cm2de2dn2fn1go1hi2ip1kl1lm2ln2op2Aq5Br5Cs5Dt5";
	char kcMoyen[]="AB2AH1BC1BK2CD2DE1DM2EF2FG1FO2GH2HI2IJ2IP1JK1JQ2KL2LM1LS2MN2NO1NU2OP2PU2QR5RU1ST5TU1AV2CW2EX2GY2";
	char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char *sGrapheType="ksPetit,kcMoyen,ksGros";
	Appel0("GrapheAllouerInitialiseR");
		switch(nGraphe){//NB ci-dessous,GrapheGenerer alloue puis initialise ppgSimple
			case 1:	GrapheGenerer(ksPetit,ppgSimple);
					break;
			case 2:	GrapheGenerer(kcMoyen,ppgSimple);
					break;
			case 3:	GrapheGenerer(ksGros,ppgSimple);
					break;
			default: Assert1("GrapheAllouerInitialiseR default",0);
		}//switch
		GrapheVoir0(*ppgSimple,sC2b("Graphe",sG(sItem(sGrapheType,nGraphe))),grCouleur);
		Assert1("GrapheAllouerInitialiseR",bGrapheSimple(*ppgSimple));
	Appel1("GrapheAllouerInitialiseR");
}//GrapheAllouerInitialiseR

void PerformanceCompareR(){
}//PerformanceCompareR

void Tp1AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp1AmorceR=kV;
}//Tp1AMORCER

void Tp1Distancier(graf *pgG,int bAfficher){
//calculer le distancier de pgG supposé peu dense (algo de Dijkstra avec tas)
	int temp;

	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgG->nSommetEnTout;

	int i = 0;
	int j = 0;	
	int chemin[1+nSommet][1+nSommet];//matrice contenant les résultats

	for (uL=1;uL<=nSommet;uL++){
		for (uC=1;uC<=nSommet;uC++){
	        	chemin[uL][uC] = INFINI;
	  	}
	}
	
	for (uL=1;uL<=nSommet;uL++){
		chemin[uL][uL] = 0;
	}

	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

       	for (sX=1; sX <= nSommet; sX++ ){
          	for(sY=1 ; sY <= nSommet; sY++ ){
			if(sX != sY){
				chemin[sX][sY] = nGrapheCheminerTas(pgG,sX,sY);
			}
        	}
	}
	if (bAfficher){//afficher le distancier dM
		//code à compléter...
		for(i = 1; i <= nSommet; i++){
			for(j = 1; j <= nSommet; j++){
				if(chemin[i][j] == INFINI){
					printf("        I");
				}
				else{
					printf("%9i",chemin[i][j]);
				}
			}
			printf("\n");
		}
	}
	
}//Tp1Distancier

void Tp1INITIALISER(){//O(?)
	//relance le présent module
	Assert1("Tp1INITIALISER",bTp1AmorceR);
}//Tp1INITIALISER

void Tp1TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	float fDensiteh;
	Appel0(sC2("Tp1TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 0: //calculer la densité d'un graphe simple
			GrapheCreer(4,&pgG);
				fDensiteh=fGrapheDensiteh(pgG);
				GrapheVoir(pgG,"Graphe simple généré");
				f(fDensiteh);
			GrapheCreer(0,&pgG);
			break;
		case 1: //appeler DistancierCalculeR sur le graphe ksHomeSlipHome
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			DistancierCalculeR(pgG,k1Afficher);
			break;
		case 2: //appeler Tp1Distancier sur le graphe ksHomeSlipHome
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			Tp1Distancier(pgG,k1Afficher);
			break;
		case 3: //comparer les performances de DistancierCalculeR et Tp1Distancier
			PerformanceCompareR();
			break;
		default: Assert1("Tp1TESTER default",0);
	}
	Appel1(sC2("Tp1TESTER,test n°",sEnt(iTest)));
}//Tp1TESTER	

