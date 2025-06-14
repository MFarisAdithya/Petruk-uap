#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <list>
#include <stack>
#include <queue>
#include <windows.h>
using namespace std;

struct Project {
    char name[100];
    double time;
    double payment;
    double ratio;

    void calculate() {
        ratio = payment / time;
    }
};

void input(Project &p) {
    cout << "Nama proyek: ";
    cin.ignore();
    cin.getline(p.name, 100);
    cout << "Waktu pengerjaan (jam): ";
    cin >> p.time;
    cout << "Bayaran (Rp): ";
    cin >> p.payment;
    p.calculate();
}

bool compare(const Project &a, const Project &b) {
    return a.ratio > b.ratio;
}

void rekomen(const list<Project> &projectList, double totalTime) {
    vector<Project> sortedProjects(projectList.begin(), projectList.end());
    sort(sortedProjects.begin(), sortedProjects.end(), compare);

    double usedTime = 0;
 	long double totalPayment = 0;

    cout << "\nRekomendasi Proyek Freelance:\n";
    for (const auto &p : sortedProjects) {
        if (usedTime + p.time <= totalTime) {
            cout << "- " << p.name << " (" << p.time << " jam, Rp" << (int)p.payment << ")\n";
            usedTime += p.time;
            totalPayment += p.payment;
        }
    }

    cout << "\nTotal waktu yang digunakan: " << usedTime << " jam dari " << totalTime << " jam\n";
    cout << "Total bayaran: Rp" << (int)totalPayment << endl;
}

void clears() {
    cout << "\nEnter untuk lanjut";
    cin.ignore();
    cin.get();
    system("cls");
}

void edits(list<Project> &projectList, const string &targetName) {
    for (auto &p : projectList) {
        if (targetName == p.name) {
            cout << "Waktu: ";
            cin >> p.time;
            cout << "Bayaran: ";
            cin >> p.payment;
            p.calculate();
            cout << "Proyek berhasil diupdate.\n";
            return;
        }
    }
    cout << "Proyek tidak ada.\n";
}

void deletes(list<Project> &projectList, const string &targetName) {
    for (auto it = projectList.begin(); it != projectList.end(); ++it) {
        if (targetName == it->name) {
            projectList.erase(it);
            cout << "Proyek berhasil dihapus.\n";
            return;
        }
    }
    cout << "Proyek tidak ada.\n";
}

void searchs(const list<Project> &projectList) {
    while (true) {
        string targetName;
        cout << "Masukkan nama proyek yang dicari: ";
        getline(cin, targetName);

        if (targetName.empty()) {
            cout << "Pencarian dibatalkan.\n";
            return;
        }

        for (const auto &p : projectList) {
            if (targetName == p.name) {
                cout << "Ditemukan: " << p.name << " - " << p.time << " jam, Rp" << (int)p.payment << endl;
                return;
            }
        }

        cout << "Proyek tidak ditemukan. Coba lagi.\n";
    }
}

int main() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "                                                    	Selamat datang, wahai pejuang freelance!\n";
    cout << "                                                    	Hari ini kamu kedatangan banyak proyek...\n";
    cout << "                                                    	Tapi waktu sangatlah terbatas dan bayaran sangatlah bervariasi.\n";
    cout << "                                                    	Dan hidupmu bergantung pada KEPUTUSAN INI.\n";

    cin.get(); 
    system("cls");

    int n = 0;
    while (true) {
        cout << "Masukkan jumlah proyek: ";
        cin >> n;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid, masukkan angka.\n";
        } else if (n <= 0) {
            cout << "Jumlah proyek harus lebih besar dari nol.\n";
        } else {
            break;
        }
    }

    vector<Project> projects(n);
    list<Project> projectList;
    stack<string> undoHistory;
    queue<Project> projectQueue;

    for (int i = 0; i < n; i++) {
        cout << "\nProyek ke-" << i + 1 << endl;
        input(projects[i]);

        projectList.push_back(projects[i]);
        projectQueue.push(projects[i]);
        undoHistory.push(projects[i].name);

        cout << "Proyek '" << projects[i].name << "' disimpan.\n";
    }
	
    double totalTime;
    while (true) {
        cout << "\nMasukkan batas maksimal jam kerja per minggu: ";
        cin >> totalTime;

        if (cin.fail() || totalTime <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid, masukkan angka yang lebih besar dari nol.\n";
        } else {
            break;
        }
    }
	
    rekomen(projectList, totalTime);
    int choice;
    do {
    	clears();
        cout << "\nMenu Daftar Proyek:\n";
        cout << "1. Tampilkan semua proyek\n";
        cout << "2. Edit proyek\n";
        cout << "3. Hapus proyek\n";
        cout << "4. Cari proyek\n";
        cout << "5. Filter proyek berdasarkan waktu\n";
        cout << "6. Tambah proyek baru\n";
        cout << "7. Cek ulang rekomendasi proyek\n";
        cout << "8. Undo tambah proyek terakhir\n";
		cout << "9. Ubah batas maksimal jam kerja\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;
        cin.ignore();

        string name;
        double maxTime;

        switch (choice) {
            case 1:
                for (auto &p : projectList) {
                    cout << "- " << p.name << " (" << p.time << " jam, Rp" << (int)p.payment << ")\n";
                }
                break;
            case 2:
		cout << "Masukkan nama proyek yang ingin diedit: ";
                getline(cin, name);
                edits(projectList, name);
                break;
            case 3:
		cout << "Masukkan nama proyek yang ingin dihapus: ";
                getline(cin, name);
                deletes(projectList, name);
                break;
            case 4:
		searchs(projectList);
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
		rekomen(projectList, totalTime);
                break;
            case 8:
                break;
      			case 9:
      			    cout << "Masukkan batas maksimal jam kerja yang baru: ";
      			    cin >> totalTime;
      			    if (cin.fail() || totalTime <= 0) {
      			        cin.clear();
      			        cin.ignore(10000, '\n');
      			        cout << "Input tidak valid, waktu tidak dapat diubah.\n";
      			    } else {
      			        cout << "Batas waktu diubah menjadi " << totalTime << " jam.\n";
      			    }
      			    break;          
            case 0:
                cout << "Keluar dari menu daftar proyek.\n";
                  break;
	}
    } while (choice != 0);

    return 0;
}
