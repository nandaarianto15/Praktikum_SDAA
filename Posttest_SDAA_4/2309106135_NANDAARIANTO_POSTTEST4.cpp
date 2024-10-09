#include <iostream>
#include <limits>

using namespace std;

// Struct untuk User
struct User {
    int id;
    string username;
    string password;
    User* next; // Pointer ke user berikutnya
};

// Struct untuk Tabungan
struct Tabungan {
    int id;
    int userId;
    string namaTabungan;
    int pin;
    double jumlah; // Saldo tabungan
    Tabungan* next; // Pointer ke tabungan berikutnya
};

// Pointer untuk head dari linked list User dan Tabungan
User* headUser = nullptr;
Tabungan* headTabungan = nullptr;

// User yang sedang login
int userIdAktif = -1;

// Stack untuk menyimpan transaksi (menggunakan linked list)
struct Transaksi {
    int userId;
    int tabunganId;
    string tipe;
    double jumlah;
    Transaksi* next;
};

Transaksi* top = nullptr; // Pointer untuk top Stack

// Queue untuk menyimpan transaksi
struct QueueTransaksi {
    int userId;
    int tabunganId;
    string tipe;
    double jumlah;
    QueueTransaksi* next;
};

QueueTransaksi* front = nullptr; // Pointer untuk front Queue
QueueTransaksi* rear = nullptr; // Pointer untuk rear Queue

// Deklarasi fungsi dan prosedur
void showStartMenu();
void registerUser();
void loginUser();
bool checkLogin(string username, string password);
void showTabunganMenu();
void createTabungan();
void readTabungan();
void updateTabungan();
void deleteTabungan();
bool validasiPin(int tabunganId);
Tabungan* findTabunganById(int tabunganId);

// Fungsi Stack
void pushTransaksi(int userId, int tabunganId, string tipe, double jumlah);  // Fungsi untuk push ke Stack
void popTransaksi();  // Fungsi untuk pop dari Stack
void displayStack(int userId, int tabunganId);  // Menampilkan Stack untuk userId dan tabunganId tertentu

// Fungsi Queue
void enqueueTransaksi(int userId, int tabunganId, string tipe, double jumlah);  // Fungsi untuk enqueue ke Queue
void dequeueTransaksi();  // Fungsi untuk dequeue dari Queue
void displayQueue(int userId, int tabunganId);  // Menampilkan Queue untuk userId dan tabunganId tertentu


int main() {
    showStartMenu();
    return 0;
}

// Fungsi menampilkan menu utama
void showStartMenu() {
    int pilihan;

    cout << "=== SELAMAT DATANG ===\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Masukkan Pilihan : ";
    cin >> pilihan;

    while (cin.fail() || pilihan < 1 || pilihan > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3 : ";
        cin >> pilihan;
    }

    switch (pilihan) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();    
            break;
        case 3:
            cout << "Terima Kasih." << endl;
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
    }

    showStartMenu();
}

// Fungsi untuk registrasi user baru
void registerUser() {
    User* newUser = new User;
    newUser->id = (headUser == nullptr) ? 1 : headUser->id + 1;
    
    cout << "=== REGISTER USER ===\n";
    cout << "Masukkan username: ";
    cin >> newUser->username;
    cout << "Masukkan password: ";
    cin >> newUser->password;

    // Tambahkan user ke linked list
    newUser->next = headUser;
    headUser = newUser;

    cout << "Registrasi berhasil!\n";
}

// Fungsi untuk login user
void loginUser() {
    string username, password;

    cout << "=== LOGIN USER ===\n";
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if (checkLogin(username, password)) {
        cout << "Login berhasil!\n";
        showTabunganMenu();
    } else {
        cout << "Username atau password salah.\n";
    }
}

// Fungsi untuk memeriksa apakah user valid
bool checkLogin(string username, string password) {
    User* currentUser = headUser;
    while (currentUser != nullptr) {
        if (currentUser->username == username && currentUser->password == password) {
            userIdAktif = currentUser->id;
            return true; // Login sukses
        }
        currentUser = currentUser->next;
    }
    return false; // Login gagal
}

