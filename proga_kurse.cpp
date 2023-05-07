#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include<stdlib.h>
#include <string.h>
#include <Windows.h>
#define N 50

// основная структура
struct house_struct {
	char street[N];
	int house_number;
	int year_of_commissioning;// год сдачи в эксплучацию
	int floor_number;//кол-во этажей
	int apartment_number;// кол-во квартир
	double living_area;
	double total_area;
} house;

int check_int(int from, int to);// проверка ввода целых чисел (от; до] 3ghg 3.4
int input_and_adjustment(char n[]);//ввод и корректировка БД
int create_file_and_input(char n[]);//созданиефайла и ввод данных в него
int f_name(char n[]);// проверка ввода названия файла
int inputt(char n[], int k);//ввод
int check_street(char n[], int k);//проверка ввода строки
double check_double(double from, double to);//проверка ввода вещественного числа
int existing_file(char n[]);//выбор уже существующего файлв
int db_delete();//удаление файла
int output(char n[], int k);//вывод
int  delete_fields(char n[]);//удаление данных
int correct(char n[]);//корректировка данных
int reqq(char n[]);//запрос


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char file_name[N] = "-"; int nf=0;
	while (true) {
		system("cls");
		puts("             Программное обеспечение для ведения списка домов управляющей компании\n");
		puts("                                     Выберите функцию\n");
		puts("      1. Ввод и корректировка базы данных\n      2. Вывод содержимого базы данных\n      3. Запрос по домам\n      4. Выход из программы\n");
		puts("Выберите пункт:");
		do {
			switch (check_int(0, 4)) {
				nf = 0;
			case 1: input_and_adjustment(file_name); break;
			case 2: if (strcmp(file_name, "-") == 0) { puts("\nНеобходимо выбрать файл!"); nf = 1; }
				  else output(file_name, 1);
				break;
			case 3:if (strcmp(file_name, "-") == 0) { puts("\nНеобходимо выбрать файл!"); nf = 1; }
				  else reqq(file_name);
				break;
			case 4: return 0;
			}
		} while (nf == 1);
	}
}
//запрос
int reqq(char n[]){
	system("cls");
	FILE* fp; int id; char buf[100];long size; 
	struct request {
		char street[N];
		int house_number;
		int year_of_commissioning;
		int floor_number;
		int apartment_number;
		double living_area;
		double total_area;
	} req;
	if (!(fp = fopen(n, "r"))) { puts("ошибка при открытии файла для чтения"); return 1; }
	id = 0;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	while (size > 89L) {
		size -= 89L;
		id++;
	}
	do {
		output(n,2);
		printf("Введите улицу или '-' для пропуска:"); check_street(req.street,1);
		printf("\nВведите номер дома или 0 для пропуска:"); req.house_number = check_int(-1, 1000);
		printf("\nВведите год сдачи в эксплуатацию или 0 для пропуска:");
		do {
			req.year_of_commissioning = check_int(-1, 2050);
			if (req.year_of_commissioning != 0 && req.year_of_commissioning < 1900) puts("ошибка");
		} while (req.year_of_commissioning != 0 && req.year_of_commissioning < 1900);
		printf("\nВведите количество этажей или 0 для пропуска:"); req.floor_number = check_int(-1, 100);
		printf("\nВведите количество квартир или 0 для пропуска:"); req.apartment_number = check_int(-1, 5000);
		printf("\nВведите жилую площадь дома или 0 для пропуска:"); req.living_area = check_double(-1, 1000000);
		printf("\nВведите общую площадь дома или 0 для пропуска:"); req.total_area = check_double(-1, 1000000); puts(" ");
		fseek(fp, 0L, SEEK_SET);
		fgets(buf, 91, fp);
		printf("|№ %s", buf);
		for (int i = 1; i < id; i++) {
			fscanf(fp, "%20s%9d%5d%14d%15d%12lf%12lf\n", house.street, &house.house_number, &house.year_of_commissioning, &house.floor_number, &house.apartment_number, &house.living_area, &house.total_area);
			if ((strcmp(house.street, req.street) == 0)|| (strcmp("-", req.street) == 0)) {
				if ((house.house_number == req.house_number)|| req.house_number==0){
					if ((house.year_of_commissioning == req.year_of_commissioning)|| req.year_of_commissioning==0){
						if ((house.floor_number == req.floor_number)|| req.floor_number==0){
							if ((house.apartment_number == req.apartment_number)|| req.apartment_number==0){
								if ((house.living_area<req.living_area + 0.001 && house.living_area > req.living_area - 0.001) || (req.living_area<house.living_area + 0.001 && req.living_area > house.living_area - 0.001)||(req.living_area<0.001&& req.living_area>-0,001)|| req.living_area == house.living_area|| req.living_area==0) {
									if ((house.total_area<req.total_area + 0.001 && house.total_area > req.total_area - 0.001) || (req.total_area<house.total_area + 0.001 && req.total_area > house.total_area - 0.001)|| (req.total_area<0.001 && req.total_area>-0, 001)|| req.total_area < house.total_area|| req.total_area==0) {

										printf("%2d %-20.20s%9d%5d%14d%15d%12.2lf%12.2lf\n", i, house.street, house.house_number, house.year_of_commissioning, house.floor_number, house.apartment_number, house.living_area, house.total_area);
									}

								}
							}
						}
					}
				}
			}
		}
		printf("\nЕсли хотите завершить запрос, введите '#'");
	}while(getchar()!='#');
	return 0;
}
//ввод 
int output(char n[], int k) {
	if (k == 1)system("cls");
	FILE* fp; int id = 1; char buf[100];
	if (!(fp = fopen(n, "r"))) { puts("ошибка при открытии файла для чтения"); return 1; }
	
	fgets(buf, 91, fp);
	printf("|№ %s", buf);
	while (fgets(buf, 89, fp) != NULL) { printf("%2d %s",id++, buf); }
	fclose(fp);
	if (k == 1) { puts("Для продолжения нажмите любую клавишу..."); getchar(); }
	return 0;
}
//проверка целых чисел при вводе (от;до]
int check_int(int from, int to) {
	int res, f;
	char ch, ch1;
	do {
		while ((scanf("%d", &res) != 1))
		{ //Ошибка ввода. Надо очистить входной поток от "не числа" 
			while (getchar() != '\n');
			printf("ошибка\n");
		}
		f = 0;
		if (res <= from || res > to) {
			printf("ошибка\n");
		}
		ch = getchar();
		if (ch != '\n' && ch != ' ') {
			puts("ошибка");
			f = 1;
			while (getchar() != '\n');
		}
		else if (ch == ' ') {
			do {
				ch1 = getchar();
				if (ch1 != ' ' && ch1 != '\n') {
					f = 1;
					puts("ошибка.");
					break;
				}
			} while (ch1 != '\n');
		}
	} while (((res <= from || res > to || f == 1)));
	return res;
}
//ввод и корректировка БД

