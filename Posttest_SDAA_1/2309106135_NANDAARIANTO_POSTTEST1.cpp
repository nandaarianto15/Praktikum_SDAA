#include <iostream>
using namespace std;

void pindahPiring(int jumlahPiring, string menaraAsal, string menaraTujuan, string menaraSementara) {
    if (jumlahPiring == 1) {
        // jika hanya satu piring, langsung pindahkan dari menara asal ke menara tujuan
        cout << "Pindahkan piring 1 dari " << menaraAsal << " ke " << menaraTujuan << endl;
        return;
    }

    // pindahkan (n-1) piring dari menara asal ke menara sementara
    pindahPiring(jumlahPiring - 1, menaraAsal, menaraSementara, menaraTujuan);

    // pindahkan piring terbesar ke menara tujuan
    cout << "Pindahkan piring " << jumlahPiring << " dari " << menaraAsal << " ke " << menaraTujuan << endl;

    // pindahkan kembali (n-1) piring dari menara sementara ke menara tujuan
    pindahPiring(jumlahPiring - 1, menaraSementara, menaraTujuan, menaraAsal);
}

int main() {
    int jumlahPiring = 3;
    string menaraAsal = "Menara Asal";
    string menaraSementara = "Menara Sementara";
    string menaraTujuan = "Menara Tujuan";

    pindahPiring(jumlahPiring, menaraAsal, menaraTujuan, menaraSementara);

    // jumlah langkah yang dilakukan
    cout << "Total langkah : " << (1 << jumlahPiring) - 1 << endl;
    return 0;
}
