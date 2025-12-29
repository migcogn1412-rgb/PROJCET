#ifndef CAPNHATORDER_H
#define CAPNHATORDER_H

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using std::cout, std::cin, std::endl, std::string;
using std::ifstream, std::ofstream, std::ios, std::istringstream, std::getline;
using std::format;

const int MAX_ORDER = 100; // Giới hạn số lượng order trong mảng tĩnh

// --- CẤU TRÚC DỮ LIỆU ORDER ---
struct Order {
    string maHD, ban, doUong, size, duong, da, topping, doAnNhe, ghiChu;
};

// --- HÀM HỖ TRỢ ĐỌC/GHI ---

// Tách dữ liệu từ 1 dòng file vào struct Order
Order docDongOrder(string line) {
    istringstream ss(line);
    Order o;
    getline(ss, o.maHD, '|');
    getline(ss, o.ban, '|');
    getline(ss, o.doUong, '|');
    getline(ss, o.size, '|');
    getline(ss, o.duong, '|');
    getline(ss, o.da, '|');
    getline(ss, o.topping, '|');
    getline(ss, o.doAnNhe, '|');
    getline(ss, o.ghiChu);
    return o;
}

// Đọc toàn bộ file vào mảng tĩnh
bool loadFileOrder(string tenFile, Order ds[], int& soLuong) {
    ifstream fIn(tenFile, ios::in);
    if (!fIn.is_open()) return false;

    soLuong = 0;
    string line;
    while (getline(fIn, line) && soLuong < MAX_ORDER) {
        if (line.length() < 5) continue; // Bỏ qua dòng trống
        ds[soLuong] = docDongOrder(line);
        soLuong++;
    }
    fIn.close();
    return true;
}

// Ghi toàn bộ mảng tĩnh đè lại vào file
void saveFileOrder(string tenFile, Order ds[], int soLuong) {
    ofstream fOut(tenFile, ios::out);
    for (int i = 0; i < soLuong; i++) {
        fOut << format("{}|{}|{}|{}|{}|{}|{}|{}|{}\n", 
                ds[i].maHD, ds[i].ban, ds[i].doUong, ds[i].size, 
                ds[i].duong, ds[i].da, ds[i].topping, ds[i].doAnNhe, ds[i].ghiChu);
    }
    fOut.close();
}

// --- CHỨC NĂNG CHÍNH ---
void capNhatOrder() {
    Order danhSach[MAX_ORDER];
    int soLuong = 0;
    string fileLichSu = "LichSuOrder.txt";

    if (!loadFileOrder(fileLichSu, danhSach, soLuong)) {
        cout << "LỖI: Không thể mở file " << fileLichSu << " hoặc file trống!" << endl;
        return;
    }

    cout << "\n[?] Nhập Mã hóa đơn cần cập nhật: ";
    string maTim;
    getline(cin, maTim);

    bool found = false;
    for (int i = 0; i < soLuong; i++) {
        if (danhSach[i].maHD == maTim) {
            found = true;
            string input;
            cout << format("\n--- ĐANG CẬP NHẬT HÓA ĐƠN: {} ---\n", maTim);
            cout << "(Bấm Enter để giữ nguyên giá trị cũ)\n";

            cout << format("- Bàn (Cũ: {}): ", danhSach[i].ban); 
            getline(cin, input); if(!input.empty()) danhSach[i].ban = input;

            cout << format("- Size (Cũ: {}): ", danhSach[i].size); 
            getline(cin, input); if(!input.empty()) danhSach[i].size = input;

            cout << format("- % Đường (Cũ: {}): ", danhSach[i].duong); 
            getline(cin, input); if(!input.empty()) danhSach[i].duong = input;

            cout << format("- % Đá (Cũ: {}): ", danhSach[i].da); 
            getline(cin, input); if(!input.empty()) danhSach[i].da = input;

            cout << format("- Topping (Cũ: {}): ", danhSach[i].topping); 
            getline(cin, input); if(!input.empty()) danhSach[i].topping = input;

            cout << format("- Đồ ăn nhẹ (Cũ: {}): ", danhSach[i].doAnNhe); 
            getline(cin, input); if(!input.empty()) danhSach[i].doAnNhe = input;

            cout << format("- Ghi chú (Cũ: {}): ", danhSach[i].ghiChu); 
            getline(cin, input); if(!input.empty()) danhSach[i].ghiChu = input;

            break; 
        }
    }

    if (found) {
        saveFileOrder(fileLichSu, danhSach, soLuong);
        cout << "\n--> [THÀNH CÔNG] Đã cập nhật Order vào file!\n";
    } else {
        cout << "\n--> [THẤT BẠI] Không tìm thấy Mã hóa đơn: " << maTim << endl;
    }
}

#endif
