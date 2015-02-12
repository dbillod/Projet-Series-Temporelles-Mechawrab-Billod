#include<iostream>
#include<strstream>
#include<random>
#include<time.h>
#include<vector>
#include<cmath>
#include<typeinfo>
#include<fstream>
#include<sstream>
#include<string>
#include <stdio.h>
#include <stdlib.h>

#include"Fonc.h"


using namespace std;




int main()
{



    cout<<"***********************************************************"<<endl;
    cout<<"Bienvenue dans le projet de prevision de series temporelles"<<endl;
    cout<<"***********************************************************"<<endl;
    cout<<" "<<endl;


      ///////////////////////////////////////////////////////////////////
            //////////////// NOTA BENE ///////////////////

    //Ce fichier doit avoir un pr�sentation pr�cise//
    //Il doit avoir � la premi�re ligne une lettre//
    //Puis la s�rie correspondante, de la plus ancienne valeur � la plus r�cente//
    //Puis une autre letre , puis une autre s�rie..//

    /////ATTENTION//////
    //Ne pas cr�er accidentellement avec Entr�e, artificiellement des lignes sans caract�res en plus, cela fera bugger le compteur du nombre de series//

    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    cout<<"Ce code necessite une presentation precise du fichier txt � utiliser"<<endl;
    cout<<"Consulter le fichier Formes_donnees.txt pour plus d'explications"<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    cout<<" "<<endl;

    cout<<"*************************************************************************************************"<<endl;
    cout<<"Le programme est concu pour ne pr�voir par d�faut que la prochiane valeur de la serie a expliquer"<<endl;
    cout<<"*************************************************************************************************"<<endl;
    cout<<""<<endl;

    cout<<"Mais vous pouvez demander combien de valeurs vous voulez prevoir"<<endl;
    int nbcoup;
    cin>> nbcoup;





    /*cout<<"Veuillez indiquer le chemin d'acces du fichier txt contenant les series a utiliser"<<endl;
    string chemin;
    cin>>chemin;*/


    //string sflux = "C:/Users/David/Documents/ENSAE/2A/C++/Series_PIB_Cons_Emploi.txt";
    //string sflux = "./seriesx1_2.txt";
    string sflux ="./Series_PIB_Cons_Emploi.txt";




    ifstream monFlux(sflux);
	//ifstream monFlux(" W:/Bureau/C++/Projet C++/Pr�vision S�ries Temp/Pr�vision S�ries Temp/seriesini.txt" );
	//ifstream monFlux ("//paradis/eleves/DBILLOD/Bureau/C++/Projet C++/Pr�vision S�ries Temp/Pr�vision S�ries Temp/seriesini.txt");


    if(monFlux)
   {
      //L'ouverture s'est bien pass�e, on peut donc lire

      string ligne; //Une variable pour stocker les lignes lues
      int nbdouble = 0;
      int nbseries = 0;

      while(getline(monFlux, ligne)) //Tant qu'on n'est pas � la fin, on lit
      {
          if(ligne==""){
                cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                cout<<"!Le fichier contient une ligne vide!"<<endl;
                cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                cout<<" "<<endl;
          }
         else{
         istringstream istr(ligne);
         double i;
            if (istr>>i){
         nbdouble=nbdouble +1;//on compte le nombre de double

         }
            else{
            nbseries ++;
         }
         }

      }
      vector <double> TAB;
      int i =0;
      monFlux.close();
      ifstream monFlux(sflux);//on ferme et on r�ouvre le fichier pour pas bugger le prochain while
      string ligne2;
      while(getline(monFlux, ligne2))
      {
          if (ligne2 ==""){
          }
          else{
              istringstream istr(ligne2);
              //cout<<"ligne2="<<ligne2<<endl;
              double d;
              if (istr>>d){
              TAB.push_back(d); //on cr�e un tableau o� on stocke les doubles du fichier
              i = i+1;
              }
          }
      };

        int tailletab = nbdouble/nbseries;

	  /*for (int i = 0 ; i<nbseries; i++){
		  vector <double> data;
		  for(int j =0;j<tailletab;j++){
			  data.push_back(TAB[i*tailletab+j]);
		  }
		  tabdata.push_back(data);
	  }*/

        vector <vector <double> > tabdata = tabdata2(nbseries,tailletab,TAB);

           /* while(nbcoup>0){
                    nbcoup=nbcoup-1;
                if (nbcoup>0){
                        for (int i =0; i<tailletab-1;i++){
                            tabdata[0][i]= tabdata[0][i+1];
                        }
                        tabdata[tailletab-1] = Ensemble_prevision
                }
                //for p
                //Prevision pour tous les p
                vector <vector <double> > Ensemble_previsions2[p].push_back(Ensemnle_previsions[p]);

        	  }*/

////////////////////////////////////////////////////////////////
    //On veut trouver les meilleurs k et h par cross validation
////////////////////////////////////////////////////////////////

        vector <double> erreurkh;
        vector <double> erreurmoykh;

        vector <vector <double > > Indice_utileglobal;
        vector <double> Ensemble_previsions;

        //////////////////////////////////////////////////////////////////////
        // On va stocker le nom des series explicatives sous forme x1, x2...//
        //////////////////////////////////////////////////////////////////////

        vector <string> Nom_series;
          for(int i =0; i<nbseries;i++){
            string Res ;
            stringstream convert ;
            convert << i+1;
            Res = convert.str(); //on passe i en string

            string sxi = "x" + Res;
            Nom_series.push_back(sxi);
            }


///////////////////////////////////////////////////////////////////////////
//Pour prevoir plusieurs valeurs on va la faire distance par distance//////
//Donc on cr�e 3 tableaux de tableaux qui stockeront les donn�es updatees//
///////////////////////////////////////////////////////////////////////////
    vector <vector <double> >tabdatap0=tabdata;
    vector <vector <double> >tabdatap1=tabdata;
    vector <vector <double> >tabdatap2=tabdata;

    int nbprevision = 1;

    while(nbcoup>0){
            cout<<"****************************"<<endl;
            cout<<"Prevision de y en T+"<<nbprevision<<endl;
            cout<<"****************************"<<endl;
            nbprevision+=1;


            nbcoup = nbcoup-1;

            /*if (nbcoup>0){
                for (int i =0; i<tailletab-1;i++){
                    tabdata[0][i]= tabdata[0][i+1];
                }
                tabdata[tailletab-1] = prevision
            }*/

      for (int p =0;p<3;p++){
            ////////////////////////////////////////////
            //On va faire varier le choix de distances//
            ////////////////////////////////////////////
            if(p==0){
                tabdata = tabdatap0;
            }
            if (p==1){
                tabdata = tabdatap1;
            }
            if(p==2){
                tabdata = tabdatap2;
            }


      for(int k=1; k<10; k++){

	  for(int h=2; h<5;h++){



	  for(int t = 5;  t< tailletab ;t++){


            /*
		  //on va couper nos s�ries
		  vector < vector <double> > tabdata_coupe;
		  for(int  i= 0; i<nbseries;i++){
                vector<double> data;
			  for(int j =0; j< t; j++){
				   // on cr�e notre tableau coup�
				  data.push_back(tabdata[i][j]);

			  }
			  tabdata_coupe.push_back(data);
		  }
            */

            vector < vector <double> > tabdata_coupe = coupertab(nbseries, t,tabdata);

		  //on va renormer les tableaux
		vector <vector<double> >tabdata_r;
		for(int i =0; i<nbseries;i++){
			tabdata_r.push_back(renorm(tabdata_coupe[i]));
		}



//////////////////////////////////////////////////////////
	  //On a construit un tableau r�sumant les donn�es//
//////////////////////////////////////////////////////////



				vector <vector <vector <double> > > Mat_totale; // on va stocker dans Mat_totale toutes les sous �quences de taille h

				for(int i =0; i<nbseries;i++){
				Mat_totale.push_back(matrice_sous_seq(tabdata_r[i],h));
			   }

				vector<double> Seq_a_predire = extract(tabdata_r[0],t-h,h);// Seq_a_predire est la derni�re s�q de y d etaille h


                /*
				for(int i =1; i<nbseries;i++){
						vector <double> temp_disttab;
						for (int indice_debut = 0; indice_debut<t-h+1;indice_debut++){
							temp_disttab.push_back(  distance2( Mat_totale[i][indice_debut] , Seq_a_predire )  );

						}
						Tabdist.push_back( temp_disttab );
						cout<<"i="<<i<<endl;
				}*/


                //Tabdist est un tableau dont le premier �l�ment est un tableau de taille h qui comprte tailletab-h �l�mets qui sont les distances des s�quences extraites // � ce qu'il faut pr�dire
                vector <vector <double>  >  Tabdist=tabdist(nbseries,h,t,Mat_totale,Seq_a_predire,p);


				/*vector <double> Tabdist_simple ;
				for (int i =0; i<nbseries-1;i++){
					for (int j = 0;j<t-h+1;j++){
					Tabdist_simple.push_back(Tabdist[i][j]);
					}
				}*/

				vector <double> Tabdist_simple= simplifietab(nbseries, h,  t, Tabdist );


				vector <double> Positions_min = argminmultpile(Tabdist_simple,k);


				vector < vector <double> > Seq_min; //seq-min contient les tableaux les plus proches de seq_a_predire
				vector <double> Val_suiv; //Ce tableau va stocker les valeurs suivantes des seq_min

				for(int i =0; i<k;i++){
					int quotient = (Positions_min[i])/(t-h+1);
					int reste = Positions_min[i]-quotient*(t-h+1);
					Seq_min.push_back(Mat_totale[quotient+1][reste]);
					if(reste == t-h){
					 Val_suiv.push_back(Mat_totale[quotient+1][reste][h-1]);//Si on tombe sur le dernier terme d'une s�rie, on ne prend pas la valeur suivante mais ce terme
					}
					else {
					Val_suiv.push_back( Mat_totale[quotient+1][reste+1][h-1] );
					}
				}

				double prevision = moyenne(Val_suiv);

				erreurkh.push_back(abs(prevision-tabdata[0][t]));


	  }//fin du for t
        double m = moyenne(erreurkh);
        erreurmoykh.push_back(k);
        erreurmoykh.push_back(h);
        erreurmoykh.push_back(m);
	  }//fin du for h
	  }//fin du for k


	  int longueur = erreurmoykh.size()/3;
	  vector <double> erreurmoy;
	  for (int i =1; i<longueur; i++ ){
            erreurmoy.push_back(erreurmoykh[3*i-1]); // on stocke les m
	  };

    int arg = argmin2(erreurmoy);
    int bestk = erreurmoykh[3*arg];
    int besth = erreurmoykh[3*arg +1];


    cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
    cout<<"     p =    "<<p<<" (Relatif a la distance choisie)"<<endl;
    cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
    cout<<" "<<endl;

    cout<<"--------------------------------"<<endl;
    cout<<"Resultats de la cross-validation"<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<" "<<endl;
    cout<<"best k = " << bestk<<endl;
    cout<<"best h = " << besth<<endl;
    cout<<" "<<endl;

////////////////////////////////////////////
  //On a donc trouv� nos k et h optimaux//
////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//Il faut maintenant estimer avec ces k et h notre prochain y//
///////////////////////////////////////////////////////////////

          ///////////////////////////////
		  //on va renormer les tableaux//
		  ///////////////////////////////
		vector <vector<double> >tabdata_r;
		for(int i =0; i<nbseries;i++){
			tabdata_r.push_back(renorm(tabdata[i]));
		}


//////////////////////////////////////////////////////////
	  //On a construit un tableau r�sumant les donn�es//
//////////////////////////////////////////////////////////


vector <vector <vector <double> > > Mat_totale; // on va stocker dans Mat_totale toutes les sous �quences de taille h

				for(int i =0; i<nbseries;i++){
				Mat_totale.push_back(matrice_sous_seq(tabdata_r[i],besth));
			   }

				vector<double> Seq_a_predire = extract(tabdata_r[0],tailletab-besth,besth);// Seq_a_predire est la derni�re s�q de y d etaille h

                //Tabdist est un tableau dont le premier �l�ment est un tableau de taille h qui comprte tailletab-h �l�mets qui sont les distances des s�quences extraites // � ce qu'il faut pr�dire
                vector <vector <double>  >  Tabdist=tabdist(nbseries,besth,tailletab,Mat_totale,Seq_a_predire,p);

				vector <double> Tabdist_simple= simplifietab(nbseries, besth,  tailletab, Tabdist );

				vector <double> Positions_min = argminmultpile(Tabdist_simple,bestk);

                vector < vector <double> > Seq_min; //seq-min contient les tableaux les plus proches de seq_a_predire
				vector <double> Val_suiv; //Ce tableau va stocker les valeurs suivantes des seq_min
				double Indice_util[nbseries-1]; //On cr�e ce tableau pour svoir quelles s�ries ont �t� les plus utiles

				for (int i=0; i< nbseries -1; i++){

                    Indice_util[i]=0; //On remplit le tableau de 0, valeur par d�faut de l'utilit� d'une s�rie
				}


				for(int i =0; i<bestk;i++){
					int quotient = (Positions_min[i])/(tailletab-besth+1);
					int reste = Positions_min[i]-quotient*(tailletab-besth+1);
					Indice_util[quotient] =Indice_util[quotient]+ 100/(double)bestk;// On stocke en pourcentage l'inter�t de la s�rie comme sa part dans les plus proches voisins

					Seq_min.push_back(Mat_totale[quotient+1][reste]); //On se place ne quotient +1 pour ne pas tomber sur la s�rie � pr�voir
					if(reste == tailletab-besth){
					 Val_suiv.push_back(Mat_totale[quotient+1][reste][besth-1]);//Si on tombe sur le dernier terme d'une s�rie, on ne prend pas la valeur suivante mais ce terme
					}
					else {
					Val_suiv.push_back( Mat_totale[quotient+1][reste+1][besth-1] );
					}
				}

                //Pour des raisons pratiques, pour mieux le manipuler, on va transformer Indice_util en vector <double>
                vector <double> Indice_utile;
                for (int i=0; i< nbseries-1;i++){

                    Indice_utile.push_back(Indice_util[i]);
                }




				double prevision = moyenne(Val_suiv);

                cout<<"------------------------------------------------------"<<endl;
                cout<<"Prevision avec param�tres optimaux"<<endl;
				cout<<"------------------------------------------------------"<<endl;
				cout<< "La prevision pour le prochain terme de y renorme est " << prevision<<endl;
				cout<< "La prevision pour le prochain terme de y est "<< prevision * ecart_type(tabdata[0])<<endl;
				Ensemble_previsions.push_back(prevision * ecart_type(tabdata[0]));

				if(p==0){
                    tabdatap0[0].push_back(prevision*ecart_type(tabdata[0]));
				}
				if (p==1){
                    tabdatap1[0].push_back(prevision*ecart_type(tabdata[0]));
				}
				if (p==2){
                    tabdatap2[0].push_back(prevision*ecart_type(tabdata[0]));
				}

				double prog = 100* (prevision * ecart_type(tabdata[0])- tabdata[0][tailletab-1] )/tabdata[0][tailletab-1];
				cout<<"Soit une variation de "<<prog<<"%"<<endl;
				cout<<" "<<endl;


                cout<< "----------------------------------------"<<endl;
                cout<< "Niveau d'utilite des series explicatives"<<endl;
                cout<< "----------------------------------------"<<endl;

                for (int i =0; i< nbseries-1;i++){
                    cout<<"La serie "<<Nom_series[i]<<" a ete utile a "<<Indice_utile[i]<<"%"<<endl;
                }

                Indice_utileglobal.push_back(Indice_utile);
                cout<<" "<<endl;
      }//Fin du for p

      tabdatap0[0].erase(tabdatap0.begin()+0);
      tabdatap1[0].erase(tabdatap0.begin()+0);
      tabdatap2[0).erase(tabdatap0.begin()+0);


    }//fin du while nbcoup


      cout<<"-------------------------------------------------------------"<<endl;
      cout<<"Resume des resultats avec les differentes distances (p=0,1,2)"<<endl;
      cout<<"-------------------------------------------------------------"<<endl;
      cout<<" "<<endl;


      cout<<" p "<<" Series utiles "<<" Prediction "<<endl;
      for (int p =0; p<3;p++){
            for (int n=0;n<nbseries-1;n++){
                    if(n==0){
                        cout<<"p="<<p<<"   "<<Nom_series[n]<<" "<<"("<<Indice_utileglobal[p][n]<<"%)"<<"       "<<Ensemble_previsions[p]<<"      "<<endl;
                            }
                    else{
                        cout<<"   "<<"   "<<Nom_series[n]<<" "<<"("<<Indice_utileglobal[p][n]<<"%)"<<endl;
                    }
            }
      }


   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }








    return 0;
}
