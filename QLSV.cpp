#include <conio.h>
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <stack>
#include <map>
#include <bitset>

// 00001: class_id is sorted, 00010: student_id is sorted, 00100: name, 01000: date of birth, 10000: gpa
std::bitset<5> sorted_key{ 0b0'0'0'0'0 };

enum STUDENT_KEY
{
    CLASS_ID = '1',
    ID = '2',
    NAME = '3',
    DOB = '4',
    GPA = '5'
};

enum STUDENT_RANK
{
    EXCELLENT = 0,
    GREAT,
    GOOD,
    AVERAGE,
    FAIL,
};

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

    // 10.0 - 8.5 excellent | 8.4 - 7.0 great | 6.9 - 6.0 good | 5.9 - 5.0 - average | 4.9 - 0.0 fail
    float gpa;

    void serialize(std::ostream& os) const
    {
        size_t class_id_size = this->class_id.size();
        size_t id_size = this->student_id.size();
        size_t name_size = this->name.size();

        os.write(reinterpret_cast<const char*>(&class_id_size), sizeof(class_id_size));
        os.write(class_id.c_str(), class_id_size);

        os.write(reinterpret_cast<const char*>(&id_size), sizeof(id_size));
        os.write(student_id.c_str(), id_size);

        os.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));
        os.write(name.c_str(), name_size);

        os.write(reinterpret_cast<const char*>(&dob.day), sizeof(dob.day));
        os.write(reinterpret_cast<const char*>(&dob.month), sizeof(dob.month));
        os.write(reinterpret_cast<const char*>(&dob.year), sizeof(dob.year));
        os.write(reinterpret_cast<const char*>(&gpa), sizeof(gpa));
    }

    void deserialize(std::istream& is)
    {
        size_t class_id_size, id_size, name_size;

        is.read(reinterpret_cast<char*>(&class_id_size), sizeof(class_id_size));
        if (is.eof())
        {
            return;
        }
        class_id.resize(class_id_size);
        is.read(&class_id[0], class_id_size);

        is.read(reinterpret_cast<char*>(&id_size), sizeof(id_size));
        student_id.resize(id_size);
        is.read(&student_id[0], id_size);

        is.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));
        name.resize(name_size);
        is.read(&name[0], name_size);

        is.read(reinterpret_cast<char*>(&dob.day), sizeof(dob.day));
        is.read(reinterpret_cast<char*>(&dob.month), sizeof(dob.month));
        is.read(reinterpret_cast<char*>(&dob.year), sizeof(dob.year));
        is.read(reinterpret_cast<char*>(&gpa), sizeof(gpa));
    }
};


void add_recoid();
bool _validate_student_id(const std::string id);
bool _validate_date(const int input_day,const int input_month,const int input_year);
bool _validate_year(const int year);
bool _is_leap_year(const int year);
bool _validate_month(const int month);
bool _validate_day(const int day, const int month, const int years);
bool _validate_gpa(const float input_gpa);
std::string str_to_name_t(std::string input);
std::string trim_start(std::string input);
std::string trim_end(std::string input);
std::string clear_duplicate_space(std::string input);
void save_student_list(std::vector<Student>& students);

void list_students(const std::string table_title = "MENU 2 | Danh sach sinh vien");
void load_student_list(std::vector<Student> &students);
void _print_single_student(const int i, const std::string class_id, const std::string student_id, const std::string name, const int dob_day, const int dob_month, const int dob_year, const float gpa);

void sort_students();
void set_sorted_key(std::bitset<5> keys, const char key_choice);
void selection_sort(const char key);
void _selection_by_key(std::vector<Student>& students, int& min_index, int& j, const char key);
void bubble_sort(const char key);
void _bubble_by_key(std::vector<Student>& students, int& j, const char key);
void quicksort(const char key);
void _quicksort(std::vector<Student>& students, size_t low, size_t high, const char key);
size_t _partition_student_list(std::vector<Student>& students, size_t low, size_t high, const char key);
void mergesort(const char key);
void _mergesort(std::vector<Student>& B_list, std::vector<Student>& A_list, size_t left, size_t right, const char key);
void _merge(std::vector<Student>& B_list, std::vector<Student>& A_list, int left, int middle, int right, const char key);
void _merge_list_by_key(const char& key, std::vector<Student>& A_list, int& i, int& j, int middle, int right, std::vector<Student>& B_list, int k);
bool compare_name_fn(const std::string name1, const std::string name2);
std::string str_to_lower(const std::string input);
bool compare_date(const Date d1, const Date d2);
bool compare_date(const int year_value1, const int year_value2, const int month_value1 = 0, const int month_value2 = 0, const int day_value1 = 0, const int day_value2 = 0);

void search_students();
void _search_info(const char key);
void _search_result(const std::string search_value, const char key);
void _search_result(const int year_value, const int month_value = 0, const int day_value = 0);
void _search_result(const float gpa_value);
void _linear_search_id_or_name(const std::string search_value, const bool is_exactly, const char key);
void _binary_search_class_or_name(const std::string search_value, const char key);
void _binary_search_student_id(const std::string search_value);
void _linear_search_number(const float gpa_value, const bool is_exactly = true);
void _binary_search_number(const float gpa_value, const bool is_exactly = true);

