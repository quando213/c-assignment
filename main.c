#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char id[15];
    char name[30];
    char phone[15];
} student_st;

void addStudent(student_st *p, int size);

void printList(student_st *p);

void saveList(student_st *p);

void readList();

void searchStudent(student_st *p);

void printHeader();

int studentCounter = 0;

int main() {
    int choice = 1, size;
    student_st *studentData;

    printf("\n\nVui long nhap so sinh vien toi da: ");
    scanf("%d", &size);
    studentData = (student_st *) malloc(size * sizeof(student_st));

    while (choice != 0) {
        printf("\n\n==================================================");
        printf("\n******************* MENU CHINH *******************");
        printf("\n==================================================");
        printf("\n\nCHON TU MENU SAU: ");
        printf("\n1. Them moi sinh vien");
        printf("\n2. Hien thi danh sach sinh vien");
        printf("\n3. Luu danh sach sinh vien ra file");
        printf("\n4. Doc danh sach sinh vien tu file");
        printf("\n5. Tim kiem sinh vien");
        printf("\n0. Thoat chuong trinh");
        printf("\n\nNhap lua chon cua ban (nhap so 0 - 5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(studentData, size);
                break;
            case 2:
                printList(studentData);
                break;
            case 3:
                saveList(studentData);
                break;
            case 4:
                readList();
                break;
            case 5:
                searchStudent(studentData);
                break;
            case 0:
                printf("\nChuong trinh ket thuc.\n\n");
                break;
            default:
                printf("\nLua chon khong dung. Ban se duoc dua tro lai Menu.");
                break;
        }
    }
    return 0;
}

void addStudent(student_st *p, int size) {
    char flag;
    if (studentCounter >= size)
        printf("\nDanh sach sinh vien da day. Ban se duoc dua tro lai Menu.");
    else
        for (flag = 'Y'; studentCounter < size && (flag == 'Y' || flag == 'y'); studentCounter++) {
            printf("\nVui long nhap ma sinh vien: ");
            scanf("%s", (p + studentCounter)->id);
            while (strlen((p + studentCounter)->id) < 5) {
                printf("\nMa sinh vien co toi thieu 5 ky tu. Vui long nhap lai.");
                scanf("%s", (p + studentCounter)->id);
            }
            printf("\nVui long nhap ten sinh vien: ");
            getchar();
            scanf("%[^\n]s", (p + studentCounter)->name);
            printf("\nVui long nhap so dien thoai: ");
            scanf("%s", (p + studentCounter)->phone);
            if (studentCounter == size - 1) {
                printf("\nDanh sach sinh vien da day. Ban se duoc dua tro lai Menu.");
            } else {
                printf("\nBan co muon nhap tiep thong tin sinh vien khac? (Y/N)");
                getchar();
                scanf("%c", &flag);
            }
        }
}

void printList(student_st *p) {
    int pageTotal, resultPerPage, pageCurrent, j;
    char choice_page, flag;

    if (studentCounter == 0) {
        printf("\nKhong co sinh vien nao trong danh sach. Ban se duoc dua tro lai Menu...");
        return;
    }

    resultPerPage = 10;
    pageTotal = studentCounter / resultPerPage;
    if (studentCounter % resultPerPage)
        pageTotal = studentCounter / resultPerPage + 1;
    pageCurrent = 0;
    do {
        for (j = pageCurrent * resultPerPage; j < (pageCurrent + 1) * resultPerPage && j < studentCounter; j++) {
            if (j == pageCurrent * resultPerPage)
                printHeader();
            printf("\n| %-15s | \t%-30s | %15s |", (p + j)->id, (p + j)->name, (p + j)->phone);
        }
        printf("\n\nDang hien thi ket qua thu %d - %d tren tong so %d ket qua.", pageCurrent * resultPerPage + 1, j,
               studentCounter);
        if (pageTotal > 1)
            do {
                flag = 'n';
                printf("\nNhap L/R de sang trang truoc/trang sau, nhap cac phim khac de tro ve Menu: ");
                getchar();
                scanf("%c", &choice_page);
                if (choice_page == 'L' || choice_page == 'l') {
                    pageCurrent--;
                    if (pageCurrent < 0) {
                        printf("\nKhong ton tai trang. Vui long nhap lai.");
                        pageCurrent++;
                        flag = 'y';
                    }
                } else if (choice_page == 'R' || choice_page == 'r') {
                    pageCurrent++;
                    if (pageCurrent >= pageTotal) {
                        printf("\nKhong ton tai trang. Vui long nhap lai.");
                        pageCurrent--;
                        flag = 'y';
                    }
                } else {
                    printf("\nBan se duoc dua tro lai Menu...");
                    return;
                }
            } while (flag == 'y');
        else return;
    } while (choice_page == 'L' || choice_page == 'l' || choice_page == 'R' || choice_page == 'r');
}

