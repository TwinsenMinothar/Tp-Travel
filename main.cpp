#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

struct Clients {
    int id;
    string name,address,email;
    long long int phone;
};
struct Destines{
    int id,price,numberofvisities;
    string location,country;
};
struct Travels{
    int id;
    vector<int> clients;
    vector<int> destines;
};
void mainMenu();
bool checkIfInt(int isint);
//Clients
void clientsMenu();
bool someClientIdExist(int id);
void removeClient();
Clients insertClient();
void changeClient();
void listAllClients();
int returnClientPosition(int id);
void infoAboutClient();
void listRemovedClients();
void recoverClients();
//Destines
Destines insertDestine();
void removeDestine();
bool someDestineIdExist(int id);
void changeDestine();
void listAllDestines();
int returnDestinePosition(int id);
void infoAboutDestine();
void destinesMenu();
void listRemovedDestines();
//Travels
Travels insertTravel();
void removeTravel();
bool someTravelIdExist(int id);
void changeTravel();
void infoAboutTravel();
void insertClientTravel();
void removeClientTravel();
void listTravelByData();
void listAllTravels();
int returnTravelPosition(int id);
int travelAveragePrice();
int travelHigherPrice();
int travelLowerPrice();
int travelTotalClients();
void travelMenu();
void listAllTravelsIds();
bool someClientTravelingThisDay(Travels newTravel);
bool someClientExistInTravel(int idt,int idc);
//File Manager / ADMIN
int saveData();
int openFile();
void adminMenu();
void restartApp();
int setAInt();
// Global vectors
vector<Clients> clients;
vector<Destines> destines;
vector<Travels> travels;

//int nclients=0;

int main(){
    mainMenu();
    return 0;
}

int openFile(){
    ifstream inDestineFile("destines.dat",ios::in);
    if(!inDestineFile){
        ofstream outDestineFile("destines.dat",ios::out);
        if(!outDestineFile){
            cout << "Error" << endl; return 1;
            }
        cout << "Nao havia arquivo de importacao de Destinos, entao um vazio foi criado!" << endl;
        }
    ifstream inClientFile("clients.dat",ios::in);
    if(!inClientFile){
        ofstream outClientFile("clients.dat",ios::out);
        if(!outClientFile){
            cout << "Error" << endl;
            return 1;
        }
        cout << "Nao havia arquivo de importacao de Clientes, entao um vazio foi criado!" << endl;
    }
    ifstream inTravelFile("travels.dat",ios::in);
    if(!inTravelFile){
        ofstream outTravelFile("travels.dat",ios::out);
        if(!outTravelFile){
            cout << "Error" << endl;
            return 1;
        }
        cout << "Nao havia arquivo de importacao de Viagens, entao um vazio foi criado!" << endl;
    }
        clients.clear();
        destines.clear();
        travels.clear();
        int fileid,numberofvisities,price;
        long long int filetel;
        string filename,fileadress,fileemail,location,country;
        int ifile=0;
    while(inClientFile >> fileid && getline(inClientFile,filename) && getline(inClientFile,fileadress) && getline(inClientFile,fileemail)
    >> filetel ){
        clients.push_back(Clients());
        clients[ifile].id=fileid;
        clients[ifile].name=filename;
        clients[ifile].address=fileadress;
        clients[ifile].email=fileemail;
        clients[ifile].phone=filetel;
        ifile++;
    }
    ifile=0;
    while(inDestineFile >> fileid && getline(inDestineFile,location) && getline(inDestineFile,country) >> numberofvisities >> price){
        destines.push_back(Destines());
        destines[ifile].id=fileid;
        destines[ifile].location=location;
        destines[ifile].country=country;
        destines[ifile].numberofvisities=numberofvisities;
        destines[ifile].price=price;
        ifile++;
    }
    ifile=0;
    int clientsid,destinesid;
    while(inTravelFile >> fileid ){
        travels.push_back(Travels());
        travels[ifile].id=fileid;
        while(inTravelFile >> clientsid && clientsid != -1 ){
            travels[ifile].clients.push_back(clientsid);
        }
        while(inTravelFile >> destinesid && destinesid != -1){
            travels[ifile].destines.push_back(destinesid);
        }
        ifile++;
    }
    cout << "||Arquivos Carregados com Sucesso||" << endl;
    return 0;
}


