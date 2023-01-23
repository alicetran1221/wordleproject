#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// global variables

string correctWord, guess;
int counter = 0;

char guessArr[6][5] = { {'-','-','-','-','-'}, {'-','-','-','-','-'}, 
	{'-','-','-','-','-'}, {'-','-','-','-','-'}, 
	{'-','-','-','-','-'}, {'-','-','-','-','-'} };

char resultArr[6][5] = { {'-','-','-','-','-'}, {'-','-','-','-','-'},
	{'-','-','-','-','-'}, {'-','-','-','-','-'},
	{'-','-','-','-','-'}, {'-','-','-','-','-'} };

void wordGenerator()
{
	// open file for reading

	ifstream inputFile;
	inputFile.open("words.txt");

	// if file doesn't exist , exit function
	if (inputFile.fail())
	{
		cout << "File not found!" << endl;
		return;
	}

	// chooses a random # that is associated with a word
	srand((unsigned)time(0)); 
	int sequence;

	// random number from 1 to 212
	sequence = rand() % 212 + 1;

	int seqNum;
	string word;

	while (inputFile >> seqNum)
	{
		inputFile >> word;
		if (seqNum == sequence)
		{
			correctWord = word;
			inputFile.close();
			return;
		}
	}
}

void showArr()
{
	int guess_rsize = sizeof(guessArr) / sizeof(guessArr[0]);
	int guess_csize = sizeof(guessArr[0]) / sizeof(guessArr[0][0]);
	int result_rsize = sizeof(resultArr) / sizeof(resultArr[0]);
	int result_csize = sizeof(resultArr[0]) / sizeof(resultArr[0][0]);


	cout << "Guess: " << endl;
	for (int i = 0; i < guess_rsize; i++)
	{
		for (int j = 0; j < guess_csize; j++)
		{
			cout << guessArr[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Result: " << endl;

	for (int i = 0; i < result_rsize; i++)
	{
		for (int j = 0; j < result_csize; j++)
		{
			cout << resultArr[i][j] << " ";
		}
		cout << endl;
	}

}

void guessWord(int n)
{
	for (int i = 0; i < 5; i++)
	{
		guessArr[n][i] = guess[i];

		if (guess[i] != correctWord[i])
		{
			resultArr[n][i] = 'X';
		}

		if (guess[i] == correctWord[0] || guess[i] == correctWord[1] ||
			guess[i] == correctWord[2] || guess[i] == correctWord[3] ||
			guess[i] == correctWord[4])
		{
			resultArr[n][i] = '*';
		}

		if (guess[i] == correctWord[i])
		{
			resultArr[n][i] = 'O';
		}
	}

	counter++;
}

int main()
{
	cout << "Hello! Welcome to Alice's Wordle! \n * Please use ALL CAPS, case sensitive *" << endl;
	cout << "LEGEND: O = green, X = black, * = yellow" << endl;

	showArr();

	wordGenerator();

	

	for (int i = 0; i < 6; i++)
	{
		cout << "Guess: ";
		cin >> guess;
		guessWord(i);
		showArr();

		if (resultArr[i][0] == 'O' && resultArr[i][1] == 'O' && resultArr[i][2] == 'O' &&
			resultArr[i][3] == 'O' && resultArr[i][4] == 'O')
		{
			break;
		}
	}


	cout << endl;
	cout << "\n Alice's Wordle Results: " << counter << "/6" << endl;

	showArr();

	cout << "Correct word: " << correctWord << endl;

	return 0;
}