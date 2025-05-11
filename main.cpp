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
    string idcambien;
    bool trangthai;
    int muckhoi;
    string vitri;

public:
    cambien(string ma, string phong) {
        idcambien = ma;
        trangthai = 0;
        muckhoi = 0;
        vitri = phong;
    }

    void bat() {
        trangthai=1;
    }
    void tat() {
        trangthai= 0;
    }
    void mophongkhoi(int muc){
        if (trangthai) {
            muckhoi = muc;
        }
    }

    void hienthi(){
        cout << "Cam bien " << idcambien << " - ";
            if (trangthai) {
                cout << "Dang bat";
            }
            else{
                cout << "Dang tat";
            }
        cout << " - Muc khoi: " << muckhoi;
        cout << " - Vi tri: " << vitri << endl;
    }
    string getidcambien(){
        return idcambien;
    }
    string getvitri(){
        return vitri;
    }

    int getmuckhoi(){
        return muckhoi;
    }
    bool dangbat(){
        return trangthai;
    }
   void doitrangthai() {
        if (trangthai == 1){
            trangthai = 0;
        }else{
            trangthai = 0;
        }
    }
};

class HeThongBaoChay {
private:
    vector<NguoiDung> danhsachnguoidung;
    vector<cambien> danhsachcambien;
    string filecambien = "cambien.txt";

public:
    void capnhatfilecambien() {
        ofstream tep(filecambien);
        for (int i = 0; i < danhsachcambien.size(); ++i) {
            tep <<"ID: "<<danhsachcambien[i].getidcambien()<<" - Trang thai: ";
                if (danhsachcambien[i].dangbat() == 1){
        tep<<"Dang bat";
    }
    else{tep << "Dang tat";}
    tep<<" - Muc khoi: "<< danhsachcambien[i].getmuckhoi();
    tep<<" - Vi tri: "<<danhsachcambien[i].getvitri()<<endl;
}
        tep.close();
    }

    void dangky() {
        string ten, mk;
        cout<<"Nhap ten dang nhap: ";
        cin>>ten;
        cout << "Nhap mat khau: ";
        cin>>mk;
        danhsachnguoidung.push_back(NguoiDung(ten, mk));
        cout << "Dang ky thanh cong!\n";
    }

    bool dangnhap(){
        string ten, mk;
        cout << "Nhap ten dang nhap: ";
        cin >> ten;
        cout << "Nhap mat khau: ";
        cin >> mk;

        for(int i =0; i<danhsachnguoidung.size(); i++){
            if (danhsachnguoidung[i].getusername() == ten && danhsachnguoidung[i].checkpass(mk)) {
                cout << "Dang nhap thanh cong!"<<endl;
                return true;
            }
}
        cout<<"Nhap sai"<<endl;
        return false;
    }

    bool checktrungidcambien(string _idcambien) {
    for(int i=0; i<danhsachcambien.size(); i++){
        if (danhsachcambien[i].getidcambien() == _idcambien){
            return true;
        }
    }

    void themcambien() {
        string ma, phong;
        cout<<"Nhap ma cam bien: ";
        cin>>ma;
        if(checktrungidcambien(ma)){
        cout << "Trung ma, nhap ma khac.";
        return;}
        cout<<"Nhap vi tri cam bien: ";
        cin.ignore();
        getline(cin, phong);
        cambien moi(ma, phong);
        danhsachcambien.push_back(moi);
        cout << "Da them cam bien ID: " << ma << " tai phong: " << phong << endl;
        capnhatfilecambien();
    }


    return false;}

    void xoacambien() {
        int ma;
        cout<<"Nhap ma cam bien muon xoa: ";
        cin >> ma;
        bool timthay = false;

        for(int i = 0; i < danhsachcambien.size(); i++){
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
        cout << "Nhap ID cam bien: ";
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
            cambien* p = &danhsachcambien[i];
            p->hienthi();
        }
    }

    void xemdanhsachcambiendathem() {
        ifstream tep(filecambien);
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
        cout<<endl;
        cout<<"==================================="<<endl;        
        cout<<endl;
        cout<<"HE THONG BAO CHAY"<<endl;
        cout<<"1. Them cam bien"<<endl;
        cout<<"2. Xoa cam bien"<<endl;
        cout<<"3. Trang thai cam bien"<<endl;
        cout<<"4. Chinh sua muc khoi"<<endl;
        cout<<"5. Hien thi cam bien"<<endl;
        cout<<"6. Xem danh sach cam bien da them"<<endl;
        cout<<"7. Doi trang thai cam bien"<<endl;
        cout<<"8. Thoat"<<endl;
        cout<<endl;
        cout<<"Lua chon: ";
        cin>>chon;
        cout<<endl;
        cout<<"==================================="<<endl;
        cout<<endl;

        switch (chon) {
            case 1: ht.themcambien(); break;
            case 2: ht.xoacambien(); break;
            case 3: ht.trangthaicambien(); break;
            case 4: ht.mophongkhoi(); break;
            case 5: ht.hienthicambien(); break;
            case 6: ht.xemdanhsachcambiendathem(); break;
            case 7: ht.doitrangthaicambien(); break;
            case 8: cout << "Thoat"<<endl; break;
            default: cout << "Lua chon sai"<<endl;
        }
    } while (chon != 8);
}

int main() {
    HeThongBaoChay ht;
    int luachon;
    do{
        cout<<endl;
        cout << "TAI KHOAN"<<endl;
        cout<<endl;
        cout << "1. Dang ky";
        cout<<endl;
        cout << "2. Dang nhap";
        cout<<endl;
        cout << "3. Thoat";
        cout<<endl;
        cout << "Lua chon: ";
        cin >> luachon;
        switch(luachon){
            case 1:
                ht.dangky();
                break;
            case 2:
                if(ht.dangnhap()){
                    menuhethong(ht);
                }
                break;
            case 3: cout << "ok"<<endl; break;
            default: cout << "Lua chon sai.\n";
        }
    } while(luachon != 3);
    return 0;
}
