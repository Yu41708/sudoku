#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int board[9][9];
int quiz1[9][9] = { // 題目 1
    {0, 4, 7, 8, 0, 1, 0, 0, 6},
    {0, 8, 2, 0, 0, 3, 4, 0, 0},
    {3, 0, 0, 7, 0, 0, 8, 0, 9},
    {4, 7, 0, 3, 0, 2, 0, 0, 5},
    {2, 0, 8, 1, 9, 7, 0, 4, 3},
    {0, 0, 0, 5, 0, 0, 0, 0, 2},
    {0, 3, 1, 6, 7, 0, 2, 5, 4},
    {5, 2, 6, 4, 0, 0, 7, 9, 0},
    {0, 0, 0, 0, 0, 0, 0, 6, 0},
};
int ans1[9][9] = {  // 答案 1 
    {9, 4, 7, 8, 2, 1, 5, 3, 6},
    {6, 8, 2, 9, 5, 3, 4, 1, 7},
    {3, 1, 5, 7, 4, 6, 8, 2, 9},
    {4, 7, 9, 3, 6, 2, 1, 8, 5},
    {2, 5, 8, 1, 9, 7, 6, 4, 3},
    {1, 6, 3, 5, 8, 4, 9, 7, 2},
    {8, 3, 1, 6, 7, 9, 2, 5, 4},
    {5, 2, 6, 4, 3, 8, 7, 9, 1},
    {7, 9, 4, 2, 1, 5, 3, 6, 8},
};
int quiz2[9][9] = { // 題目 2
    {0, 0, 4, 0, 5, 0, 6, 0, 9},
    {5, 3, 0, 0, 0, 0, 0, 0, 2},
    {7, 2 ,0, 0, 0, 9, 0, 0, 1},
    {0, 0, 8, 6, 0, 4, 0, 1, 0},
    {0, 0, 7, 0, 0, 0, 4, 2, 3},
    {0, 0 ,0, 0, 0, 0, 0, 8, 0},
    {0, 8, 0, 0, 1, 7, 0, 6, 5},
    {0, 0, 0, 3, 0, 0, 1, 0, 4},
    {9, 5, 1, 0, 0, 0, 3, 0, 0},
};
int ans2[9][9] = { // 答案 2 
    {8, 1, 4, 7, 5, 2, 6, 3, 9},
    {5, 3, 9, 8, 6, 1, 7, 4, 2},
    {7, 2 ,6, 4, 3, 9, 8, 5, 1},
    {3, 9, 8, 6, 2, 4, 5, 1, 7},
    {1, 6, 7, 5, 9, 8, 4, 2, 3},
    {2, 4 ,5, 1, 7, 3, 9, 8, 6},
    {4, 8, 3, 9, 1, 7, 2, 6, 5},
    {6, 7, 2, 3, 8, 5, 1, 9, 4},
    {9, 5, 1, 2, 4, 6, 3, 7, 8},
};


bool editable[9][9];

int cur_r = 0, cur_c = 0;//第幾橫排 直排 的光標位置
int changeN;

bool is_invalid_horizontal(int a) //is_invalid_horizontal
{
    int e = 0;//錯誤次數
    for(int c = 0; c < 9; c++){//除了0 一一比較數字是否重複
        for(int d = c + 1; d < 9; d++){
            if(board[a][c]!=0 && (board[a][c] == board[a][d])){
                e++;
            }
        }
    }
    if(e>0) return true;
    else return false;
}
        
bool is_done_horizontal(int a) //is_done_horizontal
{
    int e = 0;//正確次數
    for(int c = 0; c < 9; c++){//一一比較數字是否都不一樣 且沒有0
        for(int d = c + 1; d < 9; d++){
            if(board[a][c]!=0 && (board[a][c]!=board[a][d])&&board[a][8]!=0){
                e++;
            }
        }
    }
    if(e==36) return true;
    else return false;
}

