#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib> 
using namespace std;

struct NhanVien {
    char ID[10];
    char HoTen[55];
    float luong;
};
struct Node {
    NhanVien nv;
    Node* pNext;
};
struct List {
    Node* pHead, * pTail;
};
List* newList() {
    List* l = new List;
    if (l != NULL) {
        l->pHead = nullptr;
        l->pTail = nullptr;
    }
    return l;
}
bool AddNode(List* l, Node* n) {
    if (n == nullptr) return false;  // Kiểm tra node có null không
    n->pNext = nullptr;  // Khởi tạo pNext
    if (l->pHead == nullptr) {
        l->pHead = l->pTail = n;
    }
    else {
        l->pTail->pNext = n;
        l->pTail = n;
    }
    return true;
}
void FreeList(List* l) {
    //Xóa list
    Node* temp;
    while (l->pHead != nullptr) {
        temp = l->pHead;
        l->pHead = l->pHead->pNext;
        delete temp;
    }
    delete l;
}
int main() {
    ofstream outFile("output.txt", ios::out);  // Mở file để ghi
    ifstream inFile("data.txt");  // Mở file để đọc

    if (!inFile.is_open() || !outFile.is_open()) {
        cout << "Khong the mo file!" << endl;
        return 1;  // Thoát chương trình nếu file mở thất bại
    }

    char s1[10];   // Lưu tạm ID
    char s2[55];   // Lưu tạm tên
    char s3[10];   // Lưu tạm lương
    char temp[100];
    List* l = newList();

    while (inFile.getline(temp, 100)) {
        char* token = strtok(temp, "-");
        if (token != nullptr) strcpy(s1, token);

        token = strtok(nullptr, "-");
        if (token != nullptr) strcpy(s2, token);

        token = strtok(nullptr, "-");
        if (token != nullptr) strcpy(s3, token);

        Node* n = new Node();
        if (n == nullptr) {
            cout << "Loi cap phat bo nho!" << endl;
            return 1;  // Thoát nếu không cấp phát được
        }
        strcpy(n->nv.ID, s1);
        strcpy(n->nv.HoTen, s2);
        n->nv.luong = atof(s3);

        AddNode(l, n);
    }

    int maxlen = 0;        // Khởi tạo độ dài tên lớn nhất
    float maxLuong = 0.0f; // Khởi tạo lương lớn nhất

    // Tìm độ dài tên lớn nhất và lương lớn nhất
    for (Node* temp = l->pHead; temp != nullptr; temp = temp->pNext) {
        int len = strlen(temp->nv.HoTen);
        if (len > maxlen) maxlen = len;
        if (temp->nv.luong > maxLuong) maxLuong = temp->nv.luong;
    }

    // Ghi kết quả thỏa điều kiện vào file
    for (Node* temp = l->pHead; temp != nullptr; temp = temp->pNext) {
        if (strlen(temp->nv.HoTen) == maxlen && temp->nv.luong == maxLuong) {
            outFile << temp->nv.HoTen << "-" << temp->nv.ID << "-" << temp->nv.luong << endl;
        }
    }

    cout << "Ghi du lieu thanh cong!" << endl;

    // Đóng file và giải phóng bộ nhớ
    inFile.close();
    outFile.close();
    FreeList(l);

    return 0;
}
