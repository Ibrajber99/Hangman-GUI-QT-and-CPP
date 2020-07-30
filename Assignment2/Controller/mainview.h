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
#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include<algorithm>
#include "Model/hangman.h"
#include<QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    void onClickDoIt();//If the button on the grids is clicked it will call the function form Hangman class Accordingly
    void reSetgame();//Reset game for new Game button
    ~MainView();

private:
    Ui::MainView *ui;
    std::vector<QPushButton*>uiButtons;
    QVBoxLayout* vlayout;//Vertiacal layout
    QHBoxLayout *hlayout;//Horizontal layout
    QGridLayout* gridLayout;//Grid layout
    Hangman *hangGame;//Hangman Instance


};
#endif // MAINVIEW_H