void saveList(student_st *p) {
    if (studentCounter == 0) {
        printf("\nKhong co sinh vien nao trong danh sach. Ban se duoc dua tro lai Menu...");
        return;
    }
    printf("\nThong tin sinh vien da duoc luu trong file 'danhsachsinhvien.txt'. \nBan se duoc dua tro lai Menu.");
    FILE *fp;
    if ((fp = fopen("danhsachsinhvien.txt", "w")) != NULL) {
        fprintf(fp, "DANH SACH SINH VIEN: \n");
        fprintf(fp, "\n| %-15s | \t%-30s | %-15s |", "Ma sinh vien", "Ten", "So dien thoai");
        fprintf(fp, "\n| ---------------------------------------------------------------------- |");
        for (int j = 0; j < studentCounter; j++) {
            fprintf(fp, "\n| %-15s | \t%-30s | %15s |", (p + j)->id, (p + j)->name,
                    (p + j)->phone);
        }
        fclose(fp);
    } else {
        printf("\nKhong the mo file. Ban se duoc dua tro lai Menu.\n");
    }
}

void readList() {
    FILE *fp;
    char str[80];
    if ((fp = fopen("danhsachsinhvien.txt", "r")) != NULL) {
        printf("\nTHONG TIN TRICH XUAT TU FILE 'danhsachsinhvien.txt':\n");
        while (!feof(fp)) {
            fgets(str, 81, fp);
            printf("%s", str);
        }
        fclose(fp);
    } else {
        printf("\nKhong the mo file 'danhsachsinhvien.txt'.\nBan se duoc dua tro lai Menu...\n");
    }
}

void searchStudent(student_st *p) {
    int choice_search = 1, found;
    char searchID[15], searchName[30], searchPhone[15];
    char flag = 'y';
    if (studentCounter == 0) {
        printf("\nKhong co sinh vien nao trong danh sach. Ban se duoc dua tro lai Menu...");
        return;
    }
    while (choice_search != 0) {
        printf("\n\n==================================================");
        printf("\n\nCHON TIEU CHI TIM KIEM: ");
        printf("\n1. Tim kiem theo Ma sinh vien");
        printf("\n2. Tim kiem theo Ten");
        printf("\n3. Tim kiem theo So dien thoai");
        printf("\n4. Tim kiem nang cao");
        printf("\n0. Tro ve Menu chinh");
        printf("\n\nNhap lua chon cua ban (nhap so 0 - 4): ");
        scanf("%d", &choice_search);
        if (choice_search > 0 && choice_search < 5) {
            do {
                printf("\n\n****************************************\n");
                searchID[0] = '\0';
                searchName[0] = '\0';
                searchPhone[0] = '\0';
                if (choice_search == 4)
                    printf("\n(Nhan Enter de bo qua mot tieu chi tim kiem)");
                if (choice_search == 1 || choice_search == 4) {
                    printf("\nVui long nhap ma SV can tim: ");
                    getchar();
                    scanf("%[^\n]s", searchID);
                }
                if (choice_search == 2 || choice_search == 4) {
                    printf("\nVui long nhap ten SV can tim: ");
                    getchar();
                    scanf("%[^\n]s", searchName);
                }
                if (choice_search == 3 || choice_search == 4) {
                    printf("\nVui long nhap so dien thoai cua SV can tim: ");
                    getchar();
                    scanf("%[^\n]s", searchPhone);
                }
                found = 0;
                for (int j = 0; j < studentCounter; j++)
                    if ((strcmp((p + j)->id, searchID) == 0 || strlen(searchID) == 0) &&
                        (strstr((p + j)->name, searchName) != NULL || strlen(searchName) == 0) &&
                        (strcmp((p + j)->phone, searchPhone) == 0 || strlen(searchPhone) == 0)) {
                        found++;
                        if (found == 1)
                            printHeader();
                        printf("\n| %-15s | \t%-30s | %15s |", (p + j)->id, (p + j)->name, (p + j)->phone);
                    }
                if (found == 0)
                    printf("\nKhong tim thay sinh vien nao.");
                else printf("\n\nTim thay %d ket qua.", found);
                printf("\nBan co muon tiep tuc tim kiem? (Y/N): ");
                getchar();
                scanf("%c", &flag);
            } while (flag == 'y' || flag == 'Y');
        } else printf("\nLua chon khong dung. Vui long nhap lai.");
    }
}

void printHeader() {
    printf("\nDANH SACH SINH VIEN: \n");
    printf("\n| %-15s | \t%-30s | %-15s |", "Ma sinh vien", "Ten", "So dien thoai");
    printf("\n| ---------------------------------------------------------------------- |");
}