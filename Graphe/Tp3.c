#include "Outil.h"
#include "Graphe.h"
#include "Tp3.h"
#include "Tas.h"
#include "Deque.h"
#define kuSommetMaX 100
#define INFINI 999


int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER

void ncheminertas (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh, int nDist[1+kuSommetMaX]){ // o(s2)
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
	
	//VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

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


void TP3Facturer(int sOrigine, int sDestination, int nLongueur, int nLargeur, int nHauteur){
  int nCoutKm = 1; // 1€ le km
  int nCoutDeBase = 500;
  int nCoutTotal = 0;
  graf *pgG;
  int nComplexiteh;
  int nDistance = -1;
  int aK, sX;
  char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
  char l[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";
  char L[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";
  char h[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";

  GrapheGenerer(ksPetit,&pgG);

  int nDist[pgG->nSommetEnTout];  
  
  GrapheVoir0(pgG,sC2b("Graphe",sG(ksPetit)),grCouleur);

  VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

  for (sX = 1, aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++, sX++) {
    if(nLongueur >= l[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI; 
    }
    if(nLargeur <= L[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI;
    }
    if(nHauteur <= h[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI;
    }
  }
 
  ncheminertas (pgG,sOrigine, sDestination, &nComplexiteh, nDist);

  nDistance = nDist[sDestination];
  nCoutTotal = nCoutDeBase + nDistance * nCoutKm;
  if(nDistance == INFINI){
    printf("Le transport du colis pour aller de %i a %i est impossible car ses dimensions sont trop grandes\n",sOrigine, sDestination);
  }
  else{
    printf("Le cout total du transport pour aller de %i a %i est de %i\n",sOrigine, sDestination, nCoutTotal);
  }
}


void TP3Router(int nHeure, int nMinute, int nSeconde, int sOrigine, int sDestination, int nLongueur, int nLargeur, int nHauteur){

  int nCoutKm = 1; // 1€ le km
  int nCoutVolume = nLongueur * nLargeur * nHauteur; // 5m cube
  int nCoutDeBase = 500;
  int nCoutTotal = 0;
  graf *pgG;
  int nComplexiteh;
  int nDistance = -1;
  int aK,sX;
  int nJour = 0;
  int nReste = 0;
  int pred; 
  char * sLieu="Le Mans, Paris, Nice, Lille, Brest, Strasbourg, Nantes, Perpignan, Bayonne";
  
  char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
  char l[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";
  char L[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";
  char h[]="AE5BE5EF5FC5FD5GA5GB5CH5DH5";

  GrapheGenerer(ksPetit,&pgG);

  int sItineraire[kuSommetMaX];
  int nDist[pgG->nSommetEnTout];
  
  GrapheVoir0(pgG,sC2b("Graphe",sG(ksPetit)),grCouleur);

  for (sX = 1, aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++, sX++) {
    if(nLongueur >= l[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI; 
    }
    if(nLargeur <= L[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI;
    }
    if(nHauteur <= h[sX * 3 - 1]){
      pgG -> nCout[aK] = INFINI;
    }
  }
 
  ncheminertas (pgG,sOrigine, sDestination, &nComplexiteh, nDist);   
  nDistance = nDist[sDestination];
  d(nDistance);
  if(nDistance == INFINI){
    printf("Le transport du colis pour aller de %i a %i est impossible car ses dimensions sont trop grandes\n",sOrigine, sDestination);
  }
  else{
    
    // On prend 10 min par kilometre
    nMinute = nMinute + nMinute * nDistance;
    nReste = nMinute % 60;
    nMinute = nMinute - nReste * 60;

    nHeure = nHeure + nReste;  
    nReste = nHeure % 24;
    nHeure = nHeure - nReste * 24;
 
    nJour = nJour + nReste;
  
  
    nCoutTotal = nCoutDeBase * nCoutVolume + nDistance * nCoutKm;
    
    DequeAllouer(pgG -> nSommetEnTout);
    
    pred = pgG -> sPer[sDestination];
    DequeEmpiler(sDestination);

    while(pgG -> sPer[pred] != pred){
      DequeEmpiler(pred);
      pred = pgG -> sPer[pred];
    }
    sX = pgG -> nSommetEnTout;

    while(!bDequeVide()){
      sItineraire[sX] = sDequeDepiler(); 
      sX--;
    }
   
    DequeAllouer(0);

    printf("Le transport mettra %i jours, %i heures, %i minutes, %i secondes\n",nJour,nHeure,nMinute,nSeconde);
    printf("Le cout total du transport pour aller de %i a %i est de %i\n",sOrigine, sDestination, nCoutTotal);
    for(sX = 1; sX <= sItineraire[0] || !bLigne(); sX++){
      printf(" %s%c", sItem(sLieu,sItineraire[sX]),(sX>sItineraire[0])? ',':'.');
    }

  }
}

void Tp3TESTER(int iTest){
	//teste le présent module
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //TP3 Facturer
			TP3Facturer(1,8,6,6,6);
			break;
		case 2: //TP3 Router
			TP3Router(0,0,0,1,8,1,1,1);
			break;

		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