void mainMenu(){
    cout << "Bem vindo ao GERENCIADOR DE VIAGENS" << endl;
    cout << "Digite em qual modulo deseja entrar" << endl;
    cout << "1.Funcionalidades de gestao da aplicacao" << endl;
    cout << "2.Cliente" << endl;
    cout << "3.Destinos" << endl;
    cout << "4.Viagens" << endl;
    int mainmenu;
    mreoption:
    mainmenu=setAInt();
    switch(mainmenu){
        case 1:
        adminMenu(); break;
        case 2:
        clientsMenu();break;
        case 3:
        destinesMenu();break;
        case 4:
        travelMenu();break;
        default:
            if(cin.fail()){cin.clear();cin.ignore(256,'\n');mainmenu=0;}
            cout << "Opcao invalida, digite novamente : "; goto mreoption;
    }
}

void adminMenu(){
    cout << endl << "Menu de Gestao de Aplicacao" << endl;
    cout << "1.Exportacao de dados para arquivo" << endl;
    cout << "2.Importacao de dados do arquivo" << endl;
    cout << "3.Reniciar aplicacao" << endl;
    cout << "4.Sair" << endl;
    cout << "0.Voltar" << endl;
    int admmenu;
    string YN;
    admreoption:
    admmenu=setAInt();
    switch(admmenu){
        case 1:
        saveData();adminMenu();break;
        case 2:
        openFile();adminMenu();break;
        case 3:
        restartApp();adminMenu();break;
        case 4:
        cout << "Deseja salvar?(S/N): ";
        exitop:
        cin.ignore();
        getline(cin,YN);
        if(YN=="S"){
            saveData();
            break;
        }
        else if (YN=="N"){
            break;
        } else {
            cout << "Opcao invalida digite novamente : ";
            goto exitop;
        }
        case 0:
        mainMenu();break;
        default:
            cout << "Opcao invalida, digite novamente : "; goto admreoption;
    }
}


void restartApp(){
    clients.clear();
    destines.clear();
    travels.clear();
    cout << "||Aplicacao Reiniciada com Sucesso||" << endl;
    }

void clientsMenu(){
    cout << endl << "MENU CLIENTES" << endl;
    cout << "Qual opcao deseja utilizar?" << endl;
    cout << "1.Insercao - Cadastro de novo cliente " << endl;
    cout << "2.Remocao - Exclusao de um cliente" << endl;
    cout << "3.Alteracao - Alteracao dos dados de um cliente" << endl;
    cout << "4.Consulta - Consulta dados de um cliente " << endl;
    cout << "5.Listagem - Lista dados de todos os clientes" << endl;
    cout << "6.Clientes Deletados - Lista de Clientes deletados" << endl;
    cout << "7.Restaurar Clientes - Restaura Clientes deletados" << endl;
    cout << "0.Retornar" << endl;
    int cmenu;
    creoption:
    cmenu=setAInt();
    switch(cmenu){
        case 0:
        mainMenu(); break;
        case 1:
        clients.push_back(insertClient()); cout << endl; clientsMenu();break;
        case 2: removeClient(); clientsMenu(); break;
        case 3: changeClient(); clientsMenu(); break;
        case 4: infoAboutClient(); clientsMenu(); break;
        case 5: listAllClients(); clientsMenu(); break;
        case 6: listRemovedClients(); clientsMenu(); break;
        case 7: recoverClients(); clientsMenu(); break;
        default:
            if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            cout << "Opcao invalida, digite novamente: "; goto creoption;

        }
}

void destinesMenu(){
    cout << endl << "MENU DESTINOS" << endl;
    cout << "Qual opcao deseja utilizar?" << endl;
    cout << "1.Insercao - Cadastro de novo destino" << endl;
    cout << "2.Remocao - Exclusão de um destino " << endl;
    cout << "3.Alteracao - Alteracao dos dados de um destino" << endl;
    cout << "4.Consulta - Consulta dados de um destino" << endl;
    cout << "5.Listagem - Lista dados de todos os destinos" << endl;
    cout << "0.Retornar" << endl;
    int cmenu;
    creoption:
    cmenu=setAInt();
    switch(cmenu){
        case 0:
        mainMenu(); break;
        case 1:
        destines.push_back(insertDestine()); cout << endl; destinesMenu();break;
        case 2: removeDestine(); destinesMenu(); break;
        case 3: changeDestine(); destinesMenu(); break;
        case 4: infoAboutDestine(); destinesMenu(); break;
        case 5: listAllDestines(); destinesMenu(); break;
        default:
            if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            cout << "Opcao invalida, digite novamente: "; goto creoption;
        }
}

