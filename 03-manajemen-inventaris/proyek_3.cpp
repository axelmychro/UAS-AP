#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

bool cekKodeDuplikat(vector<Barang> &inventaris, string kode) {
    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == kode) {
            return true;
        }
    }
    return false;
}

void tambahBarang(vector<Barang> &inventaris) {
    Barang baru;
    cout << "\n MENU: TAMBAH BARANG \n";
    
    while (true) {
        cout << "Masukkan Kode Barang: ";
        cin >> baru.kodeBarang;
        if (cekKodeDuplikat(inventaris, baru.kodeBarang)) {
            cout << "Error: Kode sudah terpakai! Ganti kode lain.\n";
        } else {
            break;
        }
    }
    
    cout << "Masukkan Nama Barang: ";
    cin.ignore();
    getline(cin, baru.namaBarang);
    
    while (true) {
        cout << "Masukkan Harga Barang: ";
        cin >> baru.harga;
        if (baru.harga >= 0) {
            break;
        }
        cout << "Error: Nilai harga tidak boleh negatif! Input ulang.\n";
    }
    
    while (true) {
        cout << "Masukkan Stok Barang : ";
        cin >> baru.stok;
        if (baru.stok >= 0) {
            break;
        }
        cout << "Error: Nilai stok tidak boleh negatif! Input ulang.\n";
    }
    
    inventaris.push_back(baru);
    cout << "Sukses: Barang berhasil ditambahkan!\n";
}

void tampilkanSemuaBarang(vector<Barang> &inventaris) {
    cout << "\n MENU: DAFTAR SEMUA BARANG \n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong. Silakan tambah barang terlebih dahulu!\n";
        return;
    }
    
    cout << "Kode\tNama Barang\t\tHarga\tStok\n";
    for (int i = 0; i < inventaris.size(); i++) {
        cout << inventaris[i].kodeBarang << "\t"
             << inventaris[i].namaBarang << "\t\t"
             << inventaris[i].harga << "\t"
             << inventaris[i].stok << "\n";
    }
}

void cariBarangTermahal(vector<Barang> &inventaris) {
    cout << "\n MENU: CARI BARANG TERMAHAL \n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong. Silakan tambah barang terlebih dahulu!\n";
        return;
    }
    
    int indeksTermahal = 0;
    for (int i = 1; i < inventaris.size(); i++) {
        if (inventaris[i].harga > inventaris[indeksTermahal].harga) {
            indeksTermahal = i;
        }
    }
    
    cout << "Detail Barang Termahal:\n";
    cout << "- Kode Barang: " << inventaris[indeksTermahal].kodeBarang << "\n";
    cout << "- Nama Barang: " << inventaris[indeksTermahal].namaBarang << "\n";
    cout << "- Harga      : Rp " << inventaris[indeksTermahal].harga << "\n";
    cout << "- Stok       : " << inventaris[indeksTermahal].stok << "\n";
}

void hitungTotalNilaiInventaris(vector<Barang> &inventaris) {
    cout << "\n MENU: TOTAL NILAI INVENTARIS \n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong. Total nilai aset: Rp 0\n";
        return;
    }

    double totalNilai = 0;
    for (int i = 0; i < inventaris.size(); i++) {
        totalNilai += (inventaris[i].harga * inventaris[i].stok);
    }
    
    cout << "Total nilai uang seluruh aset di gudang: Rp " << totalNilai << "\n";
}

void cekRestock(vector<Barang> &inventaris) {
    cout << "\n MENU: CEK BARANG RESTOCK \n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong. Silakan tambah barang terlebih dahulu!\n";
        return;
    }

    bool adaBarangKritis = false;
    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].stok < 5) {
            cout << "- Kode [" << inventaris[i].kodeBarang << "] " 
                 << inventaris[i].namaBarang << " (Sisa Stok: " << inventaris[i].stok << ")\n";
            adaBarangKritis = true;
        }
    }
    
    if (!adaBarangKritis) {
        cout << "Semua aman. Tidak ada barang yang stoknya kurang dari 5.\n";
    }
}

void updateStok(vector<Barang> &inventaris) {
    cout << "\n=== MENU: UPDATE STOK BARANG ===\n";
    if (inventaris.empty()) {
        cout << "Inventaris masih kosong. Silakan tambah barang terlebih dahulu!\n";
        return;
    }

    string kode;
    cout << "Masukkan kode barang yang dicari: ";
    cin >> kode;
    
    int indeksKetemu = -1;
    for (int i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].kodeBarang == kode) {
            indeksKetemu = i;
            break;
        }
    }
    
    if (indeksKetemu == -1) {
        cout << "Error: Barang tidak ditemukan!\n";
        return;
    }
    
    int* ptrStok = &inventaris[indeksKetemu].stok;
    
    cout << "Barang Ditemukan: " << inventaris[indeksKetemu].namaBarang << "\n";
    cout << "Stok Saat Ini   : " << *ptrStok << "\n";
    
    int opsi;
    cout << "1. Tambah Stok\n";
    cout << "2. Kurangi Stok\n";
    cout << "Pilih tindakan (1/2): ";
    cin >> opsi;
    
    if (opsi == 1) {
        int tambah;
        cout << "Masukkan jumlah stok yang masuk: ";
        cin >> tambah;
        *ptrStok += tambah;
        cout << "Sukses: Stok berhasil ditambahkan!\n";
    } else if (opsi == 2) {
        int kurang;
        cout << "Masukkan jumlah stok yang keluar: ";
        cin >> kurang;
        if (*ptrStok - kurang < 0) {
            cout << "Error: Gagal! Stok akhir tidak boleh negatif.\n";
        } else {
            *ptrStok -= kurang;
            cout << "Sukses: Stok berhasil dikurangi!\n";
        }
    } else {
        cout << "Opsi tidak valid. Kembali ke menu utama.\n";
    }
}

int main() {
    vector<Barang> gudangToko;
    int pilihanMenu;
    
    do {
        cout << "\n       PROGRAM INVENTARIS TOKO RETAIL     \n";
        cout << "=========================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock \n";
        cout << "6. Update Stok \n";
        cout << "7. Keluar\n";
        cout << "=========================================\n";
        cout << "Pilih Menu (1-7): ";
        cin >> pilihanMenu;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            pilihanMenu = 0;
        }
        
        switch (pilihanMenu) {
            case 1:
                tambahBarang(gudangToko);
                break;
            case 2:
                tampilkanSemuaBarang(gudangToko);
                break;
            case 3:
                cariBarangTermahal(gudangToko);
                break;
            case 4:
                hitungTotalNilaiInventaris(gudangToko);
                break;
            case 5:
                cekRestock(gudangToko);
                break;
            case 6:
                updateStok(gudangToko);
                break;
            case 7:
                cout << "\nProgram selesai. Keluar dari sistem.\n";
                break;
            default:
                cout << "Pilihan salah! Masukkan angka antara 1 sampai 7.\n";
        }
    } while (pilihanMenu != 7);
    
    return 0;
}