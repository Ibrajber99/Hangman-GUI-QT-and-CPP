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

#include "Model/hangman.h"
#include<cstring>
#include<time.h>
#include<cstdlib>
#include<random>
#include <QLabel>
#include<algorithm>
#include<QFile>
#include<QTextStream>
#include<QDebug>

//in the contructor we open the file with a QFile object read the data and push it to the words vector
//and also push the images to gameImages vector
Hangman::Hangman()
{
   std::vector<QString>tmp;
   std::string buffer;
   letters = new std::vector<char>();
   for(int i=0; i<26;i++){
       letters->push_back(alphaLetter);
       alphaLetter++;
   }
   QFile inputFile(":/words2.txt");
   if (inputFile.open(QIODevice::ReadOnly))
   {
      QTextStream in(&inputFile);
      while (!in.atEnd())
      {
         QString line = in.readLine();
         words.push_back(line);
      }
      inputFile.close();
   }


   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows1.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows2.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows3.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows4.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows5.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallows6.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallowsLost.png)"));
   gameImages.push_back(QString("border-image:url(:/assets/Images/gallowsWon.png)"));


}

//assigning the letters in the letters vector to assign the values to our buttons vector in the view
void Hangman::intializeGrid(std::vector<QPushButton *> &curr)
{
    for(unsigned int i=0; i < letters->size();i++){
        curr.at(i)->setText(QString(letters->at(i)));
    }

}

//grab the value from the button we clicked
//and check if the letter if it's there the value of the key (char) = true
void Hangman::grabInput(QString guess)
{
    std::string tmp = guess.toStdString();
    user_guess = tmp.front();
    userGuess.insert({std::tolower(user_guess),false});
    std::for_each(secretWord.begin(),secretWord.end(),[&](char c){
        auto pSearch = userGuess.find(std::tolower(c));
        if(pSearch != userGuess.end()){
            pSearch->second = true;
        }
    });
}


//transformming the word to '_'
//except for the punctuations and spaces and right guess that are stored in the map
QString Hangman::transmorgify()
{
    std::stringstream ss;
    std::ostream_iterator<char> osi(ss, " ");
    std::transform(secretWord.begin(), secretWord.end(), osi, [&](char c) {//i added & becuase i cant put the map in the capture list
        auto mapSearch = userGuess.find(std::tolower(c));
        if (mapSearch != userGuess.end() || !std::isalnum(c)) {
            return c;
        }
        else {
            return c = '_';
        }
    });
    verifyingResult = ss.str();
    return QString::fromStdString(verifyingResult);
}

//randomly picks a word form words vector and returns the word
std::string Hangman::generateguess()
{
    srand(time(0));
    int k = rand()% words.size();
    return words.at(k).toStdString();
}

//assing the vlaue from generate function to secretword variable
void Hangman::intializeGuess()
{
    secretWord = generateguess();
}


//check how many wrong guesses are there
int Hangman::wrongGuess()
{
    std::map<char, bool>wrongAnswers;
    std::copy_if(userGuess.begin(), userGuess.end(), std::inserter(wrongAnswers,wrongAnswers.end()), [](std::pair<const char,bool>& res) {return res.second == false; });

    //i added & becuase i cant put the map in the capture list
    std::for_each(wrongAnswers.begin(), wrongAnswers.end(), [&](std::pair<char, bool>res) {
            wrongGuessSet.insert({res.first});
      });

    return wrongGuessSet.size();
}

//initial image when the game starts
void Hangman::startgameImage(QLabel *lbl)
{
    lbl->setStyleSheet(QString("border-image:url(:/assets/Images/gallows0.png)"));
}

//display the proper image based on the wrongguess set size
void Hangman::currentStateImage(QLabel *lbl)
{
    if(wrongGuessSet.size() > 0 && wrongGuessSet.size() < gameImages.size()){
        lbl->setStyleSheet(gameImages.at(wrongGuessSet.size()-1));
    }else{
        startgameImage(lbl);
    }

}

//checks if the word is filled out
bool Hangman::checkifWordisFull()
{
    return std::all_of(verifyingResult.begin(),verifyingResult.end(),[](char c){return c!='_';});
}

//evaluates if the won or lost
bool Hangman::isWon()
{
    if((int)wrongGuessSet.size() < GUESS_LIMIT && checkifWordisFull()){
        return true;
    }else if((int)wrongGuessSet.size() >= GUESS_LIMIT && !checkifWordisFull()){
        return false;
    }
    return false;
}

//check if the game is still on going
bool Hangman::onGoingGame()
{
    return (int)wrongGuessSet.size() < GUESS_LIMIT && !checkifWordisFull();
}

//picks the properr image to the player if won or lost
void Hangman::gameResultImage(QLabel *lbl)
{
    if(isWon()){
        lbl->setStyleSheet(gameImages.at(gameImages.size()-1));
    }else{
        lbl->setStyleSheet(gameImages.at(gameImages.size()-2));
    }
}


//resets the gfame
//by intializing the guess again and clear the map and the set
void Hangman::reSetGame()
{

    intializeGuess();
    wrongGuessSet.clear();
    userGuess.clear();

}

//enables the vector of buttons in the view
void Hangman::enableGrid(std::vector<QPushButton *> &vec)
{
    std::for_each(vec.begin(),vec.end(),[](QPushButton *btn){return btn->setDisabled(false);});
}
//disables the vector of buttons in the view
void Hangman::disableGrid(std::vector<QPushButton *> &vec)
{
    std::for_each(vec.begin(),vec.end(),[](QPushButton *btn){return btn->setDisabled(true);});
}

//shows the button
void Hangman::showButton(QPushButton *btn)
{
    btn->setVisible(true);
}
//hides the button
void Hangman::hideButton(QPushButton *btn)
{
    btn->setVisible(false);
}




