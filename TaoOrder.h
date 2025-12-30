#ifndef TAOORDER_H
#define TAOORDER_H

#include "Menu.h"
#include <ctime>
#include <string>

// --- HÀM 1: CẬP NHẬT TRẠNG THÁI BÀN (0 -> 1) ---
void capNhatTrangThaiBan(int ban, int trangThai) {
    // Đọc toàn bộ file SoDoBan.txt lên vector
    vector<string> lines;
    ifstream fIn("SoDoBan.txt");
    string line;
    while(getline(fIn, line)) {
        lines.push_back(line);
    }
    fIn.close();

    // Ghi đè lại với trạng thái mới
    ofstream fOut("SoDoBan.txt");
    for(string s : lines) {
        if(s.empty()) continue;
        stringstream ss(s);
        string sBan;
        getline(ss, sBan, '|'); // Lấy số bàn ở đầu dòng
        
        // Nếu dòng này đúng là bàn đang chọn -> Ghi đè
        if(stoi(sBan) == ban) {
            fOut << ban << "|0|" << trangThai << endl; 
        } else {
            fOut << s << endl; // Các bàn khác giữ nguyên
        }
    }
    fOut.close();
}

// --- HÀM 2: HIỂN THỊ SƠ ĐỒ ĐỂ CHỌN ---
void hienThiSoDoBan_Order() {
    cout << "\n--- TRANG THAI BAN ---\n";
    ifstream f("SoDoBan.txt");
    string line;
    while(getline(f, line)) {
        if(line.length() < 3) continue;
        stringstream ss(line);
        string sBan, sDau, sTrangThai;
        getline(ss, sBan, '|');
        getline(ss, sDau, '|'); 
        getline(ss, sTrangThai);
        
        int iBan = stoi(sBan);
        int iTT = stoi(sTrangThai);
        
        // In ra màn hình (VD: [Ban 1: Trong] [Ban 2: CO KHACH]...)
        cout << "[Ban " << iBan << ": " << (iTT == 1 ? "CO KHACH" : "Trong") << "]  ";
        if(iBan % 5 == 0) cout << endl; // Xuống dòng cho đẹp
    }
    cout << endl;
    f.close();
}

// --- HÀM 3: LƯU ORDER VÀO FILE RIÊNG CỦA BÀN ---
// Mục đích: Để lưu lại món khách gọi. Sau này tính tiền sẽ đọc file này.
void luuOrderCuaBan(int soBan, const vector<ChiTietOrder>& dsMon, string ghiChu, long tongTamTinh) {
    // Tạo tên file tương ứng với số bàn. VD: Order_Ban_1.txt
    string tenFile = "Order_Ban_" + to_string(soBan) + ".txt";
    
    ofstream f(tenFile); // Ghi đè (tạo mới phiếu order)
    
    // Ghi dòng đầu tiên là Tổng tiền tạm tính và Ghi chú
    f << "INFO|" << tongTamTinh << "|" << ghiChu << endl;
    
    // Ghi danh sách món ăn
    for(auto m : dsMon) {
        // Format: Loai|Ma|Ten|Size|GiaSize|Topping|GiaTopping|SoLuong|ThanhTien
        f << m.loai << "|" << m.maMon << "|" << m.tenMon << "|" 
          << m.size << "|" << m.giaSize << "|" 
          << m.dsTopping << "|" << m.giaTopping << "|" 
          << m.soLuong << "|" << m.thanhTien << endl;
    }
    f.close();
    
    cout << "\n--> [THANH CONG] Da luu order vao file: " << tenFile << endl;
    cout << "--> Chuyen xuong bep/quay pha che...\n";
}

