#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

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

class CamBien{
private:
    int maso;
    bool trangthai;
    int muc_khoi;
    string vi_tri;

public:
    CamBien(int ma, string phong) {
        maso = ma;
        trangthai = false;
        muc_khoi = 0;
        vi_tri = phong;
    }

    void bat() {
        trangthai = true;
    }

    void tat() {
        trangthai = false;
    }

    void moPhongKhoi(int muc) {
        if (trangthai) {
            muc_khoi = muc;
        }
    }

    void hienThi() {
        cout << "Cam bien [" << maso << "] - " << (trangthai ? "BAT" : "TAT")
             << " - Muc khoi: " << muc_khoi
             << " - Vi tri: " << vi_tri << endl;
    }

    int getmaso() {
        return maso;
    }

    string getvitri() {
        return vi_tri;
    }

    int getmuckhoi() {
        return muc_khoi;
    }

    bool dangbat() {
        return trangthai;
    }
};

// ======================== CLASS HE THONG ==============================

class HeThongBaoChay {
private:
    vector<NguoiDung> danh_sach_nguoi_dung;
    vector<CamBien> danh_sach_cam_bien;
    string ten_file_cam_bien = "dscambien.txt";

public:
    void capNhatFileCamBien() {
        ofstream tep(ten_file_cam_bien);
        for (auto &cb : danh_sach_cam_bien) {
            tep << cb.layMaSo() << "," << (cb.dangBat() ? "BAT" : "TAT") << "," << cb.layMucKhoi() << "," << cb.layViTri() << endl;
        }
        tep.close();
    }

    void dangKy() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;
        danh_sach_nguoi_dung.push_back(NguoiDung(ten, mk));
        cout << "Dang ky thanh cong!\n";
    }

    bool dangNhap() {
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;

        for (auto nguoi : danh_sach_nguoi_dung) {
            if (nguoi.layTenDangNhap() == ten && nguoi.kiemTraMatKhau(mk)) {
                cout << "Dang nhap thanh cong!\n";
                return true;
            }
        }
        cout << "Sai ten hoac mat khau.\n";
        return false;
    }

    void themCamBien() {
        string phong;
        int ma = danh_sach_cam_bien.size() + 1;
        cout << "Nhap vi tri cam bien (ten phong): ";
        cin.ignore();
        getline(cin, phong);
        CamBien moi(ma, phong);
        danh_sach_cam_bien.push_back(moi);
        cout << "Da them cam bien ma: " << ma << " tai phong: " << phong << endl;
        capNhatFileCamBien();
    }

    void xoaCamBien() {
        int ma;
        cout << "Nhap ma cam bien muon xoa: ";
        cin >> ma;
        bool tim_thay = false;

        for (int i = 0; i < danh_sach_cam_bien.size(); i++) {
            if (danh_sach_cam_bien[i].layMaSo() == ma) {
                danh_sach_cam_bien.erase(danh_sach_cam_bien.begin() + i);
                cout << "Da xoa cam bien ma: " << ma << endl;
                capNhatFileCamBien();
                tim_thay = true;
                break;
            }
        }

        if (!tim_thay) {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void trangThaiCamBien() {
        int ma;
        cout << "Nhap ma cam bien muon kiem tra: ";
        cin >> ma;
        if (ma > 0 && ma <= danh_sach_cam_bien.size()) {
            cout << "Trang thai cam bien ma " << ma << ": "
                 << (danh_sach_cam_bien[ma - 1].dangBat() ? "BAT" : "TAT") << endl;
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
        if (ma > 0 && ma <= danh_sach_cam_bien.size()) {
            danh_sach_cam_bien[ma - 1].moPhongKhoi(muc);
            cout << "Mo phong khoi thanh cong.\n";
            capNhatFileCamBien();
        } else {
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void hienThiCamBien() {
        if (danh_sach_cam_bien.empty()) {
            cout << "Chua co cam bien nao.\n";
            return;
        }
        for (int i = 0; i < danh_sach_cam_bien.size(); i++) {
            CamBien* cb_ptr = &danh_sach_cam_bien[i]; // tạo con trỏ đến cảm biến
            cb_ptr->hienThi(); // dùng con trỏ gọi hàm
        }
    }

    void xemDanhSachCamBienDaThem() {
        ifstream tep(ten_file_cam_bien);
        string dong;
        cout << "\n=== DANH SACH CAM BIEN (doc tu file) ===\n";
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
        cout << "4. Mo phong muc khoi\n";
        cout << "5. Hien thi cam bien\n";
        cout << "6. Xem danh sach cam bien da them\n";
        cout << "7. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
            case 1: ht.themCamBien(); break;
            case 2: ht.xoaCamBien(); break;
            case 3: ht.trangThaiCamBien(); break;
            case 4: ht.moPhongKhoi(); break;
            case 5: ht.hienThiCamBien(); break;
            case 6: ht.xemDanhSachCamBienDaThem(); break;
            case 7: cout << "Dang thoat...\n"; break;
            default: cout << "Lua chon sai.\n";
        }
    } while (chon != 7);
}
// ======================== HAM MAIN ====================================

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
    } while(chon != 3);
    return 0;
}
