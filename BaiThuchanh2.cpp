
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
    phuong_tien ds_xe[3];
    int count;

public:
    bai_xe();
    bai_xe(int ma, char kt);
	int suc_chua() const{
		if(kich_thuoc == 'S') return 1;
		if(kich_thuoc == 'M') return 2;
		if(kich_thuoc == 'L') return 3;
		
		return 0;
	}
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
    count = 0;
}

bai_xe::bai_xe(int ma, char kt){
    ma_bai = ma;
    kich_thuoc = kt;
    count = 0;
    
}

int bai_xe::lay_ma() const{
    return ma_bai;
    
}

bool bai_xe::them(phuong_tien v){
    if(!chua(v.lay_ma_xe()))
        return false;

    if(count >= suc_chua()) return false;
    ds_xe[count] = v;
    count++;
    

    return true;
}

bool bai_xe::xoa(int ma_xe){
    for(int i = 0; i < count; i++){
    	if(ds_xe[i].lay_ma_xe() == ma_xe){
    		for(int j = i; j < count - 1; j++){
    			ds_xe[j] = ds_xe[j + 1];
			}
			count--;
    		return true;
		}
	}

    return false;
}

bool bai_xe::chua(int ma_xe) const{
   	for(int i = 0; i < count; i++){
   		if(ds_xe[i].lay_ma_xe() == ma_xe) return false;	
	}
    return true;
}

void bai_xe::hien_thi() const{
    cout << "\nMa bai xe: " << ma_bai;
    cout << "\nKich thuoc: " << kich_thuoc << endl;
    cout << "\n So xe hien tai: " << count << endl;

    for(int i = 0; i < count; i++){
    	ds_xe[i].hien_thi();
	}
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const{
    dem = 0;
    tong = 0;

   for(int i = 0; i < count; i++){
		if(ds_xe[i].lay_loai_xe() == loai){
			dem++;
			tong += ds_xe[i].tinh_phi();
		}
   }

    return dem > 0;
    
}

class SystemInterface{
private:
    
    bai_xe ds_bai[10];
    int count;

public:
    SystemInterface();
    void runMenu();
    void taoBai();
    void themXe();
    void xoaBai();
    void layXe();
    
};

SystemInterface::SystemInterface(){
    count = 0;
}

void SystemInterface::taoBai(){
    int ma;
    char kt;

    cout << "Nhap ma bai xe: ";
    cin >> ma;

   	for(int i = 0; i < count; i++){
   		if(ds_bai[i].lay_ma() == ma){
   			cout << "Ma bai xe da ton tai!\n";
			return;	
		}
	}
	
	if(count >= 10){
		cout << "Da du bai xe! \n";
		return;
	}

    cout << "Nhap kich thuoc (S/M/L): ";
    cin >> kt;

    if(kt != 'S' && kt != 'M' && kt != 'L'){
        cout << "Kich thuoc khong hop le!\n";
        return;
    }

	ds_bai[count] = bai_xe(ma, kt);
	count ++;

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

    phuong_tien v(ma_xe, loai, gio, tg);
    for(int i = 0; i < count; i++){
    	if(!ds_bai[i].chua(ma_xe)){
    		cout << "Xe da ton tai";
    		return;
		}
	}

	for(int i = 0; i < count; i++){
		if(ds_bai[i].lay_ma() == ma_bai){
			if(ds_bai[i].them(v)){
				cout << "Them xe thanh cong \n";
			}
			else{
				cout << "Bai xe da day \n";
			}
			return;
		}
	}
    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::xoaBai(){
    int ma;

    cout << "Nhap ma bai xe can xoa: ";
    cin >> ma;

   for(int i = 0; i < count; i++){
   		if(ds_bai[i].lay_ma() == ma){
   			for(int j = i; j < count - 1; j++){
   				ds_bai[j] = ds_bai[j + 1];	
			}
			count --;
			cout << "Xoa bai xe thanh cong \n";
			return;
		}
   }

    cout << "Khong tim thay bai xe!\n";
}

void SystemInterface::layXe(){
    int ma_bai, ma_xe;

    cout << "Nhap ma bai xe: ";
    cin >> ma_bai;

    cout << "Nhap ma xe can lay: ";
    cin >> ma_xe;

    for(int i = 0; i < count; i++){
    	if(ds_bai[i].lay_ma() == ma_bai){
    		if(ds_bai[i].xoa(ma_xe)){
    			cout << "Lay xe thanh cong\n";
			}
			else{
				cout << "Ko tim thay xe \n";
			}
			return;
		}
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
            	if(count == 0){
            		cout <<"Chua co bai xe nao! \n";
				}
                for(int i = 0; i < count; i++){
                	ds_bai[i].hien_thi();
				}
				
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

               	for(int i = 0; i < count; i++){
               		if(ds_bai[i].co_loai(loai, dem, tong)){
               			cout << "Bai " << ds_bai[i].lay_ma()
                        << ": " << dem
                        << " xe, phi = " << tong << endl;
                        
                        tim_thay = true;
					}	
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

