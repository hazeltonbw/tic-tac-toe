#include <iostream>
#include <vector>
using namespace std;


void die() {
	cout << "BAD INPUT!\n";
	exit(EXIT_FAILURE);
}

class Game {
	
	const char OPEN = ' ';
	char X = 'X';
	char O = 'O';
	const int ROWS = 3;
	const int COLS = 3;
	vector<string> board;
	unsigned int X_score = 0;
	unsigned int O_score = 0;
	unsigned int moves_made = 0;
	char last_winner = ' ';
	public:
	Game() {
		setupBoard();
		playGame();	
	}

	void printBoard() {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++){
				if (j < ROWS - 1) 
					cout << board[i][j] << "|";
				else cout << board[i][j];
			}
			cout << endl;
			if (i < 2)
				cout << "-+-+-" << endl;
		}
	}

	void setupBoard() {
		board = {"   ", "   ", "   "};
		moves_made = 0;
	}

	char checkForWinner() {
		// this function will return a space if no player won, X if X won, O if O won.
		// Row winners
		if (board[0][0] == 'X' and board[0][1] == 'X' and board[0][2] == 'X') return 'X';
		if (board[1][0] == 'X' and board[1][1] == 'X' and board[1][2] == 'X') return 'X';
		if (board[2][0] == 'X' and board[2][1] == 'X' and board[2][2] == 'X') return 'X';
		if (board[0][0] == 'O' and board[0][1] == 'O' and board[0][2] == 'O') return 'O';
		if (board[1][0] == 'O' and board[1][1] == 'O' and board[1][2] == 'O') return 'O';
		if (board[2][0] == 'O' and board[2][1] == 'O' and board[2][2] == 'O') return 'O';
		// Col winners
		if (board[0][0] == 'X' and board[1][0] == 'X' and board[2][0] == 'X') return 'X';
		if (board[0][1] == 'X' and board[1][1] == 'X' and board[2][1] == 'X') return 'X';
		if (board[0][2] == 'X' and board[1][2] == 'X' and board[2][2] == 'X') return 'X';
		if (board[0][0] == 'O' and board[1][0] == 'O' and board[2][0] == 'O') return 'O';
		if (board[0][1] == 'O' and board[1][1] == 'O' and board[2][1] == 'O') return 'O';
		if (board[0][2] == 'O' and board[1][2] == 'O' and board[2][2] == 'O') return 'O';
		// Diagonal winners
		if (board[0][0] == 'X' and board[1][1] == 'X' and board[2][2] == 'X') return 'X';
		if (board[0][0] == 'O' and board[1][1] == 'O' and board[2][2] == 'O') return 'O';
		if (board[0][2] == 'X' and board[1][1] == 'X' and board[2][0] == 'X') return 'X';
		if (board[0][2] == 'O' and board[1][1] == 'O' and board[2][0] == 'O') return 'O';
		return ' '; // if we made it here, there's no winner yet.
	}

	void playGame() {
		cout << "Who's going first? X or O\n";
		string input;
		cin >> input;
		if (input.size() < 1)
			die();
		char c = toupper(input[0]);
		char *player = nullptr;
		if (c == 'X') 
			player = &X;
		else if (c == 'O') 
			player = &O;
		else die();
		cout << endl;
		while (1) {
			cout << "Where would you like to place an ";
			cout << *player << " ? (Pick 1-9)" << endl;
			printBoard();
			int number = 0;
			cin >> number;
			if (!cin or number < 1 or number > 9) die();
			cout << endl;

			number--; // change number to 0-index so we can get row/col
			const unsigned int row = number / ROWS;
			const unsigned int col = number % COLS;
			char *spot = &board[row][col];
			if (*spot == OPEN) {
				*spot = *player;
				moves_made++;
				if (moves_made > 4) {
					last_winner = checkForWinner();
					if (last_winner != OPEN) {
						printBoard();
						cout << "Congratulations " << last_winner << "! You won! \n";
						cout << last_winner << " has won " << (last_winner == 'X' ? ++X_score : ++O_score) << " time(s)\n";
						cout << "Would you like to play again? (Y)es or press any other key to exit.\n";
						cin >> input;
						if (input.size() < 1) die();
						if (toupper(input[0]) != 'Y') break;
						setupBoard();
					} 
				}
				if (moves_made == 9) {
					printBoard();
					cout << "Tie game! Play again?\t(Y)es or press any other key to exit.\n";
					cin >> input;
					if (input.size() < 1) die();
					if (toupper(input[0]) != 'Y') break;
					setupBoard();
				}
				player = *player == X ? &O : &X;
			}
			else
				cout << "That spot is already taken! \n";
		}
	}
};

int main() {
	Game runGame;
}
