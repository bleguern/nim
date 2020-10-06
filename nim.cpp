//LE JEU DE NIM

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

#define TRUE         1  //Vrai
#define FALSE        0  //Faux

#define MAX_TAS      5  //Défini le nombre de tas d'allumettes
#define MAX_ALL     10  //Défini le nombre maximal d'allumettes


int Puis(int, int);        //Fonction puissance


//Struct Tas, défini les variables propres à Tas
struct Tas
{
	int taille;                         //Taille du tas
	int codage[4];                      //Codage en puissance de deux
};

Tas tas[MAX_TAS];                       //Créé 5 tas


int add_codage[4] = {0};                //Tableau pour l'addition du codage en puissance de deux des tas
int val_tmp[4] = {-1, -1, -1, -1};                       
int val_tmp_nb = 0;


bool FixeTailleTas();                  //Fixe la taille des tas
bool CodeTailleTasPuis2();             //Code la taille des tas en puissance de deux
void AfficheTailleTas();               //Affiche la taille des tas
void AfficheCodeTailleTasPuis2();      //Affiche la taille des tas codée en puissance de deux

void JouerADeux();                     //Jouer a deux
void JouerSolo();                      //Jouer seul

int ChercheTasMaxPuis2();              //Strategie


//Fonction principale
int main( void )
{
	srand( (unsigned)time( NULL ) );

	int choix = 0;

	//bool pair = 0;

	cout << "> > > JEU DE NIM < < <" << "\n\n";

	while((choix != 1) && (choix != 2))
	{
		cout << "Veuillez choisir le mode de jeu :\n1 : Solo\n2 : Deux Joueur\n";

		cin >> choix;	
	}

	if(choix == 1)
	{
		JouerSolo();         //Jouer seul
	}
	else if(choix == 2)
	{
		JouerADeux();        //Jouer a deux
	}
	else
	{
		cout << "Erreur de saisie\n";
		return -1;
	}

	return TRUE;           //OK
}

//Définition de la fonction FixeTailleTas()
bool FixeTailleTas()
{
	int i, j;         //Compteur
	bool pair = 0;    //La propriété PAIR

	while(!pair)      //Tant que PAIR n'est pas vérifié
	{
		for(i = 0; i < 4; i++)        //Initialise le tableau pour l'addition du codage en puissance de deux des tas à 0
		{
			add_codage[i] = 0;
		}

		for(i = 0; i < MAX_TAS; i++)   //Initialise la taille des tas aléatoirement
		{
			tas[i].taille = 1+(rand()%MAX_ALL);
		}

		if(!CodeTailleTasPuis2())      //Code la taille des tas en puissance de deux
		{
			cout << "Erreur lors du codage de la taille des tas";
			return FALSE;
		}

		for(i = 0; i < MAX_TAS; i++)    //Effectue l'addition du codage en puissance de deux des tas
		{
			for(j = 0; j < 4; j++)
			{
				add_codage[j] += tas[i].codage[j];
			}
		}

		for(i = 0, j = 0; i < 4; i++)   //Vérifie si PAIR est vrai
		{
			if(!(add_codage[i]%2))
			{
				j++;
			}

			if(j == 4)
			{
				pair = TRUE;    //PAIR vrai
			}
		}
	}

	return TRUE;          //OK
}


//Définition de la fonction CodeTailleTasPuis2()
bool CodeTailleTasPuis2()
{
	int i, j, temp;       //Compteur et variable temporaire

	for(i = 0; i < MAX_TAS; i++)    //Codage pour chaque tas
	{
		temp = tas[i].taille;

		for(j = 4; j > 0; j--)
		{
			tas[i].codage[j-1] = (temp/(Puis(2,j-1)));          //Codage de la taille en puissance de deux
			temp = tas[i].taille%(Puis(2,j-1));
		}
	}

	return TRUE;                 //OK
}


//Définition de la fonction AfficheTailleTas()
void AfficheTailleTas()
{
	int i/*, j*/;         //Compteur

	cout << '\n';

	for(i = 0; i < MAX_TAS; i++)             //Affichage pour chaque tas
	{
		//Affichage numérique
		cout << "Tas no " << i+1 << " : " << tas[i].taille << " allumette(s)\n";
		
		//Affichage en baton
		/*cout << "Tas no " << i+1 << " : ";

		for(j = 0; j < tas[i].taille; j++)
		{
			cout << "|";
		}

		cout << " allumette(s)\n";*/

	}

	cout << "\n\n";
}


