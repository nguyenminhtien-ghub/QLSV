#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
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
bool _validate_student_id(const std::string id);
bool _validate_date(const int input_day,const int input_month,const int input_year);
bool _validate_year(const int year);
bool _is_leap_year(const int year);
bool _validate_month(const int month);
bool _validate_day(const int day, const int month, const int years);
bool _validate_gpa(const float input_gpa);
void list_students(const std::string table_title = "MENU 2 | Danh sach sinh vien");
void _print_single_student(const int i, const std::string class_id, const std::string student_id, const std::string name, const int dob_day, const int dob_month, const int dob_year, const float gpa);
void sort_students();

void search_students();
void statistics_student();
void _statistics_quantity_by_class();
void _statistics_rank_students();


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

        switch (user_choice)
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
            statistics_student();
            break;
        default:
            std::cout << "\nNhap so tu 1 den 6\n";
            break;
        }

    }
}

void add_recoid()
{
    std::ofstream data_file("student.dat", std::ios::binary | std::ios::app);

    if (!data_file)
    {
        std::cerr << "Loi mo file danh sach siinh vien";
        return;
    }

    Student s;
    char user_confirm = 'y';

    std::cin.ignore();
    std::cout << "\n*** MENU 1 | Nhap thong tin sinh vien ***";
    std::cout << "\n";
    std::cout << "\n  ma lop: ";
    std::getline(std::cin, s.class_id);

    do 
    {
        std::cout << "  ma sinh vien (8 chu so): ";
        std::getline(std::cin, s.student_id);

    } while (_validate_student_id(s.student_id) == false);
    
    std::cout << "  ho va ten: ";
    std::getline(std::cin, s.name);

    do
    {
        std::cout << "  ngay sinh (dd mm yyyy): ";
        std::cin >> s.dob.day >> s.dob.month >> s.dob.year;

    } while (_validate_date(s.dob.day, s.dob.month, s.dob.year) == false);

    do
    {
        std::cout << "  diem trung binh: ";
        std::cin >> s.gpa;

    } while (_validate_gpa(s.gpa) == false);

    std::cout << s.class_id << " " << s.student_id << " " << s.name << " " << s.dob.day << " " << s.gpa << "\n";
    
    std::cout << "\n\nXac nhap thong tin sinh vien da nhap (y / n): ";
    user_confirm = _getch();

    if (user_confirm == 'y')
    {
        data_file.write(reinterpret_cast<char*>(&s), sizeof(s));
    }

}