int input_and_adjustment(char n[]) {
	int nf=0;
	while (true) {
		system("cls");
		puts("                                     Выберите функцию\n");
		puts("      1. Использовать существующий файл\n      2. Создание нового файла и ввод\n      3. Корректировка полей\n      4. Добавление полей\n      5. Удаление полей\n      6. Удаление существующей базы данных\n      7. Вернуться в главное меню\n");
		puts("Выберите пункт:");
		do {
			nf = 0;
			switch (check_int(0, 7)) {
			case 1: existing_file(n); break;
			case 2: create_file_and_input(n); break;
			case 3:if (strcmp(n, "-") == 0) {puts("\nНеобходимо выбрать файл!"); nf = 1;}
				  else correct(n);
				break;
			case 4: if (strcmp(n, "-") == 0) { puts("\nНеобходимо выбрать файл!"); nf = 1; }
				  else inputt(n, 2);
				break;
			case 5: if (strcmp(n, "-") == 0) { puts("\nНеобходимо выбрать файл!"); nf = 1; }
				  else delete_fields(n);
				break;
			case 6: db_delete();  break;
			case 7: return 0;
			}
		} while (nf !=0);
	}
}

//корректировка полей
int correct(char n[]) {
	FILE* fp,*fp2; long size; int id,str,punc=0; char buf[100];
 do{
	 if (!(fp = fopen(n, "r"))) { puts("ошибка при открытии файла для чтения"); return 1; }
		if ((fp2 = fopen("-.txt", "r"))) {
			puts("На вашем устройстве уже имеется файл с именем \"-.txt\"(промежуточный файл в программе).Возможна потеря данных.Для отмены действий введите #\n");
			fclose(fp2);
			if (getchar() == '#') return 2;
		}
		id = 0;
		fseek(fp, 0L, SEEK_END);
		size = ftell(fp);
		while (size > 89L) {
			size -= 89L;
			id++;
		}
		fseek(fp, 0L, SEEK_SET);
		if (!(fp2 = fopen("-.txt", "w"))) { puts("ошибка при открытии промежуточного файла для записи"); return 3; }
		do {
			system("cls");
			output(n, 2);
			printf("Введите 0 для выхода или номер строки:");

			str = check_int(-1, id - 1);
			if (str != 0) {
				puts("              Пункты для редактирования\n");
				puts("1. Улица\n2. Номер дома\n3. Год\n4. Количество этажей\n5. Количество квартир\n6. Общая жилая площадь\n7. Общая площадь дома\n");
				printf("Введите 0 для выхода или номер пункта:");
				punc = check_int(-1, 7);
			}
		} while (punc==0&&str!=0);
		if (str != 0 && punc!=0) {
			fgets(buf, 91, fp);
			fputs(buf, fp2);//первая строка с заголовками
			for (int i = 1; i < id; i++) {
				if (i != str) {
					fgets(buf, 89, fp);
					fputs(buf, fp2);
				}//дошли до строки которую нажали
				else {

						fscanf(fp, "%-20.20s%9d%5d%14d%15d%12.2lf%12.2lf\n", house.street, &house.house_number, &house.year_of_commissioning, &house.floor_number, &house.apartment_number, &house.living_area, &house.total_area);
						//intf("%-20.20s%9d%5d%14d%15d%12.2lf%12.2lf\n", house.street, house.house_number, house.year_of_commissioning, house.floor_number, house.apartment_number, house.living_area, house.total_area);
						switch (punc) {
						case 1:printf("Введите название улицы:"); check_street(house.street,2); break;
						case 2:printf("Введите номер дома:"); house.house_number = check_int(0, 1000); break;
						case 3:printf("Введите год сдачи в эксплуатацию:"); house.year_of_commissioning = check_int(1899, 2050); break;
						case 4:printf("Введите количество этажей:"); house.floor_number = check_int(0, 100); break;
						case 5:printf("Введите количество квартир:"); house.apartment_number = check_int(0, 5000); break;
						case 6:printf("Введите общую жилую площадь:"); house.living_area = check_double(1, 1000000); break;
						case 7:printf("Введите общую площадь дома:"); house.total_area = check_double(1, 1000000); break;
						}
						fprintf(fp2, "%-20.20s%9d%5d%14d%15d%12.2lf%12.2lf\n", house.street, house.house_number, house.year_of_commissioning, house.floor_number, house.apartment_number, house.living_area, house.total_area);
				}
			}
			fclose(fp); fclose(fp2);
			remove(n);
			rename("-.txt", n);

		}
		
	} while (str != 0);
	

	fclose(fp); fclose(fp2); remove("-.txt");
	return 0;
}
//удаление полей
int delete_fields(char n[]) {
	system("cls");
	 int id = 0, str; long size; char buf[100];
    do{
		FILE* fp, *fp2;
		if (!(fp = fopen(n, "r"))) { puts("ошибка при открытии файла для чтения"); return 1; }

		if ((fp2=fopen("-.txt", "r"))) {
			puts("На вашем устройстве уже имеется файл с именем \"-.txt\"(промежуточный файл в программе).Возможна потеря данных.Для отмены действий введите #\n");
			fclose(fp2);
			if (getchar() == '#') return 2;
		}
		if (!(fp2 = fopen("-.txt", "w"))) { puts("ошибка при открытии промежуточного файла для записи"); return 3; }
		output(n, 2);
		//подсчёт количества символов вообще чтобы можно было проверить на правильность ввод номера строки
		fseek(fp, 0L, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		while (size > 89L) {
			size -= 89L;
			id++;
		}
		puts("Введите 0 или номер строки, которую нужно удалить");
		str = check_int(-1, id - 1);
		if (str != 0) {
			fgets(buf, 91, fp);
			fputs(buf, fp2);//первая строка с заголовками
			for (int i = 1; i < id; i++) {
				if (i != str) {
					fgets(buf, 89, fp);
					fputs(buf, fp2);
				}
				else {
					fseek(fp, (long)(91+(89 * i)), SEEK_SET);
				}
			}
		}
		fclose(fp);fclose(fp2);
		remove(n);
		rename("-.txt", n);
		//getchar();
	} while (str != 0);
	return 0;
}
//удаление бд
int db_delete() {
	system("cls");
	puts("Введите название файла для удаления:");
	char n[N];
	if (f_name(n)) return 1;
	if (remove(n)) {
		puts("ошибка при удалении файла"); return 2;
	}//ошибка при удалении
	puts("Файл успешно удалён!\nДля продолжения нажмите любую клавишу...");
	getchar(); return 0;
}
//выбор уже существующего файла:
int existing_file(char n[]) {
	system("cls");
	FILE* fp;
	puts("Название файла вводится по образцу, например \"1.txt\"\nДля выхода из функции введите \"-\"\n");
	do {
		if (f_name(n)) return 1;//ввод название и формат файла 1-если введено-
		fp = fopen(n, "r"); /* открытие файла для чтения */
		if (fp == NULL) {
			puts("файла с таким именем ещё не существует!");
		}
	} while (fp == NULL);
	fclose(fp);
	puts("Название принято!");
	puts("Для продолжения нажмите любую клавишу...");
	getchar();
}
//создание и ввод нового файла с нуля
int create_file_and_input(char n[]) {
	system("cls");
	FILE* fpp;
	puts("Название файла вводится по образцу, например \"1.txt\"\nДля выхода из функции введите \"-\"\n");
	do {
		if (f_name(n)) return 1;//ввод название и формат файла 1-если введено-
		fpp = fopen(n, "r"); /* открытие файла для чтения */
		if (fpp != NULL) {
			puts("файл с таким именем уже существует!"); fclose(fpp);
		}
	} while (fpp != NULL);
	inputt(n, 1);
	return 0;
}
//проверка: название и формат файла
int f_name(char n[]) {
	char help[N]; strcpy(help, n);
	char rev[N]; int check;
	do {
		scanf("%s", n);
		while (getchar() != '\n');
		check = 0;
		if (strcmp(n, "-.txt")==0) { puts("ошибка"); check = 1; }
		strcpy(rev, n); _strrev(rev);
		if (strcmp(n, "-") == 0) { strcmp(n, help); return 1; }
		else if (_stricmp(n, "CON.txt") == 0 || _stricmp(n, "PRN.txt") == 0 || _stricmp(n, "AUX.txt") == 0 || _stricmp(n, "NUL.txt") == 0) {// || stricmp(n, "COM1.txt") == 0 || stricmp(n, "COM2.txt") == 0 || stricmp(n, "COM3.txt") == 0 || stricmp(n, "COM4.txt") == 0 || stricmp(n, "COM5.txt") == 0 || stricmp(n, "COM6") == 0 || stricmp(n, "COM7") == 0 || stricmp(n, "COM8") == 0 || stricmp(n, "COM9") == 0 || stricmp(n, "LPT1") == 0 || stricmp(n, "LPT2") == 0 || stricmp(n, "LPT3") == 0 || stricmp(n, "LPT4") == 0 || stricmp(n, "LPT5") == 0 || stricmp(n, "LPT6") == 0 || stricmp(n, "LPT7") == 0 || stricmp(n, "LPT8") == 0 || stricmp(n, "LPT9") == 0) {
			puts("ошибка"); check = 1;
		}
		else if (strlen(n) == 7 && _strnicmp(n, "COM", 3) == 0 && '1' <= n[3] && n[3] <= '9') {
			puts("ошибка"); check = 1;
		}
		else if (strlen(n) == 7 && _strnicmp(n, "LPT", 3) == 0 && '1' <= n[3] && n[3] <= '9') {
			puts("ошибка"); check = 1;
		}
		else if (strpbrk(n, "~#%&*{}\\:<>?/+|\" ")) {
			puts("ошибка"); check = 1;
		}
		else if (strncmp(rev, "txt.", 4) != 0) {
			puts("ошибка"); check = 1;
		}
		else if (check == 0)  return 0;
	} while (check == 1);
}
//ввод данных в файл
int inputt(char n[], int k) {
	system("cls");
	FILE* fp; 
	if (k == 1)fp = fopen(n, "w");
	else fp = fopen(n, "a");
	if (fp == NULL) { puts("ошибка при открытии файла для записи"); return 1; };
	puts("Введите данные:     ");
	puts("            Введите данные по следующему образцу:");
	puts("Улица: указывать с большой буквы\nНомер дома: [1;1000]\nГод сдачи в эксплуатацию: [1900;2050]\nКоличество этажей: [1;100]\nКоличество квартир: [1;5000]\nОбщая жилая площадь: [1;1000000], при вводе вещественного отделять целую часть от дробной точкой\nОбщая площадь дома: [1;1000000], при вводе вещественного отделять целую часть от дробной точкой\n");
	puts("Например:  Светлая, 7 2018 9 36 1020 2000\n");
	if (k == 1) {fputs("|Улица               |ном.дома|год |кол-во этажей|кол-во квартир|общ.жил.пл.|общ.пл.дома|\n", fp);}
	do {
		puts("Введите улицу:   ");
		check_street(house.street,2);
		puts("Введите номер дома:   ");
		house.house_number = check_int(0, 1000);
		puts("Введите год сдачи в эксплуатацию:   ");
		house.year_of_commissioning = check_int(1899, 2050);
		puts("Введите количество этажей:   ");
		house.floor_number = check_int(0, 100);
		puts("Введите количество квартир:   ");
		house.apartment_number = check_int(0, 5000);
		puts("Введите общую жилую площадь:   ");
		house.living_area = check_double(1, 1000000);
		puts("Введите общую площадь дома:   ");
		house.total_area = check_double(1, 1000000);
		//printf( "В БД ВНЕСЕНО:%-20.20s%5d%5d%5d%5d%10.2lf%10.2lf\n", house.street, house.house_number, house.year_of_commissioning, house.floor_number, house.apartment_number, house.living_area, house.total_area);
		puts("Данные сохранены!");
		fprintf(fp, "%-20.20s%9d%5d%14d%15d%12.2lf%12.2lf\n", house.street, house.house_number, house.year_of_commissioning, house.floor_number, house.apartment_number, house.living_area, house.total_area);
		puts("Если хотите закончить ввод данных, нажмите '#'");
	} while (getchar() != '#');
	fclose(fp);
	return 0;
}

//проверка правильности ввода названия улицы
int check_street(char n[], int q) {
	int check;
	do {
		check = 0;
		scanf("%20s", n);
		if (q == 1) {
			if (strcmp(n, "-") == 0) {
				while (getchar() != '\n');
				return 0;
			}
		}
		if (!((n[0] >= 'A' && n[0] <= 'Z') || ((n[0] >= 'А' && n[0] <= 'Я') || n[0] == 'Ё') || (n[0] >= '0' && n[0] <= '9'))) { puts("ошибка"); check = 1; }

		for (int i = 1; (i < strlen(n)) && check != 1; i++) {
			if (!((n[i] == ' ' || (n[i] >= '0' && n[i] <= '9') || n[i] == '-' || (n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'а' && n[i] <= 'я') || n[i] == 'ё'))) {
				puts("ошибка"); check = 1;
			}
		}
	} while (check != 0);
	while (getchar() != '\n');
	return 0;
}
//проверка при вводе вещественного числа погрешность 0.1
double check_double(double from, double to) {
	double res; int f; char ch, ch1;
	do {
		while ((scanf("%lf", &res) != 1))
		{ //Ошибка ввода. Надо очистить входной поток от "не числа" 
			while (getchar() != '\n');
			printf("ошибка.\n");
		}
		f = 0;
		if (res<from || res>to ) {
			printf("ошибка.\n");
		}
		ch = getchar();
		if (ch != '\n' && ch != ' ') {
			puts("ошибка.");
			f = 1;
			while (getchar() != '\n');
		}
		else if (ch == ' ') {
			do {
				ch1 = getchar();
				if (ch1 != ' ' && ch1 != '\n') {
					f = 1;
					puts("ошибка.");
					break;
				}
			} while (ch1 != '\n');
		}
	} while ((res<from || res>to) || f == 1);
	return res;
}
