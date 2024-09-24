#include <iostream>
#include <limits>

using namespace std;

// Struct untuk User
struct User {
    int id;
    string username;
    string password;
};

// Struct untuk Tabungan
struct Tabungan {
    int id;
    int userId;
    string namaTabungan;
    int pin;
    double* jumlah; // Pointer untuk jumlah saldo
};

// Array untuk menyimpan data User dan Tabungan
User daftarUser[100];
int jumlahUser = 0;

Tabungan daftarTabungan[100];
int jumlahTabungan = 0;


// User yang sedang login
int userIdAktif = -1;


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
Tabungan* findTabunganById(int tabunganId); // Fungsi untuk mencari tabungan berdasarkan ID

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
    User newUser;
    newUser.id = jumlahUser + 1;
    
    cout << "=== REGISTER USER ===\n";
    cout << "Masukkan username: ";
    cin >> newUser.username;
    cout << "Masukkan password: ";
    cin >> newUser.password;

    // Simpan user ke array
    daftarUser[jumlahUser] = newUser;
    jumlahUser++;

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
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username && daftarUser[i].password == password) {
            userIdAktif = daftarUser[i].id;
            return true; // Login sukses
        }
    }
    return false; // Login gagal
}

// Menu setelah user login
void showTabunganMenu() {
    int pilihan;

    cout << "\n=== MENU TABUNGAN ===\n";
    cout << "1. Buat Tabungan\n";
    cout << "2. Lihat Tabungan\n";
    cout << "3. Setor/Tarik Saldo\n";
    cout << "4. Hapus Tabungan\n";
    cout << "5. Logout\n";
    cout << "Masukkan Pilihan : ";
    cin >> pilihan;

    while (cin.fail() || pilihan < 1 || pilihan > 5) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan angka antara 1 dan 5 : ";
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
        case 5:
            cout << "Logout berhasil.\n";
            userIdAktif = -1;
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
    }

    // Panggil lagi fungsi showTabunganMenu secara rekursif
    showTabunganMenu();
}


// Fungsi untuk membuat tabungan
void createTabungan() {
    Tabungan newTabungan;
    newTabungan.id = jumlahTabungan + 1;
    newTabungan.userId = userIdAktif;

    cout << "=== BUAT TABUNGAN ===\n";
    cout << "Masukkan nama tabungan: ";
    cin >> newTabungan.namaTabungan;

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

    newTabungan.pin = pinInput; // Menyimpan input PIN yang valid

    // Mencocokan penyimpanan untuk saldo tabungan menggunakan pointer
    newTabungan.jumlah = new double(0);

    // Simpan tabungan ke array
    daftarTabungan[jumlahTabungan] = newTabungan;
    jumlahTabungan++;

    cout << "Tabungan berhasil dibuat!\n";
}

// Fungsi untuk melihat tabungan milik user
void readTabungan() {
    cout << "\n=== LIHAT TABUNGAN ===\n";
    bool adaTabungan = false;
    for (int i = 0; i < jumlahTabungan; i++) {
        if (daftarTabungan[i].userId == userIdAktif) {
            cout << "ID: " << daftarTabungan[i].id << endl;
            cout << "Nama Tabungan: " << daftarTabungan[i].namaTabungan << endl;
            cout << "Saldo: " << *daftarTabungan[i].jumlah << endl;
            adaTabungan = true;
        }
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
            if (tipeTransaksi == 'S' || tipeTransaksi == 's') {
                *tabungan->jumlah += jumlahTransaksi;
                cout << "Setor berhasil!\n";
            } else if (tipeTransaksi == 'T' || tipeTransaksi == 't') {
                if (*tabungan->jumlah >= jumlahTransaksi) {
                    *tabungan->jumlah -= jumlahTransaksi;
                    cout << "Tarik berhasil!\n";
                } else {
                    cout << "Saldo tidak cukup.\n";
                }
            }
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
        for (int i = 0; i < jumlahTabungan; i++) {
            if (daftarTabungan[i].id == tabunganId && daftarTabungan[i].userId == userIdAktif) {
                delete daftarTabungan[i].jumlah; // Menghapus penyimpanan
                for (int j = i; j < jumlahTabungan - 1; j++) {
                    daftarTabungan[j] = daftarTabungan[j + 1];
                }
                jumlahTabungan--;
                cout << "Tabungan berhasil dihapus!\n";
                return;
            }
        }
    } else {
        cout << "PIN salah.\n";
    }
}

// Fungsi untuk validasi PIN
bool validasiPin(int tabunganId) {
    int pinInput;
    Tabungan* tabungan = findTabunganById(tabunganId);
    if (tabungan != nullptr) {
        cout << "Masukkan PIN: ";
        cin >> pinInput;
        if (tabungan->pin == pinInput) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk mencari tabungan berdasarkan ID
Tabungan* findTabunganById(int tabunganId) {
    for (int i = 0; i < jumlahTabungan; i++) {
        if (daftarTabungan[i].id == tabunganId && daftarTabungan[i].userId == userIdAktif) {
            return &daftarTabungan[i];
        }
    }
    return nullptr;
}