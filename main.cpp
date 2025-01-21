#include <iostream> 
#include <fstream>  
using namespace std;

// Struct kategoriPenyakit dengan bertipe data enum
enum kategoriPenyakit
{
    kategori_1,
    kategori_2,
    kategori_3
};
// Struct obat
struct obat
{s
    string resep_obat;
    obat *nextObat;
};

// struct pasien
struct pasien
{
    string nama;
    int umur;
    float berat_badan;
    float tinggi_badan;
    string alamat;
    kategoriPenyakit kategori_penyakit;
    obat *resepObat;
    pasien *next;
};
int nomorAntrian = 0;

int maxAntrian = 5;
// definisi pointer untuk data pasien
pasien *head, *tail, *current, *del, *newNode;

// hitung jumlah antrian pasien
int hitungPasien()
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        current = head;
        int count = 0;
        while (current != NULL)
        {
            current = current->next;
            count++;
        }
        return count;
    }
}

// function tambah pasien
void tambahPasien(string nama, int umur, float berat_badan, float tinggi_badan, string alamat, kategoriPenyakit kategori_penyakit)
{
    if (hitungPasien() == maxAntrian)
    {
        cout << "Maaf untuk saat ini antrian pasien telah penuh" << endl;
        cout << "Coba lagi nanti";
    }
    else
    {
        if (hitungPasien() == 0)
        {
            head = new pasien();
            head->nama = nama;
            head->umur = umur;
            head->berat_badan = berat_badan;
            head->tinggi_badan = tinggi_badan;
            head->alamat = alamat;
            head->kategori_penyakit = kategori_penyakit;
            head->resepObat = NULL;
            head->next = NULL;
            tail = head;

            nomorAntrian++;
            cout << "Data Pasien berhasil ditambahkan! Nomor Antrian Anda adalah: " << nomorAntrian << endl;
        }
        else
        {
            newNode = new pasien();
            newNode->nama = nama;
            newNode->umur = umur;
            newNode->berat_badan = berat_badan;
            newNode->tinggi_badan = tinggi_badan;
            newNode->alamat = alamat;
            newNode->kategori_penyakit = kategori_penyakit;
            newNode->resepObat = NULL;
            tail->next = newNode;
            tail = newNode;

            nomorAntrian++;
            cout << "Data Pasien berhasil ditambahkan! Nomor Antrian Anda adalah: " << nomorAntrian << endl;
        }
    }
}

// function untuk menghapus data pasien
void hapusPasien()
{
    if (hitungPasien == 0)
    {
        cout << "Tidak ada data yang bisa dihapus, Antrian masih kosong." << endl;
    }
    else
    {
        del = head;
        head = head->next;
        del->next = NULL;
        delete del;
    }
}
// Function untuk hapus data pasien berdasarkan nama
void hapusDataPasien(string namaPasien)
{
    if (hitungPasien() == 0)
    {
        cout << "Data antrian masih kosong" << endl;
    }
    else
    {
        // Special case: deleting the first patient
        if (head->nama == namaPasien)
        {
            del = head;
            head = head->next;
            del->next = NULL;
            delete del;
        }
        else
        {
            current = head;
            while (current->next != NULL && current->next->nama != namaPasien)
            {
                current = current->next;
            }

            if (current->next != NULL)
            {
                del = current->next;
                current->next = current->next->next;
                del->next = NULL;
                delete del;
            }
            else
            {
                cout << "Data pasien dengan nama " << namaPasien << " tidak ditemukan." << endl;
            }
        }
    }
}

