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

    string getUsername() {
        return username;
    }

    bool checkPass(string _pass) {
        return pass == _pass;
    }
};

class CamBien {
private:
    int idCamBien;
    bool trangThai;
    int mucKhoi;
    string viTri;

public:
    CamBien(int ma, string phong) {
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

    void moPhongKhoi(int muc) {
        if (trangthai) {
            mucKhoi = muc;
        }
    }

    void hienThi() {
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

    int getIdCamBien() {
        return idCamBien;
    }

    string getViTri() {
        return viTri;
    }

    int getMucKhoi() {
        return mucKhoi;
    }

    bool dangBat() {
        return trangthai;
    }

    void doiTrangThai() {
        trangthai = !trangthai; // Đảo ngược trạng thái (nếu đang bật thì tắt, và ngược lại)
    }
};

class HeThongBaoChay {
private:
    vector<NguoiDung> danhSachNguoiDung;
    vector<CamBien> danhSachCamBien;
    string tenFileCamBien = "dscambien.txt";

public:
    void capNhatFileCamBien() {
        ofstream tep(tenFileCamBien);
        for (auto &cb : danhSachCamBien) {
            tep << cb.getIdCamBien() << "," << (cb.dangBat() ? "BAT" : "TAT") << "," << cb.getMucKhoi() << "," << cb.getViTri() << endl;
        }
        tep.close();
    }

    void dangKy() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;
        danhSachNguoiDung.push_back(NguoiDung(ten, mk));
        cout << "Dang ky thanh cong!\n";
    }

    bool dangNhap() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;

        for (auto nguoi : danhSachNguoiDung) {
            if (nguoi.getUsername() == ten && nguoi.checkPass(mk)) {
                cout << "Dang nhap thanh cong!\n";
                return true;
            }
        }
        cout << "Sai ten hoac mat khau.\n";
        return false;
    }

    void themCamBien() {
        string phong;
        int ma = danhSachCamBien.size() + 1;
        cout << "Nhap vi tri cam bien (ten phong): ";
        cin.ignore();
        getline(cin, phong);
        CamBien moi(ma, phong);
        danhSachCamBien.push_back(moi);
        cout << "Da them cam bien ma: " << ma << " tai phong: " << phong << endl;
        capNhatFileCamBien();
    }

    void xoaCamBien() {
        int ma;
        cout << "Nhap ma cam bien muon xoa: ";
        cin >> ma;
        bool timThay = false;

        for (int i = 0; i < danhSachCamBien.size(); i++) {
            if (danhSachCamBien[i].getIdCamBien() == ma) {
                danhSachCamBien.erase(danhSachCamBien.begin() + i);
                cout << "Da xoa cam bien ma: " << ma << endl;
                capNhatFileCamBien();
                timThay = true;
                break;
            }
        }

        if (!timThay) {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void trangThaiCamBien() {
        int ma;
        cout << "Nhap ma cam bien muon kiem tra: ";
        cin >> ma;
        if (ma > 0 && ma <= danhSachCamBien.size()) {
            cout << "Trang thai cam bien ma " << ma << ": "
                 << (danhSachCamBien[ma - 1].dangBat() ? "BAT" : "TAT") << endl;
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void moPhongKhoi() {
        int ma, muc;
        cout << "Nhap ma cam bien: ";
        cin >> ma;
        cout << "Nhap muc khoi (0-100): ";
        cin >> muc;
        if (ma > 0 && ma <= danhSachCamBien.size()) {
            danhSachCamBien[ma - 1].moPhongKhoi(muc);
            cout << "Da chinh sua muc khoi\n";
            capNhatFileCamBien();
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void doiTrangThaiCamBien() {
        int ma;
        cout << "Nhap ma cam bien muon thay doi trang thai: ";
        cin >> ma;
        if (ma > 0 && ma <= danhSachCamBien.size()) {
            danhSachCamBien[ma - 1].doiTrangThai(); // Đổi trạng thái (bật/tắt)
            cout << "Trang thai cua cam bien " << ma << " da duoc doi.\n";
            capNhatFileCamBien();
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void hienThiCamBien() {
        if (danhSachCamBien.empty()) {
            cout << "khong co\n";
            return;
        }
        for (int i = 0; i < danhSachCamBien.size(); i++) {
            CamBien* cbPtr = &danhSachCamBien[i];
            cbPtr->hienThi();
        }
    }

    void xemDanhSachCamBienDaThem() {
        ifstream tep(tenFileCamBien);
        string dong;
        while (getline(tep, dong)) {
            cout << dong << endl;
        }
        tep.close();
    }
};

void menuHeThong(HeThongBaoChay &ht) {
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
            case 1: ht.themCamBien(); break;
            case 2: ht.xoaCamBien(); break;
            case 3: ht.trangThaiCamBien(); break;
            case 4: ht.moPhongKhoi(); break;
            case 5: ht.hienThiCamBien(); break;
            case 6: ht.xemDanhSachCamBienDaThem(); break;
            case 7: ht.doiTrangThaiCamBien(); break; // Thêm lựa chọn cho thay đổi trạng thái
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
            case 1: ht.dangKy(); break;
            case 2:
                if (ht.dangNhap()) {
                    menuHeThong(ht);
                }
                break;
            case 3: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le.\n";
        }
    } while(luachon != 3);
    return 0;
}
