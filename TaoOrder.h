#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// ================= STRUCT =================
struct Ban {
    int soBan;
    int trangThai; // 0: trống, 1: có khách
};

struct Mon {
    string tenMon;
    string size;
    int duong;
    int da;
    string topping;
    int soLuong;
    double donGia;
};

struct Order {
    int soBan;
    string maHoaDon;
    string ngay;
    vector<Mon> dsMon;
    string ghiChu;
};

// ================= TIỆN ÍCH =================
string taoMaHoaDon() {
    time_t now = time(0);
    return "HD" + to_string(now);
}

string layNgayHienTai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "-" +
           to_string(1 + ltm->tm_mon) + "-" +
           to_string(ltm->tm_mday);
}

// ================= SƠ ĐỒ BÀN =================
vector<Ban> docSoDoBan(const string& tenFile) {
    vector<Ban> dsBan;
    ifstream file(tenFile);
    string dong;

    while (getline(file, dong)) {
        size_t pos = dong.find('|');
        if (pos != string::npos) {
            Ban b;
            b.soBan = stoi(dong.substr(0, pos));
            b.trangThai = stoi(dong.substr(pos + 1));
            dsBan.push_back(b);
        }
    }
    file.close();
    return dsBan;
}

void ghiSoDoBan(const string& tenFile, const vector<Ban>& dsBan) {
    ofstream file(tenFile);
    for (const auto& b : dsBan) {
        file << b.soBan << "|" << b.trangThai << endl;
    }
    file.close();
}

void hienThiBan(const vector<Ban>& dsBan) {
    cout << "\n=== TRẠNG THÁI BÀN ===\n";
    for (const auto& b : dsBan) {
        cout << "Bàn " << setw(2) << b.soBan << ": "
             << (b.trangThai ? "Có khách" : "Trống") << endl;
    }
}

// ================= HÓA ĐƠN =================
void xuLyHoaDon(vector<Ban>& dsBan, int soBan) {
    for (auto& b : dsBan) {
        if (b.soBan == soBan && b.trangThai == 1) {
            double tongTien;
            int phuongThuc;
            char xacNhan;

            cout << "\n--- HÓA ĐƠN BÀN " << soBan << " ---\n";
            cout << "Tổng tiền: ";
            cin >> tongTien;

            cout << "1. Tiền mặt\n";
            cout << "2. Chuyển khoản\n";
            cout << "Lựa chọn: ";
            cin >> phuongThuc;

            cout << "Xác nhận thanh toán? (Y/N): ";
            cin >> xacNhan;

            if (xacNhan == 'Y' || xacNhan == 'y') {
                cout << "\n===== HÓA ĐƠN =====\n";
                cout << "Bàn: " << soBan << endl;
                cout << "Tổng tiền: " << fixed << setprecision(0)
                     << tongTien << " VND\n";
                cout << "Thanh toán: "
                     << (phuongThuc == 1 ? "Tiền mặt" : "Chuyển khoản") << endl;
                cout << "Trạng thái: Đã thanh toán\n";
                cout << "===================\n";

                b.trangThai = 0;
                cout << "✔ Đã cập nhật trạng thái bàn.\n";
            } else {
                cout << "✖ Hủy thanh toán.\n";
            }
            return;
        }
    }
    cout << "❌ Bàn không tồn tại hoặc đang trống!\n";
}

// ================= TẠO ORDER =================
void taoOrderMoi(vector<Ban>& dsBan) {
    int soBan;
    cout << "Nhập số bàn: ";
    cin >> soBan;

    bool hopLe = false;
    for (auto& b : dsBan) {
        if (b.soBan == soBan && b.trangThai == 1) {
            hopLe = true;
            break;
        }
    }

    if (!hopLe) {
        cout << "❌ Bàn không tồn tại hoặc đang trống!\n";
        return;
    }

    Order order;
    order.soBan = soBan;
    order.maHoaDon = taoMaHoaDon();
    order.ngay = layNgayHienTai();

    char tiepTuc;
    do {
        Mon m;
        cin.ignore();
        cout << "\nTên món: ";
        getline(cin, m.tenMon);

        cout << "Size (S/M/L): ";
        cin >> m.size;

        cout << "% Đường: ";
        cin >> m.duong;

        cout << "% Đá: ";
        cin >> m.da;

        cin.ignore();
        cout << "Topping: ";
        getline(cin, m.topping);

        cout << "Số lượng: ";
        cin >> m.soLuong;

        cout << "Đơn giá: ";
        cin >> m.donGia;

        order.dsMon.push_back(m);

        cout << "Thêm món nữa? (Y/N): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'Y' || tiepTuc == 'y');

    cin.ignore();
    cout << "Ghi chú: ";
    getline(cin, order.ghiChu);

    ofstream file("Order.txt", ios::app);
    file << "MaHD:" << order.maHoaDon
         << "|Ban:" << order.soBan
         << "|Ngay:" << order.ngay << endl;

    for (auto& m : order.dsMon) {
        file << m.tenMon << "|"
             << m.size << "|"
             << m.duong << "%|"
             << m.da << "%|"
             << m.topping << "|"
             << m.soLuong << "|"
             << m.donGia << endl;
    }

    file << "GhiChu:" << order.ghiChu << endl;
    file << "--------------------------\n";
    file.close();

    cout << "\n✔ Tạo order thành công! Mã hóa đơn: "
         << order.maHoaDon << endl;
}

// ================= MENU =================
void hienThiMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Xử lý hóa đơn\n";
    cout << "2. Tạo order mới\n";
    cout << "0. Thoát\n";
    cout << "Lựa chọn: ";
}

// ================= MAIN =================
int main() {
    string tenFile = "SoDoBan.txt";
    vector<Ban> dsBan = docSoDoBan(tenFile);
    int luaChon;

    do {
        hienThiBan(dsBan);
        hienThiMenu();
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                int soBan;
                cout << "Nhập số bàn thanh toán: ";
                cin >> soBan;
                xuLyHoaDon(dsBan, soBan);
                ghiSoDoBan(tenFile, dsBan);
                break;
            }
            case 2:
                taoOrderMoi(dsBan);
                break;
            case 0:
                cout << "Thoát chương trình.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
        }

    } while (luaChon != 0);

    return 0;
}
