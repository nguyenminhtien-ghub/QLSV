#include <conio.h>
#include <iostream>
#include <string>
#include <array>

struct Date
{
    int year;
    int month;
    int day;
};

struct Student
{
    std::string class_id;
    std::string student_id;
    std::string name;
    Date dob;
    float gpa;

};

void add_recoid();
void list_students();
void sort_students();
void search_students();
void statistics_studnet();


int main()
{
    char user_choice;

    while (true)
    {

        std::system("cls");
        std::cout << "-|----------------------------|-";
        std::cout << "\n |     QUAN LY SINH VIEN      |";
        std::cout << "\n-|----------------------------|-";

        std::cout << "\n";
        std::cout << "\n1. Them moi ho so";
        std::cout << "\n2. In danh sach";
        std::cout << "\n3. Sap xep";
        std::cout << "\n4. Tim kiem";
        std::cout << "\n5. Thong ke";
        std::cout << "\n6. Thoat";

        std::cout << "\n(Chon chuc nang 1 - 6)";
        std::cout << "\n> ";
        std::cin >> user_choice;

;       switch (user_choice)
        {
        case '6':
            return 0;
        case '1':
            add_recoid();
            break;
        case '2':
            list_students();
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        default:
            std::cout << "\nNhap so tu 1 den 6\n";
            break;
        }

    }
}

void add_recoid()
{
    Student s;
    char user_confirm = 'y';

    std::cin.ignore();
    std::cout << "\n** MENU 1 | Nhap thong tin sinh vien **";
    std::cout << "\n";
    std::cout << "\n  ma lop: ";
    std::cout << "AAA17\n";
    //std::getline(std::cin, s.class_id);
    s.class_id = "AAA17";
    std::cout << "  ma sinh vien: ";
    std::cout << "12345678\n";
    //std::getline(std::cin, s.student_id);
    s.student_id = "12345678";
    std::cout << "  ho va ten: ";
    //std::getline(std::cin, s.name);
    std::cout << "Nguyen Minh Hoang\n";
    s.name = "Nguyen Minh Hoang";
    std::cout << "  ngay sinh: ";
    //std::cin >> s.dob.day >> s.dob.month >> s.dob.year;
    std::cout << "2 12 2000\n";
    s.dob.day = 2;
    s.dob.month = 12;
    s.dob.year = 2000;
    std::cout << "  diem trung binh: ";
    std::cout << "8.5\n";
    //std::cin >> s.gpa;
    s.gpa = 8.5f;
    
    std::cout << "\n\nXac nhap thong tin sinh vien da nhap (y / n): ";
    user_confirm = _getch();

    if (user_confirm == 'y')
    {
       
    }
    else if (user_confirm == 'n')
    {
        return;
    }
    //std::cout << s.class_id << " " << s.student_id << " " << s.name << " " << s.dob.day << " " << s.gpa << "\n";
    

}

void list_students()
{
    char return_to_main{};
    std::cout << "\n-***   ***   ***   ***   ***    MENU 2 | Danh sach sinh vien    ***   ***   ***   ***   ***-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    std::cout << "\n-| STT |  ma lop  | ma sinh vien |        ho va ten        | ngay sinh  | diem trung bing |-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    std::cout << "\n | 001 |    AAA17 |    123456789 | Nguyen Minh Hoang       | 02/12/2000 |             8.5 | ";
    std::cout << "\n | 002 |    ABB17 |    170000101 | Trinh Van Anh           | 24/10/2000 |             7.8 | ";
    std::cout << "\n | 003 |    ACC17 |    170000201 | Hoang Xuan Dat          | 15/06/2000 |             7.4 | ";
    std::cout << "\n | 003 |    ABB17 |    170000102 | Tran Van Minh           | 02/10/2000 |             7.4 | ";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";

    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    return_to_main = _getch();

}


void sort_students();
void search_students();
void statistics_studnet();