bool is_invalid_vertical(int b) //is_invalid_vertical
{
    int e = 0;//同上 is_invalid
    for(int c = 0; c < 9; c++){
        for(int d = c + 1; d < 9; d++){
            if(board[c][b]!=0 && (board[c][b] == board[d][b])){
                e++;
            }
        }
    }
    if(e>0) return true;
    else return false;
}

bool is_done_vertical(int b) //is_done_vertical
{
    int e = 0;//同上 is_done
    for(int c = 0; c < 9; c++){
        for(int d = c + 1; d < 9; d++){
            if(board[c][b]!=0 && (board[c][b]!=board[d][b])&&board[8][b]!=0){
                e++;
            }
        }
    }
    if(e==36) return true;
    else return false;
}

bool is_invalid_block(int a,int b) //is_invalid_block
{
    int A1, A2, B1, B2;//將大格的相對位置數字填入陣列0～8
    int e = 0;
    int num[9];
    if(a==0||a==3||a==6){//判斷ab是大格中的哪個位置
        A1 = a + 1;
        A2 = a + 2;
    }
    else if(a==1||a==4||a==7){
        A1 = a - 1;
        A2 = a + 1;
    }
    else if(a==2||a==5||a==8){
        A1 = a - 2;
        A2 = a - 1;
    }
    
    if(b==0||b==3||b==6){
        B1 = b + 1;
        B2 = b + 2;
    }
    else if(b==1||b==4||b==7){
        B1 = b - 1;
        B2 = b + 1;
    }
    else if(b==2||b==5||b==8){
        B1 = b - 2;
        B2 = b - 1;
    }
	
	num[0] = board[a][b];
	num[1] = board[a][B1];
	num[2] = board[a][B2];
	num[3] = board[A1][b];
	num[4] = board[A1][B1];
	num[5] = board[A1][B2];
	num[6] = board[A2][b];
	num[7] = board[A2][B1];
	num[8] = board[A2][B2];
	
	for(int c = 0; c < 9; c++){//看是否有數字重複
	    for(int d = c + 1; d < 9; d++){
	        if(num[c] != 0 && (num[c] == num[d])){
	            e++;
	        }
	    }
	}
	
	if(e>0) return true;
	else return false;
}

bool is_done_block(int a,int b) //is_done_block
{
    int A1, A2, B1, B2;//同上
    int e = 0;
    int num[9];
    if(a==0||a==3||a==6){
        A1 = a + 1;
        A2 = a + 2;
    }
    else if(a==1||a==4||a==7){
        A1 = a - 1;
        A2 = a + 1;
    }
    else if(a==2||a==5||a==8){
        A1 = a - 2;
        A2 = a - 1;
    }
    
    if(b==0||b==3||b==6){
        B1 = b + 1;
        B2 = b + 2;
    }
    else if(b==1||b==4||b==7){
        B1 = b - 1;
        B2 = b + 1;
    }
    else if(b==2||b==5||b==8){
        B1 = b - 2;
        B2 = b - 1;
    }
	
	num[0] = board[a][b];
	num[1] = board[a][B1];
	num[2] = board[a][B2];
	num[3] = board[A1][b];
	num[4] = board[A1][B1];
	num[5] = board[A1][B2];
	num[6] = board[A2][b];
	num[7] = board[A2][B1];
	num[8] = board[A2][B2];
	
	for(int c = 0; c < 9; c++){//看數字是否都不一樣
	    for(int d = c + 1; d < 9; d++){
	        if(num[c] != 0 && (num[c] != num[d]) && num[8]!=0){
	            e++;
	        }
	    }
	}
	
	if(e==36) return true;
	else return false;
}

void fill_number(int c) //fill_number
{   
    board[cur_r][cur_c]= c-48;
}

