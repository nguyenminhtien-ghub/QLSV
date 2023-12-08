#include <conio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>

enum STUDENT_KEY {
    CLASS_ID = '1',
    ID = '2',
    NAME = '3',
    DOB = '4',
    GPA = '5'
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
void selection_sort(const char key);
void bubble_sort(const char key);
void quicksort(const char key);
void _quicksort(std::vector<Student>& students, int low, int high, const char key);
int _partition_student_list(std::vector<Student>& students, int low, int high, const char key);
void mergesort(const char key);
void _mergesort(std::vector<Student>& students, int left, int right, const char key);
void _merge(std::vector<Student>& students, int left, int middle, int right, const char key);
bool compare_date(const Date d1, const Date d2);

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

    std::cout << "\n-***   ***   ***   ***   ***    " << table_title << "    ***   ***   ***   ***   ***-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    std::cout << "\n-| STT |  ma lop  | ma sinh vien |        ho va ten        | ngay sinh  | diem trung bing |-";
    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";
    
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

    std::cout << "\n-|-----|----------|--------------|-------------------------|------------|-----------------|-";

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
        switch (key_choice)
        {
        case STUDENT_KEY::CLASS_ID:
            table_title = "MENU | DS sinh vien theo lop";
        case STUDENT_KEY::ID:
            table_title = "MENU | DSSV theo ma sinhvien";
        case STUDENT_KEY::NAME:
            table_title = "MENU | DS sinh vien theo ten";
        case STUDENT_KEY::DOB:
            table_title = " MENU | DSSV theo ngay sinh ";
        case STUDENT_KEY::GPA:
            table_title = "    MENU | DSSV theo diem   ";
            std::cout << key_choice << "\n";
            break;
        default:
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

    list_students(table_title);
}

void search_students()
{
    char searched_key;
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
        searched_key = _getch();
        std::cin.ignore();
        switch (searched_key)
        {
        case '1':
        case '2':
        case '3':
            std::cout << searched_key;
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
    std::cout << " | " << std::setw(23) << std::left << name;
    std::cout << " | " << std::setw(2) << std::right << dob_day << "/" << std::setw(2) << dob_month << "/" << dob_year;
    std::cout << " | " << std::setw(15) << gpa << " |";
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
            if (key == STUDENT_KEY::CLASS_ID)
            {
                if (students[j].class_id < students[min_index].class_id)
                {
                    min_index = j;
                }
                continue;
            }

            if (key == STUDENT_KEY::ID)
            {
                if (students[j].student_id < students[min_index].student_id)
                {
                    min_index = j;
                }
                continue;
            }

            if (key == STUDENT_KEY::NAME)
            {
                if (students[j].name < students[min_index].name)
                {
                    min_index = j;
                }
                continue;
            }

            if (key == STUDENT_KEY::DOB)
            {
                if (compare_date(students[j].dob, students[min_index].dob))
                {
                    min_index = j;
                }
                continue;
            }
            
            if (key == STUDENT_KEY::GPA)
            {
                if (students[j].gpa < students[min_index].gpa)
                {
                    min_index = j;
                }
                continue;
            }
        }

        std::swap(students[i], students[min_index]);
    }

    save_student_list(students);

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
            if (key == STUDENT_KEY::CLASS_ID)
            {
                if (students[j].class_id > students[j + 1].class_id)
                {
                    std::swap(students[j], students[j + 1]);
                }
                continue;
            }
            if (key == STUDENT_KEY::ID)
            {
                if (students[j].student_id > students[j + 1].student_id)
                {
                    std::swap(students[j], students[j + 1]);
                }
                continue;
            }
            if (key == STUDENT_KEY::NAME)
            {
                if (students[j].name > students[j + 1].name)
                {
                    std::swap(students[j], students[j + 1]);
                }
                continue;
            }
            if (key == STUDENT_KEY::DOB)
            {
                if (compare_date(students[j + 1].dob, students[j].dob))
                {
                    std::swap(students[j], students[j + 1]);
                }
                continue;
            }
            if (key == STUDENT_KEY::GPA)
            {
                if (students[j].gpa > students[j + 1].gpa)
                {
                    std::swap(students[j], students[j + 1]);
                }
                continue;
            }

        }
    }
    
    save_student_list(students);
}

void quicksort(const char key)
{
    std::vector<Student> students;
    int low = 0;

    load_student_list(students);

    size_t high = students.size() - 1;
    _quicksort(students, low, high, key);

    save_student_list(students);

}

void _quicksort(std::vector<Student>& students, int low, int high, const char key)
{
    
    if (low < high)
    {
        int pivot_index = _partition_student_list(students, low, high, key);
        _quicksort(students, low, pivot_index - 1, key);
        _quicksort(students, pivot_index + 1, high, key);
    }
}


