#include <iostream>
#include <vector>
#include <string>

struct pos{
	int x,y,f,g,h;
	char val;
};

int main(){
	// std::string temp;
	int i=0, j, k, m, n;
	pos start, end, grid[100][100];
	
	std::cin >> m >> n;
	
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
	
	// while (std::cin >> temp){
		// for (j=0;j<temp.length();j++){
			// if (temp[j] == '1'){
				// start.x = i;
				// start.y = j;
				// grid[i][j].val = temp[j];
			// }else if (temp[j] == '2'){
				// end.x = i;
				// end.y = j;
				// grid[i][j].val = temp[j];
			// }else{
				// grid[i][j].val = temp[j];
			// }
		// }
		// i++;
	// }
	
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			std::cout << grid[i][j].val;
		}
		std::cout<<'\n';
	}
	
	system("pause");
	
	return 0;
}
