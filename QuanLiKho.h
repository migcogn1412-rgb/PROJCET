#ifndef QUANLYKHO_H
#define QUANLYKHO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using namespace std;

// --- CẤU TRÚC DỮ LIỆU ---
struct HangHoa {
    string ten;
    int soLuong;
    int gia;
};

// --- CÁC HÀM TIỆN ÍCH ---

// Hàm tách chuỗi để đọc file dữ liệu
vector<string> split(string s) {
    vector<string> res;
    stringstream ss(s);
    string item;
    while (getline(ss, item, '|')) res.push_back(item);
    return res;
}

// 1. QUẢN LÝ NHÀ CUNG CẤP (THÊM THỦ CÔNG)
void themNhaCungCap() {
    string tenNCC;
    cout << "\n[+] NHẬP TÊN NHÀ CUNG CẤP MỚI: ";
    getline(cin, tenNCC);
    
    ofstream f("NhaCungCap.txt", ios::app);
    if (f.is_open()) {
        f << tenNCC << endl;
        f.close();
        cout << "--> Đã lưu Nhà cung cấp thành công.\n";
    }
}

// 2. TỰ ĐỘNG CẬP NHẬT SỐ LƯỢNG VÀO FILE KHO GỐC
void capNhatKhoTuDong(vector<HangHoa> dsMoi) {
    ifstream fIn("NguyenLieuTrongKho.txt");
    vector<string> toanBoKho;
    string line;
    
    // Đọc kho hiện tại
    while (getline(fIn, line)) {
        if (!line.empty()) toanBoKho.push_back(line);
    }
    fIn.close();

    // Duyệt danh sách hàng vừa nhập từ hóa đơn để cộng dồn
    for (const auto& monMoi : dsMoi) {
        bool timThay = false;
        for (auto& dongKho : toanBoKho) {
            vector<string> p = split(dongKho);
            // Định dạng file: Tên|Loại|Giá|SốLượng
            if (p.size() >= 4 && p[0] == monMoi.ten) {
                int slCu = stoi(p[3]);
                int slMoi = slCu + monMoi.soLuong; // Cộng dồn số lượng
                dongKho = format("{}|{}|{}|{}", p[0], p[1], p[2], slMoi);
                timThay = true;
                break;
            }
        }
        // Nếu món chưa có trong kho gốc, thêm mới vào cuối
        if (!timThay) {
            toanBoKho.push_back(format("{}|ChuaPhanLoai|{}|{}", monMoi.ten, monMoi.gia, monMoi.soLuong));
        }
    }

    // Ghi đè lại file kho sau khi cập nhật
    ofstream fOut("NguyenLieuTrongKho.txt", ios::out);
    for (const auto& row : toanBoKho) {
        fOut << row << endl;
    }
    fOut.close();
}

// 3. NHẬP HÓA ĐƠN NHIỀU MÓN (HỎI SỐ LƯỢNG TRƯỚC)
void taoHoaDonNhap() {
    int n;
    cout << "\n[?] Hôm nay bạn nhập bao nhiêu loại sản phẩm: ";
    string sN; getline(cin, sN);
    try { n = stoi(sN); } catch (...) { n = 0; }

    if (n <= 0) return;

    vector<HangHoa> danhSachHang;
    long long tongTienHD = 0;

    for (int i = 1; i <= n; i++) {
        HangHoa h;
        cout << format("--- Sản phẩm {}/{} ---\n", i, n);
        cout << " + Tên: "; getline(cin, h.ten);
        cout << " + SL nhập: "; string sL; getline(cin, sL); h.soLuong = stoi(sL);
        cout << " + Giá nhập: "; string sG; getline(cin, sG); h.gia = stoi(sG);
        
        danhSachHang.push_back(h);
        tongTienHD += (long long)h.soLuong * h.gia; // Tính tổng tiền đơn nhập
    }

    string maDon, ngay;
    cout << "\n[*] Nhập Mã đơn nhập: "; getline(cin, maDon);
    cout << "[*] Nhập Ngày nhập: "; getline(cin, ngay);

    // Ghi log lịch sử hóa đơn
    ofstream fLog("LichSuHoaDon.txt", ios::app);
    fLog << format("MA: {} | NGAY: {} | TONG: {} VND\n", maDon, ngay, tongTienHD);
    for (const auto& it : danhSachHang) {
        fLog << format("   + {} (SL: {})\n", it.ten, it.soLuong);
    }
    fLog.close();

    // Cập nhật số lượng vào kho gốc
    capNhatKhoTuDong(danhSachHang);
    cout << "\n--> Đã cập nhật hóa đơn vào hệ thống!\n";
}

// 4. TRA CỨU LỊCH SỬ NHẬP HÀNG (THEO MÃ HOẶC NGÀY)
void traCuuLichSuNhap() {
    string tuKhoa;
    cout << "\nNhập Mã đơn hoặc Ngày cần tìm: ";
    getline(cin, tuKhoa);

    ifstream f("LichSuHoaDon.txt");
    string line;
    bool found = false;
    cout << "\n--- KẾT QUẢ TRA CỨU ---" << endl;
    while (getline(f, line)) {
        if (line.find(tuKhoa) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }
    if (!found) cout << "Không tìm thấy dữ liệu trùng khớp.\n";
    f.close();
}

#endif
