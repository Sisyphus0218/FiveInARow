#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer()
	: Player()
{
	;
}

HumanPlayer::HumanPlayer(int color)
	: Player(color)
{
	;
}

BoardCoord HumanPlayer::DecideNextStep(ChessBoard& board)
{
	while (true)
	{
		cout << "Enter coordinates (e.g. H8): " << endl;
		string input;
		cin >> input;

		if (input.length() < 2)
		{
			cout << "Invalid format! Please enter like 'H8'." << endl;
			continue;
		}

		if (!isalpha(input[0]))
		{
			cout << "Invalid format! First character must be a letter (A-O)." << endl;
			continue;
		}

		bool isNumber = true;
		for (size_t i = 1; i < input.length(); i++)
		{
			if (!isdigit(input[i]))
			{
				isNumber = false;
				break;
			}
		}

		if (!isNumber)
		{
			cout << "Invalid format! Row number must be digits only." << endl;
			continue;
		}

		char colChar = toupper(input[0]);
		int rowNum = stoi(input.substr(1));

		BoardNotation notation = BoardNotation(colChar, rowNum);
		BoardCoord coord = notation.ToCoord();

		if (!coord.IsValid())
		{
			cout << "Out of range! Please enter coordinates between A1 and O15." << endl;
			continue;
		}

		if (!board.IsEmptyAt(coord))
		{
			cout << "This position is already occupied! Please choose another position." << endl;
			continue;
		}

		if (board.GetStepNum() == 0)
		{
			if (colChar != 'H' || rowNum != 8)
			{
				cout << "First move must be H8!" << endl;
				continue;
			}
		}

		return coord;
	}
}