#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>
#include "./ConstantParameters/const.h"
#include "./Hash/hash.h"
#include "./Register/dataRegister.h"

using namespace std;

void clearFile(string fileName){ //Função para limpar um arquivo
    fstream fout; //Stream de dados para o arquivo
    fout.open(fileName.c_str(), ios::out | ios::trunc); //Abrindo arquivo para escrita e limpando seu conteúdo
    fout.close();
}

void hashTableToFile(){
    for(int cont = 0; cont < BUCKETS_QTD; cont++){
        
    }
}

void saveRegister(DataRegister data){ //Função para salvar os registros em memória secundaria
    fstream fout; //Stream de dados para o arquivo

    fout.open("dataFile.dat", ios::out | ios::binary | ios::app); //Abrindo arquivo para escrita

    if(fout){
        fout.write(reinterpret_cast<char*>(&data), sizeof(DataRegister)); //Escrevendo registro no arquivo
        fout.close(); //Fechando arquivo
    }
    else{
        cout << "Não foi possivel abrir o arquivo binário para escrita..." << endl;
    }
}

void processCSV(char *file){ //Função para ler os registros do csv
    ifstream inputFile; //Stream de dados para o arquivo
    inputFile.open(file); //Abrindo para leitura
    if(inputFile){ //Verificando se arquivo está aberto
        DataRegister regTemp; //Variavel para armazenar temporariamente um registro.
        string tempString; //String para receber temporariamente o conteudo de uma linha e modificá-la
        string line = "";  //String para armazenar a linha atual
        clearFile("dataFile.dat"); //Limpar arquivo de dados caso já exista
        //hashTableToFile(); //Gerar os buckets no arquivo


        while(getline(inputFile, line)){
            //A estratégia usada foi pegar uma linha, armazenar em uma stringstream, manipular a linha e colocar no campo correspondente do registro
            stringstream inputString(line);

            //ID
            tempString = "";
            getline(inputString, tempString, ';'); //Usando ';' como separador
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end()); //Para retirar as aspas
            regTemp.ID = atoi(tempString.c_str()); //Convertendo para int

            //Titulo
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            strncpy(regTemp.Titulo, tempString.c_str(), 300);

            //Ano
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            regTemp.Ano = atoi(tempString.c_str());

            //Autores
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            strncpy(regTemp.Autores, tempString.c_str(), 150);

            //Citacoes
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            regTemp.Citacoes = atoi(tempString.c_str());

            //Atualizacao
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            strncpy(regTemp.Atualizacao, tempString.c_str(), 25);

            //Snippet
            tempString = "";
            getline(inputString, tempString, ';');
            tempString.erase (remove(tempString.begin(), tempString.end(), '"'), tempString.end());
            strncpy(regTemp.Snippet, tempString.c_str(), 1024);

            line = "";

            //Para testar cada registro
            /*
            cout << "ID: " << regTemp.ID << endl;
            cout << "Titulo: " << regTemp.Titulo << endl;
            cout << "Ano: " << regTemp.Ano << endl;
            cout << "Autores: " << regTemp.Autores << endl;
            cout << "Citacoes: " << regTemp.Citacoes << endl;
            cout << "Atualizacao: " << regTemp.Atualizacao << endl;
            cout << "Snippet: " << regTemp.Snippet << endl;
            cout << endl;
            */

           saveRegister(regTemp);
        }

        inputFile.close(); //Fechar o arquivo
    }
    else{
        cout << "Não foi possivel abrir o arquivo .csv para leitura..." << endl;
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Não foram passados argumentos validos" << "\n";
    }
    else{
        char* file = argv[1];
        processCSV(file);
    }
}