void statistics_student();
std::map<std::string, std::array<int, 5>> _load_class_rank(std::vector<Student> & students);
void _statistics_quantity_per_class(const std::map<std::string, std::array<int, 5>> &class_ranks);
void _statistics_rank_students(const std::map<std::string, std::array<int, 5>>& class_ranks);
int _rank_student(const float gpa);


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
        std::cerr << "\nLoi mo file danh sach sinh vien.\n";
        return;
    }

    Student s;
    char user_confirm = 'y';

    std::cin.ignore();
    std::cout << "\n*** MENU 1 | Nhap thong tin sinh vien ***";
    std::cout << "\n";
    std::cout << "\n  ma lop: ";
    std::getline(std::cin, s.class_id);
    s.class_id = trim_start(s.class_id);
    s.class_id = trim_end(s.class_id);

    do 
    {
        std::cout << "  ma sinh vien (8 chu so): ";
        std::getline(std::cin, s.student_id);
        s.student_id = trim_start(s.student_id);
        s.student_id = trim_start(s.student_id);

    } while (_validate_student_id(s.student_id) == false);
    
    std::cout << "  ho va ten: ";
    std::getline(std::cin, s.name);
    s.name = str_to_name_t(s.name);

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

    //std::cout << s.class_id << " " << s.student_id << " " << s.name << " " << s.dob.day << " " << s.gpa << "\n";
    
    std::cout << "\n\nXac nhap thong tin sinh vien da nhap (y / n): ";
    user_confirm = _getch();

    if (user_confirm == 'y')
    {
        s.serialize(data_file);
    }

    data_file.close();

}

void list_students(const std::string table_title)
{
    char return_to_main;

    std::vector<Student> students;
    load_student_list(students);

    std::cout << "\n-***   ***   ***   ***   ***    " << table_title << "     ***   ***   ***   ***   ***-";
    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
    std::cout << "\n-| STT |  ma lop  | ma sinh vien |        ho va ten         | ngay sinh  | diem trung bing |-";
    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
    
    int i = 1;

    for (Student& s : students)
    {
        _print_single_student(i,
            s.class_id,
            s.student_id,
            s.name,
            s.dob.day,
            s.dob.month,
            s.dob.year,
            s.gpa);
        i++;
    }

    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";

    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    
    return_to_main = _getch();
    
}

void sort_students()
{
    std::string table_title;
    char algo_choice;
    char key_choice;

    std::cout << "\n*** MENU 3 | Sap xep danh sach sinh vien ***";
    std::cout << "\n\nLua chon thuat toan sap xep:";
    std::cout << "\n(1) - Sap xep chon";
    std::cout << "\n(2) - Sap xep noi bot";
    std::cout << "\n(3) - quicksort";
    std::cout << "\n(4) - mergesort";
    std::cout << "\n(0) - Quay lai Menu\n";

    std::cin.ignore();
    while(true)
    {
        std::cout << "(Chon thuat toan (1) - (4))";
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
            std::cout << algo_choice;
            break;
        default:
            std::cout << "\n";
            continue;
        }
        
        break;
    }
    
    std::cout << "\nChon truong sao xep:";
    std::cout << "\n(1) - ma lop";
    std::cout << "\n(2) - ma sinh vien";
    std::cout << "\n(3) - hoc va ten";
    std::cout << "\n(4) - ngay sinh";
    std::cout << "\n(5) - diem trung bing\n";
    
    while(true)
    {
        std::cout << "(Chon truong sap xep (1) - (4)";
        std::cout << "\n>";

        key_choice = _getch();
        std::cout << key_choice << "\n";
        switch (key_choice)
        {
        case STUDENT_KEY::CLASS_ID:
            table_title = "MENU | DS sinh vien theo lop";
            break;
        case STUDENT_KEY::ID:
            table_title = "MENU | DSSV theo ma sinhvien";
            break;
        case STUDENT_KEY::NAME:
            table_title = "MENU | DS sinh vien theo ten";
            break;
        case STUDENT_KEY::DOB:
            table_title = " MENU | DSSV theo ngay sinh ";
            break;
        case STUDENT_KEY::GPA:
            table_title = "    MENU | DSSV theo diem   ";
            break;
        default:
            std::cout << "\n";
            continue;
        }
        break;
    };

    if (algo_choice == '1')
    {
        selection_sort(key_choice);
    }
    else if (algo_choice == '2')
    {
        bubble_sort(key_choice);
    }
    else if (algo_choice == '3')
    {
        quicksort(key_choice);
    }
    else if (algo_choice == '4')
    {
        mergesort(key_choice);
    }

    set_sorted_key(sorted_key, key_choice);

    list_students(table_title);
}

void search_students()
{
    char searched_key;
    std::string search_value;
    std::cout << "\n*** MENU 4 | Tim kien sinh vien ***";

    std::cout << "\n\n Lua chon truong tim kiem:";
    std::cout << "\n(1) - ma lop";
    std::cout << "\n(2) - ma sinh vien";
    std::cout << "\n(3) - ho va ten";
    std::cout << "\n(4) - ngay sinh";
    std::cout << "\n(5) - diem trung binh";

    while (true)
    {
        std::cout << "\n(Chon truong tim kiem (1) - (5)";
        std::cout << "\n>";
        searched_key = _getch();
        std::cin.ignore();
        switch (searched_key)
        {
        case STUDENT_KEY::CLASS_ID:
        case STUDENT_KEY::ID:
        case STUDENT_KEY::NAME:
        case STUDENT_KEY::DOB:
        case STUDENT_KEY::GPA:
            std::cout << searched_key;
            break;
        default:
            continue;
        }
        break;
    };

    _search_info(searched_key);
    

    //list_students("  MENU  | Ket qua tim kiem  ");
}

