/* 	Universidade de Brasilia
	Instituto de Ciencias Exatas
	Departamento de Ciencia da Computacao
	Teoria e Aplicação de Grafos - 1/2018
	Alunos: Diego Antonio Barbosa cardoso -16/0005116 , Lucas Junior Ribas - 16/0052289
	Versão do compilador:g++ (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609
	Descricao: Este progama faz o maior emparelhamento estavel entre professores e escolas descrito no arquivo de entrada
	Sites utilizados como referencia :
	Para executar utilize  g++ -std=c++11 t.cpp -o t e depois utlize ./t lembrando que para o funcionamento adequado
	do progama os arquivos:
     */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class Professor{
    string name ;
    int hab ;
    vector<string> escolas;

    public:
        Professor(string name, int hab ,vector<string> escolas);
        void galeShapley();
};

Professor::Professor(string name, int hab, vector<string> escolas){
    this->name = name;
    this->hab = hab;
    this->escolas = escolas; 
}

class Escola{
    string name;
    int hab;
    int vagas;

    public:
        Escola(string name, int hab, int vagas);
};

Escola::Escola(string name, int hab, int vagas){
    this->name = name;
    this->hab = hab;
    this->vagas = vagas;
}

void criaListaPref(vector<Professor> prof, vector<Escola> esc){
    ifstream file;
    string linha;
    string sub = "";
    string name;
    int hab;
    vector<string> escolas;
    int vagas;
    file.open("entradaProj3TAG.txt", ios::in);
    int i = 0;
    int flag = 0;
    int spacecount = 0;
    while(getline(file,linha)){
        if(i < 3){
            i++;
        }
        else{
            if (linha == "(P100, 3): (E1, E47, E4, E50, E10)"){
                i = 0;
                flag = 1;
            }
            if((flag == 0) || (i == 0)){
                for(int j = 0; j != linha.length() ;j++){
                    if((linha[j] != ',') && (linha[j] != '(') && (linha[j] != ':') && (linha[j] != '\n')){
                        if ((linha[j] != ' ') && (linha[j] != ')')){
                            sub = sub + linha[j];
                        }
                        else{
                            spacecount++;
                            if(spacecount == 1){
                                name = sub;
                            }
                            else if(spacecount == 2){
                                hab = stoi(sub);
                            }
                            else{
                                escolas.push_back(sub);
                            }
                            sub = "";
                        }
                    }
                }
                Professor p(name,hab,escolas);
                prof.push_back(p);
                escolas.erase(escolas.begin(),escolas.end());
                spacecount = 0;
                sub = "";
            }
            else{
                 for(int j = 0; j != linha.length() ;j++){
                    if((linha[j] != '(') && (linha[j] != ':') && (linha[j] != '\n')){
                        if ((linha[j] != ')')){
                            sub = sub + linha[j];
                        }
                        else{
                            spacecount++;
                            if(spacecount == 1){
                                name = sub;
                            }
                            else if(spacecount == 2){
                                hab = stoi(sub);
                            }
                            else{
                                vagas = stoi(sub);
                            }
                            sub = "";
                        }
                    }
                }
                Escola e(name,hab,vagas);
                esc.push_back(e);
                spacecount = 0;
                sub = "";
            }  
        }
    }
}

int main(){
    vector<Professor> prof;
    vector<Escola>esc;
    criaListaPref(prof,esc);
    
}