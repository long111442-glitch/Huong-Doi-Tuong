
#include<iostream>
#include<string>
using namespace std;

class phuong_tien{
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    
    string lay_loai_xe() const;
    
    double tinh_phi() const;
    
    void hien_thi() const;
};

phuong_tien::phuong_tien(){
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg){
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    
    tg_do = tg;
    
}

int phuong_tien::lay_ma_xe() const{
    return ma_xe;
}

string phuong_tien::lay_loai_xe() const{
    return loai_xe;
}

double phuong_tien::tinh_phi() const{
    if(loai_xe == "xe may") return tg_do * 5000;
    if(loai_xe == "o to") return tg_do * 10000;
    if(loai_xe == "xe dap") return tg_do * 1000;
    return 0;
}

void phuong_tien::hien_thi() const{
    cout << "\nMa xe: " << ma_xe;
    cout << "\nLoai xe: " << loai_xe;
    cout << "\nGio vao: " << gio_vao;
    cout << "\nThoi gian do: " << tg_do;
    cout << "\nPhi: " << tinh_phi() << endl;
}

class bai_xe{
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int maxe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
    
};

bai_xe::bai_xe(){
    ma_bai = 0;
    kich_thuoc = ' ';
    co1 = co2 = co3 = false;
}

bai_xe::bai_xe(int ma, char kt){
    ma_bai = ma;
    kich_thuoc = kt;
    co1 = co2 = co3 = false;
    
}

int bai_xe::lay_ma() const{
    return ma_bai;
    
}

bool bai_xe::them(phuong_tien v){
    if(!chua(v.lay_ma_xe()))
        return false;

    if(!co1){
        pt1 = v;
        co1 = true;
        return true;
    }

    if(!co2){
        pt2 = v;
        co2 = true;
        return true;
    }

    if(!co3){
        pt3 = v;
        co3 = true;
        return true;
    }

    return false;
}

bool bai_xe::xoa(int ma_xe){
    if(co1 && pt1.lay_ma_xe() == ma_xe){
        pt1 = phuong_tien();
        co1 = false;
        return true;
    }

    if(co2 && pt2.lay_ma_xe() == ma_xe){
        pt2 = phuong_tien();
        co2 = false;
        return true;
    }

    if(co3 && pt3.lay_ma_xe() == ma_xe){
        pt3 = phuong_tien();
        co3 = false;
        return true;
    }

    return false;
}

bool bai_xe::chua(int ma_xe) const{
    if(co1 && pt1.lay_ma_xe() == ma_xe) return false;
    if(co2 && pt2.lay_ma_xe() == ma_xe) return false;
    if(co3 && pt3.lay_ma_xe() == ma_xe) return false;

    return true;
}

