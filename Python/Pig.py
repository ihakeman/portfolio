# Name: Ian Hakeman
# Student ID#: 2338119
# Chapman email: hakeman@chapman.edu
# Course Number and Section: CPSC230 - 12
# Assignment: 5 Pig.py

'''
Step 1: Explain the premise of the game
Step 2: Run a loop for each turn (user and computer)
Step 3: Create if statements for a turn, and prompt for hold or roll.
Step 4: When one person reaches 100 points, exit loop and end program.
'''

import random #import random to be used for rolling a die
print()
print("Pig is a two-player dice game in which each person rolls a die.")
print("You will be playing the computer. The first to 100 points wins the game.")
print("Each time you roll a 1 your turn is over, and you lose any points that you gathered for that turn.")
print("If you roll other numbers, they add to your total. You can choose to hold those points.")
print("If you choose to roll again, you risk losing the points that you have gained so far on that turn.")
print("At any point, if you wish to quit the game, type 'quit'.")
print()
print("You go first. Type 'r' to roll the die.")
computer_points = 0 #setting intial values of loop control variables
user_points = 0 #same
turn = 1 #turn 1 is users turn, always start with user.
temp_sum = 0 #set sum for the turn to start at 0

while computer_points < 100 and user_points < 100: #while nobody wins, run loop
    while turn == 1: #while it is users turn, run loop
        choice_str = input() #allow user to roll or hold (skip turn if haven't rolled yet)
        if choice_str == 'r':
            roll = random.randint(1,6) # roll die
            temp_sum = temp_sum + roll #add die to temporary sum
            if roll == 1: #if a 1 is rolled
                print("You rolled a 1. You gained no points for this turn. It is now the computers turn.")
                quit_str = input("Press enter to continue.") #allow user to quit, process game at own speed
                print()
                if quit_str == 'quit': #if user inputs quit, break out of loops
                    turn = 3 #turn 3 sends to "you quit the game" in this case
                    break #quit the turn
                turn = 2 #make it the computers turn
                temp_sum = 0 #reset the temporary sum for the next turn
            else: #if roll isn't 1, then tell user what they rolled and send back to their turn in loop
                print("You rolled a", roll, ". You have", temp_sum, "points collected on this turn so far.")
                print("Type 'r' to roll again or 'h' to hold your", temp_sum, "points.")
        elif choice_str == 'h': #if the user chooses to hold
            user_points = user_points + temp_sum #add the turns sum to their total
            if user_points >= 100: #if they win, quit loops
                turn = 3 #turn 3 quits sends to the outro of the program
                break #quit their turn
            print("You have held your points for this turn. It is now the computers turn.")
            quit_str = input("Press enter to continue.") #allow user to go at own pace
            print()
            if quit_str == 'quit': #if the user enters quit
                turn = 3 #sends to outro of program, in this case "you quit the game"
                break #quits their turn
            turn = 2 #makes it the computers turn because the user chose to hold
            temp_sum = 0 #reset the temporary sum for the next turn
        elif choice_str == 'quit': #if user quits
            turn = 3 #send to "you quit the game" and end of program
            break #quits the turn
        else: #if they don't put in 'r' 'h' or 'quit'
            print(choice_str, "wasn't one of the options, please input 'r' to roll or 'h' to hold.")

    while turn == 2: #while it is the computers turn
        if computer_points + temp_sum >= 100: #if the total points is >= 100
            computer_points = computer_points + temp_sum #total should be 100 or more
            turn = 3 #goes to computer winning message since computer_points >=100
            break #quits turn
        elif temp_sum < 20: #if the computer doesn't hold points for being 20 or more in a turn
            roll = random.randint(1,6) #roll the die
            if roll == 1: #if the die is a one
                temp_sum = 0 #reset the temporary sum
                print("The computer rolled a 1. The computer gained no points for this turn.")
                print()
                print("It is now your turn.")
                print("Your score:", user_points) #display scores before users turn
                print("The computers:", computer_points)
                print("Please input 'r' to roll. If you input 'h' your turn will be skipped.")
                turn = 1 #make it users turn
            else: #if roll isn't a one
                temp_sum = temp_sum + roll #add roll to temp sum
                if temp_sum < 20: #if the temp sum is less than 20, keep going
                    if computer_points + temp_sum >=100: #if computer has enough points, to be 100, hold and win
                        print("The computer rolled a", roll, "and has decided to hold its", temp_sum, "points.")
                        computer_points = computer_points + temp_sum #add points for total to be above 100
                        turn = 3 #sends to computer winning message
                        break #quits turn
                    else: # if roll isn't a one and can't win yet, keep going
                        print("The computer rolled a", roll, "and has decided to keep rolling.")
                else: #if temp sum is not less than 20, hold points
                    print("The computer rolled a", roll, "and has decided to hold its", temp_sum, "points.")
        else: # if temp sum is not less than 20, hold and add temp to total
            computer_points = computer_points + temp_sum
            if computer_points>= 100: # if total is above 100
                turn = 3 #sends to winning message because points >100
                break #quit the turn
            else: #because computer holds, send it back to users turn
                print()
                print("It is now your turn.")
                print("Your score:", user_points)
                print("The computer's score:", computer_points)
                print("Please input 'r' to roll. If you input 'h' your turn will be skipped.")
                temp_sum = 0 #reset temporary sum for next turn
                turn = 1 #make it users turn
    if turn == 3: #if sent here then quit the game loop
        break
if computer_points >= 100: #if computer has enough points to win
    print()
    print("The computer has scored", computer_points, "points and has won the game. Better luck next time.")
elif user_points >= 100: #if user has enough points to win
    print()
    print("Congratulations! You have scored", user_points, "points and have won the game!")
else: #if nobody has enough points but game loop is quit, then quit the game
    print("You have quit the game.")
