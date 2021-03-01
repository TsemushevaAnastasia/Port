#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int main ()
{
	setlocale(LC_ALL, "Russian");

	ifstream fin("SHIPS.IN.txt");
	ofstream fout("SHIPS.OUT.txt");

	if (!fin.is_open())
		fout << "Error! Cannot open file!\n";
	else if (fin.peek() == EOF)
		fout << "File is empty!\n";
	else
	{
		unsigned short N;

		fin >> N;

		vector<string> queue;

		vector<pair<int, string>> port;

		port.resize(N);

		int first_empty = 1;

		while (!fin.eof())
		{
			int num;

			fin >> num;

			switch (num)
			{

			case 1:
			{
				string ship;
				getline(fin, ship);

				if (first_empty == 0)
				{
					queue.push_back(ship);
				}

				else
				{
					port[first_empty - 1].first = 1;

					port[first_empty - 1].second = ship;

					int i = first_empty - 1;

					first_empty = 0;

					for (; i < N; i++)
					{
						if (port[i].first == 0)
						{
							first_empty = i + 1;
							break;
						}
					}
				}
				break;
			}

			case 2:
			{
				int number;

				fin >> number;

				port[number - 1].first = 0;

				if (number < first_empty || first_empty == 0)
					first_empty = number;

				if (queue.size() != 0)
				{
					port[first_empty - 1].first = 1;

					port[first_empty - 1].second = queue[0];

					queue.erase(queue.begin());

					first_empty = 0;
				}
				break;
			}

			case 3:
			{
				fout << "Текущее состояние очереди на рейде:" << endl;

				if (queue.size())
				{
					for (auto x : queue)
					{
						fout << x << endl;
					}
				}
				else
				{
					fout << "Очередь пуста!" << endl;
				}

				break;
			}

			case 4:
			{
				fout << "Текущее состояние причалов:" << endl;

				for (int i = 0; i < N; i++)
				{
					fout <<i + 1;

					if (port[i].first == 1)
						fout << port[i].second << endl;

					else
						fout << " пусто" << endl;
				}
				break;
			}

			default:
				break;
			}
		}
	}

	return 0;
}