void travelMenu(){
    cout << endl << "MENU VIAGENS" << endl;
    cout << "Qual opcao deseja utilizar" << endl;
    cout << "1.Insercao - Cadastro de nova viagem " << endl;
    cout << "2.Remocao - Exclusao de uma viagem " << endl;
    cout << "3.Alteracao - Alteracao dos dados de uma viagem" << endl;
    cout << "4.Consulta - Consulta dados de uma viagem" << endl;
    cout << "5.Inscricao de Cliente - Inscricao de cliente em viagem" << endl;
    cout << "6.Desistencia de Cliente - Remocao de cliente em viagem" << endl;
    cout << "7.Listagem por Data - Lista dados de viagens por data " << endl;
    cout << "8.Relatorio - Relatorio sumarizado de viagens" << endl;
    cout << "9.Mostrar todos os IDs utilizados" << endl;
    cout << "0.Retornar" << endl;
    int tmenu;
    treoption:
    tmenu=setAInt();
    switch(tmenu){
    case 0: mainMenu();
    case 1: travels.push_back(insertTravel()); travelMenu(); break;
    case 2: removeTravel(); travelMenu(); break;
    case 3: changeTravel(); travelMenu(); break;
    case 4: infoAboutTravel(); travelMenu(); break;
    case 5: insertClientTravel(); travelMenu(); break;
    case 6: removeClientTravel(); travelMenu(); break;
    case 7: listTravelByData(); travelMenu(); break;
    case 8: listAllTravels(); travelMenu(); break;
    case 9: listAllTravelsIds(); travelMenu(); break;
    default:
        if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
        cout << "Opcao Invalida, digite novamente"; goto treoption;
    }
}

int saveData(){
    ofstream outClientFile("clients.dat",ios::out);
    if(!outClientFile) {
        cout << "Error" << endl;
        return 1;
    }
    ofstream outDestineFile("destines.dat",ios::out);
    if(!outDestineFile){
        cout << "Error" << endl;
        return 1;
    }
    ofstream outTravelFile("travels.dat",ios::out);
    if(!outTravelFile){
        cout << "Error" << endl;
        return 1;
    }
    for (unsigned int i=0;i<travels.size();i++){
        outTravelFile << travels[i].id << "\n";
        for(unsigned int j=0;j<travels[i].clients.size();j++){
            outTravelFile << travels[i].clients[j] << " ";
        }
        outTravelFile << "-1 ";
        for(unsigned int j=0;j<travels[i].destines.size();j++){
            outTravelFile << travels[i].destines[j] << " ";
        }
        outTravelFile << "-1" << endl;
    }
    for (unsigned int j=0;j<clients.size();j++){
        outClientFile << clients[j].id << clients[j].name << "\n" << clients[j].address << "\n" << clients[j].email << "\n"
        << clients[j].phone << endl ;
    }
    for (unsigned int j=0; j<destines.size();j++){
        outDestineFile << destines[j].id << destines[j].location << "\n" << destines[j].country << "\n" << destines[j].numberofvisities
        << "\n" << destines[j].price << endl;
        }
    cout << "||Arquivos Salvos com Sucesso||" << endl;
    return 0;
}

Clients insertClient(){
    Clients newClient;
    int id=1;
    while(someClientIdExist(id)){id++;}
    cout << "Entre com os dados do Cliente " << endl;
    cout << "Digite o Id desejado ou 0 para atribuicao automatica: ";
    newClient.id=setAInt();
    while (someClientIdExist(newClient.id)||newClient.id<0){
        cout << "Id ja utilizado ou invalido, entre com outro Id: ";
        newClient.id=setAInt();
        cout << endl;
    }
    if(newClient.id==0){newClient.id=id;}
    cin.ignore();
    cout << "Nome:";
    getline(cin,newClient.name);
    cout << "Endereco:";
    getline(cin ,newClient.address);
    cout << "Email:";
    cin >> newClient.email;
    cout << "Telefone:";
    newClient.phone=setAInt();
   // while(cin.fail()){cin.clear();cin.ignore(256,'\n'); cout << "Telefone invalido Digite outro: "; cin >> newClient.phone;}
    cout << endl << "|||Cliente inserido|||" << endl;
    return newClient;
}

Destines insertDestine(){
    Destines newDestine;
    int id=1;
    while(someDestineIdExist(id)){id++;}
    cout << "Entre com os dados do Destino " << endl;
    cout << "Digite o Id desejado ou 0 para atribuicao automatica: ";
    newDestine.id=setAInt();
    while (someDestineIdExist(newDestine.id)||newDestine.id<0){
        cout << "Id ja utilizado ou invalido, entre com outro Id: ";
        newDestine.id=setAInt();
        cout << endl;
    }
    if(newDestine.id==0){newDestine.id=id;}
    cin.ignore();
    cout << "Localidade:";
    getline(cin,newDestine.location);
    cout << "Pais:";
    getline(cin ,newDestine.country);
    cout << "Numero de locais a visitar:";
    newDestine.numberofvisities=setAInt();
    cout << "Preco:";
    newDestine.price=setAInt();
    cout << endl << "|||Destino inserido|||" << endl;
    return newDestine;
}

