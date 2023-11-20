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

//int _input_to_int(int input);

void add_recoid();
void list_students(const std::string table_title = "MENU 2 | Danh sach sinh vien");
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
        std::cout << "\n(1) - Them moi ho so";
        std::cout << "\n(2) - In danh sach";
        std::cout << "\n(3) - Sap xep";
        std::cout << "\n(4) - Tim kiem";
        std::cout << "\n(5) - Thong ke";
        std::cout << "\n(6) - Thoat";

        std::cout << "\n(Chon chuc nang (1) - (6))";
        std::cout << "\n>";
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
            sort_students();
            break;
        case '4':
            search_students();
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
    std::cout << "\n*** MENU 1 | Nhap thong tin sinh vien ***";
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

    //std::cout << s.class_id << " " << s.student_id << " " << s.name << " " << s.dob.day << " " << s.gpa << "\n";
    

}

void list_students(const std::string table_title)
{
    char return_to_main{};
    std::cout << "\n-***   ***   ***   ***   ***    " << table_title << "    ***   ***   ***   ***   ***-";
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


void sort_students()
{
    char algo_choice;
    char column_choice;

    std::cout << "\n*** MENU 3 | Sap xep danh sach sinh vien ***";
    std::cout << "\n\nLua chon thuat toan sap xep:";
    std::cout << "\n(1) - Sap xep chon";
    std::cout << "\n(2) - Sap xep chen";
    std::cout << "\n(3) - Sap xep noi bot";
    std::cout << "\n(4) - quicksort";
    std::cout << "\n(5) - mergesort";
    std::cout << "\n(0) - Quay lai Menu\n";

    std::cin.ignore();
    while(true)
    {
        std::cout << "(Chon thuat toan (1) - (5))";
        std::cout << "\n>";
        algo_choice = _getch();
        
        switch (algo_choice)
        {
        case '0':
            return;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            std::cout << algo_choice;
            break;
        default:
            std::cout << "\n";
            continue;
        }
        
        break;
    }
    

    std::cout << "\nChon truong sao xep:";
    std::cout << "\n(1) - ma sinh vien";
    std::cout << "\n(2) - hoc va ten";
    std::cout << "\n(3) - ngay sinh";
    std::cout << "\n(4) - diem trung bing\n";

    
    while(true)
    {
        std::cout << "(Chon truong sap xep (1) - (4)";
        std::cout << "\n>";
        column_choice = _getch();
        switch (column_choice)
        {
        case '1':
        case '2':
        case '3':
            std::cout << column_choice;
            break;
        default:
            continue;
        }
        break;
    };


    list_students(" MENU  | Danh sach sinh vien");

}
void search_students()
{
    char searched_column;
    std::cout << "\n*** MENU $ | Tim kien sinh vien ***";

    std::cout << "\n\n Lua chon truong tim kiem:";
    std::cout << "\n(1) - ma lop";
    std::cout << "\n(2) - ma sinh vien";
    std::cout << "\n(3) - ho va ten";
    std::cout << "\n(4) - ngay sinh";
    std::cout << "\n(5) - diem trung binh";

    while (true)
    {
        std::cout << "(Chon truong tim kiem (1) - (4)";
        std::cout << "\n>";
        searched_column = _getch();
        switch (searched_column)
        {
        case '1':
        case '2':
        case '3':
            std::cout << searched_column;
            break;
        default:
            continue;
        }
        break;
    };

    list_students("MENU   | Ket qua tim kiem   ");
}
void statistics_studnet();


