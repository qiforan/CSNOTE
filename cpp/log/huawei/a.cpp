#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> > image{{1,1,1},{1,1,0},{1,0,1}};
vector<vector<int> > dir{{0,1},{0,-1},{1,0},{-1,1}};
/*----------------------------------------------------------------
编写函数，实现许多图片编辑软件都支持的「颜色填充」功能。

待填充的图像用二维数组 image 表示，元素为初始颜色值。初始坐标点的行坐标为 sr 列坐标为 sc。需要填充的新颜色为 newColor 。

「周围区域」是指颜色相同且在上、下、左、右四个方向上存在相连情况的若干元素。

请用新颜色填充初始坐标点的周围区域，并返回填充后的图像。

示例：

输入：
image = [[1,1,1],[1,1,0],[1,0,1]] 
sr = 1, sc = 1, newColor = 2
输出：[[2,2,2],[2,2,0],[2,0,1]]
解释: 
初始坐标点位于图像的正中间，坐标 (sr,sc)=(1,1) 。
初始坐标点周围区域上所有符合条件的像素点的颜色都被更改成 2 。
注意，右下角的像素没有更改为 2 ，因为它不属于初始坐标点的周围区域。
*****************************************************************/

void dfs(int i, int j, int c1, int c2)
{
	if(c1 == c2)
		return;
    if (i < 0 || j < 0 || i >= image.size() || image.size() == 0 || image[i].size() == 0 || j >= image[i].size() || image[i][j] != c1)
        return;
    image[i][j] = c2;
    for (int k = 0; k < dir.size(); k++)
        dfs(i+dir[k][0], j+dir[k][1], c1, c2);
}

int main()
{
	dfs(1,1,image[1][1],2);
	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++)
			cout << image[i][j] << " ";
		cout << endl;
	}
	return 0;
}