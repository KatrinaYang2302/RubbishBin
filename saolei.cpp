#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
using namespace std;

class saolei{
private:
	bool **map;
	int **zwls;
	bool **qizi;
	bool **wkl;
	int row, col, gs, wkgs;
	int qzgs;
	const static int GUALE = -1, MEIGUA = 0, FEIFACAOZUO = 1;
	const static char MEIWAKAI = '*';
	const static char WAKAILE = ' ';
	const static char QIZI = 'Q';
	const static char LEI = 'X';
	const static int ROW = 10, COL = 14;
	const static int EASY = 16, MID = 24, HARD = 32;
	int fx[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{1,-1},{0,1},{1,1},{1,0}};
public:
	saolei(): gs(0), qzgs(0), wkgs(0){
		row = ROW;
		col = COL;
		wkl = new bool*[row];
		for(int i = 0; i < row; i++){
			wkl[i] = new bool[col];
		}
		map = new bool*[row];
		for(int i = 0; i < row; i++){
			map[i] = new bool[col];
		}
		qizi = new bool*[row];
		for(int i = 0; i < row; i++){
			qizi[i] = new bool[col];
		}
		zwls = new int*[row];
		for(int i = 0; i < row; i++){
			zwls[i] = new int[col];
		}
	}

	~saolei(){
		for(int i = 0; i < row; i++){
			delete [] map[i];
		}
		delete [] map;
		for(int i = 0; i < row; i++){
			delete [] zwls[i];
		}
		delete [] zwls;
		for(int i = 0; i < row; i++){
			delete [] qizi[i];
		}
		delete [] qizi;
		for(int i = 0; i < row; i++){
			delete [] wkl[i];
		}
		delete [] wkl;
	}
	void initialize();
	void generateLei();
	void updateLei(int,int);
	bool inBound(int,int);
	int wa(int, int);
	int fqz(int, int);
	void dfs(int, int);
	int qxqz(int, int);
	int caozuo(char, int, int);
	void print();
	void printLei();
	void sznd();
	void play();
};

bool saolei::inBound(int row, int col){
	return row >= 0 && row < this->row && col >= 0 && col < this->col;
}

void saolei::updateLei(int row, int col){
	map[row][col] = 1;
	for(int i = 0; i < 8; i++){
		int x = row + fx[i][0], y = col + fx[i][1];
		if(inBound(x,y)){
			zwls[x][y]++;
		}
	}
}

void saolei::generateLei(){
	int *sz = new int[row * col];
	for(int i = 0; i < row*col; i++){
		sz[i] = i;
	}
	//cout << gs << endl;
	for(int i = 0; i < gs; i++){
		//生成gs个雷
		int curGs = row * col - i;
		int randomPos = rand() % curGs;
		updateLei(sz[randomPos]/col, sz[randomPos]%col);
		int tmp = sz[curGs-1];
		sz[curGs-1] = sz[randomPos];
		sz[randomPos] = tmp;
	}

	delete [] sz;
}

void saolei::sznd(){
	//cout << 1 << endl;
	cout << "nd: " << endl;
	int nd;
	cin >> nd;
	if(nd < 1) nd = 1;
	if(nd > 3) nd = 3;

	switch(nd){
	case 1:
		gs = EASY;
		break;
	case 2:
		gs = MID;
		break;
	case 3:
		gs = HARD;
		break;
	}
}

void saolei::initialize(){
	sznd();
	//cout << row << col << endl;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			map[i][j] = 0;
			qizi[i][j] = 0;
			zwls[i][j] = 0;
			wkl[i][j] = 0;
		}
	}
	generateLei();
}

void saolei::dfs(int row, int col){
	wkl[row][col] = 1;
	wkgs++;
	for(int i = 1; i < 8; i+=2){
		int x = row + fx[i][0], y = col + fx[i][1];
		if(inBound(x,y) && !map[x][y] && !wkl[x][y] && !zwls[x][y]){
			dfs(x,y);
		}
		else if(inBound(x,y) && !map[x][y] && !wkl[x][y]){
			wkgs++;
			wkl[x][y] = 1;
		}
	}
}

int saolei::wa(int row, int col){
	if(!inBound(row, col)) return FEIFACAOZUO;
	if(qizi[row][col]) return FEIFACAOZUO;
	if(map[row][col]) return GUALE;
	if(zwls[row][col]){
		wkgs++;
		wkl[row][col] = 1;
	}
	else dfs(row, col);
	return MEIGUA;
}

int saolei::fqz(int row, int col){
	if(!inBound(row, col)) return FEIFACAOZUO;
	if(wkl[row][col]) return FEIFACAOZUO;
	qzgs++;
	qizi[row][col] = 1;
	return MEIGUA;
}

int saolei::qxqz(int row, int col){
	if(!inBound(row, col)) return FEIFACAOZUO;
	if(!qizi[row][col]) return FEIFACAOZUO;
	qzgs--;
	qizi[row][col] = 0;
	return MEIGUA;
}

int saolei::caozuo(char cmd, int row, int col){
	//q: 放旗子
	//x: 取消旗子
	//w: 挖开
	if(cmd == 'q') return fqz(row, col);
	if(cmd == 'x') return qxqz(row, col);
	if(cmd == 'w') return wa(row, col);
	return FEIFACAOZUO;
}

void saolei::print(){
	cout << "  ";
	for(int i = 0; i < col; i++){
		if(i < 10) cout << i;
		else cout << (char)('A' + i - 10);
	}
	cout << endl;
	for(int i = 0; i < row; i++){
		if(i < 10) cout << i;
		else cout << (char)('A' + i - 10);
		cout << " ";
		for(int j = 0; j < col; j++){
			if(!wkl[i][j] && !qizi[i][j]) cout << MEIWAKAI;
			else if(!wkl[i][j]) cout << QIZI;
			else if(zwls[i][j]) cout << zwls[i][j];
			else cout << WAKAILE;
		}
		cout << endl;
	}
	cout << "还有" << gs-qzgs << "个雷！" << endl << endl;
}

void saolei::printLei(){
	cout << "  ";
	for(int i = 0; i < col; i++){
		if(i < 10) cout << i;
		else cout << (char)('A' + i - 10);
	}
	cout << endl;
	for(int i = 0; i < row; i++){
		if(i < 10) cout << i;
		else cout << (char)('A' + i - 10);
		cout << " ";
		for(int j = 0; j < col; j++){
			if(map[i][j]) cout << LEI;
			else cout << WAKAILE;
		}
		cout << endl;
	}
	cout << "挂了！\n\n" << endl;
}

void saolei::play(){
	initialize();
	//cout << 1 << endl;
	print();
	//cout << 1 << endl;
	while(wkgs < row * col - gs || qzgs != gs){
		char cmd;
		int h, l;
		//scanf("%s%d%d", cmd, &h, &l);
		//cout << cmd << h << l;
		cin >> cmd >> h >> l;
		int res = caozuo(cmd, h, l);
		if(res == GUALE){
			printLei();
			return;
		}
		else if(res == FEIFACAOZUO){
			cout << "此操作非法" << endl;
		}
		else{
			print();
		}
	}
	cout << "你挖开了所有的雷！\n" << endl;
}

int main() {
	srand(time(NULL));
	saolei *sl = new saolei();
	sl->play();
	return 0;
}
