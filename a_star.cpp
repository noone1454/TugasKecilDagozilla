#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct pos{
	int x,y,f,g,h;
	char val;
};

int main(){
	// std::string temp;
	int i=0, j, k, m, n;
	pos start, end, grid[100][100];
	std::ifstream file;
	
	file.open("test.txt");
	
	if (!file){
		std::cout << "Manual input\n";
		std::cin >> m >> n;
		// Input
		for (i=0;i<m;i++){
			for (j=0;j<n;j++){
				std::cin >> grid[i][j].val;
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
		while (file >> grid[i][j].val){
			if (grid[i][j].val=='1'){
				start.x=i;
				start.y=j;
			}else if (grid[i][j].val=='2'){
				end.x=i;
				end.y=j;
			}
		}
	}
	file.close();
	
	// Output
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			std::cout << grid[i][j].val;
		}
		std::cout<<'\n';
	}

	system("pause");
	
	return 0;
}