void _search_info(const char key)
{
    char return_to_main;
    if (key == STUDENT_KEY::CLASS_ID || key == STUDENT_KEY::ID || key == STUDENT_KEY::NAME)
    {
        std::string search_value;
        std::cout << "\n\nTim kiem: ";
        std::getline(std::cin, search_value);
        search_value = trim_start(search_value);
        search_value = trim_end(search_value);

        std::cout << "\n-***   ***   ***   ***   ***   ***    Ket qua tim kiem     ***   ***   ***   ***   ***   ***-";
        _search_result(search_value, key);
    }
    else if (key == STUDENT_KEY::DOB)
    {
        int day_value = 0;
        int month_value = 0;
        int year_value = 0;

        std::cout << "\n";

        while (true)
        {
            std::cout << "\nTim kiem (nhap 0 de bo qua ngay hoac thang)";
            std::cout << "\n   - ngay: ";
            std::cin >> day_value;
            std::cout << "   - thang: ";
            std::cin >> month_value;
            std::cout << "   - nam: ";
            std::cin >> year_value;

            if (day_value == 0 && month_value == 0)
            {
                _search_result(year_value);
                break;
            }
            if (day_value == 0)
            {
                if (_validate_month(month_value) == false)
                {
                    std::cout << "\nThang khong hop le.";
                    continue;
                }
                _search_result(year_value, month_value);
                break;
            }

            if (_validate_date(day_value, month_value, year_value))
            {
                _search_result(year_value, month_value, day_value);
                break;
            }
            else
            {
                std::cout << "\nThoi gian khong hop le.";
            }
        }
    }
    else if (key == STUDENT_KEY::GPA)
    {
        float gpa_input;
        std::cout << "\nGia tri diem: ";
        std::cin >> gpa_input;
        std::cout << "\n-***   ***   ***   ***   ***   ***     Ket qua tim kiem    ***   ***   ***   ***   ***   ***-";
        _search_result(gpa_input);
    }

    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";

    return_to_main = _getch();
}

void statistics_student()
{
    char user_choice;
    std::vector<Student> students;
    std::map<std::string, std::array<int, 5>> class_ranks = _load_class_rank(students);

    std::cout << "\n*** MENU 5 | Thong ke thong tin ***";
    std::cout << "\n\n(1) - Thong ke so luong sinh vien theo lop";
    std::cout << "\n(2) - Thong ke ty le ket qua hoc tap";
    std::cout << "\n>";
    user_choice = _getch();
    
    if (user_choice == '1')
    {
        std::cout << user_choice;
        _statistics_quantity_per_class(class_ranks);
        return;
    }

    if (user_choice == '2')
    {
        std::cout << user_choice;
        _statistics_rank_students(class_ranks);

        return;
    }
}

void _statistics_quantity_per_class(const std::map<std::string, std::array<int, 5>>& class_ranks)
{
    char return_to_main;

    int count = 0;
    int total = 0;
    std::cout << "\n\n  * Thong ke so luong sinh vien theo lop *  ";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n     | ma lop | so luong sinh vien |";
    std::cout << "\n    -|--------|--------------------|-";
    for (std::pair<std::string, std::array<int, 5>> class_name : class_ranks)
    {
        count = std::accumulate(class_name.second.begin(), class_name.second.end(), 0);
        total += count;
        std::cout << "\n     |" << std::setw(7) << class_name.first << " |";
        std::cout << std::setw(19) << count;
        std::cout << " |";
    }
    //std::cout << "\n     |  AAA17 |                 60 |";
    //std::cout << "\n     |  AAB17 |                 74 |";
    //std::cout << "\n     |  AAC17 |                 60 |";
    //std::cout << "\n     |  ABB17 |                 77 |";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n    -|  TONG  |";
    std::cout << std::setw(19) << total << " |";
    std::cout << "\n    -|--------|--------------------|-";
    std::cout << "\n\n(Nhap phim bat ki de QUAY VE Menu)";
    return_to_main = _getch();
}