bool someClientIdExist(int id){
    //if(cin.fail()){cin.clear();cin.ignore(256,'\n'); return true;}
    if(id<0) return false;
    for(unsigned int i=0;i<clients.size();i++){
        if(id==clients[i].id) return true;
    }
    return false;
}

void listRemovedClients(){
    int thereis = 0;
    for(unsigned int i=0;i<clients.size();i++){
        if(clients[i].id<0){
        cout << clients[i].name << " | ";
        thereis=1;
        }
    }if (thereis == 0) cout << "Nao ha clientes deletados";
    cout << endl;
}

void recoverClients(){
    cin.ignore();
    string name;
    int restaured=0;
    cout << "Digite o nome do Cliente a ser Restaurado: ";
    getline(cin,name);
    for(unsigned int i=0;i<clients.size();i++){
        if(name==clients[i].name&&clients[i].id<0){
            clients[i].id=-clients[i].id;
            restaured=1;
        }
    }
    if(restaured==1)cout << "|| " << name << " restaurado com Sucesso||" << endl;
    else cout << "Nenhum cliente com o nome " << name << " foi deletado";
}

bool someDestineIdExist(int id){
   // if(cin.fail()){cin.clear();cin.ignore(256,'\n'); return true;}
    if(id<0) return false;
    for (unsigned i=0;i<destines.size();i++){
        if(id==destines[i].id) return true;
    }
    return false;
}

void listRemovedDestines(){
    for(unsigned int i=0;i<destines.size();i++){
        if(destines[i].id==0){
        cout << destines[i].location << " | ";
        }
    }
    cout << endl;
}

void removeClient(){
    int id;
    cout << "ID do cliente a ser removido:" << endl;
    id=setAInt();
    if(someClientIdExist(id)){
        clients[returnClientPosition(id)].id=-clients[returnClientPosition(id)].id;
        cout << "||Cliente removido com Sucesso||" << endl;
    }else cout << "Cliente inexistente" << endl;
}

void removeDestine(){
    int id;
    cout << "ID do destino a ser removido:" << endl;
    id=setAInt();
    if(someDestineIdExist(id)){
        destines[returnDestinePosition(id)].id=-destines[returnDestinePosition(id)].id;
        cout << "||Destino removido com Sucesso||" << endl;
    }else cout << "Destino inexistente" << endl;
}

void changeClient(){
    cout << "Digite o id do cliente: ";
    int id;
    id=setAInt();
    id=returnClientPosition(id);
    cout << "Qual dos seguintes dados sera alterado?" << endl;
    cout << "1. Nome" << endl;
    cout << "2. Endereco" << endl;
    cout << "3. Email" << endl;
    cout << "4. Telefone" << endl;
    int option;
    option=setAInt();
    cin.ignore();
    switch(option){
    case 1:
        cout << "Qual o novo nome?" << endl;
        getline(cin,clients[id].name);
        break;
    case 2:
        cout << "Qual o novo endereco?" << endl;
        getline(cin,clients[id].address);
        break;
    case 3:
        cout << "Qual o novo email?" << endl;
        getline(cin,clients[id].email);
        break;
    case 4:
        cout << "Qual o novo telefone?" << endl;
        clients[id].phone=setAInt();
       // while(cin.fail()){cin.clear();cin.ignore(256,'\n'); cout << "Telefone invalido, Digite outro: "; cin >> clients[id].phone;}
        break;
    }
    cout << "Dados alterados" << endl;
}

void changeDestine(){
    cout << "Digite o id do destino: ";
    int id;
    id=setAInt();
    id=returnDestinePosition(id);
    cout << "Qual dos seguintes dados sera alterado?" << endl;
    cout << "1. Localidade" << endl;
    cout << "2. Pais" << endl;
    cout << "3. Numero de locais a visitar" << endl;
    cout << "4. Preco" << endl;
    int option;
    option=setAInt();
    cin.ignore();
    switch(option){
    case 1:
        cout << "Qual a nova Localidade?" << endl;
        getline(cin,destines[id].location);
        break;
    case 2:
        cout << "Qual o novo Pais?" << endl;
        getline(cin,destines[id].country);
        break;
    case 3:
        cout << "Qual e a nova quantidade de locais a visitar?" << endl;
        destines[id].numberofvisities=setAInt();
      //  while(cin.fail()){cin.clear();cin.ignore(256,'\n'); cout << "Numero de locais a visitar invalido, Digite outro: "; cin >> destines[id].numberofvisities;}
        break;
    case 4:
        cout << "Qual o novo preco?" << endl;
        destines[id].price=setAInt();
        //while(cin.fail()){cin.clear();cin.ignore(256,'\n'); cout << "Preco invalido, Digite outro: "; cin >> destines[id].price;}
        break;
    }
    cout << "Dados alterados" << endl;
}

