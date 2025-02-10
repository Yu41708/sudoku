#include <iostream>
using namespace std;

int board[4][4] = {
    {0, 0, 1, 0},
    {0, 4, 0, 0},
    {0, 0, 2, 0},
    {0, 1, 0, 0},
};

bool editable[4][4];

int cur_r = 0, cur_c = 0; 

bool is_invalid_horizontal(int a){
    int e = 0;
    for(int c = 0; c < 4; c++){
        for(int d = c + 1; d < 4; d++){
            if(board[a][c]!=0 && (board[a][c] == board[a][d])){
                e++;
            }
        }
    }
    if(e>0) return true;
    else return false;
}
        

bool is_done_horizontal(int a){
    int e = 0;
    for(int c = 0; c < 4; c++){
        for(int d = c + 1; d < 4; d++){
            if(board[a][c]!=0 && (board[a][c]!=board[a][d])&&board[a][3]!=0){
                e++;
            }
        }
    }
    if(e==6) return true;
    else return false;
    
}

bool is_invalid_vertical(int b){
    
    int e = 0;
    for(int c = 0; c < 4; c++){
        for(int d = c + 1; d < 4; d++){
            if(board[c][b]!=0 && (board[c][b] == board[d][b])){
                e++;
            }
        }
    }
    if(e>0) return true;
    else return false;
}

bool is_done_vertical(int b){
    int e = 0;
    for(int c = 0; c < 4; c++){
        for(int d = c + 1; d < 4; d++){
            if(board[c][b]!=0 && (board[c][b]!=board[d][b])&&board[3][b]!=0){
                e++;
            }
        }
    }
    if(e==6) return true;
    else return false;
    
    if( board[0][b]!=0 && board[1][b]!=0 && board[2][b]!=0 && board[3][b]!=0 &&
	board[0][b]!=board[1][b] && board[0][b]!=board[2][b] && board[0][b]!=board[3][b] &&
	board[1][b]!=board[2][b] && board[1][b]!=board[3][b] &&
	board[2][b]!=board[3][b]) return true;
	else return false;
	
    
}

bool is_invalid_block(int a,int b){
    
    int A, B;
    int e = 0;
    int num[4];
    if(a==0||a==2) A=a+1;
    else if (a==1||a==3) A=a-1;
    
    if(b==0||b==2) B=b+1;
	else if (b==1||b==3) B=b-1;
	
	num[0] = board[a][b];
	num[1] = board[a][B];
	num[2] = board[A][b];
	num[3] = board[A][B];
	
	for(int c = 0; c < 4; c++){
	    for(int d = c + 1; d < 4; d++){
	        if(num[c] != 0 && (num[c] == num[d])){
	            e++;
	        }
	    }
	}
	
	if(e>0) return true;
	else return false;
	

	
}

bool is_done_block(int a,int b){
    
    int A, B;
    int e = 0;
    int num[4];
    if(a==0||a==2) A=a+1;
    else if (a==1||a==3) A=a-1;
    
    if(b==0||b==2) B=b+1;
	else if (b==1||b==3) B=b-1;
	
	num[0] = board[a][b];
	num[1] = board[a][B];
	num[2] = board[A][b];
	num[3] = board[A][B];
	
	for(int c = 0; c < 4; c++){
	    for(int d = c + 1; d < 4; d++){
	        if(num[c] != 0 && (num[c] != num[d]) && num[3] != 0){
	            e++;
	        }
	    }
	}
	
	if(e==6) return true;
	else return false;
	
	

}

void fill_number(int c){
    board[cur_r][cur_c]= c-48;
}

void move_cursor(char c){
    int CUR_R=cur_r,CUR_C=cur_c; 		 
    if((c=='w'||c=='W')&&cur_r>0){
	    cur_r--;						
	   	while(!editable[cur_r][cur_c]){ 	 
	   		if(cur_r<1){				 		
	   			cur_r=CUR_R;			 		
	   			break;
			   }
			else cur_r--;					
	   }
	   
	}
	
    else if((c=='s'||c=='S')&&cur_r<3){	 
	   cur_r++;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_r>2){
	   			cur_r=CUR_R;
	   			break;
			   }
			else cur_r++;
	}
}
	
    else if((c=='a'||c=='A')&&cur_c>0){	
	   cur_c--;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_c<1){
	   			cur_c=CUR_C;
	   			break;
			   }
			else cur_c--;
	}
}
	
    else if((c=='d'||c=='D')&&cur_c<3){ 
	  cur_c++;
	  while(!editable[cur_r][cur_c]){
	   		if(cur_c>2){
	   			cur_c=CUR_C;
	   			break;
			   }
			else cur_c++;
	}

}
}

bool is_invalid(int i, int j){
	if (is_invalid_horizontal(i)||is_invalid_vertical(j)||is_invalid_block(i,j)) return true;
    return false;
}

bool is_done(int i, int j){
    if (is_done_horizontal(i)||is_done_vertical(j)||is_done_block(i,j)) return true;
    return false;
}

bool check_win(){
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if(!is_done(i,j)){
            	return false;
            	break;
			}
	return true;
}

bool is_moving_action(char c){
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c){
    return (c >= '0' && c <= '4');
}

string get_styled_text(string text, string style){
    string color = "", font = "";
    for (char c : style){
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

void print_board(){
    // Flush the screen
    cout << "\x1b[2J\x1b[1;1H";
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;
    // Iterate through and print each cell.
    for (int i = 0; i < 4; ++i){
        // Print horizontal divider.
        if (i && i % 2 == 0)
            cout << "---------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 4; ++j){
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
            if ((j + 1) % 2 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize(){
    // Mark editable cells
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            editable[i][j] = !board[i][j];

    // Print the initial board out.
    print_board();
}

int main(){
    char c;
    bool action_ok;

    initialize();
    while (cin >> c){
        action_ok = false;
        if (is_moving_action(c)){
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c)){
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();

        if (check_win()){
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }
    return 0;
}

