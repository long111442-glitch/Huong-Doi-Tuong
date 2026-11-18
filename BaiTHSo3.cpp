
#include<iostream>
#include<string>
using namespace std;

class Vehicle{
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle(){
        vehicleID = 0;
        vehicleType = "";
        entryTime = 0;
        parkingDuration = 0;
        parkingFee = 0;
    }

    Vehicle(int id, string type, int gio, int tg){
        vehicleID = id;
        vehicleType = type;
        entryTime = gio;
        parkingDuration = tg;
        parkingFee = 0;
    }

    int getID() const{
        return vehicleID;
    }

    string getType() const{
        return vehicleType;
    }

    void setID(int id){
        vehicleID = id;
    }

    void setType(string type){
        vehicleType = type;
    }

    void setEntryTime(int gio){
        entryTime = gio;
    }

    void setParkingDuration(int tg){
        parkingDuration = tg;
    }

    double calculateFee() const{
        if(vehicleType == "xe may") return parkingDuration * 5000;
        if(vehicleType == "o to") return parkingDuration * 10000;
        if(vehicleType == "xe dap") return parkingDuration * 1000;
        return 0;
    }

    void display() const{
        cout << "\nMa xe: " << vehicleID;
        cout << "\nLoai xe: " << vehicleType;
        cout << "\nGio vao: " << entryTime;
        cout << "\nThoi gian do: " << parkingDuration;
        cout << "\nPhi: " << calculateFee() << endl;
    }
};

class ParkingLot{
private:
    int parkID;
    char size;
    int capacity;
    int currentVehicleCount;
    Vehicle** vehicles;

public:
    ParkingLot(){
        parkID = 0;
        size = 'S';
        capacity = 1;
        currentVehicleCount = 0;

        vehicles = new Vehicle*[capacity];

        for(int i = 0; i < capacity; i++){
            vehicles[i] = nullptr;
        }
    }

    ParkingLot(int id, char s){
        parkID = id;
        size = s;
        currentVehicleCount = 0;

        if(size == 'S') capacity = 1;
        else if(size == 'M') capacity = 2;
        else if(size == 'L') capacity = 3;
        else capacity = 1;

        vehicles = new Vehicle*[capacity];

        for(int i = 0; i < capacity; i++){
            vehicles[i] = nullptr;
        }
    }

    ~ParkingLot(){
        for(int i = 0; i < currentVehicleCount; i++){
            delete vehicles[i];
        }

        delete[] vehicles;
    }

    ParkingLot(const ParkingLot& other){
        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];

        for(int i = 0; i < capacity; i++){
            vehicles[i] = nullptr;
        }

        for(int i = 0; i < currentVehicleCount; i++){
            vehicles[i] = new Vehicle(*other.vehicles[i]);
        }
    }

    ParkingLot& operator=(const ParkingLot& other){
        if(this == &other) return *this;

        for(int i = 0; i < currentVehicleCount; i++){
            delete vehicles[i];
        }

        delete[] vehicles;

        parkID = other.parkID;
        size = other.size;
        capacity = other.capacity;
        currentVehicleCount = other.currentVehicleCount;

        vehicles = new Vehicle*[capacity];

        for(int i = 0; i < capacity; i++){
            vehicles[i] = nullptr;
        }

        for(int i = 0; i < currentVehicleCount; i++){
            vehicles[i] = new Vehicle(*other.vehicles[i]);
        }

        return *this;
    }

    int getID() const{
        return parkID;
    }

    int getCount() const{
        return currentVehicleCount;
    }

    bool chua(int ma) const{
        for(int i = 0; i < currentVehicleCount; i++){
            if(vehicles[i]->getID() == ma)
                return false;
        }
        return true;
    }

    void resize(int newCapacity){
        Vehicle** newVehicles = new Vehicle*[newCapacity];

        for(int i = 0; i < newCapacity; i++){
            newVehicles[i] = nullptr;
        }

        for(int i = 0; i < currentVehicleCount; i++){
            newVehicles[i] = vehicles[i];
        }

        delete[] vehicles;

        vehicles = newVehicles;
        capacity = newCapacity;
    }

    bool addVehicle(const Vehicle& v){
        if(!chua(v.getID())) return false;

        if(currentVehicleCount >= capacity){
            resize(capacity * 2);
        }

        vehicles[currentVehicleCount] = new Vehicle(v);
        currentVehicleCount++;

        return true;
    }

    bool removeVehicle(int id){
        for(int i = 0; i < currentVehicleCount; i++){
            if(vehicles[i]->getID() == id){

                delete vehicles[i];

                for(int j = i; j < currentVehicleCount - 1; j++){
                    vehicles[j] = vehicles[j + 1];
                }

                currentVehicleCount--;

                vehicles[currentVehicleCount] = nullptr;

                return true;
            }
        }

        return false;
    }

    void display() const{
        cout << "\nMa bai xe: " << parkID;
        cout << "\nKich thuoc: " << size;
        cout << "\nSuc chua hien tai: " << capacity;
        cout << "\nSo xe hien co: " << currentVehicleCount << endl;

        for(int i = 0; i < currentVehicleCount; i++){
            vehicles[i]->display();
        }
    }

    bool co_loai(string loai, int& dem, double& tong) const{
        dem = 0;
        tong = 0;

        for(int i = 0; i < currentVehicleCount; i++){
            if(vehicles[i]->getType() == loai){
                dem++;
                tong += vehicles[i]->calculateFee();
            }
        }

        return dem > 0;
    }
};