void move_cursor(char c) //move_cursor
{
    int CUR_R=cur_r,CUR_C=cur_c;//光標原位置 
    if((c=='w'||c=='W')&&cur_r>0) {
	    cur_r--;//先移動
	   	while(!editable[cur_r][cur_c]){//當移動後的光標為不可編輯之格子 
	   		if(cur_r<1){//如果光標再移動一次會碰到邊界 
	   			cur_r=CUR_R;//則退回原位
	   			break;
			   }
			else cur_r--;//如果光標再移動不會碰到邊界 即繼續移動 
	   }
	   
	}
	
    else if((c=='s'||c=='S')&&cur_r<8) {//同上 
	   cur_r++;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_r>7){
	   			cur_r=CUR_R;
	   			break;
			   }
			else cur_r++;
	}
}
	
    else if((c=='a'||c=='A')&&cur_c>0) {//同上 
	   cur_c--;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_c<1){
	   			cur_c=CUR_C;
	   			break;
			   }
			else cur_c--;
	}
}
	
    else if((c=='d'||c=='D')&&cur_c<8) {//同上 
	  cur_c++;
	  while(!editable[cur_r][cur_c]){
	   		if(cur_c>7){
	   			cur_c=CUR_C;
	   			break;
			   }
			else cur_c++;
	}

}
}

bool is_invalid(int i, int j)
{
    
	//格子在橫、列、大格是否衝突
	if (is_invalid_horizontal(i)||is_invalid_vertical(j)||is_invalid_block(i,j)) return true;
    return false;
}

bool is_done(int i, int j)
{
    //格子在橫、列、大格是否完成 
    if (is_done_horizontal(i)||is_done_vertical(j)||is_done_block(i,j)) return true;
    return false;
}

bool check_win()
{
    //查看遊戲是否完成
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if(!is_done(i,j)) {
            	return false;
            	break;
			}
	return true;
}

bool is_moving_action(char c)
{	
	// 查看輸入的字是否為wasd 
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{	
	// 查看輸入的字是否為數字 
    return (c >= '0' && c <= '9');
}

string get_styled_text(string text, string style)
{	
	// 標示字顏色或粗體
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

void print_board()
{
    // Flush the screen刷新頁面 
    cout << "\x1b[2J\x1b[1;1H";

    // 輸出遊戲的指令按鍵 
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << get_styled_text("      G: ", "B") << "check the answer" << endl;
    cout << endl;

    // Iterate through and print each cell.輸出遊戲頁面 
    for (int i = 0; i < 9; ++i)
    {
        // Print horizontal divider.
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // Set text style based on the state of the cell.
            string style = "";

            // Set style for the cell the cursor pointing to.
            if (cur_r == i && cur_c == j)
                style = "C";
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // Print the vertical divider for each block.
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

int change(){//隨機出題
	std::srand(std::time(0));
	
	return std::rand()%2+1;
}

void initialize()
{
    // Set up styled text for Windows.
    if(changeN==1){//看是哪個題目
    	for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				board[i][j]=quiz1[i][j];
				
			}
		}
	}
	else{
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				board[i][j]=quiz2[i][j];
			}
		}
	}
    // Mark editable cells
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = !board[i][j];

    // Print the initial board out.
    print_board();
}





int main()
{
    char c;
    bool action_ok;

	changeN=change();//隨機出題
	
    initialize();
    
    
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))
        {
            
			action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
			action_ok = true;
            fill_number(c);
            
        }

        if (c == 'Q' || c == 'q'){
        	action_ok = true;
        	
        	if(changeN==1){//看是哪個題目 輸出他的解答
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				board[i][j]=ans1[i][j];
			}
		}
	}
	else{
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				board[i][j]=ans2[i][j];
			}
		}
	}
        	
        	for (int i = 0; i < 9; ++i){
        if (i && i % 3 == 0)
            cout << "-------------------------------" << endl;

        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            string style = "";
            cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
        	
        	
			break;
		}
            
		
		if (c == 'G' || c == 'g'){
			
			action_ok = true;
		}
		
        print_board();

        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return 0;
}