void _statistics_rank_students(const std::map<std::string, std::array<int, 5>>& class_ranks)
{
    char return_to_main;
    std::array<int, 5> total_per_rank{ 0, 0, 0, 0, 0 };
    int count = 0;
    std::cout << "\n\n                           * Thong ke ket qua hoc tap *  ";
    std::cout << "\n    -|--------|------------|------------|------------|------------|------------|-";
    std::cout << "\n     |        |  xuat sac  |    gioi    |    kha     | trung binh |    yeu     |";
    std::cout << "\n     | ma lop |------------|------------|------------|------------|------------|";
    std::cout << "\n     |        |  SL |  (%) |  SL |  (%) |  SL |  (%) |  SL |  (%) |  SL |  (%) |";
    for (std::pair<std::string, std::array<int, 5>> class_name : class_ranks)
    {
        std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
        std::cout << "\n     | " << std::setw(6) << class_name.first << " |";
        count = std::accumulate(class_name.second.begin(), class_name.second.end(), 0);
        for (int i = 0; i < 5; i++)
        {
            std::cout << " " << std::setw(3) << class_name.second[i];
            std::cout << " | " << std::setw(4) << 100 * class_name.second[i] / count << " |";
            total_per_rank[i] += class_name.second[i];
        }
    }
    //std::cout << "\n     |  AAA17 |   5 |    8 |  11 |   18 |  24 |   40 |  17 |   28 |   3 |    5 |";
    //std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    //std::cout << "\n     |  AAB17 |   7 |    9 |   9 |   12 |  30 |   41 |  21 |   28 |   7 |    9 |";
    //std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    //std::cout << "\n     |  AAC17 |   3 |    5 |  12 |   20 |  21 |   35 |  19 |   32 |   5 |    8 |";
    //std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    //std::cout << "\n     |  ABB17 |   6 |    8 |  15 |   19 |  29 |   29 |  22 |   29 |   5 |    6 |";
    std::cout << "\n    -|--------|-----|------|-----|------|-----|------|-----|------|-----|------|-";
    std::cout << "\n    -|  TONG  |";
    count = std::accumulate(total_per_rank.begin(), total_per_rank.end(), 0);
    for (int i : total_per_rank)
    {
        std::cout << " " << std::setw(3) << i;
        std::cout << " | " << std::setw(4) << 100 * i / count << " |";
    }
    //std::cout << "\n     |  TONG  |  21 |    8 |  47 |   17 | 104 |   38 |  79 |   29 |  20 |    7 |";
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

std::string str_to_name_t(std::string input)
{
    input = trim_start(input);
    input = trim_end(input);
    input = clear_duplicate_space(input);

    input[0] = std::toupper(input[0]);
    for (int i = 1; i < input.length(); i++)
    {
        if (input[i - 1] == ' ')
        {
            input[i] = std::toupper(input[i]);
            continue;
        }
        input[i] = std::tolower(input[i]);
    }

    return input;
}

std::string trim_start(std::string input)
{
    if (input == "")
    {
        return input;
    }
    while (input.at(0) == std::string::npos)
    {
        input = input.substr(1);
    };
    return input;
}

std::string trim_end(std::string input)
{
    if (input == "")
    {
        return input;
    }

    while (input.at(input.length() - 1) == std::string::npos)
    {
        input.pop_back();
    }
    return input;
}

std::string clear_duplicate_space(std::string input)
{
    if (input == "")
    {
        return input;
    }
    char duplicate_space_char[3] = "  ";
    while (input.find(duplicate_space_char) != std::string::npos)
    {
        input.replace(input.find(duplicate_space_char), sizeof(duplicate_space_char), " ");
    }
    return input;
}

std::string str_to_lower(const std::string input)
{
    std::string lower_case = "";
    for (int i = 0; i < input.length(); i++)
    {
        lower_case += std::tolower(input[i]);
    }
    return lower_case;
}

void save_student_list(std::vector<Student>& students)
{
    std::ofstream data_file("student.dat", std::ios::binary);

    if (!data_file)
    {
        std::cerr << "\nLoi mo file danh sach sinh vien.\n";
        return;
    }

    for (Student& s : students)
    {
        s.serialize(data_file);
    }

    data_file.close();

}

void load_student_list(std::vector<Student>& students)
{
    std::ifstream data_file("student.dat", std::ios::binary);

    if (!data_file)
    {
        return;
        std::cerr << "\nLoi mo file danh sach sinh vien.\n";
    }
    while (data_file.eof() == false)
    {
        Student s;
        s.deserialize(data_file);
        if (data_file.eof())
        {
            break;
        }
        students.push_back(s);
    }
    data_file.close();
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
    std::cout << i;
    std::cout << " | " << std::setw(8) << class_id;
    std::cout << " | " << std::setw(12) << student_id;
    std::cout << " | " << std::setw(24) << std::left << name;
    std::cout << " | " << std::setw(2) << std::right << dob_day << "/" << std::setw(2) << dob_month << "/" << dob_year;
    std::cout << " | " << std::setw(15) << gpa << " |";
}

void set_sorted_key(std::bitset<5> keys, const char key_choice)
{
    if (key_choice == STUDENT_KEY::CLASS_ID)
    {
        sorted_key = 0b0'0'0'0'1;
    }
    else if (key_choice == STUDENT_KEY::ID)
    {
        sorted_key = 0b0'0'0'1'0;
    }
    else if (key_choice == STUDENT_KEY::NAME)
    {
        sorted_key = 0b0'0'1'0'0;
    }
    else if (key_choice == STUDENT_KEY::DOB)
    {
        sorted_key = 0b0'1'0'0'0;
    }
    else if (key_choice == STUDENT_KEY::GPA)
    {
        sorted_key = 0b1'0'0'0'0;
    }
}

void selection_sort(const char key)
{
    std::vector<Student> students;

    load_student_list(students);

    size_t total_student = students.size();
    for (int i = 0; i < total_student - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1;  j < total_student; j++)
        {
            _selection_by_key(students, min_index, j, key);

            /*
            if (students[j].class_id < students[min_index].class_id)
            {
                min_index = j;
            }
            continue;
            */
        }

        std::swap(students[i], students[min_index]);
    }

    save_student_list(students);

}

