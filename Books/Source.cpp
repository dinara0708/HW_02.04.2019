﻿#include"Books.h"


int cur_size = 0, buf_size = 0;
void add(Book*&bs, Book el) {
	if (buf_size == 0)
	{
		buf_size = 4;
		bs = new Book[buf_size];
	}
	else
	{
		if (cur_size == buf_size)
		{
			buf_size *= 2;
			Book*tmp1 = new Book[buf_size];
			for (int i = 0; i < cur_size; i++)
				tmp1[i] = bs[i];
			delete[] bs;
			bs = tmp1;
		}
	}
	bs[cur_size++] = el;
}

int main() {
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream in_file("books.txt");
	Book *bs = 0;
	Book tmp;
	char str[100];
	int y, p;
	if (!in_file)
		cerr << "File open error" << endl;
	else
	{
		while (!in_file.eof())// если текст в файле русский, то обязательно кодировку сделать 1251 при сохранении
		{
			in_file.getline(str, 50, '#'); //кол-во максимальных символов строго по массивам в классе!!! если там 50, нельзя считать 100
			tmp.set_author(str);

			in_file.getline(str, 100, '#'); //кол-во максимальных символов строго по массивам в классе!!!
			tmp.set_name(str);

			in_file.getline(str, 50, '#'); //кол-во максимальных символов строго по массивам в классе!!! если там 50, нельзя считать 100
			tmp.set_publisher(str);

			in_file >> y >> p;
			in_file.ignore();//потому что при следующей итерации нужно прервать поток
			tmp.set_year(y);
			tmp.set_pages(p);

			add(bs, tmp);

		}
		//cout << cur_size << endl;
		int n;
		cout << "Enter the earliest year:" << endl;
		cin >> n;
		for (int i = 0; i < cur_size; i++)
			if (bs[i].by_year(n))
				bs[i].print();
		cout << endl;

		cout << "Enter an author's full name:" << endl;
		cin.ignore();
		cin.getline(str, 50);
		for (int i = 0; i < cur_size; i++)
			if (bs[i].by_author(str))
				bs[i].print();
		cout << endl;

		cout << "Enter needed publishing house:" << endl;
		//cin.ignore();
		cin.getline(str, 50);
		for (int i = 0; i < cur_size; i++)
			if (bs[i].by_publisher(str))//после # сразу считается следующая строка, т.е. в txt файле нужно убирать пробелы между # строками
				bs[i].print();
		cout << endl;
	}
	system("pause");
}