#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>

using std::cout, std::cin, std::endl;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

const int TOI_DA = 100;

// =========================================================
// KHAI BÁO STRUCT
// =========================================================
struct DoUong {
	string ten, loai, ma;
	int giaGoc = 0;
};

struct DoAn {
	string ten, loai, ma;
	int giaGoc = 0;
};

struct Topping {
	string ten, ma;
	int giaGoc = 0;
};

struct CauHinh {
	string size;
	int giaCongThem = 0;
};

// =========================================================
// HÀM TIỆN ÍCH CHUNG
// =========================================================
void veDuong(int doDai) {
	cout << string(doDai, '-') << endl;
}

void veTieuDe(string tieuDe) {
	cout << endl;
	veDuong(60);
	cout << format("|-{:^56}-|", tieuDe) << endl;
	veDuong(60);
	cout << endl;
}

void dungManHinh() {
	cout << endl;
	veDuong(60);
	cout << "--> Nhấn [ENTER] để quay lại...";
	string rac;
	getline(cin, rac);
}

bool xacNhan() {
	string xacNhan;
	veDuong(60);
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, xacNhan);
	if (xacNhan == "Y" || xacNhan == "y") return true;
	if (xacNhan == "N" || xacNhan == "n") return false;
}

// =========================================================
// QUẢN LÍ CƠ SỞ DỮ LIỆU
// =========================================================

// =========================================================
// I. QUẢN LÝ ĐỒ UỐNG
// =========================================================

//ĐỌC THÔNG TIN ĐỒ UỐNG TỪ 1 DÒNG
DoUong docDoUong(string thongTin) {
	istringstream phanTach(thongTin);
	DoUong d;
	string boNhoDem;
	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|'); d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);
	return d;
}

//ĐỌC THÔNG TIN TỪ FILE ĐỒ UỐNG
bool docFileTuNguonDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docDoUong(boNhoDem);
		if (danhSach[thuTu].ma != "") thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE ĐỒ UỐNG
bool ghiFileVaoNguonDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|"
				<< danhSach[i].giaGoc << "|"
				<< danhSach[i].loai << "|"
				<< danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

//XÓA 1 DÒNG THÔNG TIN ĐỒ UỐNG
void xoaDongDoUong(DoUong danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN ĐỒ UỐNG
void capNhatDoUong(DoUong& mon) {
	string boNhoDem;

	cout << format("Mã mới (cũ: {}): ", mon.ma);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ma = boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.ten);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ten = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaGoc);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaGoc = stoi(boNhoDem);

	cout << format("Loại mới (cũ: {}): ", mon.loai);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.loai = boNhoDem;
}

//IN MENU ĐỒ UỐNG
void inMenuDoUong(string tieuDeMenu, DoUong danhSach[], int& thuTu) {
	cout << tieuDeMenu << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
	}
	veDuong(73);
	cout << endl;
}

//NHẬP ĐỒ UỐNG MỚI
void nhapDoUongMoi(DoUong& moi) {
	cout << format("{:<25}: ", "Nhập mã đồ uống");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên đồ uống");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ uống");
	getline(cin, moi.loai);
}

//THÊM THÔNG TIN ĐỒ UỐNG
void themDoUong(string fileDoUong) {
	veTieuDe("THÊM ĐỒ UỐNG MỚI");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	ofstream themDoUong(fileDoUong, ios::app);
	if (!themDoUong.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoUong << "'!" << endl;
		return;
	}
	DoUong moi;
	nhapDoUongMoi(moi);
	if (xacNhan()) {
		themDoUong << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ uống vào hệ thống! *_*\n" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ uống mới! *_*" << endl;
	}
	themDoUong.close();
}

//XÓA ĐỒ UỐNG
void xoaDoUong(string fileDoUong) {
	veTieuDe("XÓA ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);
			if (xacNhan()) {
				xoaDongDoUong(danhSach, thuTu, i);
				cout << "\n--> [THÀNH CÔNG] Đã xóa đồ uống! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ uống! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống: " << maXoa << endl;
	}

	ghiFileVaoNguonDoUong(fileDoUong, danhSach, thuTu);
}

//SỬA ĐỒ UỐNG
void suaDoUong(string fileDoUong) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatDoUong(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống!" << endl;
	}

	ghiFileVaoNguonDoUong(fileDoUong, danhSach, thuTu);
}

