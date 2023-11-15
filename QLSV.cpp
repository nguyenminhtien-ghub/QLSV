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


        std::cout << "-|---------------------------|-";
        std::cout << "\n |    QUAN LY SINH VIEN      |";
        std::cout << "\n-|---------------------------|-";

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

    std::cin.ignore();
    std::cout << "\n** Nhap thong tin sinh vien **";
    std::cout << "\n";
    std::cout << "\n  ma lop: ";
    std::getline(std::cin, s.class_id);
    std::cout << "  ma sinh vien: ";
    std::getline(std::cin, s.student_id);

    std::cout << "  ho va ten: ";
    std::getline(std::cin, s.name);
    std::cout << "  ngay sinh: ";
    std::cin >> s.dob.day >> s.dob.month >> s.dob.year;
    std::cout << "  diem trung binh: ";
    std::cin >> s.gpa;
    

    std::cout << s.class_id << " " << s.student_id << " " << s.name << " " << s.dob.day << " " << s.gpa << "\n";
}

void list_students()
{
    std::cout << "\n**                                     Danh sach sinh vien                                       **";

    std::cout << "\n-| STT | ma lop    | ma sinh vien | ho va ten                | ngay sinh       | diem trung bing |-";

}


void sort_students();
void search_students();
void statistics_studnet();

