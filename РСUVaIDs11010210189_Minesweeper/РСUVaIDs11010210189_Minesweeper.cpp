
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>      // std::setw
static const int Ship = 8;
enum myMode
{
	App,
	Out,
	Finish
};
void ViewTest(int**, int, int);
void Print(int** data, int x, int y);
void InitArrayByZero(int** data, int x, int y)
{
	for (size_t j = 0; j < y; j++)
	{
		for (size_t i = 0; i < x; i++)
		{
			data[j][i] = 0;
		}
	}

}

void PutMinesByRandom(int** data, int mine, int x, int y)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distribX(1, x);
	std::uniform_int_distribution<> distribY(1, y);

	for (size_t i = 0; i < mine; i++)
	{
		data[distribY(gen)][distribX(gen)] = Ship;
	}

}

void Border(int** data, int x, int y)
{
	for (size_t j = 0; j < y; j++)
	{
		for (size_t i = 0; i < x; i++)
		{
			if (data[j][i] == Ship)
			{
				if (data[j - 1][i - 1] != Ship)
					data[j - 1][i - 1] += 1;

				if (data[j - 1][i] != Ship)
					data[j - 1][i] += 1;

				if (data[j - 1][i + 1] != Ship)
					data[j - 1][i + 1] += 1;

				if (data[j][i - 1] != Ship)
					data[j][i - 1] += 1;

				if (data[j][i + 1] != Ship)
					data[j][i + 1] += 1;

				if (data[j + 1][i - 1] != Ship)
					data[j + 1][i - 1] += 1;

				if (data[j + 1][i] != Ship)
					data[j + 1][i] += 1;

				if (data[j + 1][i + 1] != Ship)
					data[j + 1][i + 1] += 1;
			}
		}
	}


}

void ViewTest(int** data, int x, int y)
{
	std::cout << "////////////////////////////////" << std::endl;
	for (size_t j = 0; j < y; j++)
	{
		for (size_t i = 0; i < x; i++)
		{
			std::cout << data[j][i];
		}
		std::cout << std::endl;
	}
}

void Print(int** data, int x, int y)
{
	std::cout << "////////////////////////////////" << std::endl;
	std::cout << x - 2 << ' ' << y - 2 << std::endl;
	for (size_t j = 1; j < y - 1; j++)
	{
		for (size_t i = 1; i < x - 1; i++)
		{
			if (data[j][i] == Ship)
				std::cout << " *";
			else
				std::cout << " .";
		}
		std::cout << std::endl;
	}
}
void Save(const std::string& path, int** data, int x, int y, myMode my_mode)
{
	using namespace std;
	std::ofstream out;          // поток для записи

	switch (my_mode)
	{
	case App:
		out.open(path.c_str(), std::ios::app); // окрываем файл для записи
		if (out.is_open())
		{
			out << x - 2 << ' ' << y - 2 << endl;
			for (size_t j = 1; j < y - 1; j++)
			{
				for (size_t i = 1; i < x - 1; i++)
				{
					if (data[j][i] == Ship)
					{
						out << " *";
					}
					else
					{
						out << " .";
					}
				}
				out << endl;
			}
		}
		out.close();
		break;
	case Out:
		out.open(path.c_str(), std::ios::out); // окрываем файл для записи
		if (out.is_open())
		{
			out << x - 2 << ' ' << y - 2 << endl;
			for (size_t j = 1; j < y - 1; j++)
			{
				for (size_t i = 1; i < x - 1; i++)
				{
					if (data[j][i] == Ship)
					{
						out << " *";
					}
					else
					{
						out << " .";
					}
				}
				out << endl;
			}
		}
		out.close();
		break;
	case Finish:
		out.open(path.c_str(), std::ios::app); // окрываем файл для записи
		if (out.is_open())
		{
			out << 0 << std::endl;
		}
		out.close();
		break;
	default:
		break;
	}

}