void listAllClients(){
    if(clients.size()==0){cout << "Nao ha clientes cadastrados" << endl; return;}
    for(unsigned int i=0;i<clients.size();i++){
        if (clients[i].id>0){
            cout << fixed << left;
            cout << "Id: " << setw(4) << clients[i].id << " Nome: " << setw(25) << clients[i].name << " Endereco: " << setw(40) << clients[i].address << " Email: " << setw(30) << clients[i].email << " Telefone: " << setw(15) << clients[i].phone << endl;
        }
    }
}

void listAllDestines(){
    if(destines.size()==0){cout << "Nao ha destinos cadastrados" << endl; return;}
    for(unsigned int i=0;i<destines.size();i++){
        if (destines[i].id>0){
            cout << fixed << left;
            cout << "Id: " << setw(4) << destines[i].id << " Localidade: " << setw(15) << destines[i].location << " Pais: " << setw(15) << destines[i].country << " Numero de locais a visitar: " << setw(10) << destines[i].numberofvisities << " Custo: " << setw(10) << destines[i].price << endl;
        }
    }
}

int returnClientPosition(int id){
    int i=0;
    while(clients[i].id!=id){
        i++;
    }
    return i;
}

int returnDestinePosition(int id){
    int i=0;
    while(destines[i].id!=id){
        i++;
    }
    return i;
}

void infoAboutClient(){
    int id;
    cout << "Digite o id do Cliente: ";
    id=setAInt();
    if(someClientIdExist(id)){
        int i=returnClientPosition(id);
            cout << fixed << left;
            cout << "Id: " << setw(4) << clients[i].id << " Nome: " << setw(25) << clients[i].name << " Endereco: " << setw(40) << clients[i].address << " Email: " << setw(30) << clients[i].email << " Telefone: " << setw(15) << clients[i].phone << endl;
        }else {
            cout << "Cliente nao cadastrado" << endl;
            }
    }

void infoAboutDestine(){
    int id;
    cout << "Digite o id do Destino: ";
    id=setAInt();
    if(someDestineIdExist(id)){
        int i=returnDestinePosition(id);
        cout << fixed << left;
        cout << "Id: " << setw(4) << destines[i].id << " Localidade: " << setw(15) << destines[i].location << " Pais: " << setw(15) << destines[i].country << " Numero de locais a visitar: " << setw(10) << destines[i].numberofvisities << " Custo: " << setw(10) << destines[i].price << endl;
        }else {
            cout << "Destino nao cadastrado" << endl;
            }
    }

