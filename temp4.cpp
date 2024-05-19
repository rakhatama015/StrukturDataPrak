#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define SIZE 100

class Perpus {
private:
    string table[SIZE];
    string buku;
    string CopyTable[SIZE];
public:
    void setSize(int capacity);
    void hash(string buku, int key);
    int hashFunction(int key);
    int quadraticProbe(int index, int attempt);
    void merge(int L, int M, int R);
    void mergeSort(int L, int R);
    void displayBooks();
    void searchBooks(string cariBuku);

    void addBook(Perpus &p, string buku, int key);
    void sortBook();
    void sortBook2();
    void copyTable();

    void searchByName();
    void searchByKey();
    int searchBook(int L, int R, string bookName);
    int searchKey(int key);

    void pinjamBuku();
    void returnBook(Perpus& p, string buku, int key);

    string toUpper(string& judulBuku);
};

int main() {
    Perpus p;
    string buku;
    int key, pilihan, option, pilihan2;
    do{
        cout << "\n|=====================================================|\n";
        cout << "|=========== SELAMAT DATANG DI PERPUSTAKAAN ==========|\n";
        cout << "|=====================================================|\n";
        cout << "1. Masuk\n";
        cout << "0. Keluar\n";
        cout << "> ";
        cin >> option;
        cout << endl;
        if(option == 1){
            do{
                cout << "<======================= MENU ========================>\n";
                cout << "1. Tambahkan Buku\n";
                cout << "2. Cari Buku (By Name)\n";
                cout << "3. Cari Buku (By key)\n";
                cout << "4. Tampilkan Semua Buku\n";
                cout << "5. Pinjam Buku\n";
                cout << "6. Kembalikan Buku\n";
                cout << "0. Keluar\n";
                cout << "> ";

                cin >> pilihan;
                cin.ignore();

                switch (pilihan)
                {
                case 1:
                    p.addBook(p, buku, key);
                    p.copyTable();
                    break;
                case 2:
                    p.searchByName();
                    break;
                case 3:
                    p.searchByKey();
                    break;
                case 4:
                    p.sortBook();
                    break;
                case 5: 
                    p.pinjamBuku();
                    break;
                case 6:
                    p.returnBook(p, buku, key);
                case 0: 
                    break;
                default:
                    cout << "Pilihan Tidak Valid\n";
                    break;
                }
            }while(pilihan != 0);
        }
        else if(option == 0){
            cout << "Anda Telah Keluar\n";
            break;
        }
        else{
            cout << "Pilihan Tidak Valid\n";
        }
    }while(option != 0);
    return 0;
}

void Perpus::hash(string buku, int key) {
    int index = hashFunction(key);
    
    // Quadratic probing to handle collisions
    int attempt = 0;
    while (!table[index].empty()) {
        index = quadraticProbe(index, attempt);
        attempt++;
    }

    table[index] = buku;
}

int Perpus::hashFunction(int key) {
    return abs(key) % SIZE;
}

int Perpus::quadraticProbe(int index, int attempt) {
    return (index + attempt * attempt) % SIZE;
}

void Perpus::merge(int L, int M, int R) {
    int n1 = M - L + 1;
    int n2 = R - M;

    vector<string> Left(n1), Right(n2);

    for (int i = 0; i < n1; i++)
        Left[i] = CopyTable[L + i];
    for (int j = 0; j < n2; j++)
        Right[j] = CopyTable[M + 1 + j];

    int i = 0, j = 0, k = L;
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            CopyTable[k] = Left[i];
            i++;
        } else {
            CopyTable[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        CopyTable[k] = Left[i];
        i++;
        k++;
    }

    while (j < n2) {
        CopyTable[k] = Right[j];
        j++;
        k++;
    }
}

void Perpus::mergeSort(int L, int R) {
    if (L < R) {
        int M = L + (R - L) / 2;

        mergeSort(L, M);
        mergeSort(M + 1, R);

        merge(L, M, R);
    }
}

void Perpus::displayBooks() {

    cout << endl;
    for(int i = 0; i < SIZE; ++i) {
        if (!CopyTable[i].empty()) {
            cout << "- " << CopyTable[i] << endl;

        }
        else if(i == SIZE - 1 && CopyTable[i].empty()){
            cout << "Tidak Ada Buku Sama Sekali";
        }
    }
    cout << endl;
}

void Perpus::addBook(Perpus &p, string buku, int key){
    cout << "\nMasukkan Nama Buku Yang Akan Dimasukkan/Disimpan[Masukkan -1 Pada Key Untuk Stop]\n\n";
    do {
        cout << "Masukkan Nama Buku: ";
        getline(cin, buku);
        cout << "Masukkan Key: ";
        cin >> key;
        cout << endl;
        cin.ignore(); // Clear buffer after cin
        if (key != -1){
            buku = toUpper(buku);
            p.hash(buku, key);
        }
    } while (key != -1);
}

void Perpus::sortBook(){
    
    cout << "\nDaftar Buku" << endl;
    mergeSort(0, SIZE - 1);
    displayBooks();
}

void Perpus::copyTable(){
    for (int i = 0; i < SIZE; ++i) {
        CopyTable[i] = table[i];
    }
}

