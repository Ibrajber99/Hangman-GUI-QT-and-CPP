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
#include "mainview.h"
#include "ui_mainview.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include<QDebug>
MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
{
    ui->setupUi(this);
    hangGame = new Hangman();

    vlayout = new QVBoxLayout(ui->centralwidget);
    hlayout = new QHBoxLayout();
    vlayout->addLayout(hlayout);
    gridLayout = new QGridLayout();
    hlayout->addLayout(gridLayout);
    hlayout->addStretch();


    //generating 26 buttons
    for(unsigned int i=0; i < 26;i++){
        auto btn = new QPushButton();
        btn->setStyleSheet( QString("QPushButton{font-size: 15px;}"));
        gridLayout->addWidget(btn, i/9, i%9);
        uiButtons.push_back(btn);
        connect(btn,&QPushButton::clicked,this,[this](){onClickDoIt();});
    }
    hangGame->intializeGrid(uiButtons);//filling the buttons with the text value
    hangGame->intializeGuess();//initializing guess
    hangGame->startgameImage(ui->showStatusLbl);//diplaying the start of game image
    ui->currentWordLbl->setText(hangGame->transmorgify());//displaying the secret word

    connect(ui->newGameBtn,&QPushButton::clicked,this,&MainView::reSetgame);//connecting new game button to reSetgame function
    hangGame->hideButton(ui->newGameBtn);//hid ther new game button
}


void MainView::onClickDoIt()
{
    QObject * theButton =sender();//sender
    for(unsigned int i=0 ; i <uiButtons.size();i++){
       if(theButton ==qobject_cast<QObject *>(uiButtons.at(i))){
           hangGame->grabInput(uiButtons.at(i)->text());//grab the input
           ui->currentWordLbl->setText(hangGame->transmorgify());//displaying the secret word
           uiButtons.at(i)->setDisabled(true);//disable the button that was clicked
           hangGame->wrongGuess();
           hangGame->currentStateImage(ui->showStatusLbl);//display current state of the game image
           if(!hangGame->onGoingGame()){//check if game is not going
               hangGame->gameResultImage(ui->showStatusLbl);//display the game result image WON/LOSE
               hangGame->showButton(ui->newGameBtn);//show the new game button
               hangGame->disableGrid(uiButtons);//disables all the buttons in the grid
           }
       }
    }

}

//resets the game by calling the corresponding fucntions in the hgangman class
//and hides the new game button
void MainView::reSetgame()
{
    hangGame->reSetGame();
    hangGame->startgameImage(ui->showStatusLbl);
    ui->currentWordLbl->setText(hangGame->transmorgify());
    hangGame->intializeGuess();
    hangGame->enableGrid(uiButtons);
    hangGame->hideButton(ui->newGameBtn);

}


MainView::~MainView()
{
    delete ui;
}