//TÌM KIẾM ĐỒ UỐNG
void timKiemDoUong(string fileDoUong) {
	veTieuDe("TÌM KIẾM ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
			timThay = true;
		}
	}
	veDuong(73);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN ĐỒ UỐNG
void quanLiDoUong() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÍ ĐỒ UỐNG");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themDoUong("DoUong.txt");
		else if (luaChon == 2) xoaDoUong("DoUong.txt");
		else if (luaChon == 3) suaDoUong("DoUong.txt");
		else if (luaChon == 4) timKiemDoUong("DoUong.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// II. QUẢN LÝ ĐỒ ĂN
// =========================================================
//ĐỌC THÔNG TIN ĐỒ ĂN TỪ 1 DÒNG
DoAn docDoAn(string thongTin) {
	istringstream phanTach(thongTin);
	DoAn d;
	string boNhoDem;
	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|'); d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);
	return d;
}

//ĐỌC THÔNG TIN TỪ FILE ĐỒ ĂN
bool docFileTuNguonDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docDoAn(boNhoDem);
		if (danhSach[thuTu].ma != "") thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE ĐỒ ĂN
bool ghiFileVaoNguonDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|"
				<< danhSach[i].giaGoc << "|"
				<< danhSach[i].loai << "|"
				<< danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

//XÓA 1 DÒNG ĐỒ ĂN
void xoaDongDoAn(DoAn danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN ĐỒ ĂN
void capNhatDoAn(DoAn& mon) {
	string boNhoDem;

	cout << format("Mã mới (cũ: {}): ", mon.ma);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ma = boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.ten);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ten = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaGoc);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaGoc = stoi(boNhoDem);

	cout << format("Loại mới (cũ: {}): ", mon.loai);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.loai = boNhoDem;
}

//IN MENU ĐỒ ĂN
void inMenuDoAn(string tieuDeMenu, DoAn danhSach[], int& thuTu) {
	cout << tieuDeMenu << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ ĂN", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
	}
	veDuong(73);
	cout << endl;
}

//NHẬP ĐỒ ĂN MỚI
void nhapDoAnMoi(DoAn& moi) {
	cout << format("{:<25}: ", "Nhập mã đồ ăn");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ ăn");
	getline(cin, moi.loai);
}

//THÊM ĐỒ ĂN
void themDoAn(string fileDoAn) {
	veTieuDe("THÊM ĐỒ ĂN MỚI");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) {
		inMenuDoAn("* MENU ĐỒ ĂN HIỆN TẠI *", danhSach, thuTu);
	}

	ofstream themDoAn(fileDoAn, ios::app);
	if (!themDoAn.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoAn << "'!" << endl;
		return;
	}
	DoAn moi;
	nhapDoAnMoi(moi);
	if (xacNhan()) {
		themDoAn << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ ăn vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ ăn mới! *_*" << endl;
	}
	themDoAn.close();
}

