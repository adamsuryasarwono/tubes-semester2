#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

// Deklarasi Node untuk Doubly Linked List
class Node {
public:
    string namaProduk;
    double harga;
    Node* prev;
    Node* next;
};

// Deklarasi Order untuk pesanan
class Order {
public:
    string namaProduk;
    int jumlah;
    string satuan;
    Order* next;
    Order(string nama, int qty, string sat) : namaProduk(nama), jumlah(qty), satuan(sat), next(nullptr) {}
};

// Kelas untuk Doubly Linked List
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

// Kelas untuk Queue
class OrderQueue {
public:
    Order* front;
    Order* rear;

    OrderQueue() {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(string nama, int jumlah, string satuan) {
        Order* newOrder = new Order(nama, jumlah, satuan);
        if (rear == nullptr) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue kosong, tidak ada pesanan untuk dihapus." << endl;
            return;
        }
        Order* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    void tampilkan() {
        Order* current = front;
        cout << "Daftar Pesanan (Queue):" << endl;
        while (current != nullptr) {
            cout << "Nama Produk: " << current->namaProduk << ", Jumlah: " << current->jumlah << " " << current->satuan << endl;
            current = current->next;
        }
        cout << endl;
    }
};

// Struct untuk menyimpan data stok
struct Stok {
    string namaProduk;
    int jumlah;
    string satuan;
};

// Kelas untuk Stack
class StockStack {
public:
    stack<Stok> stockStack;

    void push(string nama, int jumlah, string satuan) {
        Stok newStok = {nama, jumlah, satuan};
        stockStack.push(newStok);
        cout << "Stok " << nama << " (" << jumlah << " " << satuan << ") berhasil ditambahkan ke stack." << endl;
    }

    void pop() {
        if (stockStack.empty()) {
            cout << "Stack kosong, tidak ada stok yang dapat dihapus." << endl;
        } else {
            Stok stok = stockStack.top();
            stockStack.pop();
            cout << "Stok " << stok.namaProduk << " (" << stok.jumlah << " " << stok.satuan << ") berhasil dihapus dari stack." << endl;
        }
    }

    void tampilkan() {
        if (stockStack.empty()) {
            cout << "Stack kosong, tidak ada stok yang dapat ditampilkan." << endl;
        } else {
            stack<Stok> tempStack = stockStack;
            cout << "Daftar Stok (Stack):" << endl;
            while (!tempStack.empty()) {
                Stok stok = tempStack.top();
                cout << "Nama Produk: " << stok.namaProduk << ", Jumlah: " << stok.jumlah << " " << stok.satuan << endl;
                tempStack.pop();
            }
            cout << endl;
        }
    }
};

int main() {
    DoublyLinkedList daftarProduk;
    unordered_map<string, Node*> hashTable; // Hash table untuk pencarian cepat berdasarkan nama produk
    OrderQueue pesananQueue; // Queue untuk menyimpan pesanan
    StockStack stokStack; // Stack untuk mengelola stok produk

    // Tambah data dummy saat program dimulai
    daftarProduk.tambahDataDummy();

    // Buat hash table dari daftar produk
    Node* current = daftarProduk.head;
    while (current != nullptr) {
        hashTable[current->namaProduk] = current;
        current = current->next;
    }

    while (true) {
        cout << "Menu: " << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Ubah Data" << endl;
        cout << "3. Sisipkan Data Setelah Produk Tertentu" << endl;
        cout << "4. Hapus Data Berdasarkan Nama Barang" << endl;
        cout << "5. Hapus Data Urutan Tertentu" << endl;
        cout << "6. Hapus Seluruh Data" << endl;
        cout << "7. Tampilkan Data" << endl;
        cout << "8. Tambah Stok" << endl; // Tambah stok ke stack
        cout << "9. Hapus Stok" << endl; // Hapus stok dari stack
        cout << "10. Tampilkan Stok" << endl; // Tampilkan stok dari stack
        cout << "11. Tambah Pesanan" << endl;
        cout << "12. Hapus Pesanan" << endl;
        cout << "13. Tampilkan Pesanan" << endl;
        cout << "14. Exit" << endl;

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
                string nama, satuan;
                int jumlah;
                cout << "Masukkan nama produk yang ingin ditambahkan ke stok: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan jumlah stok: ";
                cin >> jumlah;
                cin.ignore();
                getline(cin, satuan);
                stokStack.push(nama, jumlah, satuan);
                break;
            }
            case 9: {
                stokStack.pop();
                break;
            }
            case 10: {
                stokStack.tampilkan();
                break;
            }
            case 11: {
                string nama, satuan;
                int jumlah;
                cout << "Masukkan nama produk yang dipesan: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan jumlah barang yang dipesan: ";
                cin >> jumlah;
                cin.ignore();
                getline(cin, satuan);
                pesananQueue.enqueue(nama, jumlah, satuan);
                cout << "Pesanan berhasil ditambahkan ke list antrian" << endl;
                break;
            }
            case 12: {
                pesananQueue.dequeue();
                cout << "Pesanan pertama berhasil dihapus" << endl;
                break;
            }
            case 13: {
                pesananQueue.tampilkan();
                break;
            }
            case 14: {
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
