#include <iostream>
#include <fstream>
#include "./Hash/hash.h"
#include "./ConstantParameters/const.h"
#include "./Register/dataRegister.h"

using namespace std;

int main(int argc, char *argv[]){
    int id = atoi(argv[1]); //Id para a busca
    int bucketPosition = hashFunction(id, BUCKETS_QTD) * BLOCK_SIZE * BLOCKS_PER_BUCKET;
    DataRegister tempData; //Para guardar o registro temporariamente
    
    fstream fout; //Stream de dados para o arquivo

    fout.open("dataFile.dat", ios::in | ios::binary); //Abrindo arquivo para leitura

    if(fout){
        fout.seekg(bucketPosition, ios::beg);
        
        //Loop para procurar o registro no bucket
        //Para fazer.
        
        fout.read(reinterpret_cast<char*>(&tempData), sizeof(DataRegister));

        fout.close(); //Fechando arquivo
    }
    else{
        cout << "Não foi possivel abrir o arquivo binário para escrita..." << endl;
    }
}