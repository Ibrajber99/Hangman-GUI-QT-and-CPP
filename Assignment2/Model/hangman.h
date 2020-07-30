/*
* @file
* @author  <Ibrahim Jaber>
* @version 1.0
*
*
* @section DESCRIPTION
* <HangMan Game GUI>
*
*
* @section LICENSE
* <any necessary attributions>
*
* Copyright 2020
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
*  I certify that this work is solely my own and complies with
*  NBCC Academic Integrity Policy (policy 1111)
*/
#ifndef HANGMAN_H
#define HANGMAN_H
#include<vector>
#include<QPushButton>
#include <QLabel>
#include<algorithm>
#include<fstream>
#include<QString>
#include<string>
#include<QFile>
#include<map>
#include<set>
#include<unordered_set>
#include<random>
#include <QLabel>
#include<sstream>
class Hangman
{
public:
    Hangman();
    void intializeGrid(std::vector<QPushButton*>&curr);//Initilizing the grid
    void grabInput(QString guess);//grab input form the button that is clicked
    QString transmorgify();//transform the wsecret word to '_'
    std::string generateguess();//generate a random guess from words vector
    void intializeGuess();//grab the result from generateGuess() function
    int wrongGuess();//wrong guess
    void startgameImage(QLabel *lbl);//Generate the initial image for the game and asing the value to a QLbale Object
    void currentStateImage(QLabel *lbl);//returns current state image
    bool checkifWordisFull();//check if the word is completed
    bool isWon();//see if won or lost
    bool onGoingGame();//check if the game is still going
    void gameResultImage(QLabel *lbl);//returns the game resutl image of lose or won
    void reSetGame();//resets the game
    void enableGrid(std::vector<QPushButton*>&vec);//enables the vector of buttons
    void disableGrid(std::vector<QPushButton*>&vec);//disables the vector of buttons
    void showButton(QPushButton *btn);//show button
    void hideButton(QPushButton *btn);//hides button

private:
    std::vector<QString>gameImages;//vector to store the images
    std::vector<char>*letters;//vectors of the alphabet letters
    std::vector<QString>words;//words vector to grab to store the data that is being read from the file
    std::map<char,bool>userGuess;//map for user guess
    std::unordered_set<char>wrongGuessSet;//wrong guesses set
    const int GUESS_LIMIT = 6;
    char alphaLetter ='a';
    char user_guess;
    std::string secretWord;//secret word
    std::string verifyingResult;//actual word before it's being trnsformed
    std::random_device rd;//random device
};

#endif // HANGMAN_H
