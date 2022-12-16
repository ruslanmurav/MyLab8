#include <iostream>   
#include <cstdio>  
#include <string.h> 
#include <ctype.h> 
#include <Windows.h>  
#include <iomanip>  
#include <io.h>

using namespace std;

int convert_char_to_int(char* str)
{
    int result = 0;
    for (; *str != '\0'; str++)
    {
        result *= 10;
        result += *str - '0';
    }
    return result;
}

double convert_char_to_double(char* str)
{
    bool check = true;
    double result = 0;
    int i = 1;
    for (; *str != '\0'; str++)
    {
        if (*str == 46)
        {
            check = false;
            continue;
        }
        if (check)
        {
            result *= 10;
            result += *str - '0';
        }
        if (!check)
        {
            result += pow(0.1, i) * (*str - '0');
            i++;
        }
    }
    return result;
}


bool check_double(char arr[100])
{
    int  iMin = 0, iPoint = 0;
    bool proverka = false;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (int(arr[i]) < 48 && int(arr[i]) != 46 && int(arr[i]) != 45 ||
            int(arr[i]) > 57 && int(arr[i]) != 46 && int(arr[i]) != 45)
        {
            proverka = true;

        }
        if (int(arr[i] == 45))
        {
            iMin++;
        }
        if (int(arr[i]) == 48 && int(arr[i + 1]) != 46)
        {
            proverka = true;
        }
        if (int(arr[i]) == 46)
        {
            iPoint++;
        }
        if (iMin == 2 || iPoint == 2)
        {
            proverka = true;
        }
    }
    if (proverka) //несоответствующий тип данных  
    {

        return 0;
    }
    else
    {
        return 1;
    }
}

bool check_int(char arr[100])
{
    int iMin = 0;
    bool proverka = false;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (int(arr[i]) < 48 && int(arr[i]) != 45 ||
            int(arr[i]) > 57 && int(arr[i]) != 45)
        {
            proverka = true;
        }
        if (int(arr[i]) == 48 && int(arr[i + 1] != 46))
        {
            proverka = true;
        }
        if (int(arr[i] == 45))
        {
            iMin++;
        }
        if (iMin == 2)
        {
            proverka = true;
        }
    }
    if (proverka)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//---------------------------------------------
struct car {
    char car_brand[100];
    int release_date, volume, max_speed;
};
//-------------------------------------------
void create_binary_file(char* file_name)
{
    FILE* file;
    fopen_s(&file, file_name, "wb");
    if ((fopen_s(&file, file_name, "wb")) == 0)
    {
        cout << "Ошибка при создании!" << endl;
    }
    else
    {
        cout << "Файл успешно создан";
    }
    int fclose_s(FILE * file);
}

void write_binary_file(char* file_name)
{

    char amount_string[100];
    int amount;

    cout << "Введите число машин: ";
    cin >> amount_string;
    while (1)
    {
        if (!check_int(amount_string))
        {
            cout << "Вы ввели некорректный тип данных!";
            break;
        }
        amount = convert_char_to_int(amount_string);
        car* list;
        list = new car[amount];

        FILE* file;
        fopen_s(&file, file_name, "wb");
        if (file == 0)
        {
            cout << "Файл не был открыт";
            break;
        }
        for (int i = 0; i < amount; i++)
        {
            cout << "Введите характеристики " << i + 1 << "-ой машины " << endl;

            cout << "Введите марку машины: ";
            cin >> list[i].car_brand;

            cout << "Введите год выпуска: ";
            cin >> list[i].release_date;

            cout << "Введите объем двигателя: ";
            cin >> list[i].volume;

            cout << "Введите максимальную скорость: ";
            cin >> list[i].max_speed;
            cout << endl;
            if (file != 0)
            {
                fwrite(&list[i], sizeof(car), 1, file);

            }
        }

        if (file != 0)
        {
            fclose(file);
        }

        delete[]list;
        break;
    }
}

