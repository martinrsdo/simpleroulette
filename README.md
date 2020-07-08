# Simple Roulette simulation

_Six players playing the same simple bet each time_
_Players:_
* _A: RED_
* _B: BLACK_
* _C: HIGH_
* _D: LOW_
* _E: EVEN_
* _F: ODD_ 


_They take notes of their bets individually following the next patron:_

1. _Start with 1,2,3,4_
2. _Bet First + Last Numbers_
3. _Draw Number_
    1. _If Won append that value to the end (Ex: first round would be 5 leading to 1,2,3,4,5)_
    2. _If Lost, remove first and last number (Ex: 2,3)_
4. _Repeat 2 to 3. If only one number left, thats the bet. If no number left, start from 1 again.

_Minimum bet is 5, Maximun is 4000. If the bet is greater than 4000, start again with 1,2,3,4 and bet 5._

_After 10000 round the conbined balance of all players as a team is show_ 

## Instructions

_Clone and cd into the project folder and execute_

```
$ git clone https://github.com/martinrsdo/simpleroulette.git
$ cd simpleroulette


$ g++ -o roulette roulette.cpp

 or: 

$ make roulette

 and then

$./roulette
 
``` 

