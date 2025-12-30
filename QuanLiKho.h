#ifndef QUANLYKHO_H
#define QUANLYKHO_H

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using namespace std;

const int MAX_KHO = 500;
const int MAX_NHAP = 50;

struct HangHoa {
    string ten;
    int soLuong = 0;
    int gia = 0;
};

struct NguyenLieu {
    string ten, loai;
    int gia = 0;
    int soLuong = 0;
};

// --- CÁC HÀM HỖ TRỢ ---

void capNhatKhoTuDong(HangHoa dsMoi[], int n) {
    NguyenLieu kho[MAX_KHO];
    int soLuongTrongKho = 0;

    ifstream fIn("NguyenLieuTrongKho.txt");
    string line;
    while (getline(fIn, line) && soLuongTrongKho < MAX_KHO) {
        if (line.empty()) continue;
        istringstream ss(line);
        getline(ss, kho[soLuongTrongKho].ten, '|');
        getline(ss, kho[soLuongTrongKho].loai, '|');
        string sGia, sSL;
        if (getline(ss, sGia, '|') && getline(ss, sSL)) {
            try {
                kho[soLuongTrongKho].gia = stoi(sGia);
                kho[soLuongTrongKho].soLuong = stoi(sSL);
                soLuongTrongKho++;
            } catch (...) { continue; }
        }
    }
    fIn.close();

    for (int i = 0; i < n; i++) {
        bool timThay = false;
        for (int j = 0; j < soLuongTrongKho; j++) {
            if (kho[j].ten == dsMoi[i].ten) {
                kho[j].soLuong += dsMoi[i].soLuong;
                kho[j].gia = dsMoi[i].gia;
                timThay = true;
                break;
            }
        }
        if (!timThay && soLuongTrongKho < MAX_KHO) {
            kho[soLuongTrongKho].ten = dsMoi[i].ten;
            kho[soLuongTrongKho].loai = "ChuaPhanLoai";
            kho[soLuongTrongKho].gia = dsMoi[i].gia;
            kho[soLuongTrongKho].soLuong = dsMoi[i].soLuong;
            soLuongTrongKho++;
        }
    }

    ofstream fOut("NguyenLieuTrongKho.txt");
    for (int i = 0; i < soLuongTrongKho; i++) {
        fOut << format("{}|{}|{}|{}\n", kho[i].ten, kho[i].loai, kho[i].gia, kho[i].soLuong);
    }
    fOut.close();
}
void themNhaCungCap() {
    string tenNCC;
    cout << "\n[+] NHẬP TÊN NHÀ CUNG CẤP MỚI: ";
    getline(cin, tenNCC);
    
    ofstream f("NhaCungCap.txt", ios::app);
    if (f.is_open()) {
        f << tenNCC << endl;
        f.close();
        cout << "--> [THÀNH CÔNG] Đã lưu Nhà cung cấp.\n";
    }
}

void taoHoaDonNhap() {
    int n;
    cout << "\n[?] Hôm nay bạn nhập bao nhiêu loại sản phẩm: ";
    string sN; getline(cin, sN);
    try { n = stoi(sN); } catch (...) { n = 0; }

    if (n <= 0 || n > MAX_NHAP) {
        cout << "--> Số lượng không hợp lệ!\n";
        return;
    }

    HangHoa danhSachHang[MAX_NHAP];
    long long tongTienHD = 0;

    for (int i = 0; i < n; i++) {
        cout << format("--- Sản phẩm {}/{} ---\n", i + 1, n);
        cout << " + Tên: ";      getline(cin, danhSachHang[i].ten);
        cout << " + SL nhập: ";  string sL; getline(cin, sL); danhSachHang[i].soLuong = stoi(sL);
        cout << " + Giá nhập: "; string sG; getline(cin, sG); danhSachHang[i].gia = stoi(sG);
        tongTienHD += (long long)danhSachHang[i].soLuong * danhSachHang[i].gia;
    }

    string maDon, ngay;
    cout << "\n[*] Nhập Mã đơn nhập: "; getline(cin, maDon);
    cout << "[*] Nhập Ngày nhập: ";    getline(cin, ngay);

    ofstream fLog("LichSuHoaDon.txt", ios::app);
    if (fLog.is_open()) {
        fLog << format("Ma hoa don: {} | NGAY: {} | TONG: {} VND\n", maDon, ngay, tongTienHD);
        for (int i = 0; i < n; i++) {
            fLog << format("   + {} (SL: {})\n", danhSachHang[i].ten, danhSachHang[i].soLuong);
        }
        fLog.close();
    }

    capNhatKhoTuDong(danhSachHang, n);
    cout << "\n--> [THÀNH CÔNG] Đã cập nhật kho và lưu lịch sử!\n";
}

void traCuuLichSuNhap() {
    string tuKhoa;
    cout << "\nNhập Mã đơn cần tìm: ";
    getline(cin, tuKhoa);

    ifstream f("LichSuHoaDon.txt");
    if (!f.is_open()) {
        cout << "Lỗi: Không thể mở file lịch sử!\n";
        return;
    }

    string line;
    bool found = false;
    bool dangInHoaDon = false; 

    cout << "\n--- KẾT QUẢ TRA CỨU ---" << endl;
    while (getline(f, line)) {
        if (line.find("Ma hoa don:") == 0) { 
            if (line.find(tuKhoa) != string::npos) {
                cout << "------------------------------------------\n";
                cout << line << endl;
                dangInHoaDon = true;
                found = true;
            } else {
                dangInHoaDon = false;
            }
        } 
        else if (dangInHoaDon && !line.empty()) {
            cout << line << endl;
        }
    }

    if (!found) cout << "Không tìm thấy dữ liệu trùng khớp.\n";
    cout << "------------------------------------------\n";
    f.close();
}

#endif
