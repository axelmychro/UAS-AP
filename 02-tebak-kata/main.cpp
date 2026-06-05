#include <iostream>
#include "lib_tebak_kata.h"
using namespace std;

void log(string msg)
{
		cout << " => " << msg << endl;
}
int main()
{
		/*
		 * INISIALISASI
		 */
		KataGame game;
		game.kata_asli = { "lompat",	"gaya",		  "tanaman",  "bibi",
						   "pencarian", "kesempatan", "hamparan", "bersyukur",
						   "asumsi",	"rahang",	  "pingsan",  "saksi",
						   "rekaman",	"narasumber", "simulasi" };

		//cout << time(0) << endl;
		string kata_rahasia = game.pilihKataAcak();

		for (int i = 0; i < kata_rahasia.size(); ++i)
				cout << "_";
		cout << endl;

		return 0;
}
