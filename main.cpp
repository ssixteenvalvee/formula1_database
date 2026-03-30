#include "Driver.h"
#include "Engine.h"
#include "Racecar.h"
#include "Team.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using std::cin, std::cout, std::endl, std::vector;
namespace fs = std::filesystem;
Driver d1("max_verstappen", 4, 22, 33);
Driver d2("kimi_antonelli", 0, 2, 2);

Team build_team() {
	Engine eng1("Honda", "V6", 1040);
	Racecar car1(eng1, "RB21");
	Team team1("red_bull", car1, d1, d2, 8, 88);
	return team1;
}

int main()
{
	fs::path basePath = "alldata";
	if (!fs::exists(basePath) || !fs::is_directory(basePath)) {
		cout << "Directory is not found. Do something.\n";
		return 0;
	}
	vector<string> seasons;
	for (const auto& dir : fs::directory_iterator(basePath)) {
		if (dir.is_directory()) {
			seasons.push_back(dir.path().filename().string());
		}
	}
	if (seasons.empty()) {
		cout << "There is no data" << endl;
		return 0;
	}
	cout << "Please, choose the number of the season:" << endl;
	int cnt = 1;
	for (auto& option : seasons) {
		cout << cnt << ". " << option << endl;
		cnt++;
	}

	/*после выбора сезона открывается поток на чтение для
	всех .txt файлов с информацией. Затем вся информация
	"разлетается по классам" и в конце объединяется в общую
	структуру, для последующей модификации или просмотра.
	В конце, если data изменена, файл перезаписывается.
	Иначе просто закрывается.
	Это опуская тот факт, что ещё необходима куча способов
	взаимодействовать с полученной информацией.*/
	
	Team red_bull = build_team();
	red_bull.show_team();
	return 0;
}