void _selection_by_key(std::vector<Student>& students, int& min_index, int& j, const char key)
{
    if (key == STUDENT_KEY::CLASS_ID)
    {
        if (students[j].class_id < students[min_index].class_id)
        {
            min_index = j;
        }
        return;
    }

    if (key == STUDENT_KEY::ID)
    {
        if (students[j].student_id < students[min_index].student_id)
        {
            min_index = j;
        }
        return;
    }

    if (key == STUDENT_KEY::NAME)
    {
        if(compare_name_fn(students[j].name, students[min_index].name))
        {
            min_index = j;
        }
        return;
    }

    if (key == STUDENT_KEY::DOB)
    {
        if (compare_date(students[j].dob, students[min_index].dob))
        {
            min_index = j;
        }
        return;
    }

    if (key == STUDENT_KEY::GPA)
    {
        if (students[j].gpa < students[min_index].gpa)
        {
            min_index = j;
        }
        return;
    }
}

void bubble_sort(const char key)
{
    std::vector<Student> students;

    load_student_list(students);

    size_t total_student = students.size();
    for (int i = 0; i < total_student - 1; i++)
    {
        for (int j = 0; j < total_student - i - 1; j++)
        {
            _bubble_by_key(students, j, key);
        }
    }
    
    save_student_list(students);
}

void _bubble_by_key(std::vector<Student>& students, int& j, const char key)
{
    if (key == STUDENT_KEY::CLASS_ID)
    {
        if (students[j].class_id > students[j + 1].class_id)
        {
            std::swap(students[j], students[j + 1]);
        }
        return;
    }
    if (key == STUDENT_KEY::ID)
    {
        if (students[j].student_id > students[j + 1].student_id)
        {
            std::swap(students[j], students[j + 1]);
        }
        return;
    }
    if (key == STUDENT_KEY::NAME)
    {
        if (compare_name_fn(students[j + 1].name, students[j].name))
        {
            std::swap(students[j], students[j + 1]);
        }
        return;
    }
    if (key == STUDENT_KEY::DOB)
    {
        if (compare_date(students[j + 1].dob, students[j].dob))
        {
            std::swap(students[j], students[j + 1]);
        }
        return;
    }
    if (key == STUDENT_KEY::GPA)
    {
        if (students[j].gpa > students[j + 1].gpa)
        {
            std::swap(students[j], students[j + 1]);
        }
        return;
    }
}

void quicksort(const char key)
{
    std::vector<Student> students;
    size_t low = 0;

    load_student_list(students);

    size_t high = students.size() - 1;
    _quicksort(students, low, high, key);

    save_student_list(students);

}

void _quicksort(std::vector<Student>& students, size_t low, size_t high, const char key)
{
    
    if (low < high)
    {
        size_t pivot_index = _partition_student_list(students, low, high, key);
        _quicksort(students, low, pivot_index - 1, key);
        _quicksort(students, pivot_index + 1, high, key);
    }
}


// Function to partition the list for quicksort
size_t _partition_student_list(std::vector<Student>& students, size_t low, size_t high, const char key)
{
    size_t i = low - 1;

    bool is_value_lesser;
    for (size_t j = low; j < high; j++)
    {
        if (key == STUDENT_KEY::CLASS_ID)
        {
            is_value_lesser = students[j].class_id < students[high].class_id;
        }
        else if (key == STUDENT_KEY::ID)
        {
            is_value_lesser = students[j].student_id < students[high].student_id;
        }
        else if (key == STUDENT_KEY::NAME)
        {
            is_value_lesser = compare_name_fn(students[j].name, students[high].name);
        }
        else if (key == STUDENT_KEY::DOB)
        {
            is_value_lesser = compare_date(students[j].dob, students[high].dob);
        }
        else
        {
            is_value_lesser = students[j].gpa < students[high].gpa;
        }

        if (is_value_lesser)
        {
            i++;
            std::swap(students[i], students[j]);
        }
    }

    std::swap(students[i + 1], students[high]);
    return i + 1;
   
}


void mergesort(const char key)
{
    std::vector<Student> students;

    load_student_list(students);
    std::vector<Student> temp_list{ students };

    _mergesort(students, temp_list, 0, students.size(), key);

    save_student_list(students);
}


void _mergesort(std::vector<Student>& B_list, std::vector<Student>& A_list, size_t left, size_t right, const char key)
{
    if (right - left <= 1)
    {
        return;
    }

    size_t middle = left + (right - left) / 2;
    _mergesort(A_list, B_list, left, middle, key);
    _mergesort(A_list, B_list, middle, right, key);
    
    _merge(B_list, A_list, left, middle, right, key);
}

void _merge(std::vector<Student>& B_list, std::vector<Student>& A_list, int left, int middle, int right, const char key)
{
    int i = left;
    int j = middle;

    for (int k = left; k < right; k++)
    {
        _merge_list_by_key(key, A_list, i, j, middle, right, B_list, k);

        /*
        if (i < middle
            && (j >= right || A_list[i].class_id <= A_list[j].class_id))
        {
            B_list[k] = A_list[i];
            i++;
        }
        else
        {
            B_list[k] = A_list[j];
            j++;
        }*/
    }
}

