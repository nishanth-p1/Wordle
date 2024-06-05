#include <fstream>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <fstream>
#include <algorithm>
#include <random>
#include "Wordle.h"


 /**
     * @brief Constructor for WordleApp class.
     * @param env The Wt environment.
     */
Wordle::Wordle(const Wt::WEnvironment& env)
  : WApplication(env)
{
  setTitle("Wordle");                            // application title 
  root()->addWidget(std::make_unique<Wt::WText>("What is your guess: ")); // show some text

  guessInput_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow text input
  guessInput_->setFocus();                              // give focus

  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Guess"));
                                                      // create a button
  button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

  startNewGame();

  button->clicked().connect(this, &Wordle::handleGuess);
  guessInput_->enterPressed().connect(std::bind(&Wordle::handleGuess, this));
}

void Wordle::handleGuess() { // method to handle each guess before being sent to check guess method
    std::string guess = guessInput_->text().toUTF8();
    std::string uppcerCaseGuess = guess;
    std::transform(uppcerCaseGuess.begin(), uppcerCaseGuess.end(), uppcerCaseGuess.begin(), ::toupper); // converts guess to uppercase

    root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line break
    feedbackText_ = root()->addWidget(std::make_unique<Wt::WText>()); // empty text

    std::string result = checkGuess(uppcerCaseGuess);
    feedbackText_->setText(result);
}

/**
 * @brief Checks the user's guess compared to the target word and provides feedback.
 *
 * @param guess The user's guess input.
 * @return Feedback message for the user.
 */
std::string Wordle::checkGuess(const std::string& uppcerCaseGuess) { // method to work with user guesses
    std::string result; // represents the guess to be printed out

    if (uppcerCaseGuess == targetWord_) { // checks if guess is correct and strats new game if so
        result = "Congratulations! You guessed the word!";
        startNewGame();
    } else if ((uppcerCaseGuess != targetWord_) && (remainingGuesses_ != 0)) { // check if guess is wrong and more guesses are left
        std::string coloredGuess = "<div style='display:flex; flex-direction:column;'>"; // Create a container for guesses
        
        for (char c : uppcerCaseGuess) { // for loop to colour code letters from user guess
            std::string color = "";
            
            auto targetPos = targetWord_.find(c);
            if (targetPos != std::string::npos) {
                if (targetPos == coloredGuess.size()) {
                    color = "color:green;"; // Correct letter in correct position (green)
                } else {
                    color = "color:orange;"; // Correct letter in incorrect position (orange)
                }
            }
            coloredGuess += "<span style='" + color + "display:inline-block;'>" + std::string(1, c) + "</span>";
        }
        
        coloredGuess += "</div>"; // Close container
        result = coloredGuess;
        remainingGuesses_--;
        
    } else if (remainingGuesses_ == 0) { // print answer if last guess was incorrect
        result = "Sorry, you've run out of guesses. The word was: " + targetWord_;
        startNewGame();
    }

    remainingGuessesText_->setText("Remaining guesses: " + std::to_string(remainingGuesses_)); // always prints the number of remaining guesses in appropriate container
    return result;
}

/**
 * @brief Initializes a new game by loading a randomly ordered word list, and setting up game.
 */
void Wordle::startNewGame() {
    // Load words from file
    std::ifstream file("words_list.txt");
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) {
            if (word.length() == 5) // adds word to list if 5 letters long
                wordList_.push_back(word);
        }
        file.close();
    }

    // Random shuffle the word list
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wordList_.begin(), wordList_.end(), g);

    // Initialize game conditions
    remainingGuesses_ = 6;
    targetWord_ = getRandomWord();
    //feedbackText_->setText("");
    root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line break
    remainingGuessesText_ = root()->addWidget(std::make_unique<Wt::WText>()); // empty text
    remainingGuessesText_->setText("Remaining guesses: " + std::to_string(remainingGuesses_));
}

/**
 * @brief to get random word from word list.
 * @return uses random index to get word from wordList_
 */
std::string Wordle::getRandomWord() { 
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distribution(0, wordList_.size() - 1);
    return wordList_[distribution(g)];
}