void Perpus::searchByName(){
    string bookName;
    int pilihan;
    int pilihan2 = 1;
    do{
        cout << "\nMasukkan Nama Buku Yang Ingin Dicari: ";
        getline(cin, bookName);
        
        int output = searchBook(0, SIZE - 1, bookName);
        bookName = toUpper(bookName);

        if (output == -1) {
            cout << "Buku Sedang Di Pinjam" << endl;
        } 
        else if(output == -2){
            cout << "Buku Tidak Tersedia" << endl;
        }
        else {
            cout << "Nama Buku:  " << bookName << endl;
            cout << "Rak: " << output << endl << endl;
        }
        cout << "1. Ulang\n";
        cout << "2. Pinjam Buku\n";
        cout << "0. Keluar\n";
        cout << "> ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 2:
            pinjamBuku();
            cout << "\nLanjut Mencari Buku?\n";
            cout << "1. Ulang\n";
            cout << "0. Keluar\n";
            cout << "> ";
            cin >> pilihan2;
            cin.ignore();
            break;
        
        default:
            break;
        }
    }while(pilihan != 0 && pilihan2 != 0);
    cout << endl;
}
void Perpus::searchByKey() {
    int keyNum;
    int option;
    int option2 = 1;

    do {
        cout << "\nMasukkan Key Dari Buku Yang Ingin Dicari: ";
        cin >> keyNum;

        int index = hashFunction(keyNum);
        int attempt = 0;
        bool found = false;

        while (attempt < SIZE) {
            if (table[index] != "") {
                cout << "\nNama Buku: " << table[index] << endl;
                cout << "Rak: " << index << endl << endl;
                found = true;
                break;
            }
            index = quadraticProbe(index, attempt);
            attempt++;
        }

        if (!found) {
            cout << "\nBuku Tidak Ditemukan atau Dipinjam\n" << endl;
        }
        
        cout << "1. Ulang\n";
        cout << "2. Pinjam Buku\n";
        cout << "0. Keluar\n";
        cout << "> ";
        cin >> option;

        switch (option)
        {
        case 2:
            cin.ignore();
            pinjamBuku();
            cout << "\nLanjut Mencari Buku?\n";
            cout << "1. Ulang\n";
            cout << "0. Keluar\n";
            cout << "> ";
            cin >> option2;
            option = 2;
            break;
        
        default:
            break;
        }
    } while(option != 0 && option2 != 0);
    cout << endl;
}

int Perpus::searchBook(int L, int R, string bookName){
    bookName = toUpper(bookName);
    int i, j;
    for(i = 0; i < SIZE; i++){
        if(CopyTable[i] == bookName){
            for(j = 0; j < SIZE; j++){
                if(table[j] == bookName){

                    return j;
                }
                else if((j == SIZE - 1) && table[j].empty()){

                    return -1;
                }
            }
        }
        else if(CopyTable[i] != bookName && (i == SIZE - 1)){

            return -2;
        }
    }

    return -1;
}

void Perpus::pinjamBuku(){
    char input, input2;
    string judulBuku;
    bool allEmpty = true;
    int i, j;
    int status = 0;
    do{ 
        cout << "\nSilahkan Masukkan Buku Yang Ingin Anda Pinjam: ";

        getline(cin, judulBuku);

        judulBuku = toUpper(judulBuku);

        for(i = 0; i < SIZE; i++){
            if(CopyTable[i] == judulBuku){
                for(j = 0; j < SIZE; j++){
                    if(table[j] == judulBuku){
                        cout << "Judul Buku: " << table[j] << endl;
                        cout << "Letak Buku: " << j << endl;
                        cout << "Status: Tersedia" << endl; 

                        i = i;
                        j = j;
                        break;
                    }
                    else if((j == SIZE - 1) && table[j].empty()){
                        cout << "Buku Sedang Dipinjam\n";
                        status = -1;
                        break;
                    }
                }
                break;
            }
            else if(i == SIZE - 1 && CopyTable[i] != judulBuku){
                cout << "Buku Tidak Tersedia\n";
                status = -1;
            }
        }

        if(status == 0){
            cout << "\nApakah Anda Yakin Ingin Meminjam?[Y/n]: ";
            cin >> input;
            cin.ignore();
            if(input == 'y' || input == 'Y'){
                cout << "\nAnda Berhasil Meminjam Buku: " << judulBuku << endl;
                table[j] = "";
            }
            else if(input == 'n' || input == 'N'){
                cout << "\nAnda Tidak Jadi Meminjam\n";
            }
            else{
                cout << "\nInput Tidak Valid\n";
            }
        }
            cout << "\nApakah Anda Ingin Meminjam Buku Lagi?[Y/n]: ";
            cin >> input2;
            cin.ignore();

    }while(input2 != 'n' && input2 != 'N');
}

string Perpus::toUpper(string& judulBuku){
    string result = judulBuku;
    bool capitalize = true;

    for (size_t i = 0; i < result.size(); ++i) {
        if (isspace(result[i])) {
            capitalize = true;
        } else if (capitalize && isalpha(result[i])) {
            result[i] = toupper(result[i]);
            capitalize = false;
        }
    }
    
    return result;
}

void Perpus::returnBook(Perpus& p, string buku, int key){
    cout << "\nMasukkan Nama Buku Yang Akan Dikembalikan/Disimpan[Masukkan -1 Pada Key Untuk Stop]\n\n";
    do {
        cout << "Masukkan Nama Buku: ";
        getline(cin, buku);
        cout << "Masukkan Key: ";
        cin >> key;
        cout << endl;
        cin.ignore(); // Clear buffer after cin
        if (key != -1){
            buku = toUpper(buku);
            p.hash(buku, key);
        }
    } while (key != -1);
}