//XÓA ĐỒ ĂN
void xoaDoAn(string fileDoAn) {
	veTieuDe("XÓA ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) {
		inMenuDoAn("* MENU ĐỒ ĂN HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ ăn muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);
			if (xacNhan()) {
				xoaDongDoAn(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa đồ ăn! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ ăn! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn: " << maXoa << endl;
	}

	ghiFileVaoNguonDoAn(fileDoAn, danhSach, thuTu);
}

//SỬA ĐỒ ĂN
void suaDoAn(string fileDoAn) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) {
		inMenuDoAn("* MENU ĐỒ ĂN HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ ăn muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatDoAn(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn!" << endl;
	}

	ghiFileVaoNguonDoAn(fileDoAn, danhSach, thuTu);
}

//TÌM KIẾM ĐỒ ĂN
void timKiemDoAn(string fileDoAn) {
	veTieuDe("TÌM KIẾM ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ ĂN", "GIÁ", "LOẠI") << endl;
	veDuong(73);
	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
			timThay = true;
		}
	}
	veDuong(73);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN ĐỒ ĂN
void quanLiDoAn() {
	while (true) {
		system("cls");
		veTieuDe("[II] QUẢN LÍ ĐỒ ĂN");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themDoAn("DoAn.txt");
		else if (luaChon == 2) xoaDoAn("DoAn.txt");
		else if (luaChon == 3) suaDoAn("DoAn.txt");
		else if (luaChon == 4) timKiemDoAn("DoAn.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// III. QUẢN LÝ TOPPING
// =========================================================
//ĐỌC THÔNG TIN TOPPING TỪ 1 DÒNG
Topping docTopping(string thongTin) {
	istringstream phanTach(thongTin);
	Topping t;
	string boNhoDem;
	getline(phanTach, t.ten, '|');
	getline(phanTach, boNhoDem, '|'); t.giaGoc = stoi(boNhoDem);
	getline(phanTach, t.ma);
	return t;
}

//ĐỌC THÔNG TIN TỪ FILE TOPPING
bool docFileTuNguonTopping(string tenFile, Topping danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docTopping(boNhoDem);
		if (danhSach[thuTu].ma != "") thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE TOPPING
bool ghiFileVaoNguonTopping(string tenFile, Topping danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|"
				<< danhSach[i].giaGoc << "|"
				<< danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

//XÓA 1 DÒNG TOPPING
void xoaDongTopping(Topping danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN TOPPING
void capNhatTopping(Topping& mon) {
	string boNhoDem;

	cout << format("Mã mới (cũ: {}): ", mon.ma);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ma = boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.ten);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ten = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaGoc);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaGoc = stoi(boNhoDem);
}

//IN MENU TOPPING
void inMenuTopping(string tieuDeMenu, Topping danhSach[], int& thuTu) {
	cout << tieuDeMenu << endl;
	veDuong(60);
	cout << format("| {:<10} | {:<30} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ") << endl;
	veDuong(60);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc) << endl;
	}
	veDuong(60);
	cout << endl;
}

//NHẬP TOPPING MỚI
void nhapToppingMoi(Topping& moi) {
	cout << format("{:<25}: ", "Nhập mã topping");
	getline(cin, moi.ma);

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, moi.ten);

	cout << format("{:<25}: ", "Nhập giá gốc");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaGoc = stoi(boNhoDem);
}

//THÊM TOPPING
void themTopping(string fileTopping) {
	veTieuDe("THÊM TOPPING MỚI");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonTopping(fileTopping, danhSach, thuTu)) {
		inMenuTopping("* MENU TOPPING HIỆN TẠI *", danhSach, thuTu);
	}

	ofstream themTopping(fileTopping, ios::app);
	if (!themTopping.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileTopping << "'!" << endl;
		return;
	}
	Topping moi;
	nhapToppingMoi(moi);
	if (xacNhan()) {
		themTopping << moi.ten << "|" << moi.giaGoc << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm topping vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm topping mới! *_*" << endl;
	}
	themTopping.close();
}

//XÓA TOPPING
void xoaTopping(string fileTopping) {
	veTieuDe("XÓA TOPPING");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonTopping(fileTopping, danhSach, thuTu)) {
		inMenuTopping("* MENU TOPPING HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ topping muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);
			if (xacNhan()) {
				xoaDongTopping(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa topping! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa topping! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã topping: " << maXoa << endl;
	}

	ghiFileVaoNguonTopping(fileTopping, danhSach, thuTu);
}

//SỬA TOPPING
void suaTopping(string fileTopping) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonTopping(fileTopping, danhSach, thuTu)) {
		inMenuTopping("* MENU TOPPING HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* topping muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;
			cout << format("\nĐang sửa món: {}\n", danhSach[i].ten);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatTopping(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
				break;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
				break;
			}
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã topping!" << endl;
	}

	ghiFileVaoNguonTopping(fileTopping, danhSach, thuTu);
}

//TÌM KIẾM TOPPING
void timKiemTopping(string fileTopping) {
	veTieuDe("TÌM KIẾM TOPPING");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonTopping(fileTopping, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(75);
	cout << format("| {:<10} | {:<30} | {:<10} |", "MÃ", "TÊN TOPPING", "GIÁ") << endl;
	veDuong(75);
	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc) << endl;
			timThay = true;
		}
	}
	veDuong(75);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN TOPPING
void quanLiTopping() {
	while (true) {
		system("cls");
		veTieuDe("[III] QUẢN LÍ TOPPING");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themTopping("Topping.txt");
		else if (luaChon == 2) xoaTopping("Topping.txt");
		else if (luaChon == 3) suaTopping("Topping.txt");
		else if (luaChon == 4) timKiemTopping("Topping.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// IV. CẤU HÌNH ORDER
// =========================================================
//ĐỌC THÔNG TIN CẤU HÌNH TỪ 1 DÒNG
CauHinh docCauHinh(string thongTin) {
	istringstream phanTach(thongTin);
	CauHinh c;
	string boNhoDem;
	getline(phanTach, c.size, '|');
	getline(phanTach, boNhoDem); c.giaCongThem = stoi(boNhoDem);
	return c;
}

//ĐỌC THÔNG TIN TỪ FILE CẤU HÌNH
bool docFileTuNguonCauHinh(string tenFile, CauHinh danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docCauHinh(boNhoDem);
		if (danhSach[thuTu].giaCongThem != 0) thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE CẤU HÌNH
bool ghiFileVaoNguonCauHinh(string tenFile, CauHinh danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].size << "|"
				<< danhSach[i].giaCongThem << endl;
	}
	ghiFile.close();
	return true;
}

//XÓA 1 DÒNG CẤU HÌNH
void xoaDongCauHinh(CauHinh danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN CẤU HÌNH
void capNhatCauHinh(CauHinh& mon) {
	string boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.size);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.size = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaCongThem);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaCongThem = stoi(boNhoDem);
}

//IN CẤU HÌNH
void inCauHinh(string tieuDeCauHinh, CauHinh danhSach[], int& thuTu) {
	cout << tieuDeCauHinh << endl;
	veDuong(37);
	cout << format("| {:<15} | {:<15} |", "SIZE", "GIÁ CỘNG THÊM") << endl;
	veDuong(37);
	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<15} | {:<15} |", danhSach[i].size, danhSach[i].giaCongThem) << endl;
	}
	veDuong(37);
	cout << endl;
}

