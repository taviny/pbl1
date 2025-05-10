#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class NguoiDung {
private:
    string username;
    string pass;

public:
    NguoiDung(string _username, string _pass) {
        username = _username;
        pass = _pass;
    }

    string getusername() {
        return username;
    }

    bool checkpass(string _pass) {
        return pass == _pass;
    }
};

class cambien {
private:
    int idcambien;
    bool trangthai;
    int muckhoi;
    string vitri;

public:
    cambien(int ma, string phong) {
        idcambien = ma;
        trangthai = 0;
        muckhoi = 0;
        vitri = phong;
    }

    void bat() {
        trangthai=1;
    }

    void tat() {
        trangthai= 1;
    }

    void mophongkhoi(int muc) {
        if (trangthai) {
            muckhoi = muc;
        }
    }

    void hienthi() {
        cout << "Cam bien [" << idcambien << "] - ";
            if (trangthai == true) {
                cout << "BAT";
            }
            else{
                cout << "TAT";
            }
        cout << " - Muc khoi: " << muckhoi;
        cout << " - Vi tri: " << vitri << endl;
    }

    int getidcambien() {
        return idcambien;
    }

    string getvitri() {
        return vitri;
    }

    int getmuckhoi() {
        return muckhoi;
    }

    bool dangbat() {
        return trangthai;
    }

    void doitrangthai() {
        trangthai = !trangthai;
    }
};

class HeThongBaoChay {
private:
    vector<NguoiDung> danhsachnguoidung;
    vector<cambien> danhsachcambien;
    string tenfilecambien = "cambien.txt";

public:
    void capnhatfilecambien() {
        ofstream tep(tenfilecambien);
        for (auto &cb : danhsachcambien) {
            tep << cb.getidcambien() << "," << (cb.dangbat() ? "BAT" : "TAT") << "," << cb.getmuckhoi() << "," << cb.getvitri() << endl;
        }
        tep.close();
    }

    void dangky() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;
        danhsachnguoidung.push_back(NguoiDung(ten, mk));
        cout << "Dang ky thanh cong!\n";
    }

    bool dangnhap() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;

        for (auto nguoi : danhsachnguoidung) {
            if (nguoi.getusername() == ten && nguoi.checkpass(mk)) {
                cout << "Dang nhap thanh cong!\n";
                return true;
            }
        }
        cout << "Sai ten hoac mat khau.\n";
        return false;
    }

    void themcambien() {
        string phong;
        int ma = danhsachcambien.size() + 1;
        cout << "Nhap vi tri cam bien (ten phong): ";
        cin.ignore();
        getline(cin, phong);
        cambien moi(ma, phong);
        danhsachcambien.push_back(moi);
        cout << "Da them cam bien ma: " << ma << " tai phong: " << phong << endl;
        capnhatfilecambien();
    }

    void xoacambien() {
        int ma;
        cout << "Nhap ma cam bien muon xoa: ";
        cin >> ma;
        bool timthay = false;

        for (int i = 0; i < danhsachcambien.size(); i++) {
            if (danhsachcambien[i].getidcambien() == ma) {
                danhsachcambien.erase(danhsachcambien.begin() + i);
                cout << "Da xoa cam bien ma: " << ma << endl;
                capnhatfilecambien();
                timthay = true;
                break;
            }
        }

        if (!timthay) {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void trangthaicambien() {
        int ma;
        cout << "Nhap ma cam bien muon kiem tra: ";
        cin >> ma;
        if (ma > 0 && ma <= danhsachcambien.size()) {
            cout << "Trang thai cam bien ma " << ma << ": "
                 << (danhsachcambien[ma - 1].dangbat() ? "BAT" : "TAT") << endl;
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void mophongkhoi() {
        int ma, muc;
        cout << "Nhap ma cam bien: ";
        cin >> ma;
        cout << "Nhap muc khoi (0-100): ";
        cin >> muc;
        if (ma > 0 && ma <= danhsachcambien.size()) {
            danhsachcambien[ma - 1].mophongkhoi(muc);
            cout << "Da chinh sua muc khoi\n";
            capnhatfilecambien();
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void doitrangthaicambien() {
        int ma;
        cout << "Nhap ma cam bien muon thay doi trang thai: ";
        cin >> ma;
        if (ma > 0 && ma <= danhsachcambien.size()) {
            danhsachcambien[ma - 1].doitrangthai();
            cout << "Trang thai cua cam bien " << ma << " da duoc doi.\n";
            capnhatfilecambien();
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void hienthicambien() {
        if (danhsachcambien.empty()) {
            cout << "khong co\n";
            return;
        }
        for (int i = 0; i < danhsachcambien.size(); i++) {
            cambien* cbptr = &danhsachcambien[i];
            cbptr->hienthi();
        }
    }

    void xemdanhsachcambiendathem() {
        ifstream tep(tenfilecambien);
        string dong;
        while (getline(tep, dong)) {
            cout << dong << endl;
        }
        tep.close();
    }
};

void menuhethong(HeThongBaoChay &ht) {
    int chon;
    do {
        cout << "\nHE THONG BAO CHAY\n";
        cout << "1. Them cam bien\n";
        cout << "2. Xoa cam bien\n";
        cout << "3. Trang thai cam bien\n";
        cout << "4. Chinh sua muc khoi\n";
        cout << "5. Hien thi cam bien\n";
        cout << "6. Xem danh sach cam bien da them\n";
        cout << "7. Doi trang thai cam bien\n";
        cout << "8. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
            case 1: ht.themcambien(); break;
            case 2: ht.xoacambien(); break;
            case 3: ht.trangthaicambien(); break;
            case 4: ht.mophongkhoi(); break;
            case 5: ht.hienthicambien(); break;
            case 6: ht.xemdanhsachcambiendathem(); break;
            case 7: ht.doitrangthaicambien(); break;
            case 8: cout << "Dang thoat...\n"; break;
            default: cout << "Lua chon sai.\n";
        }
    } while (chon != 8);
}

int main() {
    HeThongBaoChay ht;
    int luachon;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Thoat\n";
        cout << "Lua chon: ";
        cin >> luachon;
        switch(luachon){
            case 1:
                ht.dangky();
                break;
            case 2:
                if(ht.dangnhap()) {
                    menuhethong(ht);
                }
                break;
            case 3: cout << "ok\n"; break;
            default: cout << "Lua chon sai.\n";
        }
    } while(luachon != 3);
    return 0;
}
