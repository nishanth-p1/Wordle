#ifndef WORDLE_H
#define WORDLE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <fstream>
#include <algorithm>
#include <random>

class Wordle : public Wt::WApplication
{
public:
    Wordle(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *guessInput_;
    Wt::WPushButton *guessButton_;
    Wt::WText *feedbackText_;
    Wt::WText *remainingGuessesText_;
    std::vector<std::string> wordList_;
    std::string targetWord_;
    int remainingGuesses_;

    void startNewGame();
    void handleGuess();
    std::string getRandomWord();
    std::string checkGuess(const std::string& guess);
};

#endif // WORDLE_H