//NHẬP CẤU HÌNH MỚI
void nhapCauHinhMoi(CauHinh& moi) {
	cout << format("{:<25}: ", "Nhập tên size");
	getline(cin, moi.size);

	cout << format("{:<25}: ", "Nhập giá cộng thêm");
	string boNhoDem;
	getline(cin, boNhoDem); moi.giaCongThem = stoi(boNhoDem);
}

//THÊM CẤU HÌNH
void themSize(string fileCauHinh) {
	veTieuDe("THÊM SIZE MỚI");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonCauHinh(fileCauHinh, danhSach, thuTu)) {
		inCauHinh("* CẤU HÌNH HIỆN TẠI *", danhSach, thuTu);
	}

	ofstream themSize(fileCauHinh, ios::app);
	if (!themSize.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileCauHinh << "'!" << endl;
		return;
	}
	CauHinh moi;
	nhapCauHinhMoi(moi);
	if (xacNhan()) {
		themSize << moi.size << "|" << moi.giaCongThem << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm size vào hệ thống! *_*" << endl;
	}
	else {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm size mới! *_*" << endl;
	}
	themSize.close();
}

//XÓA CẤU HÌNH
void xoaSize(string fileCauHinh) {
	veTieuDe("XÓA SIZE");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonCauHinh(fileCauHinh, danhSach, thuTu)) {
		inCauHinh("* CẤU HÌNH HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập size muốn xóa: ";
	string sizeXoa;
	getline(cin, sizeXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].size == sizeXoa) {
			cout << format("\nĐang xóa size: [{}]\n", danhSach[i].size);
			timThay = true;
			if (xacNhan()) {
				xoaDongCauHinh(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa size! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa size! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy size: " << sizeXoa << endl;
	}

	ghiFileVaoNguonCauHinh(fileCauHinh, danhSach, thuTu);
}

//SỬA CẤU HÌNH
void suaCauHinh(string fileCauHinh) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	CauHinh danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonCauHinh(fileCauHinh, danhSach, thuTu)) {
		inCauHinh("* CẤU HÌNH HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập size muốn sửa: ";
	string sizeSua;
	getline(cin, sizeSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].size == sizeSua) {
			timThay = true;
			cout << format("\nĐang sửa size: {}\n", danhSach[i].size);
			cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";
			if (xacNhan()) {
				capNhatCauHinh(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
			}
			else {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
			}
			return;
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy size!" << endl;
	}

	ghiFileVaoNguonCauHinh(fileCauHinh, danhSach, thuTu);
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN CẤU HÌNH
void cauHinhOrder() {
	while (true) {
		system("cls");
		veTieuDe("[IV] CẤU HÌNH ORDER");
		cout << format("{:<60}", "[1] Thêm") << endl;
		cout << format("{:<60}", "[2] Xóa") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themSize("CauHinhOrder.txt");
		else if (luaChon == 2) xoaSize("CauHinhOrder.txt");
		else if (luaChon == 3) suaCauHinh("CauHinhOrder.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// QUẢN LÍ DỮ LIỆU PHÁT SINH
// =========================================================

// =========================================================
// I. QUẢN LÍ BÁN HÀNG VÀ ORDER
// =========================================================

// =========================================================
// II. QUẢN LÍ KHO
// =========================================================

// =========================================================
// TRA CỨU DỮ LIỆU GIAO DỊCH
// =========================================================

// =========================================================
// CÁC HÀM CHỨC NĂNG CHÍNH
// =========================================================
void quanLiCoSoDuLieu() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÍ CƠ SỞ DỮ LIỆU");
		cout << format("{:<60}", "[1] Quản lí đồ uống") << endl;
		cout << format("{:<60}", "[2] Quản lí đồ ăn") << endl;
		cout << format("{:<60}", "[3] Quản lí topping") << endl;
		cout << format("{:<60}", "[4] Cấu hình order") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) quanLiDoUong();
		else if (luaChon == 2) quanLiDoAn();
		else if (luaChon == 3) quanLiTopping();
		else if (luaChon == 4) cauHinhOrder();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

void quanLiDuLieuPhatSinh() {
	while (true) {
		system("cls");
		veTieuDe("[II] QUẢN LÍ DỮ LIỆU PHÁT SINH");
		cout << format("{:<60}", "[1] Quản lí bán hàng và order") << endl;
		cout << format("{:<60}", "[2] Quản lí kho") << endl;
		cout << format("{:<60}", "[3] Tra cứu dữ liệu giao dịch") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1);
		else if (luaChon == 2);
		else if (luaChon == 3);
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

void baoCaoThongKe() {
	while (true) {
		system("cls");
		veTieuDe("[III] BÁO CÁO THỐNG KÊ");
		cout << format("{:<60}", "[1] Thống kê bán hàng") << endl;
		cout << format("{:<60}", "[2] Thống kê đặc biệt") << endl;
		cout << format("{:<60}", "[0] Quay lại màn hình chính") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1);
		else if (luaChon == 2);
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

// =========================================================
// MAIN
// =========================================================
int main() {
	while (true) {
		system("cls");
		veTieuDe("CỬA HÀNG CÀ PHÊ");
		cout << format("{:<60}", "[1] QUẢN LÍ CƠ SỞ DỮ LIỆU") << endl;
		cout << format("{:<60}", "[2] QUẢN LÍ DỮ LIỆU PHÁT SINH") << endl;
		cout << format("{:<60}", "[3] BÁO CÁO THỐNG KÊ") << endl;
		cout << format("{:<60}", "[0] THOÁT CỬA HÀNG") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) quanLiCoSoDuLieu();
		else if (luaChon == 2) quanLiDuLieuPhatSinh();
		else if (luaChon == 3) baoCaoThongKe();
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}

	return 0;
}