class SystemInterface{
private:
    int lotCapacity;
    int currentLotCount;
    ParkingLot** parkingLots;

public:
    SystemInterface(){
        lotCapacity = 5;
        currentLotCount = 0;

        parkingLots = new ParkingLot*[lotCapacity];

        for(int i = 0; i < lotCapacity; i++){
            parkingLots[i] = nullptr;
        }
    }

    ~SystemInterface(){
        for(int i = 0; i < currentLotCount; i++){
            delete parkingLots[i];
        }

        delete[] parkingLots;
    }

    SystemInterface(const SystemInterface& other){
        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];

        for(int i = 0; i < lotCapacity; i++){
            parkingLots[i] = nullptr;
        }

        for(int i = 0; i < currentLotCount; i++){
            parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
        }
    }

    SystemInterface& operator=(const SystemInterface& other){
        if(this == &other) return *this;

        for(int i = 0; i < currentLotCount; i++){
            delete parkingLots[i];
        }

        delete[] parkingLots;

        lotCapacity = other.lotCapacity;
        currentLotCount = other.currentLotCount;

        parkingLots = new ParkingLot*[lotCapacity];

        for(int i = 0; i < lotCapacity; i++){
            parkingLots[i] = nullptr;
        }

        for(int i = 0; i < currentLotCount; i++){
            parkingLots[i] = new ParkingLot(*other.parkingLots[i]);
        }

        return *this;
    }

    void resizeSystem(int newCapacity){
        ParkingLot** newLots = new ParkingLot*[newCapacity];

        for(int i = 0; i < newCapacity; i++){
            newLots[i] = nullptr;
        }

        for(int i = 0; i < currentLotCount; i++){
            newLots[i] = parkingLots[i];
        }

        delete[] parkingLots;

        parkingLots = newLots;
        lotCapacity = newCapacity;
    }

    void taoBai(){
        int ma;
        char kt;

        cout << "Nhap ma bai xe: ";
        cin >> ma;

        for(int i = 0; i < currentLotCount; i++){
            if(parkingLots[i]->getID() == ma){
                cout << "Ma bai xe da ton tai!\n";
                return;
            }
        }

        if(currentLotCount >= lotCapacity){
            resizeSystem(lotCapacity * 2);
        }

        cout << "Nhap kich thuoc (S/M/L): ";
        cin >> kt;

        if(kt != 'S' && kt != 'M' && kt != 'L'){
            cout << "Kich thuoc khong hop le!\n";
            return;
        }

        parkingLots[currentLotCount] = new ParkingLot(ma, kt);
        currentLotCount++;

        cout << "Tao bai xe thanh cong!\n";
    }

    void themXe(){
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

        for(int i = 0; i < currentLotCount; i++){
            if(!parkingLots[i]->chua(ma_xe)){
                cout << "Xe da ton tai!\n";
                return;
            }
        }

        for(int i = 0; i < currentLotCount; i++){
            if(parkingLots[i]->getID() == ma_bai){

                Vehicle v(ma_xe, loai, gio, tg);

                if(parkingLots[i]->addVehicle(v)){
                    cout << "Them xe thanh cong!\n";
                }
                else{
                    cout << "Xe da ton tai!\n";
                }

                return;
            }
        }

        cout << "Khong tim thay bai xe!\n";
    }

    void xoaBai(){
        int ma;

        cout << "Nhap ma bai xe can xoa: ";
        cin >> ma;

        for(int i = 0; i < currentLotCount; i++){
            if(parkingLots[i]->getID() == ma){

                delete parkingLots[i];

                for(int j = i; j < currentLotCount - 1; j++){
                    parkingLots[j] = parkingLots[j + 1];
                }

                currentLotCount--;

                parkingLots[currentLotCount] = nullptr;

                cout << "Xoa bai xe thanh cong!\n";
                return;
            }
        }

        cout << "Khong tim thay bai xe!\n";
    }

    void layXe(){
        int ma_bai, ma_xe;

        cout << "Nhap ma bai xe: ";
        cin >> ma_bai;

        cout << "Nhap ma xe can lay: ";
        cin >> ma_xe;

        for(int i = 0; i < currentLotCount; i++){
            if(parkingLots[i]->getID() == ma_bai){

                if(parkingLots[i]->removeVehicle(ma_xe)){
                    cout << "Lay xe thanh cong!\n";
                }
                else{
                    cout << "Khong tim thay xe!\n";
                }

                return;
            }
        }

        cout << "Khong tim thay bai xe!\n";
    }

    void hienThi(){
        if(currentLotCount == 0){
            cout << "Chua co bai xe nao!\n";
            return;
        }

        for(int i = 0; i < currentLotCount; i++){
            parkingLots[i]->display();
        }
    }

    void thongKe(){
        string loai;
        int dem;
        double tong;
        bool timThay = false;

        cout << "Nhap loai xe can thong ke: ";
        cin.ignore();
        getline(cin, loai);

        cout << "\nKET QUA THONG KE\n";

        for(int i = 0; i < currentLotCount; i++){
            if(parkingLots[i]->co_loai(loai, dem, tong)){
                cout << "Bai " << parkingLots[i]->getID()
                     << ": " << dem
                     << " xe, phi = " << tong << endl;

                timThay = true;
            }
        }

        if(!timThay){
            cout << "Khong co xe thuoc loai nay!\n";
        }
    }

    void runMenu(){
        int chon;

        do{
            cout << "\n===== QUAN LY BAI XE =====\n";
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
                    hienThi();
                    break;

                case 6:
                    thongKe();
                    break;

                case 0:
                    cout << "Ket thuc chuong trinh!\n";
                    break;

                default:
                    cout << "Lua chon khong hop le!\n";
            }

        }while(chon != 0);
    }
};

int main(){
    SystemInterface ql;
    ql.runMenu();

    return 0;
}
