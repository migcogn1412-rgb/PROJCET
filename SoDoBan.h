#ifndef SODOBAN_H
#define SODOBAN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ===== STRUCT =====
struct Ban {
    int soBan;
    int trangThai; // 0: trống, 1: có khách
};

// ===== ĐỌC / GHI FILE =====
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

// ===== HIỂN THỊ =====
void hienThiBan(const vector<Ban>& dsBan) {
    cout << "\n=== TRẠNG THÁI BÀN ===\n";
    for (const auto& b : dsBan) {
        cout << "Bàn " << setw(2) << b.soBan << ": "
             << (b.trangThai ? "Có khách" : "Trống") << endl;
    }
}

void hienThiMenu() {
    cout << "\n===== OPTIONS =====\n";
    cout << "1. Xử lý hóa đơn\n";
    cout << "0. Thoát\n";
    cout << "Lựa chọn của bạn: ";
}

// ===== XỬ LÝ HÓA ĐƠN =====
void xuLyHoaDon(vector<Ban>& dsBan, int soBan) {
    for (auto& b : dsBan) {
        if (b.soBan == soBan && b.trangThai == 1) {
            double tongTien;
            int phuongThuc;
            char xacNhan;

            cout << "\n--- HÓA ĐƠN BÀN " << soBan << " ---\n";
            cout << "TỔNG TIỀN: ";
            cin >> tongTien;

            cout << "1. Tiền mặt\n";
            cout << "2. Chuyển khoản\n";
            cout << "Lựa chọn: ";
            cin >> phuongThuc;

            cout << "Xác nhận thanh toán? (Y/N): ";
            cin >> xacNhan;

            if (xacNhan == 'y' || xacNhan == 'Y') {
                cout << "\n===== HÓA ĐƠN =====\n";
                cout << "Bàn: " << soBan << endl;
                cout << "Tổng tiền: " << fixed << setprecision(0)
                     << tongTien << " VND\n";
                cout << "Thanh toán: "
                     << (phuongThuc == 1 ? "Tiền mặt" : "Chuyển khoản") << endl;
                cout << "Trạng thái: Đã thanh toán\n";
                cout << "===================\n";

                b.trangThai = 0;
                cout << "Đã cập nhật trạng thái bàn.\n";
            } else {
                cout << "Hủy thanh toán.\n";
            }
            return;
        }
    }
    cout << "Bàn không tồn tại hoặc đang trống!\n";
}

// ===== XỬ LÝ LỰA CHỌN =====
void xuLyLuaChon(int luaChon, vector<Ban>& dsBan, const string& tenFile) {
    int soBan;
    switch (luaChon) {
        case 1:
            cout << "Nhập số bàn cần thanh toán: ";
            cin >> soBan;
            xuLyHoaDon(dsBan, soBan);
            ghiSoDoBan(tenFile, dsBan);
            break;
        case 0:
            cout << "Thoát chương trình.\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ!\n";
    }
}