//Définition de la fonction AfficheCodeTailleTasPuis2()
void AfficheCodeTailleTasPuis2()
{
	int i, j;

	for(i = 0; i < MAX_TAS; i++)
	{
		cout << "Tas no " << i+1 << " : ";
		
		for(j = 4; j > 0; j--)
		{
			cout << tas[i].codage[j-1];    //Affiche le codage pour chaque puissance
		
			if(j > 1)
			{
				cout << ',';
			}
		}

		cout << '\n';
	}
}

//Définition de la fonction JouerADeux()
void JouerADeux()
{
	bool gagne = 0, joueur = 0;

	int choix_tas, choix_all, i, j;        //Variables de choix et compteur
	
	if(!FixeTailleTas())              //Fixe la taille des tas
	{
		cout << "\nErreur lors de l'entrée de la taille des tas";
		return;
	}

	while(!gagne)           //Tant que personne n'a gagne
	{
		AfficheTailleTas();       //Affiche la taille des tas

		cout << "Joueur " << joueur+1 << "\nChoisissez le tas : ";    //Affichage du joueur actif

		do
		{
			cin >> choix_tas;              //Entrée du choix du tas

			if((choix_tas < 1) || (choix_tas > MAX_TAS))
			{
				cout << "Erreur de saisie (entre 1 et " << MAX_TAS << ") : ";
			}

		}while((choix_tas < 1) || (choix_tas > MAX_TAS));

		cout << "\nChoississez le nombre d'allumettes a retirer : ";

		do
		{
			cin >> choix_all;                 //Entrée du choix du nombre d'allumettes

			if((choix_all < 1) || (choix_all > tas[choix_tas-1].taille))
			{
				cout << "Erreur de saisie (entre 1 et " << tas[choix_tas-1].taille << ") : ";
			}

		}while((choix_all < 1) || (choix_all > tas[choix_tas-1].taille));


		tas[choix_tas-1].taille = tas[choix_tas-1].taille - choix_all;          //Affectation au tas


		for(i = 0, j = 0; i < MAX_TAS; i++)         //Test si quelqu'un a gagne
		{
			if(tas[i].taille == 0)
			{
				j += 1;
			}

			if(j == 5)
			{
				cout << "\nJoueur " << joueur+1 << " : Vous avez gagne!";          //Affiche le gagnant
				gagne = 1;
			}
		}

		cout << '\n';

		joueur = !joueur;           //Change le joueur actif
	}
}



//Définition de la fonction JouerSolo()
void JouerSolo()
{
	bool gagne = 0, joueur = 0;

	int choix_tas, choix_all, i, j;         //Compteur et variables de choix

	if(!FixeTailleTas())           //Fixe la taille des ts
	{
		cout << "Erreur lors de l'entrée de la taille des tas";
		return;
	}


	while(!gagne)              //Tant que personne n'a gagne
	{
		choix_tas = choix_all = 0;

		AfficheTailleTas();         //Affiche la taille des tas

		if(!CodeTailleTasPuis2())         //Code la taille des tas en puissance de 2
		{
			cout << "Erreur lors du codage de la taille des tas";
			return;
		}

		if(!joueur)        //Si le joueur est humain
		{
			cout << "Joueur " << joueur+1 << "\nChoisissez le tas : ";

			do
			{
				cin >> choix_tas;          //Entrée du choix du tas

				if((choix_tas < 1) || (choix_tas > MAX_TAS))
				{
					cout << "Erreur de saisie (entre 1 et " << MAX_TAS << ") : ";
				}
				else if(tas[choix_tas-1].taille == 0)
				{
					cout << "Veuillez choisir un tas ou il reste des allumette(s) : ";
				}

			}while(((choix_tas < 1) || (choix_tas > MAX_TAS)) || (tas[choix_tas-1].taille == 0));

			cout << "\nChoississez le nombre d'allumettes a retirer : ";

			do
			{
				cin >> choix_all;           //Entrée du choix du nombre d'allumettes

				if((choix_all < 1) || (choix_all > tas[choix_tas-1].taille))
				{
					cout << "Erreur de saisie (entre 1 et " << tas[choix_tas-1].taille << ") : ";
				}

			}while((choix_all < 1) || (choix_all > tas[choix_tas-1].taille));
		}
		else          //L'ordinateur joue
		{
			choix_tas = choix_all = 0;

			//STRATEGIE
			/*
			choix_tas = ChercheTasMaxPuis2();

			if(choix_tas == -1)
			{
				cout << "Erreur!!!";
				return;
			}*/


			//SANS STRATEGIE (choix aleatoire)
			do
			{
				choix_tas = 1+(rand()%MAX_TAS);

			}while(tas[choix_tas-1].taille == 0);

			choix_all = 1+(rand()%(tas[choix_tas-1].taille));

			cout << "L'ordinateur prend " << choix_all << " allumette(s) dans le tas " << choix_tas << '\n';


		}

		tas[choix_tas-1].taille = tas[choix_tas-1].taille - choix_all;           //Affectation de la taille du tas

		//Test si quelqu'un a gagne
		for(i = 0, j = 0; i < MAX_TAS; i++)
		{
			if(tas[i].taille == 0)
			{
				j++;
			}

			if(j == 5)
			{
				cout << "\nJoueur " << joueur+1 << " : Vous avez gagne!";         //Affiche le gagnant
				gagne = 1;
			}
		}

		cout << '\n';

		joueur = !joueur;           //Changement du joueur actif
	}
}


