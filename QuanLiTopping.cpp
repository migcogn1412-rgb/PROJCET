#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>

using std::cout, std::cin, std::endl;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

const int TOI_DA = 100;

//KHAI BÁO STRUCT
struct Topping {
	string ten, ma;
	int giaGoc = 0;
};

//HÀM TIỆN ÍCH
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

//ĐỌC THÔNG TIN TOPPING TỪ 1 DÒNG
Topping docTopping(string thongTin) {
	istringstream phanTach(thongTin);
	Topping t;
	t.ten = ""; t.giaGoc = 0; t.ma = "";
	string boNhoDem;

	getline(phanTach, t.ten, '|');
	getline(phanTach, boNhoDem, '|');
	t.giaGoc = stoi(boNhoDem);
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
	thuTu = 0;
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
	cout << format("\n--- ĐANG SỬA MÓN: {} ---\n", mon.ten);
	cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";

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

//THÊM TOPPING
void themTopping(string fileTopping) {
	veTieuDe("THÊM TOPPING MỚI");

	ofstream themTopping(fileTopping, ios::app);
	if (!themTopping.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileTopping << "'!" << endl;
		return;
	}

	Topping moi;
	string boNhoDem;

	cout << format("{:<25}: ", "Nhập mã topping");
	getline(cin, boNhoDem);
	moi.ma = boNhoDem;

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, boNhoDem);
	moi.ten = boNhoDem;

	cout << format("{:<25}: ", "Nhập giá gốc");
	getline(cin, boNhoDem);
	moi.giaGoc = stoi(boNhoDem);

	veDuong(60);
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, boNhoDem);

	if (boNhoDem == "Y" || boNhoDem == "y") {
		themTopping << moi.ten << "|" << moi.giaGoc << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm topping vào hệ thống! *_*" << endl;
	}
	if (boNhoDem == "N" || boNhoDem == "n") {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm topping mới! *_*" << endl;
	}

	themTopping.close();
}

//XÓA TOPPING
void xoaTopping(string fileTopping) {
	veTieuDe("XÓA TOPPING");

	Topping danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonTopping(fileTopping, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* đồ topping muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);

			veDuong(60);
			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			if (boNhoDem == "Y" || boNhoDem == "y") {
				xoaDongTopping(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa topping! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa topping! *_*" << endl;
				break;
			}
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
	if (!docFileTuNguonTopping(fileTopping, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* topping muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;

			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			if (boNhoDem == "Y" || boNhoDem == "y") {
				capNhatTopping(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
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
		cout << format("{:<60}", "[1] Thêm topping mới") << endl;
		cout << format("{:<60}", "[2] Xóa topping") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa thông tin") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm topping") << endl;
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

int main(){
    quanLiTopping();
}
