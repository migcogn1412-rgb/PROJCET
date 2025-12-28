#ifndef CAPNHATORDER_H
#define CAPNHATORDER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using namespace std;

// Thứ tự của file text lưu trữ order.txt nên là Mã|Bàn|Đồ uống|Size|Đường|Đá|Topping|Đồ ăn nhẹ|Ghi chú

// --- CẤU TRÚC DỮ LIỆU ORDER ---
struct Order {
    string maHD;
    string ban;
    string doUong;
    string size;
    string duong;
    string da;
    string topping;
    string doAnNhe;
    string ghiChu;
};

// --- HÀM HỖ TRỢ ---
// Tách chuỗi dữ liệu từ file .txt
vector<string> splitOrder(string s) {
    vector<string> res;
    stringstream ss(s);
    string item;
    while (getline(ss, item, '|')) res.push_back(item);
    return res;
}

// --- CHỨC NĂNG CHÍNH: CẬP NHẬT ORDER CŨ ---
void capNhatOrder() {
    string maTim;
    cout << "\n[?] Nhập Mã hóa đơn cần cập nhật: ";
    getline(cin, maTim);

    // 1. Đọc toàn bộ dữ liệu từ file của bạn khác làm (ví dụ: LichSuOrder.txt)
    ifstream fIn("LichSuOrder.txt");
    vector<Order> danhSach;
    string line;
    bool found = false;

    while (getline(fIn, line)) {
        if (line.empty()) continue;
        vector<string> p = splitOrder(line);
        // Giả sử định dạng: MaHD|Ban|DoUong|Size|Duong|Da|Topping|DoAnNhe|GhiChu
        if (p.size() >= 9) {
            danhSach.push_back({p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]});
        }
    }
    fIn.close();

    // 2. Tìm kiếm và sửa đổi
    for (auto &o : danhSach) {
        if (o.maHD == maTim) {
            found = true;
            string input;
            cout << format("\n--- ĐANG CẬP NHẬT HÓA ĐƠN: {} ---\n", maTim);
            cout << "(Bấm Enter để giữ nguyên giá trị cũ)\n";

            // Cập nhật các Option theo Mind Map
            cout << format("- Bàn cần thêm/đổi (Cũ: {}): ", o.ban); 
            getline(cin, input); if(!input.empty()) o.ban = input;

            cout << format("- Size (Cũ: {}): ", o.size); 
            getline(cin, input); if(!input.empty()) o.size = input;

            cout << format("- % Đường (Cũ: {}): ", o.duong); 
            getline(cin, input); if(!input.empty()) o.duong = input;

            cout << format("- % Đá (Cũ: {}): ", o.da); 
            getline(cin, input); if(!input.empty()) o.da = input;

            cout << format("- Topping (Cũ: {}): ", o.topping); 
            getline(cin, input); if(!input.empty()) o.topping = input;

            cout << format("- Đồ ăn nhẹ (Cũ: {}): ", o.doAnNhe); 
            getline(cin, input); if(!input.empty()) o.doAnNhe = input;

            cout << format("- Ghi chú (Cũ: {}): ", o.ghiChu); 
            getline(cin, input); if(!input.empty()) o.ghiChu = input;

            break;
        }
    }

    // 3. Ghi đè lại file nếu tìm thấy
    if (found) {
        ofstream fOut("LichSuOrder.txt", ios::out);
        for (const auto &o : danhSach) {
            fOut << format("{}|{}|{}|{}|{}|{}|{}|{}|{}\n", 
                    o.maHD, o.ban, o.doUong, o.size, o.duong, o.da, o.topping, o.doAnNhe, o.ghiChu);
        }
        fOut.close();
        cout << "\n--> [THÀNH CÔNG] Đã cập nhật Order trên hệ thống!\n";
    } else {
        cout << "\n--> [THẤT BẠI] Không tìm thấy Mã hóa đơn này.\n";
    }
}

#endif
