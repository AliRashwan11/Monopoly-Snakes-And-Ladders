
# Game Modes

The Game Contains 2 Modes .. Design Mode & Play Mode

## Design Mode

Design Mode Gives The Player The Ability To Design The Grid 
The Player Is Able To Add Ladders - Add Snakes - Add Cards
The Player Is Able To Remove Any Added Game Object
Adding Game Objects Is With Respect To Not Overlap Eachother Giving An Error Message If Done

Everything Done By The Player Is By Him Clicking On The Cell He Wants The Game Object To Be Added To


## Play Mode

Players Is Given The Ability To Roll Random Dice - Enter Specific Dice Number - Start A New Game
Rolling A Random Dice Is For Fair Play
Entering A Specific Number Was Mainly For Testing Purposes .. But I Decided To Keep It In For Curiousity
Starting A New Game From Scratch With Every Player At First Cell And 100 Coins



# Game Rules

. Are Given To Toll Dice In Order
. Every 3 Turns The Dice Rolled Number Will Be Multiplied By 10 And Added To The Players Wallet Instead Of Moving
. Ladders Bring You Up .. Snakes Slide You Down
. Standing On A Card Will Punish/Reward You According To The Card Number
. First Player To Cell 99 Wins The Game !



# Cards

CardOne : User Enters A Value To Decrement From The ByPassers Wallet 
          If Entered Value Is Positive .. Card Acts As A Punishment 
          If Entered Value Is Negative .. Card Acts As A Reward As It Increments The ByPassers Wallet

CardTwo : Moves ByPasser To Next Ladder In Grid 
          If No Ladder After Card .. Card Has No Effect

CardThree : Gives ByPasser Another Dice Roll Without Incrementing His TurnCount

CardFour : Prohibites Player From Rolling Dice For His Next Turn

CardFive : Makes Player Move Rolled Dice Number Backwards In Grid Instead Of Forwards
           Player Moves Back With Number Rolled To Get To The Card Cell

CardSix : User Enters A Certain Cell To Which ByPassers Will Teleport To Throughout The Game
          Card Acts As A Punishment If Chosen Cell Is Before Cell Of Card
          Card Acts As A Reward If Chosen Cell Is After Cell Of Card

CardSeven : Returns First Player After ByPasser To Cell One 
            If ByPasser Is Winning (No Players After Him) Card Has No Effect
            If 2 Players At Same Cell After ByPasser .. ByPasser Chooses Which Player To Return

CardEight : Gives ByPasser Choice To Either Be In Prison For 3 Whole Rounds (Not Able To Roll Dice) Or Pay The Fee Entered By User (Has To Be A Positive Number)
            ByPasser Not Given The Choice If Has Insufficinet Funds (Imprisoned)
          


# Overlapping

. A Ladder Cant Be Touching A Snake
. A Card Can Be Under A Snake Or A Ladder (Not At Starting Point)
. Snakes Cant Be On Top Of EachOther
. Ladders Cant Be On Top Of Eachother


