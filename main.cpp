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
    void bat(){
        trangthai=1;
    }
    void tat(){
        trangthai= 0;
    }
    void mophongkhoi(int muc){
        if(trangthai){
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
            trangthai = 1;
        }
    }
};

class HeThongBaoChay{
private:
    vector<NguoiDung> danhsachnguoidung;
    vector<cambien> danhsachcambien;

public:
    void capnhatfilecambien(){
        ofstream tep("cambien.txt");
        for (int i = 0; i <danhsachcambien.size(); i++){
            tep <<"ID: "<<danhsachcambien[i].getidcambien()<<" - Trang thai: ";
                if (danhsachcambien[i].dangbat() == 1){
        tep<<"Dang bat";
    }
    else{tep<<"Dang tat";}
    tep<<" - Muc khoi: "<< danhsachcambien[i].getmuckhoi();
    tep<<" - Vi tri: "<<danhsachcambien[i].getvitri()<<endl;
}
        tep.close();
    }
    void dangky(){
        string ten, mk;
        cout<<"Nhap ten dang nhap: ";
        cin>>ten;
        cout << "Nhap mat khau: ";
        cin>>mk;
        danhsachnguoidung.push_back(NguoiDung(ten, mk));
        cout << "Dang ky thanh cong"<<endl;
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

    bool checktrungidcambien(string _idcambien){
    for(int i=0; i<danhsachcambien.size(); i++){
        if(danhsachcambien[i].getidcambien() == _idcambien){
            return true;
        }
    }
    return false;
}

    void themcambien(){
        string ma, phong;
        cout<<"Nhap ID cam bien: ";
        cin>>ma;
        if(checktrungidcambien(ma)){
        cout << "Trung ID, nhap ID khac.";
        return;}
        cout<<"Nhap vi tri cam bien: ";
        cin.ignore();
        getline(cin, phong);
        cambien moi(ma, phong);
        danhsachcambien.push_back(moi);
        cout << "Da them cam bien ID: " << ma << " tai phong: " << phong << endl;
        capnhatfilecambien();
    }

    void xoacambien(){
        string ma;
        cout<<"Nhap ID cam bien muon xoa: ";
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

        if(!timthay){
            cout << "Khong tim thay cam bien.\n";
        }
    }

    void trangthaicambien(){
        string ma;
        cout << "Nhap ID cam bien: ";
        cin >> ma;
        for(int i = 0; i < danhsachcambien.size(); i++){
        if(danhsachcambien[i].getidcambien() == ma){
            if(danhsachcambien[i].dangbat()){
                cout<<"ID: "<<danhsachcambien[i].getidcambien()<<": Dang bat"<<endl;
            }
            else{cout<<"ID: "<<danhsachcambien[i].getidcambien()<<": Dang tat"<<endl;}
        }
        else{cout<<"Khong tim thay cam bien;"<<endl;}
    }}
    void mophongkhoi(){
        string ma;
        int muc;
        cout<<"Nhap ma cam bien: ";
        cin>>ma;
        cout<<"Nhap muc khoi (0-100): ";
        cin>>muc;

        for(int i=0; i < danhsachcambien.size(); i++){
        if(danhsachcambien[i].getidcambien() == ma){
            danhsachcambien[i].mophongkhoi(muc);
            cout<<"Da chinh sua muc khoi"<<endl;
            capnhatfilecambien();
        } else {
            cout<<"Khong tim thay cam bien"<<endl;
        }
    }
      
    }

    void doitrangthaicambien(){
        string ma;
        cout<<"Nhap ID cam bien: ";
        cin>>ma;

    for(int i=0; i <danhsachcambien.size(); i++){
        if (danhsachcambien[i].getidcambien() == ma){
            danhsachcambien[i].doitrangthai();
            cout << "Trang thai cua cam bien " << ma << " da duoc doi" << endl;
            capnhatfilecambien();
        } 
        else{
            cout<<"Khong tim thay cam bien"<<endl;
        }
    }}

    void hienthicambien(){
        if (danhsachcambien.empty()) {
            cout << "khong co"<<endl;
            return;
        }
        for(int i = 0; i < danhsachcambien.size(); i++){
            cambien* p = &danhsachcambien[i];
            p->hienthi();
        }
    }

    void xemdanhsachcambiendathem(){
        ifstream tep("cambien.txt");
        string dong;
        while(getline(tep, dong)){
            cout << dong << endl;
        }
        tep.close();
    }
void kiemtrachay(){
    for(int i=0; i < danhsachcambien.size(); i++){
    if(danhsachcambien[i].getmuckhoi()>69){
        cout<<"SOS: PHONG "<<danhsachcambien[i].getvitri()<<" DANG CHAY"<<endl;
    }}
};

void menuhethong(HeThongBaoChay &ht){
    int luachon;
    do{
        cout<<endl;
        cout<<"================================================"<<endl;        
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
        cin>>luachon;
        cout<<endl;
        cout<<"================================================"<<endl;
        cout<<endl;

        switch(luachon){
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
    }while(luachon != 8);
}

int main(){
    HeThongBaoChay ht;
    int luachon1;
    int dem=0;
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
        cin >> luachon1;
        switch(luachon1){
            case 1:
                ht.dangky();
                break;
            case 2:
                if(ht.dangnhap()){
                    dem=0;
                    menuhethong(ht);
                }
                else{
                    dem++;
                    if(dem>=3){
                        cout<<"============================"<<endl;
                        cout<<" Nhap sai qua 3 lan \n THOAT CHUONG TRINH\n";
                        return 0;

                    }
                else{
                    cout<<"Ban da nhap sai "<<dem<<" lan. Ban con "<<3-dem<<" lan thu";
                }}
                break;
            case 3: cout << "ok"<<endl; break;
            default: cout << "Lua chon sai.\n";
        }
    } while(luachon1 != 3);
    return 0;
}