// function untuk lihat antrian pasien
void lihatAntrian()
{
    if (hitungPasien == 0)
    {
        cout << "Data antrian pasien masih kosong" << endl;
    }
    else
    {
        cout << "Antrian saat ini : " << hitungPasien() << " pasien" << endl;
        current = head;
        int nomorPasien = 1;
        while (nomorPasien <= maxAntrian)
        {
            if (current != NULL)
            {
                cout << nomorPasien << ". "
                     << "Nomor antrian : " << nomorPasien << "\nPasien   : " << current->nama << " | " << current->umur << " | " << current->alamat << " | ";

                switch (current->kategori_penyakit)
                {
                case kategori_1:
                    cout << "penyakit Kategori 1";
                    break;
                case kategori_2:
                    cout << "penyakit Kategori 2";
                    break;
                case kategori_3:
                    cout << "penyakit Kategori 3";
                    break;
                default:
                    cout << "Tidak diketahui";
                }

                obat *tempObat = current->resepObat;
                while (tempObat != NULL)
                {
                    cout << "\n\tNama Obat : " << tempObat->resep_obat;
                    tempObat = tempObat->nextObat;
                }

                cout << endl;
                current = current->next;
            }
            else
            {
                cout << nomorPasien << ". "
                     << "(Kosong)" << endl;
            }
            nomorPasien++;
        }
    }
    cout << "\n"
         << endl;
}
// function untuk menambahkan obat pasien
void tambahObat(pasien *p)
{
    string nama_obat, dosis;
    char tambahLagi;

    do
    {
        cout << "Masukkan Nama Obat: ";
        cin.ignore();
        getline(cin, nama_obat);

        obat *newObat = new obat();
        newObat->resep_obat = nama_obat;
        newObat->nextObat = NULL;

        if (p->resepObat == NULL)
        {
            p->resepObat = newObat;
        }
        else
        {
            obat *temp = p->resepObat;
            while (temp->nextObat != NULL)
            {
                temp = temp->nextObat;
            }
            temp->nextObat = newObat;
        }

        cout << "Apakah Anda ingin menambahkan obat lagi? (y/n): ";
        cin >> tambahLagi;
    } while (tambahLagi == 'y' || tambahLagi == 'Y');
}
// function untuk tambah obat berdasarkan nomor antrian pasien
bool tambahObatByAntrian(int nomorPasien)
{
    if (nomorPasien <= 0 || nomorPasien > hitungPasien())
    {
        cout << "Nomor Antrian tidak valid. \n"
             << endl;
        return false;
    }

    current = head;
    int counter = 1;
    while (counter < nomorPasien)
    {
        current = current->next;
        counter++;
    }

    // current sekarang berisi pasien dengan nomor antrian yang dipilih
    tambahObat(current);
    return true;
}

// function save file menjadi txt
void eksporKeTxt()
{
    ofstream outFile("data_pasien.txt"); // Membuka file untuk penulisan

    if (!outFile)
    {
        cout << "Tidak dapat membuka file untuk diekspor." << endl;
        return;
    }

    if (hitungPasien() == 0)
    {
        cout << "Data antrian masih kosong \n"
             << endl;
    }
    else
    {
        current = head;

        while (current != NULL)
        {
            outFile << "Nama: " << current->nama << "\n";
            outFile << "Umur: " << current->umur << "\n";
            outFile << "Berat Badan: " << current->berat_badan << "\n";
            outFile << "Tinggi Badan: " << current->tinggi_badan << "\n";
            outFile << "Alamat: " << current->alamat << "\n";

            switch (current->kategori_penyakit)
            {
            case kategori_1:
                outFile << "Kategori Penyakit: Kategori 1\n";
                break;
            case kategori_2:
                outFile << "Kategori Penyakit: Kategori 2\n";
                break;
            case kategori_3:
                outFile << "Kategori Penyakit: Kategori 3\n";
                break;
            default:
                outFile << "Kategori Penyakit: Tidak diketahui\n";
            }

            obat *tempObat = current->resepObat;
            while (tempObat != NULL)
            {
                outFile << "Obat: " << tempObat->resep_obat << "\n";
                tempObat = tempObat->nextObat;
            }

            outFile << "\n";

            current = current->next;
        }

        cout << "Data pasien berhasil diekspor ke data_pasien.txt" << endl;
    }

    outFile.close(); // Menutup file
}

