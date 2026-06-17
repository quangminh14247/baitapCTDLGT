#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Nut {
    int khoa;
    int chieu_cao;
    Nut* trai;
    Nut* phai;
};

int LayChieuCao(Nut* n) {
    if (n == nullptr) return 0;
    return n->chieu_cao;
}

Nut* TaoNutMoi(int value) {
    Nut* n = new Nut();
    n->khoa = value;
    n->chieu_cao = 1;
    n->trai = nullptr;
    n->phai = nullptr;
    return n;
}

Nut* XoayPhai(Nut* y) {
    Nut* x = y->trai;
    Nut* T2 = x->phai;

    x->phai = y;
    y->trai = T2;

    y->chieu_cao = max(LayChieuCao(y->trai), LayChieuCao(y->phai)) + 1;
    x->chieu_cao = max(LayChieuCao(x->trai), LayChieuCao(x->phai)) + 1;

    return x;
}

Nut* XoayTrai(Nut* x) {
    Nut* y = x->phai;
    Nut* T2 = y->trai;

    y->trai = x;
    x->phai = T2;

    x->chieu_cao = max(LayChieuCao(x->trai), LayChieuCao(x->phai)) + 1;
    y->chieu_cao = max(LayChieuCao(y->trai), LayChieuCao(y->phai)) + 1;

    return y;
}

int LayDoChenhLech(Nut* n) {
    if (n == nullptr) return 0;
    return LayChieuCao(n->trai) - LayChieuCao(n->phai);
}

Nut* ThemNut(Nut* goc, int value) {
    if (goc == nullptr) return TaoNutMoi(value);

    if (value < goc->khoa) {
        goc->trai = ThemNut(goc->trai, value);
    } else if (value > goc->khoa) {
        goc->phai = ThemNut(goc->phai, value);
    } else {
        return goc;
    }

    goc->chieu_cao = 1 + max(LayChieuCao(goc->trai), LayChieuCao(goc->phai));

    int chenh_lech = LayDoChenhLech(goc);

    if (chenh_lech > 1 && value < goc->trai->khoa) {
        return XoayPhai(goc);
    }

    if (chenh_lech < -1 && value > goc->phai->khoa) {
        return XoayTrai(goc);
    }

    if (chenh_lech > 1 && value > goc->trai->khoa) {
        goc->trai = XoayTrai(goc->trai);
        return XoayPhai(goc);
    }

    if (chenh_lech < -1 && value < goc->phai->khoa) {
        goc->phai = XoayPhai(goc->phai);
        return XoayTrai(goc);
    }

    return goc;
}

void DuyetTruoc(Nut* goc) {
    if (goc != nullptr) {
        cout << goc->khoa << " ";
        DuyetTruoc(goc->trai);
        DuyetTruoc(goc->phai);
    }
}

void DuyetGiua(Nut* goc) {
    if (goc != nullptr) {
        DuyetGiua(goc->trai);
        cout << goc->khoa << " ";
        DuyetGiua(goc->phai);
    }
}

void DuyetTheoTang(Nut* goc) {
    if (goc == nullptr) return;
    queue<Nut*> hang_doi;
    hang_doi.push(goc);
    while (!hang_doi.empty()) {
        Nut* hien_tai = hang_doi.front();
        hang_doi.pop();
        cout << hien_tai->khoa << " ";
        if (hien_tai->trai != nullptr) hang_doi.push(hien_tai->trai);
        if (hien_tai->phai != nullptr) hang_doi.push(hien_tai->phai);
    }
}

int main() {
    Nut* goc_cay = nullptr;
    int day_so[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    int so_phan_tu = sizeof(day_so) / sizeof(day_so[0]);

    for (int i = 0; i < so_phan_tu; i++) {
        goc_cay = ThemNut(goc_cay, day_so[i]);
    }

    cout << "Duyet truoc (NLR): ";
    DuyetTruoc(goc_cay);
    cout << endl;

    cout << "Duyet giua (LNR): ";
    DuyetGiua(goc_cay);
    cout << endl;

    cout << "Duyet theo tung tang: ";
    DuyetTheoTang(goc_cay);
    cout << endl;

    return 0;
}