// Menu setelah user login
void showTabunganMenu() {
    int pilihan, tabunganId;

    cout << "\n=== MENU TABUNGAN ===\n";
    cout << "1. Buat Tabungan\n";
    cout << "2. Lihat Tabungan\n";
    cout << "3. Setor/Tarik Saldo\n";
    cout << "4. Hapus Tabungan\n";
    cout << "5. Tampilkan (Stack) Transaksi\n";
    cout << "6. Tampilkan (Queue) Transaksi\n";
    cout << "7. Logout\n";
    cout << "Masukkan Pilihan : ";
    cin >> pilihan;

    while (cin.fail() || pilihan < 1 || pilihan > 7) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 7 : ";
        cin >> pilihan;
    }

    switch (pilihan) {
        case 1:
            createTabungan();
            break;
        case 2:
            readTabungan();
            break;
        case 3:
            updateTabungan();
            break;
        case 4:
            deleteTabungan();
            break;
        case 5: {
            readTabungan();
            cout << "Masukkan ID tabungan: ";
            cin >> tabunganId;
            displayStack(userIdAktif, tabunganId);
            break;
        }
        case 6: {
            readTabungan();
            cout << "Masukkan ID tabungan: ";
            cin >> tabunganId;
            displayQueue(userIdAktif, tabunganId);
            break;
        }
        case 7:
            cout << "Logout berhasil.\n";
            userIdAktif = -1;
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
    }

    showTabunganMenu();
}

// Fungsi untuk membuat tabungan
void createTabungan() {
    Tabungan* newTabungan = new Tabungan;
    newTabungan->id = (headTabungan == nullptr) ? 1 : headTabungan->id + 1;
    newTabungan->userId = userIdAktif;

    cout << "=== BUAT TABUNGAN ===\n";
    cout << "Masukkan nama tabungan: ";
    cin >> newTabungan->namaTabungan;

    int pinInput;
    bool validPin = false;

    while (!validPin) {
        cout << "Masukkan PIN tabungan (4 digit, hanya angka): ";
        cin >> pinInput;

        // Validasi input
        if (cin.fail() || pinInput < 1000 || pinInput > 9999) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Pastikan PIN adalah 4 digit dan hanya terdiri dari angka.\n";
        } else {
            validPin = true;
        }
    }

    newTabungan->pin = pinInput; // Menyimpan input PIN yang valid
    newTabungan->jumlah = 0; // Set saldo awal

    // Tambahkan tabungan ke linked list
    newTabungan->next = headTabungan;
    headTabungan = newTabungan;

    cout << "Tabungan berhasil dibuat!\n";
}

// Fungsi untuk melihat tabungan milik user
void readTabungan() {
    cout << "\n=== LIHAT TABUNGAN ===\n";
    bool adaTabungan = false;
    Tabungan* currentTabungan = headTabungan;
    while (currentTabungan != nullptr) {
        if (currentTabungan->userId == userIdAktif) {
            cout << "ID: " << currentTabungan->id << endl;
            cout << "Nama Tabungan: " << currentTabungan->namaTabungan << endl;
            cout << "Saldo: " << currentTabungan->jumlah << endl;
            cout << endl;
            adaTabungan = true;
        }
        currentTabungan = currentTabungan->next;
    }
    if (!adaTabungan) {
        cout << "Anda belum memiliki tabungan.\n";
    }
}

// Fungsi untuk setor/tarik saldo
void updateTabungan() {
    int tabunganId;
    double jumlahTransaksi;
    char tipeTransaksi;

    cout << "=== SETOR/TARIK SALDO ===\n";
    readTabungan();
    cout << "Masukkan ID tabungan: ";
    cin >> tabunganId;

    if (validasiPin(tabunganId)) {
        cout << "Masukkan jumlah transaksi: ";
        cin >> jumlahTransaksi;
        cout << "Setor (S) atau Tarik (T): ";
        cin >> tipeTransaksi;

        Tabungan* tabungan = findTabunganById(tabunganId);
        if (tabungan != nullptr) {
            string tipe;
            if (tipeTransaksi == 'S' || tipeTransaksi == 's') {
                tabungan->jumlah += jumlahTransaksi;
                tipe = "Setor";
                cout << "Setor berhasil!\n";
            } else if (tipeTransaksi == 'T' || tipeTransaksi == 't') {
                if (tabungan->jumlah >= jumlahTransaksi) {
                    tabungan->jumlah -= jumlahTransaksi;
                    tipe = "Tarik";
                    cout << "Tarik berhasil!\n";
                } else {
                    cout << "Saldo tidak cukup.\n";
                    return;
                }
            }

            // Tambahkan transaksi dengan userId dan tabunganId ke Stack dan Queue
            pushTransaksi(userIdAktif, tabunganId, tipe, jumlahTransaksi);
            enqueueTransaksi(userIdAktif, tabunganId, tipe, jumlahTransaksi);
        }
    } else {
        cout << "PIN salah.\n";
    }
}