//Définition de la fonction Puis() (de notre programme)
int Puis(int nb, int power)
{
	int i, result = nb;

	if(power < 0)     //Puissance négative
	{
		return FALSE;
	}
	else if(power == 0)         //Puissance 0
	{
		return 1;
	}
	else               //Puissance positive (0 exclut)
	{
		for(i = 1; i < power; i++)
		{
			result = result * nb;
		}

		return result;         //Retourne la valeur
	}

	return FALSE;        //Pas de résultat
}




//STRATEGIE
int ChercheTasMaxPuis2()
{
	bool ok;        //Variable temporaire

	int i, j, k, num_puis = 0, tmp;         //Compteur et variables temporaires
	Tas temp;                    //Tas temporaire

	temp.taille = tas[0].taille;


	//Recherche de la taille de tas la plus grande
	for(i = 0, j = 0; i < MAX_TAS-1; i++)
	{
		for(k = 0; k < 4; k++)
		{
			if((j+1) == val_tmp[k])
			{
				i++;
			}
		}

		if(temp.taille < tas[i+1].taille)
		{
			for(k = 0; k < 4; k++)
			{
				if((j+1) != val_tmp[k])
				{
					temp.taille = tas[i+1].taille;
					j = i+1;
				}
			}
		}
	}

	///////////////////////TEST
	cout << "j " << j << " val_tmp " << val_tmp[j] << " tai " << temp.taille << "  ";  //ICI OK POUR LES VALEURS DE LA PREMIERE FOIS




	//Codage de la taille de ce tas
	tmp = temp.taille;

	for(i = 4; i > 0; i--)
	{
		temp.codage[i-1] = (tmp/(Puis(2,i-1)));       //Codage de la taille
		tmp = temp.taille%(Puis(2,i-1));
	}




	////////////////////TEST
	cout << "cod ";
	for(i = 4; i > 0; i--)
	{
		cout << temp.codage[i-1] << ',';
	}
	cout << "   ";  //OK POUR LE CODAGE PREMIERE FOIS


	//Recherche de la plus grande puissance
	for(i = 4, ok = FALSE; (i > 0) && (!ok); i--)
	{
		if(temp.codage[i-1] == 1)
		{
			num_puis = i-1;
			ok = TRUE;
		}
	}

	////////////////////TEST
	cout << "puis " << num_puis << "   ";   //OK POUR LA VALEUR DE LA PREMIERE


	//Effectue l'addition du codage des tailles des tas
	for(i = 0; i < 4; i++)
	{
		add_codage[i] = 0;
	}

	for(i = 0; i < MAX_TAS; i++)
	{
		for(k = 0; k < 4; k++)
		{
			if(i == j)
			{
				add_codage[k] += temp.codage[k];
			}
			else
			{
				add_codage[k] += tas[i].codage[k];
			}
		}
	}



	////////////////////TEST

	cout << "add ";
	for(i = 0; i < 4; i++)
	{
		cout << add_codage[i] <<',';
	}
	cout << "  "; //OK POUR L'ADDITION DE PREMIERE


	//Test si PAIR est vrai
	if((add_codage[num_puis])%2)
	{
		return j;
	}
	else
	{
		cout << j << "  " << val_tmp[j] << '\n';
		val_tmp[val_tmp_nb] = j;
		val_tmp_nb++;
		ChercheTasMaxPuis2();
	}

	return -1;
}