void list_students(const std::string table_title)
{
    std::array<Student, 1> s_list;
    std::ifstream data_file("student.dat", std::ios::binary);
    char return_to_main;
    data_file.read(reinterpret_cast<char*>(&s_list), sizeof(Student) * 1);
    std::cout << "\n-***   ***   ***   ***   ***    " << table_title << "    ***   ***   ***   ***   ***-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    std::cout << "\n-| STT |  ma lop  | ma sinh vien |        ho va ten        | ngay sinh  | diem trung bing |-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    
    for (int i = 0; i < s_list.size(); i++)
    {
        _print_single_student(i,
            s_list[i].class_id,
            s_list[i].student_id,
            s_list[i].name,
            s_list[i].dob.day,
            s_list[i].dob.month,
            s_list[i].dob.year,
            s_list[i].gpa);
    }
    

    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";

    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    std::cin.ignore();
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
    std::cout << "\n*** MENU 4 | Tim kien sinh vien ***";

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
void statistics_student()
{
    char user_choice;

    std::cout << "\n*** MENU 5 | Thong ke thong tin ***";
    std::cout << "\n\n(1) - Thong ke so luong sinh vien theo lop";
    std::cout << "\n(2) - Thong ke ty le ket qua hoc tap";
    std::cout << "\n>";
    user_choice = _getch();
    
    if (user_choice == '1')
    {
        std::cout << user_choice;
        _statistics_quantity_by_class();
        return;
    }

    if (user_choice == '2')
    {
        std::cout << user_choice;
        _statistics_rank_students();

        return;
    }
}

void _statistics_quantity_by_class()
{
    char return_to_main;
    std::cout << "\n\n  * Thong ke so luong sinh vien theo lop *  ";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n     | ma lop | so luong sinh vien |";
    std::cout << "\n     |  AAA17 |                 60 |";
    std::cout << "\n     |  ABB17 |                 74 |";
    std::cout << "\n     |  ABB17 |                 60 |";
    std::cout << "\n     |  ABB17 |                 77 |";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n    -|  TONG  |                271 |-";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    return_to_main = _getch();
}

void _statistics_rank_students()
{
    char return_to_main;
    std::cout << "\n\n                           * Thong ke ket qua hoc tap *  ";
    std::cout << "\n    -|--------|------------|------------|------------|------------|------------|-";
    std::cout << "\n     |        |  xuat sac  |    gioi    |    kha     | trung binh |    yeu     |";
    std::cout << "\n     | ma lop |------------|------------|------------|------------|------------|";
    std::cout << "\n     |        |  SL | (%)  |  SL | (%)  |  SL | (%)  |  SL | (%)  |  SL | (%)  |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n     |  AAA17 |   5 |    8 |  11 |   18 |  24 |   40 |  17 |   28 |   3 |    5 |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n     |  AAA17 |   7 |    9 |   9 |   12 |  30 |   41 |  21 |   28 |   7 |    9 |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n     |  AAA17 |   3 |    5 |  12 |   20 |  21 |   35 |  19 |   32 |   5 |    8 |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n     |  AAA17 |   6 |    8 |  15 |   19 |  29 |   29 |  22 |   29 |   5 |    6 |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n     |  TONG  |  21 |    8 |  47 |   17 | 104 |   38 |  79 |   29 |  20 |    7 |";
    std::cout << "\n    -|-------------------------------------------------------------------------|-";

    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    return_to_main = _getch();
}

bool _validate_student_id(const std::string id)
{
     return id.length() == 8;
}

bool _validate_date(const int input_day, const int input_month, const int input_year)
{
    return _validate_year(input_year)
        && _validate_month(input_month)
        && _validate_day(input_day, input_month, input_year);
}

bool _validate_year(const int year)
{
    return year < 2016 && year > 1900;
}

bool _validate_month(const int month)
{
    return month > 0 && month < 13;
}

bool _validate_day(const int day, const int month, const int year)
{

    if (day < 0)
    {
        return false;
    }

    if (month == 1
        || month == 3
        || month == 5
        || month == 7
        || month == 8
        || month == 10
        || month == 12)
    {
        return day < 32;
    }

    if (month == 4
        || month == 6
        || month == 9
        || month == 11)
    {
        return day < 31;
    }

    // month == 2
    if (_is_leap_year(year))
    {
        return day < 30;
    }
    else
    {
        return day < 29;
    }
}

bool _is_leap_year(const int year)
{
    return (year % 4 == 0) && (year % 100 != 0);
}

bool _validate_gpa(const float input_gpa)
{
    return input_gpa >= 0.0f && input_gpa <= 10.0f;
}

void _print_single_student(const int i, const std::string class_id, const std::string student_id, const std::string name, const int dob_day, const int dob_month, const int dob_year, const float gpa)
{
    if (i < 10)
    {
        std::cout << "\n | 00";

    }
    else if (i < 10)
    {
        std::cout << "\n | 0";
    }
    std::cout << i + 1;
    std::cout << " | " << std::setw(8) << std::right << class_id;
    std::cout << " | " << std::setw(12) << std::right << student_id;
    std::cout << " | " << std::setw(23) << name;
    std::cout << " | " << std::setw(3) << dob_day << "/" << dob_month << "/" << dob_year;
    std::cout << " | " << std::setw(15) << std::right << gpa << " |";
}


