#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
#include "Tas.h"
#define kuSommetMaX 100


int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void DistancierAvecFloyD(graf *pgSimple,int nDist[][1+kuSommetMaX], int *pnComplexiteh){//(O(S3)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int aK,sX,sY;//a comme arc;s comme sommet
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgSimple->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances,supposées être des entiers ou des réels déjà ramenés à des entiers
        
        *pnComplexiteh=0;
	int k = 0;
	int j = 0;
	int i = 0;
	int pere[1+nSommet][1+nSommet];//matrice des peres
	
	
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
	// Init
	for (uL=1;uL<=nSommet;uL++,*pnComplexiteh++){
		for (uC=1;uC<=nSommet;uC++){
	        	nDist[uL][uC] = INFINI;
	    		pere[uL][uC]= 0;
	  	}
	}
	
	for (uL=1;uL<=nSommet;uL++,*pnComplexiteh++){
		nDist[uL][uL] = 0;
	}
	for(i = 1; i <= nSommet; i++){
		for(j = 1; j <= nSommet; j++){
			if(nDist[i][j] == INFINI){
				printf("        I");
			}
			else{
				printf("%9i",nDist[i][j]);
			}
		}
		printf("\n");
	}



       	for (sX=1; sX <= nSommet; sX++,*pnComplexiteh++ ){
		//pere[sX][sX]; //Superflu car redondance
          	for(sY=1 ; sY <= nSommet; sY++ ){
            		if( dM[sX][sY] != 0 && sX != sY ){
              			nDist[sX][sY] = dM[sX][sY];
	      			pere[sX][sY] = sX;
          		}
		}
	}
	for (k = 1; k <= nSommet; k++,*pnComplexiteh++){
		for (i = 1; i <= nSommet; i++,*pnComplexiteh++){
			for (j = 1; j <= nSommet; j++,*pnComplexiteh++){
				if(nDist[i][j] > nDist[i][k] + nDist[k][j] && nDist[i][k] != INFINI && nDist[k][j] != INFINI){
					nDist[i][j] = nDist[i][k] + nDist[k][j];
					pere[i][j] = pere[k][j];
				}
			}
		}
	}
}//DistancierCalculeR

void nCheminerTas (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh, int nDist[1+kuSommetMaX]){ // O(S2)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo plus court chemin, Dijkstra AVEC tas.
	const int kuInfini=999;
	int nDistanceParX;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int sProche;
	int uSommet;
	int sX,sY;
	*pnComplexiteh=0;
	VecteurRazer(bFait,1,pgG->nSommetEnTout);
	VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
	VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	TasAllouer(pgG->nSommetEnTout);
	
	for (sX=1; sX<=pgG->nSommetEnTout; sX++){
		TasInsererValuer(sX,kuInfini);
	}
	TasActualiser(sSource,0);
	
	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	//TasVoir("Tas après initialisation");
	nDist[sSource]=0;//distance entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()

	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
		//TasVoir("Tas avant extraction");
		sProche=eTasExtraire();
		sX=sProche;
		if (sX!=0) {
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];
				nDistanceParX=nDist[sX]+pgG->nCout[aK];
				if ( nDist[sY]>nDistanceParX ) {
					nDist[sY]=nDistanceParX;
					pgG->sPer[sY]=sX;
					//tee("sY,nDistanceParX",sY,nDistanceParX);
					TasActualiser(sY,nDistanceParX);
					//TasVoir("Tas après TasActualiser");
				}
			}
			bFait[sX]=kV;
		}
	}//chaque sProche coûte O(S) et chaque arc est consulté 1 fois,soit une complexité au pire égale à sup( O(S*S),O(A) ), dc O(S2)
	//VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	(*pnComplexiteh)+=nTasCout();
	TasAllouer(0);
}//nGrapheCheminerTaS


void DistancierAvecDijkstrA(graf *pgG, int sSource, int nDist[1+kuSommetMaX], int *pnComplexiteh){
//calculer le distancier de pgG supposé peu dense (algo de Dijkstra avec tas)
	//calcule le distancier de pgG supposé dense (algo de Floyd);poids des arcs dans pgSimple->coulh[]
	int sX;//a comme arc;s comme sommet
	int nSommet=pgG->nSommetEnTout;
        d(nSommet);
	for (sX = 1; sX <= nSommet; sX++, *pnComplexiteh++){
		nDist[sSource * sX] = INFINI;
	}
	nDist[sSource] = 0;

       	for (sX=1; sX <= nSommet; sX++ ,*pnComplexiteh++){
			if(sX != sSource){
				nCheminerTas(pgG,sSource,sX,pnComplexiteh,nDist);
			}
        }
}//Tp1Distancier

int nDistancierCalculeR(graf *pgG, int nSommet, int bFloydSinonDijsktra, int bAfficher){
	int nDist[1+nSommet][1+nSommet];
	int nComplexiteh;
	int i, j;
	if(bFloydSinonDijsktra == 1){
		DistancierAvecFloyD(pgG,nDist,&nComplexiteh);
		printf("Complexite : %i \n",nComplexiteh);
		if(bAfficher){
			for(i = 1; i <= nSommet ; i++){
				for(j = 1; j <= nSommet; j++){
					if(nDist[i][j] == INFINI){
						printf("        I");
					}
					else{
						printf("%9i",nDist[i][j]);
					}
				}
				printf("\n");
			}
		}
	}
	else{
		for(i = 1; i <= nSommet; i++){
			DistancierAvecDijkstrA(pgG,i,nDist[i * nSommet],&nComplexiteh);
		}
		printf("Complexite : %i \n",nComplexiteh);	
		if(bAfficher){
			for(i = 1; i <= nSommet; i++){
				for(j = 1; j <= nSommet; j++){
					if(nDist[i][j] == INFINI){
						printf("        I");
					}
					else{
						printf("%9i",nDist[i][j]);
					}
				}
				printf("\n");
			}
		}
	}
	return nComplexiteh;
}

void GrapheAllouer(int nGraphe,graf **ppgSimple){
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

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	int nDist[1+kuSommetMaX][1+kuSommetMaX];
	int nComplexiteh;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire Floyd
			GrapheAllouer(1,&pgG);
			DistancierAvecFloyD(pgG,nDist,&nComplexiteh);
			break;
		case 2: //calcul de la densité d'un graphe simple aléatoire Dijsktra
			GrapheAllouer(1,&pgG);
			DistancierAvecDijkstrA(pgG,1,nDist[1],&nComplexiteh);
			break;
		case 3: //calcul de la densité d'un graphe simple aléatoire Dijsktra
			GrapheAllouer(1,&pgG);
			nComplexiteh = nDistancierCalculeR(pgG,pgG->nSommetEnTout,0,1);
			printf("Complexite : %i\n",nComplexiteh);
			break;


		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