// Fungsi untuk menghapus tabungan
void deleteTabungan() {
    int tabunganId;

    cout << "=== HAPUS TABUNGAN ===" << endl;
    readTabungan();
    cout << "Masukkan ID tabungan yang ingin dihapus: ";
    cin >> tabunganId;

    if (validasiPin(tabunganId)) {
        Tabungan* prevTabungan = nullptr;
        Tabungan* currentTabungan = headTabungan;

        while (currentTabungan != nullptr && currentTabungan->id != tabunganId) {
           
            prevTabungan = currentTabungan;
            currentTabungan = currentTabungan->next;
        }

        if (currentTabungan == nullptr) {
            cout << "Tabungan tidak ditemukan.\n";
            return;
        }

        // Jika tabungan ditemukan, hapus dari linked list
        if (prevTabungan == nullptr) {
            headTabungan = currentTabungan->next; // Hapus node pertama
        } else {
            prevTabungan->next = currentTabungan->next; // Hubungkan node sebelumnya ke node setelahnya
        }

        delete currentTabungan; // Hapus tabungan
        cout << "Tabungan berhasil dihapus!\n";
    } else {
        cout << "PIN salah.\n";
    }
}

// Fungsi untuk validasi PIN saat melakukan transaksi
bool validasiPin(int tabunganId) {
    Tabungan* tabungan = findTabunganById(tabunganId);
    if (tabungan != nullptr) {
        int pinInput;
        cout << "Masukkan PIN: ";
        cin >> pinInput;

        if (pinInput == tabungan->pin) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk mencari tabungan berdasarkan ID
Tabungan* findTabunganById(int tabunganId) {
    Tabungan* currentTabungan = headTabungan;
    while (currentTabungan != nullptr) {
        if (currentTabungan->id == tabunganId) {
            return currentTabungan;
        }
        currentTabungan = currentTabungan->next;
    }
    return nullptr; // Tabungan tidak ditemukan
}

// Fungsi untuk menambah transaksi ke Stack
void pushTransaksi(int userId, int tabunganId, string tipe, double jumlah) {
    Transaksi* newTransaksi = new Transaksi;
    newTransaksi->userId = userId;
    newTransaksi->tabunganId = tabunganId;
    newTransaksi->tipe = tipe;
    newTransaksi->jumlah = jumlah;
    newTransaksi->next = top;
    top = newTransaksi;
}

// Fungsi untuk menambah transaksi ke Queue
void enqueueTransaksi(int userId, int tabunganId, string tipe, double jumlah) {
    QueueTransaksi* newTransaksi = new QueueTransaksi;
    newTransaksi->userId = userId;
    newTransaksi->tabunganId = tabunganId;
    newTransaksi->tipe = tipe;
    newTransaksi->jumlah = jumlah;
    newTransaksi->next = nullptr;

    if (rear == nullptr) {
        front = rear = newTransaksi;
    } else {
        rear->next = newTransaksi;
        rear = newTransaksi;
    }
}

// Fungsi untuk menampilkan Stack
void displayStack(int userId, int tabunganId) {
    Transaksi* current = top;
    if (current == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    cout << "=== STACK TRANSAKSI ===\n";
    bool adaTransaksi = false;
    while (current != nullptr) {
        if (current->userId == userId && current->tabunganId == tabunganId) {
            cout << current->tipe << " - " << current->jumlah << endl;
            adaTransaksi = true;
        }
        current = current->next;
    }
    if (!adaTransaksi) {
        cout << "Tidak ada transaksi untuk tabungan ini.\n";
    }
}

// Fungsi untuk menampilkan Queue
void displayQueue(int userId, int tabunganId) {
    QueueTransaksi* current = front;
    if (current == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    cout << "=== QUEUE TRANSAKSI ===\n";
    bool adaTransaksi = false;
    while (current != nullptr) {
        if (current->userId == userId && current->tabunganId == tabunganId) {
            cout << current->tipe << " - " << current->jumlah << endl;
            adaTransaksi = true;
        }
        current = current->next;
    }
    if (!adaTransaksi) {
        cout << "Tidak ada transaksi untuk tabungan ini.\n";
    }
}

// Fungsi untuk menghapus transaksi dari Stack
void popTransaksi() {
    if (top == nullptr) {
        cout << "Stack kosong.\n";
        return;
    }

    Transaksi* temp = top;
    top = top->next;
    delete temp;
    cout << "Pop transaksi berhasil.\n";
}

// Fungsi untuk menghapus transaksi dari Queue
void dequeueTransaksi() {
    if (front == nullptr) {
        cout << "Queue kosong.\n";
        return;
    }

    QueueTransaksi* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    cout << "Dequeue transaksi berhasil.\n";
}