void LoadAndSave()
{
	int _x, _y, offsetField = 0;

	std::ifstream infile("Field3.txt");
	std::stringstream header_stream;
	header_stream << infile.rdbuf();

	while (true)
	{
		header_stream.seekg(offsetField, std::ios::beg);


		header_stream >> _x >> _y;
		if (_x == 0)
		{
			break;
		}
		int offset = header_stream.tellg();
		_x += 2;
		_y += 2;



		//create dyn array data
		int** data = new int* [_y];
		for (int i = 0; i < _y; i++)
		{
			data[i] = new int[_x];
		}
		InitArrayByZero(data, _x, _y);

		for (size_t j = 1; j < _y - 1; j++)
		{
			for (size_t i = 1; i < _x - 1; i++)
			{
				char c;
				header_stream >> std::ws >> c;

				if (c == '*')
				{
					data[j][i] = Ship;
				}
				else
				{
					data[j][i] = 0;
				}

			}

		}
		offsetField = header_stream.tellg();

		ViewTest(data, _x, _y);

		Border(data, _x, _y);

		ViewTest(data, _x, _y);





		header_stream.seekg(offset, std::ios::beg);
		std::ofstream out;          // поток для записи
		out.open("Field2.txt", std::ios::app); // окрываем файл для записи
		if (out.is_open())
		{
			out << _x - 2 << ' ' << _y - 2 << std::setw(20) << "Field" << std::endl;
			for (size_t j = 1; j < _y - 1; j++)
			{
				std::string line;
				std::getline(header_stream >> std::ws, line);
				out << line << std::setw(10);

				for (size_t i = 1; i < _x - 1; i++)
				{
					if (data[j][i] == Ship)
						out << '*';
					else
						out << data[j][i];
				}
				out << std::endl;
			}
		}

		out.close();
		//delete dyn array data
		for (size_t i = 0; i < _y; i++)
		{
			delete[] data[i];
		}
	}

}
void SetMines()
{
	char ch = 't';
	while (true)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> distrib(5, 20);
		const int mines = distrib(gen);
		int x = distrib(gen);
		int _x = x + 2;
		int y = distrib(gen);
		int _y = y + 2;
		//create dyn array data
		int** data = new int* [_y];
		for (int i = 0; i < _y; i++)
		{
			data[i] = new int[_x];
		}

		InitArrayByZero(data, _x, _y);
		PutMinesByRandom(data, mines, x, y);
		Border(data, x, y);
		ViewTest(data, _x, _y);
		
		std::cout << "Put more mines push (c Enter), clean push t, other way push (q) \n";
		std::cin >> ch;
		if (ch == 't')
			Save("Field3.txt", data, _x, _y, Out);
		if (ch == 'q')
		{
			Save("Field3.txt", data, _x, _y, Finish);
			break;
		}
		if(ch=='c')
			Save("Field3.txt", data, _x, _y, App);
		//delete dyn array data
		for (size_t i = 0; i < _y; i++)
		{
			delete[] data[i];
		}


	}

}
void GetMines()
{
	LoadAndSave();
}
int main()
{

	char ch;
	while (true)
	{
		std::cout << "Set Mines push (s), get mines push (g) exit push q" << std::endl;
		std::cin >> ch;
		if (ch == 'q')
			break;
		switch (ch)
		{
		case 's':
			SetMines();
			break;
		case 'g':
			GetMines();
			break;
		default:
			break;
		}


	}
	//SetMines(10, 10, 10);


	return 0;
}



//int main()
//{
//	int a[3][5] = { { 1, 1, 1, 1, 1 },
//					{ 2, 2, 2, 2, 2 }, 
//					{ 3, 3, 3, 3, 3 } };
//	for (size_t y = 0; y < 3; y++)
//	{
//		for (size_t x = 0; x < 5; x++)
//		{
//			cout << a[y][x];
//		}
//		cout << endl;
//	}
//	
//	return 0;
//}