#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

int m, n;

struct pos{
	int x,y,g,prevX,prevY;
	double f,h;
	char val;
	bool checked;
	bool operator<(const pos& rhs) const{
        return f < rhs.f;
    }
};

int approximateDistance(int x1, int y1, int x2, int y2){
	// Euclidean approach
	// return sqrt(abs(x2-x1)*abs(x2-x1)+abs(y2-y1)*abs(y2-y1));
	
	// Manhattan approach
	return (abs(x2-x1)+abs(y2-y1));
}

void neighbour(pos grid[][100], pos curr, pos goal, std::priority_queue<pos>& openSet){
	// Cek 4 tetangga
	// hitung nilai f, g, h dan juga mencatat parent
	// Note : algoritma dapat diimprove dengan mengecek 8 tetangga (diagonal) juga
	if ((curr.x-1>=0) && (!grid[curr.x-1][curr.y].checked) && (grid[curr.x-1][curr.y].g==0) && (grid[curr.x-1][curr.y].val=='-')){
		grid[curr.x-1][curr.y].g=curr.g+1;
		grid[curr.x-1][curr.y].h=approximateDistance(curr.x-1,curr.y,goal.x,goal.y);
		grid[curr.x-1][curr.y].f=-1*(grid[curr.x-1][curr.y].g+grid[curr.x-1][curr.y].h);
		grid[curr.x-1][curr.y].prevX=curr.x;
		grid[curr.x-1][curr.y].prevY=curr.y;
		openSet.push(grid[curr.x-1][curr.y]);
	}
	if ((curr.y-1>=0) && (!grid[curr.x][curr.y-1].checked) && (grid[curr.x][curr.y-1].g==0) && (grid[curr.x][curr.y-1].val=='-')){
		grid[curr.x][curr.y-1].g=curr.g+1;
		grid[curr.x][curr.y-1].h=approximateDistance(curr.x,curr.y-1,goal.x,goal.y);
		grid[curr.x][curr.y-1].f=-1*(grid[curr.x][curr.y-1].g+grid[curr.x][curr.y-1].h);
		grid[curr.x][curr.y-1].prevX=curr.x;
		grid[curr.x][curr.y-1].prevY=curr.y;
		openSet.push(grid[curr.x][curr.y-1]);
	}
	if ((curr.x+1<m) && (!grid[curr.x+1][curr.y].checked) && (grid[curr.x+1][curr.y].g==0) && (grid[curr.x+1][curr.y].val=='-')){
		grid[curr.x+1][curr.y].g=curr.g+1;
		grid[curr.x+1][curr.y].h=approximateDistance(curr.x+1,curr.y,goal.x,goal.y);
		grid[curr.x+1][curr.y].f=-1*(grid[curr.x+1][curr.y].g+grid[curr.x+1][curr.y].h);
		grid[curr.x+1][curr.y].prevX=curr.x;
		grid[curr.x+1][curr.y].prevY=curr.y;
		openSet.push(grid[curr.x+1][curr.y]);
	}
	if ((curr.y+1<n) && (!grid[curr.x][curr.y+1].checked) && (grid[curr.x][curr.y+1].g==0) && (grid[curr.x][curr.y+1].val=='-')){
		grid[curr.x][curr.y+1].g=curr.g+1;
		grid[curr.x][curr.y+1].h=approximateDistance(curr.x,curr.y+1,goal.x,goal.y);
		grid[curr.x][curr.y+1].f=-1*(grid[curr.x][curr.y+1].g+grid[curr.x][curr.y+1].h);
		grid[curr.x][curr.y+1].prevX=curr.x;
		grid[curr.x][curr.y+1].prevY=curr.y;
		openSet.push(grid[curr.x][curr.y+1]);
	}
}

void makePath(pos grid[][100], int currX, int currY, pos start){
	// Backtrack
	if ((grid[currX][currY].prevX!=-1) || (grid[currX][currY].prevY!=-1)){
		grid[currX][currY].val='!';
		makePath(grid, grid[currX][currY].prevX, grid[currX][currY].prevY, start);
	}else{
		// Output
		for (int i=0;i<m;i++){
			for (int j=0;j<n;j++){
				std::cout << grid[i][j].val;
			}
			std::cout<<'\n';
		}
	}
}

void A_star(pos grid[100][100], pos start, pos goal, std::priority_queue<pos> openSet, bool& found){
	// Buat liat cara algoritmanya mikir, uncomment semua comment yang ad di fungsi ini
	// for (int i=0;i<m;i++){
		// for (int j=0;j<n;j++){
			// std::cout << grid[i][j].val;
		// }
		// std::cout<<'\n';
	// }
	// std::cout<<'\n';
	neighbour(grid, openSet.top(), goal, openSet);
	if (approximateDistance(openSet.top().x, openSet.top().y, goal.x, goal.y)-1>0.1){
		// grid[openSet.top().x][openSet.top().y].val='*';
		openSet.pop();
		while((!found) && (!openSet.empty())){
			A_star(grid, start, goal, openSet, found);
			openSet.pop();
		}
		if (!found){
			std::cout << "Tidak ada jalan\n";
			found=true;
		}
	}else{
		// grid[openSet.top().x][openSet.top().y].val='*';
		found=true;
		makePath(grid, openSet.top().x, openSet.top().y, start);
	}
}

int main(){
	int i=0, j, k;
	pos start, end, grid[100][100];
	std::ifstream file;
	std::priority_queue<pos> openSet;
	bool found=false;
	
	file.open("test2.txt");
	if (!file){
		std::cout << "Manual input\n";
		std::cin >> m >> n;
		// Input
		for (i=0;i<m;i++){
			for (j=0;j<n;j++){
				std::cin >> grid[i][j].val;
				grid[i][j].checked=false;
				if (grid[i][j].val=='1'){
					start.x=i;
					start.y=j;
				}else if (grid[i][j].val=='2'){
					end.x=i;
					end.y=j;
				}
			}
		}
	}else{
		file >> m >> n;
		// Input
		for (i=0;i<m;i++){
			for (j=0;j<n;j++){
				file >> grid[i][j].val;
				grid[i][j].checked=false;
				grid[i][j].g=0;
				if (grid[i][j].val=='1'){
					start.x=i;
					start.y=j;
					start.f=0;
					grid[i][j].checked=true;
				}else if (grid[i][j].val=='2'){
					end.x=i;
					end.y=j;
				}else{
					grid[i][j].x=i;
					grid[i][j].y=j;
				}
			}
		}
	}
	file.close();
	
	neighbour(grid, start, end, openSet);
	
	// set titik start tidak punya parent pos
	grid[start.x][start.y].prevX=-1;
	grid[start.x][start.y].prevY=-1;
	
	A_star(grid, start, end, openSet, found);
	
	system("pause");
	
	return 0;
}