//============================================================================
// Name        : system_expert.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <cstdlib>
#include <ostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <queue>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

//#include "system_expert.hpp"
using namespace std;

string file_content;

struct Predicate
{
	string subject;
	string value;
};

struct Proposition
{
    queue<Predicate> predicats;
    //enum(ET , >, < )
    queue<string>   operators;
}Propositon;

typedef Predicate Conclusion;

struct Rule
{
	string name;
	// could be unique
	Proposition proposition;
	Conclusion conclusion;
	bool used;
};

typedef vector<Rule> Rules;

	string const file_name = "rulesDB2.xml";
	string const file_xml = "rulesDB2.xml";
	//Rules my_rules;

void testBoost(){
std::string hello( "Hello, world!" );

    BOOST_FOREACH( char ch, hello )
    {
       cout << ch;
    }
}

//Predicate getPredicate( )
Rules fillMyRules(){
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(file_xml, pt);
	Rules vecteur_regles;


	BOOST_FOREACH (ptree::value_type const& u, pt.get_child("BASE_DE_REGLES")){
        if(u.first == "REGLE"){
        	// instance exclusive a une règle
        	Rule regle;
        	queue<Predicate> predicats;
            queue<string>   operateurs;
            Conclusion conclusion;

            // Récupération du nom de la règle
            regle.name=u.second.get<string>("NAME");

            // Boucle sur les élements de la règle
            BOOST_FOREACH (ptree::value_type const& x, pt.get_child("BASE_DE_REGLES.REGLE")){
                if(x.first == "PROPOSITION"){
                    Predicate predicat;
                    predicat.subject=x.second.get<string>("SUJET");
                    predicat.value=x.second.get<string>("VALEUR");

                    predicats.push(predicat);
                }
                else if(x.first == "OPERATEUR")
                {
                    string val = u.second.get<string>("OPERATEUR");

                    // Gestion des variables vide
                    if(!val.empty()){
                        operateurs.push(val);
                    	}
                    	else
                    	{
                    	val = "NONE";
                        }
                }
                else if(x.first == "CONCLUSION")
                {

                conclusion.subject=x.second.get<string>("SUJET");
                conclusion.value=x.second.get<string>("VALEUR");

                }
                else
                {
                 //Noting to do cout << x.first <<"\n";
                }
            }
            // création de la proposition
            Proposition proposition;
            proposition.predicats = predicats;
            proposition.operators = operateurs;

            // creation de la règle
            regle.proposition = proposition;
            regle.conclusion = conclusion;
            vecteur_regles.push_back(regle);
        }

	}
	return vecteur_regles;
}




void testfillMyRules(){
    Rules file_content = fillMyRules();
    file_content.size();
    cout << file_content.size() << " Entrees" ;
}

void readFileByLine(){

	ifstream fichier( file_name.c_str(), ifstream::in );
	string ligne;

	while(getline(fichier, ligne)){
		string file_content = file_content + ligne + " \n";
	}

	fichier.close();
}

void test_file(){
	ifstream fichier( file_name.c_str(), ios::in );

		    if(fichier) {
		    	cout << "file exist ! \n";
		    	string ligne;
		    	//Read caractere
		    	char caractere;
		    	fichier.get(caractere);
		    	cout << caractere;
		    	int nbLignes = 0;
		    	while(fichier.ignore(numeric_limits<int>::max(),'\n')){
		    		nbLignes++;
		    		cout << "Le fichier contient " << nbLignes << " Lignes"<<endl ;

		    	}
		    	fichier.close();
		    	//readFileByLine();
		    	cout << file_content << " \n";

		    }else{
		    	cout << "file failed to open \n" ;
		    }
}

int main(int argc, char* argv[]){

        testfillMyRules();
	    return 0;
	}