void read_binary_file(char* file_name)
{

    FILE* file;
    fopen_s(&file, file_name, "rb");
    if (file != 0)
    {

        cout << "Исходный список" << endl;
        cout << setw(20) << "Марка машины" << "\t" << setw(20) << "Дата выпуска" << "\t" << setw(20) << "Объем двигателя"
            << "\t" << setw(20) << "Максимальная скорость" << endl;
        int amount = _filelength(_fileno(file)) / sizeof(car);

        car* list;
        list = new car[amount];

        if (file != 0)
        {
            fread(list, sizeof(car), amount, file);

            for (int i = 0; i < amount; i++)
            {
                cout << setw(20) << list[i].car_brand << "\t" << setw(20) << list[i].release_date << "\t";
                cout << setw(20) << list[i].volume << "\t" << setw(20) << list[i].max_speed << endl;
            }
        }
        delete[] list;
        fclose(file);
    }
    else
    {
        cout << "Ошибка при работе с файлом!";
    }


}

void output_on_display(char* file_name)
{
    FILE* file;
    fopen_s(&file, file_name, "rb");
    if (file != 0)
    {
        car* list;

        char car_brand[100]{};
        int amount = _filelength(_fileno(file)) / sizeof(car);

        list = new car[amount];
        fread(list, sizeof(car), amount, file);

        car temporary;
        for (int i = 1; i < amount; i++)
        {
            if (list[i].max_speed > list[i - 1].max_speed)
            {
                temporary = list[i];
                list[i] = list[i - 1];
                list[i - 1] = temporary;
                i = 1;
            }
        }
        cout << endl << "Готовый список" << endl;
        cout << setw(20) << "Марка машины" << "\t" << setw(20) << "Дата выпуска" << "\t" << setw(20) << "Объем двигателя"
            << "\t" << setw(20) << "Максимальная скорость" << endl;
        for (int i = 0; i < amount; i++)
        {
            if (list[i].release_date > 2005)
            {
                cout << setw(20) << list[i].car_brand << "\t" << setw(20) << list[i].release_date << "\t";
                cout << setw(20) << list[i].volume << "\t" << setw(20) << list[i].max_speed << endl;
            }
        }
        delete[] list;
        fclose(file);

    }
    else
    {
        cout << "Ошибка при работе с файлом!";
    }
}

void output_on_fail(char* binary_file_name, char* file_name)
{
    int amount = 0;
    FILE* file_binary;
    fopen_s(&file_binary, binary_file_name, "rb");
    car* list = 0;
    if (file_binary != 0)
    {
        char car_brand[100]{};
        amount = _filelength(_fileno(file_binary)) / sizeof(car);
        list = new car[amount];
        fread(list, sizeof(car), amount, file_binary);

        car temporary;
        for (int i = 1; i < amount; i++)
        {
            if (list[i].max_speed > list[i - 1].max_speed)
            {
                temporary = list[i];
                list[i] = list[i - 1];
                list[i - 1] = temporary;
                i = 1;
            }
        }
        fclose(file_binary);
    }
    else
    {
        cout << "Ошибка при работе с файлом";
    }

    FILE* file_text;
    fopen_s(&file_text, file_name, "w");
    if (file_text != 0)
    {

        for (int i = 0; i < amount; i++)
        {
            if (list[i].release_date > 2005)
            {
                fprintf(file_text, "Марка машины: %s, дата выпуска: %d,", list[i].car_brand, list[i].release_date);
                fprintf(file_text, "обьем двигателя: %d,  максимальная скорость: %d\n", list[i].volume, list[i].max_speed);
            }

        }
        fclose(file_text);
    }
    else
    {
        cout << "Ошибка при работе с файлом";
    }
    delete[] list;

}


//--------------------------------------------
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    char binary_file_name[100]{ "binary_file.bin" }, file_name[100]{ "text_file.txt" };
    char string_menu[100]{}, text[100]{};
    int menu;
    while (1)
    {
        cout << "Ввеите действие:\n1. Создание бинарного файла \n2. Запись в бинарный файл ";
        cout << "\n3.Открытие файла и чтение из него \n4. Вывод результата на экран";
        cout << "\n5. Вывод результата в текстовый документ " << endl;
        cin.get(string_menu, 100);
        if (!check_int(string_menu))
        {
            cout << "Пункт меню может быть только целым числом";
            break;
        }
        else
        {
            menu = convert_char_to_int(string_menu);
            switch (menu)
            {
            case 1:
                create_binary_file(binary_file_name);
                break;
            case 2:
                write_binary_file(binary_file_name);
                break;
            case 3:
                read_binary_file(binary_file_name);
                break;
            case 4:
                output_on_display(binary_file_name);
                break;
            case 5:
                output_on_fail(binary_file_name, file_name);
                break;
            default:
                cout << "Нет такого пукта меню!";
                break;
            }
            break;
        }
    }

}

