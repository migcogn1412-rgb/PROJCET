#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void traCuuLichSuDatBan() {
    ifstream file("LichSuDatBan.txt");

    if (!file.is_open()) {
        cout << "Không mở được file LichSuDatBan.txt!\n";
        return;
    }

    string ngayTraCuu;
    cout << "Nhập ngày cần tra cứu (dd/mm/yyyy): ";
    getline(cin, ngayTraCuu);

    string dong;
    bool timThay = false;

    cout << "\n=== KET QUA TRA CUU ===\n";

    while (getline(file, dong)) {
        size_t pos1 = dong.find('|');
        size_t pos2 = dong.rfind('|');

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string ngay = dong.substr(0, pos1);
        int soBan = stoi(dong.substr(pos1 + 1, pos2 - pos1 - 1));
        string tenKhach = dong.substr(pos2 + 1);

        if (ngay == ngayTraCuu) {
            cout << "Ngày: " << ngay
                 << " | Bàn: " << soBan
                 << " | Khách: " << tenKhach << endl;
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Không có.\n";
    }

    file.close();
}
