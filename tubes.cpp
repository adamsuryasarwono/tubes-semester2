#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// Deklarasi
class Node {
public:
    string namaProduk;
    double harga;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Tambah node baru di belakang linked list
    void tambah(string nama, double harga) { 
        Node* newNode = new Node;
        newNode->namaProduk = nama;
        newNode->harga = harga;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Tambah data dummy menggunakan array
    void tambahDataDummy() {
    if (head == nullptr) { // tambahkan data dummy hanya jika list kosong
        string dataDummy[5][2] = {{"Beras", "50000"},
                                   {"Susu", "20000"},
                                   {"Gula", "15000"},
                                   {"Telur", "30000"},
                                   {"Teh", "10000"}};

        for (int i = 0; i < 5; i++) {
            tambah(dataDummy[i][0], stod(dataDummy[i][1]));
        }
    }
}

    // Hapus node pertama
    void hapus() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }

    // Memperbarui harga produk
    bool perbarui(string namaLama, string namaBaru, double hargaBaru) {
        Node* current = head;
        while (current != nullptr) {
            if (current->namaProduk == namaLama) {
                current->namaProduk = namaBaru;
                current->harga = hargaBaru;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Menyisipkan node baru 
    void sisipSetelah(string nama, double harga, string namaSebelum) {
        Node* newNode = new Node;
        newNode->namaProduk = nama;
        newNode->harga = harga;
        Node* current = head;
        while (current != nullptr) {
            if (current->namaProduk == namaSebelum) {
                newNode->prev = current;
                newNode->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = newNode;
                } else {
                    tail = newNode;
                }
                current->next = newNode;
                return;
            }
            current = current->next;
        }
        cout << "Produk sebelumnya tidak ditemukan!" << endl;
    }

    // Menghapus node berdasarkan nama produk
    void hapusNode(string nama) {
        Node* current = head;
        while (current != nullptr) {
            if (current->namaProduk == nama) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    } else {
                        tail = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
        cout << "Produk tidak ditemukan." << endl;
    }

    // Menghapus node berdasarkan posisi
    void hapusDataUrutanTertentu(int posisi) {
        if (head == nullptr || posisi <= 0) {
            cout << "Posisi tidak valid" << endl;
            return;
        }

        Node* current = head;
        int count = 1;
        
        while (current != nullptr && count < posisi) {
            current = current->next;
            count++;
        }

        // Jika posisi melebihi jumlah node
        if (current == nullptr) {
            cout << "Posisi tidak valid" << endl;
            return;
        }
        // Hapus node pada posisi yang diminta
        if (current == head) {
            head = current->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (current == tail) {
            tail = current->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        cout << "Data pada posisi " << posisi << " berhasil dihapus" << endl;
    }

    // Hapus semua node dari linked list
    void hapusSemua() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        cout << "Semua data telah dihapus" << endl;
    }

    void tampilkan() {
        Node* current = head;
        cout << fixed << setprecision(2);
        while (current != nullptr) {
            cout << setw(20) << left << current->namaProduk << setw(10) << left << current->harga << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList daftarProduk;
    unordered_map<string, Node*> hashTable; // Hash table untuk pencarian cepat berdasarkan nama produk

    // Tambah data dummy saat program dimulai
    daftarProduk.tambahDataDummy();

    // Buat hash table dari daftar produk
    Node* current = daftarProduk.head;
    while (current != nullptr) {
        hashTable[current->namaProduk] = current;
        current = current->next;
    }

    while (true) {
        cout << "Aplikasi Inventaris Manajemen Toko" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Update Data" << endl;
        cout << "3. Tambah Data Urutan Tertentu" << endl;
        cout << "4. Hapus Data Berdasarkan Nama Barang" << endl;
        cout << "5. Hapus Data Urutan Tertentu" << endl;
        cout << "6. Hapus Seluruh Data" << endl;
        cout << "7. Tampilkan Data" << endl;
        cout << "8. Exit" << endl;

        int pilihan;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        // pilihan user
        switch (pilihan) {
            case 1: {
                string nama;
                double harga;
                cout << "Masukkan nama produk: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan harga produk: ";
                cin >> harga;
                cin.ignore();
                daftarProduk.tambah(nama, harga);
                hashTable[nama] = daftarProduk.tail; // tambahkan ke hash table
                cout << "Produk berhasil ditambahkan" << endl;
                break;
            }
            
           case 2: {
                string namaLama, namaBaru;
                double hargaBaru;
                cout << "Masukkan nama produk yang ingin diubah: ";
                cin.ignore();
                getline(cin, namaLama);
                cout << "Masukkan nama produk baru: ";
                getline(cin, namaBaru);
                cout << "Masukkan harga baru: ";
                cin >> hargaBaru;
                cin.ignore();
                
                // Cek apakah namaLama ada dalam hash table
                if (hashTable.find(namaLama) != hashTable.end()) {
                    Node* produk = hashTable[namaLama];
                    produk->namaProduk = namaBaru;
                    produk->harga = hargaBaru;
                    hashTable.erase(namaLama); // hapus dari hash table
                    hashTable[namaBaru] = produk; // tambahkan ke hash table dengan nama baru
                    cout << "Data produk berhasil diperbarui" << endl;
                } else {
                    cout << "Produk tidak ditemukan" << endl;
                }
                break;
            }
            case 3: {
                string nama, namaSebelumnya;
                double harga;
                cout << "Masukkan nama produk yang ingin disisipkan: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan harga produk: ";
                cin >> harga;
                cout << "Masukkan nama produk setelahnya: ";
                cin.ignore();
                getline(cin, namaSebelumnya);
                daftarProduk.sisipSetelah(nama, harga, namaSebelumnya);
                hashTable[nama] = daftarProduk.tail; // tambahkan ke hash table
                cout << "Produk berhasil disisipkan" << endl;
                break;
            }
            case 4: {
                string nama;
                cout << "Masukkan nama produk yang akan dihapus: ";
                cin.ignore();
                getline(cin, nama);
                daftarProduk.hapusNode(nama);
                hashTable.erase(nama); // hapus dari hash table
                cout << "Produk berhasil dihapus" << endl;
                break;
            }
            case 5: {
                int posisi;
                cout << "Masukkan posisi data yang ingin dihapus: ";
                cin >> posisi;
                daftarProduk.hapusDataUrutanTertentu(posisi);
                break;
            }
            case 6: {
                daftarProduk.hapusSemua();
                cout << "Semua data telah dihapus" << endl;
                // Kosongkan hash table
                hashTable.clear();
                break;
            }
            case 7: {
                cout << setw(20) << left << "Nama Produk" << setw(10) << left << "Harga" << endl;
                daftarProduk.tampilkan();
                break;
            }
            case 8: {
                return 0;
            }
            default: {
                cout << "Pilihan tidak valid" << endl;
                break;
            }
        }
    }
    return 0;
}