Travels insertTravel(){
    newtravel:
    Travels newTravel;
    int id,seq;
    int id2=1;
    while(someTravelIdExist(id2)){id2++;}
    cout << "Digite o id da Viagem desejado ou 0 para atribuicao automatica :"; cin >> newTravel.id;
    while(someTravelIdExist(newTravel.id)||newTravel.id<0){
        cout << "Id ja utilizado ou invalido, entre com outro Id: ";
        newTravel.id=setAInt();
        cout << endl;
    }
    if(newTravel.id==0)newTravel.id=id2;
    cout << "Digite o Id dos clientes que participarao da viagem: ";
    id=setAInt();
    if(!someClientIdExist(id)){
        cout << "Cliente inexistente" << endl;
        }else  newTravel.clients.push_back(id);
        id=1;
    while(id!=0){
        cout << "Proximo Cliente (Digite 0 ao fim dos Clientes): ";
        id=setAInt();
        if(!someClientIdExist(id)){
           //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            if(id!=0)cout << "Cliente inexistente" << endl;
        }else if(id!=0) newTravel.clients.push_back(id);
    }
/*    cout << "Digite as sequencias de deslocamentos (id do destino/Mes/Dia sem barras): ";
    seq=setAInt();
    id=seq/10000;
    while(!someDestineIdExist(id)){
        cout << "Destino Inexistente digite outro Destino: " << endl;
        id=setAInt();
    }*/
    cout << "Digite o id do Destino a data da Partida (Id 01 no Mes e Dia 25 de dezembro = 011225)" << endl;
    seq=setAInt();
    id=seq/10000;
    if(seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1){
        cout << "Data invalida" << endl;
    }else if(!someDestineIdExist(id)){
		cout << "Destino invalido" << endl;
	} else newTravel.destines.push_back(seq);
    seq=1;
    while (seq!=0){
        cout << "Proximo Destino (Digite id 0 para finalizar destinos) :";
        seq=setAInt();
        id=seq/10000;
        while(!someDestineIdExist(id)){
            cout << "Destino Inexistente, digite novamente o id e a data" << endl;
            seq=setAInt();
        }
        while((seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1)&&seq!=0){
            cout << "Data invalida, digite novamente o id e a data: ";
            seq=setAInt();
            while(seq%10000<newTravel.destines.back()%10000&&seq!=0){
               // if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
                cout << "Cronologicamente impossivel, digite novamente o id e a data: ";
                seq=setAInt();
        }
        while(seq%10000<newTravel.destines.back()%10000&&seq!=0){
            //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            cout << "Cronologicamente impossivel, digite novamente o id e a data: ";
            seq=setAInt();
        }
            while((seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1)&&seq!=0){
                cout << "Data invalida, digite novamente o id e a data: ";
                seq=setAInt();
            }
        }
		if(seq!=0) newTravel.destines.push_back(seq);
        }
    if(someClientTravelingThisDay( newTravel)){
        int opterr;
        cout << "Deseja sair ou rever os dados de Viajem?" << endl;
        newTravel.clients.clear();
        newTravel.destines.clear();
        cout << "1.Sair" << endl;
        cout << "2.Rever" << endl;
        while((opterr=setAInt())){
            switch(opterr) {
                case 1: travelMenu(); break;
                case 2: goto newtravel;
                default: cout << "Opcao invalida digite novamente" << endl;
            }
        }
    }
    cout << "||Viagem Cadastrada com Sucesso||" << endl;
    return newTravel;
}

void removeTravel(){
    cout << "Digite o id da Viagem a remover: ";
    int id;
    id=setAInt();
    if(someTravelIdExist(id)){
        travels.erase(travels.begin()+returnTravelPosition(id));
        cout << endl << "|| Viagem Removida com Sucesso||" << endl;
    }else cout << endl << "Viagem Inexistente" << endl;
}

bool someTravelIdExist(int id){
    //if(cin.fail()){cin.clear();cin.ignore(256,'\n');return true;}
    if(id<0) return false;
    for (unsigned int i=0;i<travels.size();i++){
        if(travels[i].id==id)return true;
        }
    return false;
    }

int returnTravelPosition(int id){
    for(unsigned int i=0;i<travels.size();i++){
        if(travels[i].id==id) return i;
        }
    return -1;
    }

void changeTravel(){
    cout << "Digite o id da Viagem que deseja mudar: ";
    int id,seq;
    id=setAInt();
    if(!someTravelIdExist(id)){
        cout << "Viagem Inexistente" << endl;
        return ;
    }
    changetravel:
    int i = returnTravelPosition(id);
    travels.erase(travels.begin()+i);
    travels[i].id=id;
    cout << "Digite o Id dos clientes que participarao da viagem: ";
    id=setAInt();
    if(!someClientIdExist(id)){
        cout << "Cliente inexistente" << endl;
        }else  travels[i].clients.push_back(id);
        id=1;
    while(id!=0){
        cout << "Proximo Cliente (Digite 0 ao fim dos Clientes): ";
        id=setAInt();
        if(!someClientIdExist(id)){
            //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            if(id!=0)cout << "Cliente inexistente" << endl;
        }else if(id!=0) travels[i].clients.push_back(id);
    }
    cout << "Digite as sequencias de deslocamentos (id do destino/Mes/Dia sem barras): ";
    seq=setAInt();
    id=seq/10000;
    if(!someDestineIdExist(id)){
        //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
        cout << "Destino Inexistente" << endl;
    }else if((seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1)&&seq!=0){
        cout << "Data invalida" << endl;
    } else travels[i].destines.push_back(seq);
    seq=1;
    while (seq!=0){
        cout << "Proximo Destino (Digite 0 ao fim dos Destinos) :";
        seq=setAInt();
        while(seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1){
        //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            cout << "Data invalida, digite novamente o id e a data: ";
            seq=setAInt();
            while(seq%10000<travels[i].destines.back()%10000&&seq!=0){
                //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
                cout << "Cronologicamente impossivel, digite novamente o id e a data: ";
                seq=setAInt();
            }
        }
        while(seq%10000<travels[i].destines.back()%10000&&seq!=0){
            if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
            cout << "Cronologicamente impossivel, digite novamente o id e a data: ";
            cin >> seq;
            while(seq%100>31||seq%100<1||seq%10000/100>12||seq%10000/100<1){
                if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
                cout << "Data invalida, digite novamente o id e a data: ";
                seq=setAInt();
        }
    }
        id=seq/10000;
    if(!someDestineIdExist(id)){
        //if(cin.fail()){cin.clear();cin.ignore(256,'\n');}
        if(seq!=0)cout << "Destino inexistente" << endl;
            }else if(seq!=0) travels[i].destines.push_back(seq);
        }
    if(someClientTravelingThisDay(travels[i])){
        int opterr;
        cout << "Deseja sair ou rever os dados de Viajem?" << endl;
        travels[i].clients.clear();
        travels[i].destines.clear();
        cout << "1.Sair" << endl;
        cout << "2.Rever" << endl;
        while((opterr=setAInt())){
            switch(opterr) {
                case 1: travelMenu(); break;
                case 2: goto changetravel;
                default: cout << "Opcao invalida digite novamente" << endl;
            }
        }
    }
    cout << "||Viagem Alterada com Sucesso||" << endl;
}