void _merge_list_by_key(const char& key, std::vector<Student>& A_list, int& i, int& j, int middle, int right, std::vector<Student>& B_list, int k)
{
    bool is_lesser_or_equal_right_head;

    if (key == STUDENT_KEY::CLASS_ID)
    {
        is_lesser_or_equal_right_head = j >= right || A_list[i].class_id <= A_list[j].class_id;
    }
    else if (key == STUDENT_KEY::ID)
    {
        is_lesser_or_equal_right_head = j >= right || A_list[i].student_id <= A_list[j].student_id;
    }
    else if (key == STUDENT_KEY::NAME)
    {
        //is_lesser_or_equal_right_head = j >= right || A_list[i].name <= A_list[j].name;
        is_lesser_or_equal_right_head = j >= right || (compare_name_fn(A_list[j].name, A_list[i].name) == false);
    }
    else if (key == STUDENT_KEY::DOB)
    {
        is_lesser_or_equal_right_head = j >= right || compare_date(A_list[j].dob, A_list[i].dob) == false;
    }
    else
    {
        is_lesser_or_equal_right_head = j >= right || A_list[i].gpa <= A_list[j].gpa;
    }

    if (i < middle && is_lesser_or_equal_right_head)
    {
        B_list[k] = A_list[i];
        i++;
    }
    else
    {
        B_list[k] = A_list[j];
        j++;
    }
}

// Search id or name
void _search_result(const std::string search_value, const char key)
{
    bool is_sort_by_key = (key == STUDENT_KEY::CLASS_ID && sorted_key == 0b0'0'0'0'1)
        || (key == STUDENT_KEY::ID && sorted_key == 0b0'0'0'1'0)
        || (key == STUDENT_KEY::NAME && sorted_key != 0b0'0'1'0'1);

    std::cout << "\n-|-----|----------|--------------|----Ket qua chinh xac-----|------------|-----------------|-";

    if (is_sort_by_key == false)
    {
        _linear_search_id_or_name(search_value, true, key);
    }
    else if (key == STUDENT_KEY::CLASS_ID || key == STUDENT_KEY::NAME)
    {
        _binary_search_class_or_name(search_value, key);
    }
    else
    {
        _binary_search_student_id(search_value);
    }

    std::cout << "\n-|-----|----------|--------------|-----Ket qua gan dung-----|------------|-----------------|-";
    _linear_search_id_or_name(search_value, false, key);
    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
}

void _linear_search_id_or_name(const std::string search_value, const bool is_exactly,const char key)
{
    int count = 0;
    std::vector<Student> students;
    load_student_list(students);
    bool is_find;
    for (Student& s : students)
    {
        if (key == STUDENT_KEY::CLASS_ID)
        {
            if (is_exactly)
            {
                is_find = str_to_lower(s.class_id) == str_to_lower(search_value);
            }
            else
            {
                std::string str_lower = str_to_lower(s.class_id);
                is_find = str_lower.find(str_to_lower(search_value)) != std::string::npos;
            }
        }
        else if (key == STUDENT_KEY::ID)
        {
            if (is_exactly)
            {
                is_find = s.student_id == search_value;
                _print_single_student(1,
                    s.class_id,
                    s.student_id,
                    s.name,
                    s.dob.day,
                    s.dob.month,
                    s.dob.year,
                    s.gpa);
                return;
            }
            else
            {
                is_find = s.student_id.find(search_value) != std::string::npos;
            }
        }
        else
        {
            if (is_exactly)
            {
                is_find = str_to_lower(s.name) == str_to_lower(search_value);
            }
            else
            {
                std::string str_lower = str_to_lower(s.name);
                is_find = str_lower.find(str_to_lower(search_value)) != std::string::npos;
            }
        }

        if (is_find)
        {
            count++;
            _print_single_student(count,
                s.class_id,
                s.student_id,
                s.name,
                s.dob.day,
                s.dob.month,
                s.dob.year,
                s.gpa);
        }
    }

    if (count == 0)
    {
        std::cout << "\n-|                           (Khong tim thay thong tin sinh vien)                          |-";
    }
    
}

void _binary_search_class_or_name(const std::string search_value, const char key)
{
    int count = 0;
    std::vector<Student> students;
    load_student_list(students);

    int left = 0;
    int right = students.size() - 1;
    int mid = -1;
    bool is_equal;
    bool is_lesser;
    bool is_prev_equal;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (key == STUDENT_KEY::CLASS_ID)
        {
            is_equal = str_to_lower(students[mid].class_id) == str_to_lower(search_value);
            is_lesser = str_to_lower(students[mid].class_id) < str_to_lower(search_value);
        }
        else
        {
            is_equal = str_to_lower(students[mid].name) == str_to_lower(search_value);
            //is_lesser = students[mid].name < search_value;
            is_lesser = compare_name_fn(
                str_to_lower(students[mid].name), 
                str_to_lower(search_value));
        }

        if (is_equal)
        {
            break;
            
        }

        else if (is_lesser)
        {
            left = mid + 1;
        }

        else
        {
            right = mid - 1;
        }
    }

    // Find first index students who == search value
    while (mid > 0)
    {
        if (key == STUDENT_KEY::CLASS_ID)
        {
            is_prev_equal = str_to_lower(students[mid - 1].class_id) == str_to_lower(search_value);
        }
        else
        {
            is_prev_equal = str_to_lower(students[mid - 1].name) == str_to_lower(search_value);
        }
        
        if (is_prev_equal == false)
        {
            break;
        }
        mid--;

    }

    // If found student 
    if (left > right)
    {
        std::cout << "\n-|                      (Khong tim thay thong tin sinh vien trung hop)                     |-";
        return;
    }

    do 
    {
        count++;

        _print_single_student(count,
            students[mid].class_id,
            students[mid].student_id,
            students[mid].name,
            students[mid].dob.day,
            students[mid].dob.month,
            students[mid].dob.year,
            students[mid].gpa);
        mid++;
            
        if (key == STUDENT_KEY::CLASS_ID)
        {
            is_equal = str_to_lower(students[mid].class_id) == str_to_lower(search_value);
        }
        else
        {
            is_equal = str_to_lower(students[mid].name) == str_to_lower(search_value);

        }
    } while (mid < students.size() && is_equal);
    
}

