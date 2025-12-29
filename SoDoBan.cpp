#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Ban {
    int soBan;
    int trangThai; // 0: trống, 1: có khách
};

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

void xuLyHoaDon(vector<Ban>& dsBan, int soBan) {
    for (auto& b : dsBan) {
        if (b.soBan == soBan && b.trangThai == 1) {

            double tongTien;
            int phuongThuc;
            char xacNhan;

            cout << "\n--- HÓA ĐƠN BÀN " << soBan << " ---\n";
            cout << "TỔNG TIỀN: ";
            cin >> tongTien;

            cout << "Hãy chọn phương thức thanh toán:\n";
            cout << "1. Tiền mặt\n";
            cout << "2. Chuyển khoản\n";
            cout << "Lựa chọn: ";
            cin >> phuongThuc;

            cout << "Xác nhận thanh toán? (Y/N): ";
            cin >> xacNhan;

            if (xacNhan == 'y' || xacNhan == 'Y') {
                // In hoa don
                cout << "\n===== HÓA ĐƠN =====\n";
                cout << "Bàn: " << soBan << endl;
                cout << "Tổng tiền: " << fixed << setprecision(0) << tongTien << " VND\n";
                cout << "Thanh toán: "
                     << (phuongThuc == 1 ? "Tiền mặt" : "Chuyển khoản") << endl;
                cout << "Trạng thái: Đã thanh toán\n";
                cout << "===================\n";

                // Cap nhat ban ve trong
                b.trangThai = 0;
                cout << "Trạng thái của bàn " << soBan << " đã được cập nhật.\n";
            } else {
                cout << "Hủy thanh toán.\n";
            }
            return;
        }
    }
    cout << "Bàn không tồn tại hoặc đang TRỐNG!\n";
}

// ===== MAIN =====
int main() {
    string tenFile = "SoDoBan.txt";
    vector<Ban> dsBan = docSoDoBan(tenFile);

    int luaChon, soBan;

    do {
        hienThiBan(dsBan);

        cout << "\n===== MENU =====\n";
        cout << "1. Xử lý hóa đơn\n";
        cout << "0. Thoát\n";
        cout << "Lựa chọn: ";
        cin >> luaChon;

        if (luaChon == 1) {
            cout << "Nhập số bàn cần thanh toán: ";
            cin >> soBan;

            xuLyHoaDon(dsBan, soBan);
            ghiSoDoBan(tenFile, dsBan); // cap nhat tu dong
        }

    } while (luaChon != 0);

    return 0;
}
