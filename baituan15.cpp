#include <iostream>
#include <string>
#include <queue>

using namespace std;

const int SO_DINH = 11; 

string TenTinh[SO_DINH] = {
    "Ha Noi",      
    "Hai Duong",   
    "Hung Yen",    
    "Phu Ly",      
    "Hoa Binh",    
    "Son Tay",     
    "Thai Nguyen", 
    "Bac Ninh",    
    "Bac Giang",   
    "Uong Bi",     
    "Hai Phong"    
};

struct Nut {
    int du_lieu;
    Nut* tiep_theo;
};

int MaTranKe[SO_DINH][SO_DINH];

void KhoiTaoMaTran() {
    for (int i = 0; i < SO_DINH; i++) {
        for (int j = 0; j < SO_DINH; j++) {
            MaTranKe[i][j] = 0;
        }
    }
}

void ThemCanhMaTran(int u, int v) {
    MaTranKe[u][v] = 1;
    MaTranKe[v][u] = 1; 
}

void DuyetBFS_MaTran(int dinhBatDau) {
    bool DaChek[SO_DINH] = {false};
    queue<int> HangDoi;

    HangDoi.push(dinhBatDau);
    DaChek[dinhBatDau] = true;

    while (!HangDoi.empty()) {
        int u = HangDoi.front();
        HangDoi.pop();
        
        cout << TenTinh[u] << " -> ";

        for (int v = 0; v < SO_DINH; v++) {
            if (MaTranKe[u][v] == 1 && !DaChek[v]) {
                HangDoi.push(v);
                DaChek[v] = true;
            }
        }
    }
    cout << "END\n";
}

Nut* DanhSachKe[SO_DINH]; 

void KhoiTaoDanhSach() {
    for (int i = 0; i < SO_DINH; i++) {
        DanhSachKe[i] = nullptr;
    }
}

void ThemNut(Nut* &dau, int v) {
    Nut* moi = new Nut();
    moi->du_lieu = v;
    moi->tiep_theo = dau;
    dau = moi;
}

void ThemCanhDanhSach(int u, int v) {
    ThemNut(DanhSachKe[u], v);
    ThemNut(DanhSachKe[v], u);
}

void DuyetBFS_DanhSach(int dinhBatDau) {
    bool DaChek[SO_DINH] = {false};
    queue<int> HangDoi;

    HangDoi.push(dinhBatDau);
    DaChek[dinhBatDau] = true;

    while (!HangDoi.empty()) {
        int u = HangDoi.front();
        HangDoi.pop();

        cout << TenTinh[u] << " -> ";

        Nut* tam = DanhSachKe[u];
        while (tam != nullptr) {
            int v = tam->du_lieu;
            if (!DaChek[v]) {
                HangDoi.push(v);
                DaChek[v] = true;
            }
            tam = tam->tiep_theo;
        }
    }
    cout << "END\n";
}

void NapDuLieuDoThi() {
    ThemCanhMaTran(0, 1); ThemCanhDanhSach(0, 1); 
    ThemCanhMaTran(0, 3); ThemCanhDanhSach(0, 3); 
    ThemCanhMaTran(0, 4); ThemCanhDanhSach(0, 4); 
    ThemCanhMaTran(0, 5); ThemCanhDanhSach(0, 5); 
    ThemCanhMaTran(0, 6); ThemCanhDanhSach(0, 6); 
    ThemCanhMaTran(0, 7); ThemCanhDanhSach(0, 7); 

    ThemCanhMaTran(1, 2); ThemCanhDanhSach(1, 2); 
    ThemCanhMaTran(2, 3); ThemCanhDanhSach(2, 3); 
    ThemCanhMaTran(7, 8); ThemCanhDanhSach(7, 8); 
    ThemCanhMaTran(7, 9); ThemCanhDanhSach(7, 9); 
    ThemCanhMaTran(8, 9); ThemCanhDanhSach(8, 9); 
    ThemCanhMaTran(9, 10); ThemCanhDanhSach(9, 10); 
    ThemCanhMaTran(1, 10); ThemCanhDanhSach(1, 10); 
}

int main() {
    KhoiTaoMaTran();
    KhoiTaoDanhSach();
    NapDuLieuDoThi();

    cout << "=== DUYET BFS THEO MA TRAN KE ===" << endl;
    DuyetBFS_MaTran(0); 

    cout << "\n=== DUYET BFS THEO DANH SACH LIEN KET ===" << endl;
    DuyetBFS_DanhSach(0);

    return 0;
}