// Function to partition the list for quicksort
int _partition_student_list(std::vector<Student>& students, int low, int high, const char key)
{
    int i = low - 1;

    if (key == STUDENT_KEY::CLASS_ID)
    {
        std::string pivot = students[high].class_id;

        for (int j = low; j < high; j++)
        {
            if (students[j].class_id < pivot)
            {
                i++;
                std::swap(students[i], students[j]);
            }
        }

        std::swap(students[i + 1], students[high]);
        return i + 1;
    }
    else if (key == STUDENT_KEY::ID)
    {
        std::string pivot = students[high].student_id;

        for (int j = low; j < high; j++)
        {
            if (students[j].student_id < pivot)
            {
                i++;
                std::swap(students[i], students[j]);
            }
        }

        std::swap(students[i + 1], students[high]);
        return i + 1;

    }
    else if (key == STUDENT_KEY::NAME)
    {
        std::string pivot = students[high].name;

        for (int j = low; j < high; j++)
        {
            if (students[j].name < pivot)
            {
                i++;
                std::swap(students[i], students[j]);
            }
        }

        std::swap(students[i + 1], students[high]);
        return i + 1;
    }
    else if (key == STUDENT_KEY::DOB)
    {
        Date pivot = students[high].dob;

        for (int j = low; j < high; j++)
        {
            if (compare_date(students[j].dob, pivot))
            {
                i++;
                std::swap(students[i], students[j]);
            }
        }

        std::swap(students[i + 1], students[high]);
        return i + 1;
    }
    else
    {
        float pivot = students[high].gpa;

        for (int j = low; j < high; j++)
        {
            if (students[j].gpa < pivot)
            {
                i++;
                std::swap(students[i], students[j]);
            }
        }

        std::swap(students[i + 1], students[high]);
        return i + 1;
    }
}


void mergesort(const char key)
{
    std::vector<Student> students;

    load_student_list(students);

    _mergesort(students, 0, students.size() - 1, key);

    save_student_list(students);
}


void _mergesort(std::vector<Student>& students, int left, int right, const char key)
{
    if (left < right)
    {
        // avoids overflow
        int middle = left + (right - left) / 2;

        _mergesort(students, left, middle, key);
        _mergesort(students, middle + 1, right, key);

        _merge(students, left, middle, right, key);
    }
}

void _merge(std::vector<Student>& students, int left, int middle, int right, const char key)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    std::vector<Student> left_list{};
    std::vector<Student> right_list{};

    for (int i = 0; i < left_size; i++)
    {
        left_list.push_back(students[left + i]);
    }

    for (int i = 0; i < right_size; i++)
    {
        right_list.push_back(students[middle + i + 1]);
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < left_size
        && j < right_size)
    {
        if (key == STUDENT_KEY::CLASS_ID)
        {
            if (left_list[i].class_id <= right_list[j].class_id)
            {
                students[k] = left_list[i];
                i++;
            }
            else
            {
                students[k] = right_list[j];
                j++;
            }
            k++;
            continue;
        }

        if (key == STUDENT_KEY::ID)
        {
            if (left_list[i].student_id <= right_list[j].student_id)
            {
                students[k] = left_list[i];
                i++;
            }
            else
            {
                students[k] = right_list[j];
                j++;
            }
            k++;
            continue;
        }

        if (key == STUDENT_KEY::NAME)
        {
            if (left_list[i].name <= right_list[j].name)
            {
                students[k] = left_list[i];
                i++;
            }
            else
            {
                students[k] = right_list[j];
                j++;
            }
            k++;
            continue;
        }
        if (key == STUDENT_KEY::DOB)
        {
            if (compare_date(right_list[j].dob, left_list[i].dob) == false)
            {
                students[k] = left_list[i];
                i++;
            }
            else
            {
                students[k] = right_list[j];
                j++;
            }
            k++;
            continue;
        }
        if (key == STUDENT_KEY::GPA)
        {
            if (left_list[i].gpa <= right_list[j].gpa)
            {
                students[k] = left_list[i];
                i++;
            }
            else
            {
                students[k] = right_list[j];
                j++;
            }
            k++;
            continue;
        }

    }

    while (i < left_size)
    {
        students[k] = left_list[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        students[k] = right_list[j];
        j++;
        k++;
    }
}

// Return True if d1 is before d2
bool compare_date(const Date d1, const Date d2)
{
    if (d1.year < d2.year)
    {
        return true;
    }
    else if (d1.year > d2.year)
    {
        return false;
    }
    else
    {
        if (d1.month < d2.month)
        {
            return true;
        }
        else if(d1.month > d2.month)
        {
            return false;
        }
        else
        {
            if (d1.day < d2.day)
            {
                return true;
            }

            return false;
        }
    }
}


