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
struct CauHinh {
	string size;
	int giaCongThem = 0;
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

//ĐỌC THÔNG TIN CẤU HÌNH TỪ 1 DÒNG
CauHinh docCauHinh(string thongTin) {
	istringstream phanTach(thongTin);
	CauHinh c;
	c.size = ""; c.giaCongThem = 0;
	string boNhoDem;

	getline(phanTach, c.size, '|');
	getline(phanTach, boNhoDem);
	c.giaCongThem = stoi(boNhoDem);

	return c;
}

//ĐỌC THÔNG TIN TỪ FILE CẤU HÌNH
bool docFileTuNguonCauHinh(string tenFile, CauHinh danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	thuTu = 0;
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
	cout << format("\n--- ĐANG SỬA MÓN: {} ---\n", mon.size);
	cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";

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
	string boNhoDem;

	cout << format("{:<25}: ", "Nhập tên size");
	getline(cin, boNhoDem);
	moi.size = boNhoDem;

	cout << format("{:<25}: ", "Nhập giá cộng thêm");
	getline(cin, boNhoDem);
	moi.giaCongThem = stoi(boNhoDem);

	veDuong(60);
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, boNhoDem);

	if (boNhoDem == "Y" || boNhoDem == "y") {
		themSize << moi.size << "|" << moi.giaCongThem << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm size vào hệ thống! *_*" << endl;
	}
	if (boNhoDem == "N" || boNhoDem == "n") {
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

			veDuong(60);
			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			timThay = true;
			if (boNhoDem == "Y" || boNhoDem == "y") {
				xoaDongCauHinh(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa size! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa size! *_*" << endl;
				break;
			}
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

			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			if (boNhoDem == "Y" || boNhoDem == "y") {
				capNhatCauHinh(danhSach[i]);
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
		cout << "\n--> [CẢNH BÁO] Không tìm thấy size!" << endl;
	}

	ghiFileVaoNguonCauHinh(fileCauHinh, danhSach, thuTu);
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN CẤU HÌNH
void cauHinhOrder() {
	while (true) {
		system("cls");
		veTieuDe("[IV] CẤU HÌNH ORDER");
		cout << format("{:<60}", "[1] Thêm size mới") << endl;
		cout << format("{:<60}", "[2] Xóa size") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa thông tin") << endl;
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

int main(){
    cauHinhOrder();
}