// --- HÀM CHÍNH: TẠO ORDER (CHỈ GỌI MÓN) ---
void taoOrderMoi() {
    // 1. Load Menu từ các file txt
    vector<MonUong> listUong = loadMenuDoUong();
    vector<MonAn> listAn = loadMenuDoAn();
    vector<MonTopping> listTopping = loadMenuTopping();
    vector<ConfigSize> listSize = loadCauHinhSize();

    // 2. Chọn Bàn
    hienThiSoDoBan_Order();
    int soBan;
    cout << ">> Chon so ban de goi mon (0 thoat): ";
    cin >> soBan;
    if (soBan == 0) return;

    // Biến lưu danh sách món vừa gọi
    vector<ChiTietOrder> dsMonOrder;
    long tongTamTinh = 0;
    string maChon;

    cout << "\n=== BAT DAU GOI MON CHO BAN " << soBan << " ===\n";

    // --- PHẦN A: GỌI ĐỒ UỐNG ---
    while(true) {
        hienThi_MenuUong(listUong); // Hàm bên Menu.h
        cout << "Nhap MA Do Uong (Nhap '0' de chuyen sang Do An): ";
        cin >> maChon;
        if(maChon == "0") break;

        MonUong m = timMonUong(maChon, listUong);
        if(m.ma == "") { cout << "(!) Ma khong hop le!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.ma; ct.tenMon = m.ten; ct.loai = "DO_UONG";
        
        // A1. Chọn Size
        hienThi_Size(listSize);
        cout << "   -> Chon Size: "; cin >> ct.size;
        ConfigSize sz = timSize(ct.size, listSize);
        if(sz.size == "") { ct.giaSize = 0; } else { ct.giaSize = sz.giaThem; }

        // A2. Chọn Topping
        hienThi_Topping(listTopping);
        ct.dsTopping = ""; ct.giaTopping = 0;
        cin.ignore();
        while(true) {
            cout << "   -> Nhap MA Topping (Enter de dung): ";
            string maTP; getline(cin, maTP);
            if(maTP == "") break;
            MonTopping tp = timTopping(maTP, listTopping);
            if(tp.ma != "") {
                ct.dsTopping += tp.ten + ", ";
                ct.giaTopping += tp.gia;
            }
        }

        // A3. Số lượng
        cout << "   -> So luong: "; cin >> ct.soLuong;
        
        // Tính thành tiền món này
        ct.thanhTien = (m.gia + ct.giaSize + ct.giaTopping) * ct.soLuong;
        dsMonOrder.push_back(ct);
        tongTamTinh += ct.thanhTien;
        
        cout << "   => Da them: " << ct.tenMon << " (Tam tinh: " << tongTamTinh << "d)\n";
    }

    // --- PHẦN B: GỌI ĐỒ ĂN ---
    while(true) {
        hienThi_MenuAn(listAn);
        cout << "Nhap MA Do An (Nhap '0' de ket thuc goi mon): ";
        cin >> maChon;
        if(maChon == "0") break;

        MonAn m = timMonAn(maChon, listAn);
        if(m.ma == "") { cout << "(!) Ma khong hop le!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.ma; ct.tenMon = m.ten; ct.loai = "DO_AN";
        ct.size = ""; ct.giaSize = 0; ct.dsTopping = ""; ct.giaTopping = 0;

        cout << "   -> So luong: "; cin >> ct.soLuong;
        
        ct.thanhTien = m.gia * ct.soLuong;
        dsMonOrder.push_back(ct);
        tongTamTinh += ct.thanhTien;
        
        cout << "   => Da them: " << ct.tenMon << " (Tam tinh: " << tongTamTinh << "d)\n";
    }

    // --- PHẦN C: GHI CHÚ & KẾT THÚC ---
    cin.ignore();
    string ghiChu;
    cout << ">> Ghi chu cho bep/pha che: "; 
    getline(cin, ghiChu);

    // Xử lý lưu dữ liệu
    if (!dsMonOrder.empty()) {
        // 1. Cập nhật trạng thái bàn thành Có Khách
        capNhatTrangThaiBan(soBan, 1);
        
        // 2. Lưu món ăn vào file riêng của bàn đó
        luuOrderCuaBan(soBan, dsMonOrder, ghiChu, tongTamTinh);
        
        cout << "\n=== HOAN TAT DAT MON BAN " << soBan << " ===\n";
    } else {
        cout << "\n(!) Chua chon mon nao. Huy Order.\n";
    }
}

#endif
