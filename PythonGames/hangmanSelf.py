#created by Sudhanshu Shekhar
# The game runs on the console and let's the user play the Hangman game by guessing one letter at a time.
# Additions :- 1) Can add the corpus dynamically. 2) Can find a better way to get a random word maybe
# Special thanks to Captain Deadbones whose code I referred for printing the hangman board




import random

board = [
'  +---+   \n  |   |   \n      |   \n      |   \n      |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n      |   \n      |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n  |   |   \n      |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n /|   |   \n      |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n /|\\  |   \n      |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n /|\\  |   \n /    |   \n      |   \n========= \n',
'  +---+   \n  |   |   \n  0   |   \n /|\\  |   \n / \\  |   \n      |   \n========= \n'
]


class hangman:
    def __init__(self,word):
        self.word = word
        self.missed_letters = []
        self.guessed_letters = []
        self.wrongTries = 0
        
    def guess(self,letter):
        if letter in self.missed_letters or letter in self.guessed_letters:
            self.wrongTries+=1
            return False
        elif letter not in self.word: 
            self.wrongTries+=1
            self.missed_letters.append(letter)
            return False
        else:
            self.guessed_letters.append(letter)
            return True
    def presentState(self):
        w= ""
        for l in self.word:
            if l in self.guessed_letters:
                w+=l
            else :w+= '_'
        return w
    
    def printState(self):
        w = self.presentState()
        print board[self.wrongTries]
        print "Word to guess :" + w
        print "Previously guessed (wrong) letters:",
        for i in self.missed_letters:
            print i,
        print

    def hasWon(self):
        if '_' in self.presentState():
            return False
        return True
    def is_notFinished(self):
        if self.wrongTries == 6 or self.hasWon():
            return False
        return True
    
def rand_word():
	
	bank = ['the','living','pearl','.com','captain','deadbones']
	return bank[random.randint(0,len(bank)-1)]

def main():
    word= rand_word()
    game = hangman(word)

    while game.is_notFinished():
        game.printState()
        print "Enter your next guess"
        c = raw_input()
        if len(c) > 1:
            while(1):
                print "Please Enter only 1 letter at a time"
                c = raw_input()
                if len(c) == 1 :
                    break
                
        game.guess(c)

    game.printState()
    if game.hasWon():
        print "\n-----Congratulations you won!-----\n"
        print "The word was = " + word
    else:
        print "\n----Sorry you lost-----\n"
        print "The word was = " + word    
    
if __name__ == "__main__":
	main()