void bai_xe::hien_thi() const{
    cout << "\nMa bai xe: " << ma_bai;
    cout << "\nKich thuoc: " << kich_thuoc << endl;

    if(co1) pt1.hien_thi();
    if(co2) pt2.hien_thi();
    if(co3) pt3.hien_thi();

    if(!co1 && !co2 && !co3)
        cout << "Bai xe trong!";
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const{
    dem = 0;
    tong = 0;

    if(co1 && pt1.lay_loai_xe() == loai){
        dem++;
        tong += pt1.tinh_phi();
    }

    if(co2 && pt2.lay_loai_xe() == loai){
        dem++;
        tong += pt2.tinh_phi();
        
    }
    
    

    if(co3 && pt3.lay_loai_xe() == loai){
        dem++;
        tong += pt3.tinh_phi();
    }

    return dem > 0;
    
}

class SystemInterface{
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
    void taoBai();
    void themXe();
    void xoaBai();
    void layXe();
    
};

SystemInterface::SystemInterface(){
    co1 = co2 = co3 = false;
}

void SystemInterface::taoBai(){
    int ma;
    char kt;

    cout << "Nhap ma bai xe: ";
    cin >> ma;

    if((co1 && bai1.lay_ma() == ma) ||
       (co2 && bai2.lay_ma() == ma) ||
       (co3 && bai3.lay_ma() == ma)){
        cout << "Ma bai xe da ton tai!\n";
        return;
    }

    if(co1 && co2 && co3){
        cout << "Da du 3 bai xe!\n";
        return;
    }

    cout << "Nhap kich thuoc (S/M/L): ";
    cin >> kt;

    if(kt != 'S' && kt != 'M' && kt != 'L'){
        cout << "Kich thuoc khong hop le!\n";
        return;
    }




    if(!co1){
        bai1 = bai_xe(ma, kt);
        co1 = true;
    }
    else if(!co2){
        bai2 = bai_xe(ma, kt);
        co2 = true;
    }
    else{
        bai3 = bai_xe(ma, kt);
        co3 = true;
    }

    cout << "Tao bai xe thanh cong!\n";
}



void SystemInterface::themXe(){
    int ma_bai, ma_xe, gio, tg;
    string loai;

    cout << "Nhap ma bai xe: ";
    cin >> ma_bai;

    cout << "Nhap ma xe: ";
    cin >> ma_xe;

    cout << "Nhap loai xe (xe may/o to/xe dap): ";
    cin.ignore();
    getline(cin, loai);

    cout << "Nhap gio vao: ";
    cin >> gio;

    cout << "Nhap thoi gian do: ";
    cin >> tg;

    if(loai != "xe may" && loai != "o to" && loai != "xe dap"){
        cout << "Loai xe khong hop le!\n";
        return;
    }

    if(gio < 0 || gio > 23 || tg <= 0){
        cout << "Thong tin thoi gian khong hop le!\n";
        return;
    }

    bool trung = false;

    if(co1 && !bai1.chua(ma_xe)) trung = true;
    if(co2 && !bai2.chua(ma_xe)) trung = true;
    if(co3 && !bai3.chua(ma_xe)) trung = true;

    if(trung){
        cout << "Ma xe da ton tai!\n";
        return;
    }

    phuong_tien v(ma_xe, loai, gio, tg);

    if(co1 && bai1.lay_ma() == ma_bai){
        if(bai1.them(v))
            cout << "Them xe thanh cong!\n";
        else
            cout << "Bai xe da day!\n";
        return;
    }

    if(co2 && bai2.lay_ma() == ma_bai){
        if(bai2.them(v))
            cout << "Them xe thanh cong!\n";
        else
            cout << "Bai xe da day!\n";
        return;
    }

    if(co3 && bai3.lay_ma() == ma_bai){
        if(bai3.them(v))
            cout << "Them xe thanh cong!\n";
        else
            cout << "Bai xe da day!\n";
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::xoaBai(){
    int ma;

    cout << "Nhap ma bai xe can xoa: ";
    cin >> ma;

    if(co1 && bai1.lay_ma() == ma){
        bai1 = bai_xe();
        co1 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    if(co2 && bai2.lay_ma() == ma){
        bai2 = bai_xe();
        co2 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    if(co3 && bai3.lay_ma() == ma){
        bai3 = bai_xe();
        co3 = false;
        cout << "Xoa bai xe thanh cong!\n";
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::layXe(){
    int ma_bai, ma_xe;

    cout << "Nhap ma bai xe: ";
    cin >> ma_bai;

    cout << "Nhap ma xe can lay: ";
    cin >> ma_xe;

    if(co1 && bai1.lay_ma() == ma_bai){
        if(bai1.xoa(ma_xe))
            cout << "Lay xe thanh cong!\n";
        else
            cout << "Khong tim thay xe!\n";
        return;
    }

    if(co2 && bai2.lay_ma() == ma_bai){
        if(bai2.xoa(ma_xe))
            cout << "Lay xe thanh cong!\n";
        else
            cout << "Khong tim thay xe!\n";
        return;
    }

    if(co3 && bai3.lay_ma() == ma_bai){
        if(bai3.xoa(ma_xe))
            cout << "Lay xe thanh cong!\n";
        else
            cout << "Khong tim thay xe!\n";
        return;
    }

    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::runMenu(){
    int chon;

    do{
        cout << "\n QUAN LY BAI XE\n";
        cout << "1. Tao bai xe\n";
        cout << "2. Them phuong tien\n";
        cout << "3. Xoa bai xe\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi danh sach bai xe\n";
        cout << "6. Thong ke theo loai xe\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> chon;

        switch(chon){
            case 1:
                taoBai();
                break;
			

            case 2:
                themXe();
                break;
			

            case 3:
                xoaBai();
                break;

            case 4:
                layXe();
                break;

            case 5:
                if(co1) bai1.hien_thi();
                if(co2) bai2.hien_thi();
                if(co3) bai3.hien_thi();

                if(!co1 && !co2 && !co3)
                    cout << "Chua co bai xe nao!\n";
                break;

            case 6:{
                string loai;
                int dem;
                double tong;
                bool tim_thay = false;

                cout << "Nhap loai xe can thong ke: ";
                cin.ignore();
                getline(cin, loai);

                cout << "\nKET QUA THONG KE\n";

                if(co1 && bai1.co_loai(loai, dem, tong)){
                    cout << "Bai " << bai1.lay_ma()
                         << ": " << dem
                         << " xe, phi = " << tong << endl;
                    tim_thay = true;
                }

                if(co2 && bai2.co_loai(loai, dem, tong)){
                    cout << "Bai " << bai2.lay_ma()
                         << ": " << dem
                         << " xe, phi = " << tong << endl;
                    tim_thay = true;
                }

                if(co3 && bai3.co_loai(loai, dem, tong)){
                    cout << "Bai " << bai3.lay_ma()
                         << ": " << dem
                         << " xe, phi = " << tong << endl;
                    tim_thay = true;
                }

                if(!tim_thay)
                    cout << "Khong co xe thuoc loai nay!\n";

                break;
            }

            case 0:
                cout << "Ket thuc chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    }while(chon != 0);
}

int main(){
    SystemInterface ql;
    ql.runMenu();
    return 0;
}