void _binary_search_student_id(const std::string search_value)
{
    std::vector<Student> students;
    load_student_list(students);
    int left = 0;
    int right = students.size() - 1;
    int mid = -1;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (students[mid].student_id == search_value)
        {
            _print_single_student(1,
                students[mid].class_id,
                students[mid].student_id,
                students[mid].name,
                students[mid].dob.day,
                students[mid].dob.month,
                students[mid].dob.year,
                students[mid].gpa);
            break;
        }

        else if (students[mid].student_id < search_value)
        {
            left = mid + 1;
        }

        else
        {
            right = mid - 1;
        }
    }
}

void _search_result(const int year_value, const int month_value, const int day_value)
{
    int count = 0;
    const bool is_only_year = month_value == 0 && day_value == 0;
    const bool is_day_not_assign = year_value != 0 && month_value != 0;
    bool is_date_equal;
    std::vector<Student> students;
    load_student_list(students);

    std::cout << "\n-***   ***   ***   ***   ***   ***    Ket qua tim kiem     ***   ***   ***   ***   ***   ***-";
    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
    if (sorted_key != 0b0'1'0'0'0)
    {
        
        for (Student& s : students)
        {
            if (month_value == 0 && day_value == 0)
            {
                is_date_equal = s.dob.year == year_value;
            }
            else if (day_value == 0)
            {
                is_date_equal = s.dob.year == year_value && s.dob.month == month_value;
            }
            else
            {
                is_date_equal = s.dob.year == year_value && s.dob.month == month_value && s.dob.day == day_value;
            }

            if (is_date_equal)
            {
                count++;
                _print_single_student(count,
                    s.class_id,
                    s.student_id,
                    s.name,
                    s.dob.day,
                    s.dob.month,
                    s.dob.year,
                    s.gpa);
            }
        }
    }
    else
    {
        int left = 0;
        int right = students.size() - 1;
        int mid = -1;
        bool is_date_before;
        bool is_prev_date_equal;

        while (left <= right)
        {
            mid = left + (right - left) / 2;

            if (is_only_year)
            {
                is_date_equal = students[mid].dob.year == year_value;
                is_date_before = students[mid].dob.year < year_value;
            }
            else if (is_day_not_assign)
            {
                is_date_equal = students[mid].dob.year == year_value && students[mid].dob.month == month_value;
                is_date_before = compare_date(students[mid].dob.year, year_value, students[mid].dob.month, month_value);
            }
            else
            {
                is_date_equal = students[mid].dob.year == year_value
                    && students[mid].dob.month == month_value
                    && students[mid].dob.day == day_value;
                Date d;
                d.year = year_value;
                d.month = month_value;
                d.day = day_value;
                is_date_before = compare_date(students[mid].dob, d);
            }

            if (is_date_equal)
            {
                break;
            }
            else if (is_date_before)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        // Find first index students who == search value
        while (mid > 0)
        {
            if (is_only_year)
            {
                is_prev_date_equal = students[mid - 1].dob.year == year_value;
            }
            else if (is_day_not_assign)
            {
                is_prev_date_equal = (students[mid - 1].dob.year == year_value && students[mid - 1].dob.month == month_value);
            }
            else
            {
                Date d;
                d.year = year_value;
                d.month = month_value;
                d.day = day_value;
                is_prev_date_equal = (compare_date(students[mid - 1].dob, d) == false);
            }

            if (is_prev_date_equal == false)
            {
                break;
            }
            mid--;
        }

        if (left <= right)
        {
            do 
            {
                count++;

                _print_single_student(count,
                    students[mid].class_id,
                    students[mid].student_id,
                    students[mid].name,
                    students[mid].dob.day,
                    students[mid].dob.month,
                    students[mid].dob.year,
                    students[mid].gpa);
                mid++;

                if (is_only_year)
                {
                    is_date_equal = students[mid].dob.year == year_value;
                }
                else if (is_day_not_assign)
                {
                    is_date_equal = students[mid].dob.year == year_value && students[mid].dob.month == month_value;
                }
                else
                {
                    is_date_equal = students[mid].dob.year == year_value
                        && students[mid].dob.month == month_value
                        && students[mid].dob.day == day_value;
                }
                
            } while (mid < students.size() && is_date_equal);
        }
    }

    if (count == 0)
    {
        std::cout << "\n-|                       (Khong tim thay thong tin sinh vien trung hop)                     |-";
    }
    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
}

void _search_result(const float gpa_value)
{
    std::cout << "\n-|-----|----------|--------------|----Ket qua chinh xac-----|------------|-----------------|-";
    // linear search if list not sorted by gpa
    const bool is_sort_by_gpa = sorted_key != 0b1'0'0'0'0;
    if (is_sort_by_gpa)
    {
        _linear_search_number(gpa_value, true);
    }
    else
    {
        _binary_search_number(gpa_value, true);
    }
    std::cout << "\n-|-----|----------|--------------|-----Ket qua gan dung-----|------------|-----------------|-";
    if (is_sort_by_gpa)
    {
        _linear_search_number(gpa_value, false);
    }
    else
    {
        _binary_search_number(gpa_value, false);
    }

    std::cout << "\n-|-----|----------|--------------|--------------------------|------------|-----------------|-";
}

void _linear_search_number(const float gpa_value, bool is_exactly)
{
    int count = 0;
    std::vector<Student> students;
    load_student_list(students);
    
    for (Student& s : students)
    {
        bool is_equal;
        if (is_exactly)
        {
            is_equal = s.gpa == gpa_value;
        }
        else
        {
            is_equal = (int)s.gpa == (int)gpa_value;
        }

        if (is_equal)
        {
            count++;
            _print_single_student(count,
                s.class_id,
                s.student_id,
                s.name,
                s.dob.day,
                s.dob.month,
                s.dob.year,
                s.gpa);
        }
    }

    if (count == 0)
    {
        std::cout << "\n-|                      (Khong tim thay thong tin sinh vien trung hop)                     |-";
    }
}

void _binary_search_number(const float gpa_value, const bool is_exactly)
{
    int count = 0;
    std::vector<Student> students;
    load_student_list(students);

    int left = 0;
    size_t right = students.size() - 1;
    int mid = -1;
    bool is_equal;
    bool is_prev_equal;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (is_exactly)
        {
            is_equal = students[mid].gpa == gpa_value;
        }
        else
        {
            is_equal = (int)students[mid].gpa == (int)gpa_value;
        }

        if (is_equal)
        {
            break;
        }
        else if (students[mid].gpa < gpa_value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    // Find first index students who == search value
    while (mid > 0)
    {
        if (is_exactly)
        {
            is_prev_equal = students[mid - 1].gpa == gpa_value;
        }
        else
        {
            is_prev_equal = (int)students[mid - 1].gpa == (int)gpa_value;
        }

        if (is_prev_equal == false)
        {
            break;
        }
        mid--;

    }

    // If found student 
    if (left > right)
    {
        std::cout << "\n-|                      (Khong tim thay thong tin sinh vien trung hop)                     |-";
        return;
    }

    do
    {
        count++;

        _print_single_student(count,
            students[mid].class_id,
            students[mid].student_id,
            students[mid].name,
            students[mid].dob.day,
            students[mid].dob.month,
            students[mid].dob.year,
            students[mid].gpa);
        mid++;

        if (is_exactly)
        {
            is_equal = students[mid].gpa == gpa_value;
        }
        else
        {
            is_equal = (int)students[mid].gpa == (int)gpa_value;
        }

    }
    while (mid < students.size() && is_equal);
}

std::map<std::string, std::array<int, 5>> _load_class_rank(std::vector<Student>& students)
{
    load_student_list(students);

    std::map<std::string, std::array<int, 5>> class_ranks;

    for (Student& s : students)
    {
        if (class_ranks.count(s.class_id) > 0)
        {
            class_ranks[s.class_id][_rank_student(s.gpa)]++;
            continue;
        }

        class_ranks[s.class_id][_rank_student(s.gpa)] = 1;
    }

    return class_ranks;
}

int _rank_student(const float gpa)
{
    if (gpa >= 8.5f)
    {
        return STUDENT_RANK::EXCELLENT;
    }
    if (gpa >= 7.0f)
    {
        return STUDENT_RANK::GREAT;
    }
    if (gpa >= 6.0f)
    {
        return STUDENT_RANK::GOOD;
    }
    if (gpa >= 5.0f)
    {
        return STUDENT_RANK::AVERAGE;
    }
    return STUDENT_RANK::FAIL;
}

bool compare_name_fn(const std::string name1, const std::string name2)
{
    std::stack<std::string> words1;
    std::stack<std::string> words2;
    std::string word;
    std::string n1 = str_to_lower(name1);
    std::string n2 = str_to_lower(name2);
    std::istringstream iss(n1);

    while (iss)
    {
        iss >> word;
        words1.push(word);
    }
    
    iss = std::istringstream(n2);

    while (iss)
    {
        iss >> word;
        words2.push(word);
    }

    const int min_word = std::min(words1.size(), words2.size());
    for (int i = 0; i < min_word; i++)
    {
        if (words1.top() != words2.top())
        {
            return words1.top() < words2.top();
        }
        words1.pop();
        words2.pop();
    }
    return n1.size() < n2.size();
}

// Return True if d1 is before d2
bool compare_date(const Date d1, const Date d2)
{
    if (d1.year != d2.year)
    {
        return d1.year < d2.year;
    }
    
    if (d1.month != d2.month)
    {
        return d1.month < d2.month;
    }

    return d1.day < d2.day;

}

// Return True if d1 is before d2
bool compare_date(const int year_value1, const int year_value2, const int month_value1, const int month_value2, const int day_value1, const int day_value2)
{
    if (year_value1 != year_value2)
    {
        return year_value1 < year_value2;
    }

    if (month_value1 != month_value2)
    {
        return month_value1 < month_value2;
    }

    return day_value1 < day_value2;
}