void infoAboutTravel(){
    int id,price=0;
    cout << "Digite o id da Viagem: ";
    id=setAInt();
    if(someTravelIdExist(id)){
        int idt=returnTravelPosition(id);
        cout << endl <<"Id da Viagem: " << travels[idt].id << endl;
        cout << "Clientes:" << endl;
        for (unsigned int j=0;j<travels[idt].clients.size();j++){
            cout <<"Id: " << travels[idt].clients[j] << " " << clients[returnClientPosition(travels[idt].clients[j])].name << "||";
        }
        cout << endl << "Destinos: " << endl;
        for(unsigned int j=0;j<travels[idt].destines.size();j++){
            cout << "Id: " << travels[idt].destines[j]/10000 << " " << destines[returnDestinePosition(travels[idt].destines[j]/10000)].location << ", na data(mes/dia): " << (travels[idt].destines[j]/100)%100 << "/" << travels[idt].destines[j]%100 << "||";
        }
        for(unsigned int j=0;j<travels[idt].destines.size();j++){
            price+=destines[returnDestinePosition(travels[idt].destines[j]/10000)].price;
        }
        cout << endl << "Preco total da Viajem : R$" << price;
    }else {
            cout << endl <<"Viagem nao cadastrada";
        }
    cout << endl;
    }

void insertClientTravel(){
    int idt,idc;
    cout << "Digite o id da Viagem: ";
    idt=setAInt();
    if(someTravelIdExist(idt)){
        int i = returnTravelPosition(idt);
        cout << "Digite o id do Cliente que deseja inserir na Viagem: ";
        idc=setAInt();
        if(someClientIdExist(idc)&&(!someClientExistInTravel(idt,idc))){
            travels[i].clients.push_back(idc);
            cout << "|| Cliente inserido com Sucesso||" << endl;
        }else cout << endl << "Cliente nao existe ou ja esta presente nesta Viajem" << endl;
    }else cout << "Viagem nao Cadastrada" << endl;
}

void removeClientTravel(){
    int id;
    cout << "Digite o id da Viagem: ";
    id=setAInt();
    if(someTravelIdExist(id)){
        int i = returnTravelPosition(id);
        cout << "Digite o id do Cliente que deseja remover da Viagem: ";
        id=setAInt();
        if(someClientIdExist(id)){
            for(unsigned int j=0;j<travels[i].clients.size();j++){
                if(travels[i].clients[j]==id){
                    travels[i].clients.erase(travels[i].clients.begin()+j);
                    cout << "||Cliente Removido com Sucesso||" << endl;
                    return ;
                }
            }
            cout << "Cliente nao inscrito" << endl;
        }
    }else cout << "Cliente Inexistente" << endl;
}