int main()
{
    int pilih;

    do
    {
        cout << "=========== PORTAL LAYANAN KESEHATAN ===========\n " << endl;
        cout << "Pilihan Menu: " << endl;
        cout << "1. Tambah Data Pasien" << endl;
        cout << "2. Cek Antrian yang Tersedia" << endl;
        cout << "3. Tampilkan Antrian Pasien" << endl;
        cout << "4. Hapus Antrian " << endl;
        cout << "5. Tambah Obat untuk Pasien" << endl;
        cout << "6. Keluar program \n"
             << endl;
        cout << "Masukkan pilihan (1-6): ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
        {
            string nama, alamat;
            int umur;
            float berat_badan, tinggi_badan;
            kategoriPenyakit kategori_penyakit;

            cout << "Masukkan Nama Pasien: ";
            cin.ignore(); // clear buffer
            getline(cin, nama);

            cout << "Masukkan Umur Pasien: ";
            cin >> umur;

            cout << "Masukkan Berat Badan Pasien: ";
            cin >> berat_badan;

            cout << "Masukkan Tinggi Badan Pasien: ";
            cin >> tinggi_badan;

            cout << "Masukkan Alamat Pasien: ";
            cin.ignore(); // clear buffer
            getline(cin, alamat);

            // cout << "Pilih kategori penyakit berdasarkan keluhan anda :" << endl;

            cout << "==== Pilih Kategori Penyakit berdasarkan keluhan anda =====\n"
                 << "1. Kategori 1 - Penyakit ringan seperti (Flu Ringan, Demam Ringan, Flu Perut, Batuk, Pilek, Keracunan Makanan)\n"
                 << "2. Kategori 2 - Penyakit sedang seperti (Pneumonia Sedang, Bronkitis, Sinusitis, Asma Sedang, Hipertensi Sedang)\n"
                 << "3. Kategori 3 - Penyakit berat seperti (Serangan Jantung, Stroke, Krisis Hipertensi, Asma Akut, Pendarahan Berat dan penyakit lain selain yang tersedia diatas)\n";

            int pilihKategori;

            do
            {
                cout << "Masukkan angka kategori yang sesuai dengan keluhan penyakit anda (1-3) : ";
                cin >> pilihKategori;

                switch (pilihKategori)
                {
                case 1:
                    kategori_penyakit = kategori_1;
                    break;
                case 2:
                    kategori_penyakit = kategori_2;
                    break;
                case 3:
                    kategori_penyakit = kategori_3;
                    break;
                default:
                    cout << "Input tidak valid. masukkan input sesuai kategori yang sesuai (1-3) \n"
                         << endl;
                    break;
                }
            } while (pilihKategori < 1 || pilihKategori > 3);

            tambahPasien(nama, umur, berat_badan, tinggi_badan, alamat, kategori_penyakit);
            cout << "Data Pasien berhasil ditambahkan! \n"
                 << endl;
            break;
        }
        case 2:
            cout << "Jumlah Antrian yang Tersedia: " << maxAntrian - hitungPasien() << endl;
            break;
        case 3:
            lihatAntrian();
            break;
        case 4:
        {
            hapusPasien();
            if (hitungPasien() == 0)
            {
                cout << "Masih kosong";
            }
            else
            {
                lihatAntrian();
            }
            lihatAntrian();
            break;
        }
        case 5:
            int nomorPasien;
            cout << "Masukkan nomor antrian pasien untuk menambah obat: ";
            cin >> nomorPasien;
            if (tambahObatByAntrian(nomorPasien) == true)
            {
                cout << "Obat berhasil ditambahkan untuk pasien nomor antrian : " << nomorPasien << endl;
            }
            else
            {
                cout << "Nomor Antrian tidak valid. Obat tidak berhasil ditambahkan. \n"
                     << endl;
            }
            break;
        case 6:
            eksporKeTxt(); // Menambahkan fitur ekspor
            cout << "Keluar dari Program. " << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan masukkan pilihan 1-6." << endl;
            break;
        }

    } while (pilih != 6);

    return 0;
}