void listTravelByData(){
    int begindata,finaldata;
    cout << "Digite a data inicial da listagem (mes/dia) sem barra (1225 para 25 de dezembro) : ";
    begindata=setAInt();
    cout << "Digite a data final da listagem (mes/dia) sem barras (1225 para 25 de dezembro) : ";
    finaldata=setAInt();
    for(unsigned int i=0;i<travels.size();i++){
        for(unsigned int j=0;j<travels[i].destines.size();j++){
            if(begindata<=travels[i].destines[j]%10000 && travels[i].destines[j]%10000<=finaldata){
                cout << endl <<"Id da Viagem: " << travels[i].id << endl;
                cout << "Clientes:" << endl;
                for (unsigned int j=0;j<travels[i].clients.size();j++){
                    cout <<"Id: " << travels[i].clients[j] << " " << clients[returnClientPosition(travels[i].clients[j])].name << "||";
                }
                cout << endl << "Destinos: " << endl;
                for(unsigned int j=0;j<travels[i].destines.size();j++){
                cout << "Id: " << travels[i].destines[j]/10000 << " " << destines[returnDestinePosition(travels[i].destines[j]/10000)].location << ", na data(mes/dia): " << (travels[i].destines[j]/100)%100 << "/" << travels[i].destines[j]%100 << "||";
                }
                cout << endl;
                break;
            }else cout << "Nao ha viagens cadastradas nessas datas" << endl;
        }
    }
    cout << endl;
}

void listAllTravels(){
    cout << "Numero total de Viagens: " << travels.size() << endl;
    cout << "Menor valor de Viagem: " << travelLowerPrice() << endl;
    cout << "Maior valor de Viagem: " << travelHigherPrice() << endl;
    cout << "Valor medio das Viagens: " << travelAveragePrice() << endl;
    cout << "Numero total de clientes: " << travelTotalClients() << endl;
    cout << "Numero medio de clientes: " << travelTotalClients()/travels.size() << endl;
}

int travelTotalClients(){
    int nclients=0;
    for(unsigned int i=0;i<travels.size();i++){
        nclients+=travels[i].clients.size();
    }
    return nclients;
}

int travelLowerPrice(){
    int price=0,price2=0,id,k;
    for(unsigned int i=0;i<travels.size();i++){
        for(unsigned int j=0;j<travels[i].destines.size();j++){
            id=travels[i].destines[j]/10000;
            k=returnDestinePosition(id);
            price+=destines[k].price;
        }
        if(price2==0)price2=price;
        if(price<price2&&price!=0)price2=price;
        price = 0;
    }
    return price2;
}

int travelHigherPrice(){
    int price=0,price2=0,id,k;
    for(unsigned int i=0;i<travels.size();i++){
        for(unsigned int j=0;j<travels[i].destines.size();j++){
            id=travels[i].destines[j]/10000;
            k=returnDestinePosition(id);
            price+=destines[k].price;
        }
    if(price2==0)price2=price;
    if(price>price2)price2=price;
    price = 0;
    }
    return price2;
}

int travelAveragePrice(){
    int price=0,n=travels.size(),id,k;
    for(unsigned int i=0;i<travels.size();i++){
        for(unsigned int j=0;j<travels[i].destines.size();j++){
            id=travels[i].destines[j]/10000;
            k=returnDestinePosition(id);
            price+=destines[k].price;
        }
    }
    price=price/n;
    return price;
}

void listAllTravelsIds(){
    cout << "Ids: ";
    for(unsigned int i=0;i<travels.size();i++){
        cout << travels[i].id << " | ";
    }
    cout << endl;
}

bool checkIfInt(int isint){
    if(isint/isint==0) return true;
    else return false;
}
/*
    Pega os clientes  da nova viajem e compara com todas outras existentes.
Caso cliente esteja em uma outra viajem compare as datas dos deslocamentos.


 */
bool someClientTravelingThisDay(Travels newTravel){
    for(unsigned int j=0;j<travels.size();j++){
        for(unsigned int k=0;k<travels[j].clients.size();k++){
            for(unsigned int i=0;i<newTravel.clients.size();i++){
                if(newTravel.clients[i]==travels[j].clients[k]){
                    for(unsigned int i2=0;i2<newTravel.destines.size();i2++){
                        for(unsigned int j2=0;j2<travels[j].destines.size();j2++){
                            if(newTravel.destines[i2]%10000==travels[j].destines[j2]%10000){
                                cout << "O cliente " << clients[returnClientPosition(travels[j].clients[k])].name << " esta em outra viajem na mesma data" << endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool someClientExistInTravel(int idt, int idc){
    for(unsigned int i=0;i < travels[returnTravelPosition(idt)].clients.size();i++){
        if(travels[returnTravelPosition(idt)].clients[i]==idc) return true;
    }
    return false;
}

int setAInt(){
    long long int myint;
    cin >> myint;
    while(cin.fail()||myint<0){
        cin.clear();
        cin.ignore(256,'\n');
        cout << "Entrada invalida digite novamente: ";
        cin >> myint;
    }
    return myint;
}
