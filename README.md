# PPD42

Yet another example of PPD42 with arduino, I think it is less crap then the others I've found. The mathematical formulae were copied from the spec, I have no idea if they are right.

I've tested with esp8266 (wemos), using ports D6 and D7 for P10 and P25, respectively, with a simple tension divider:

                   R                         R      R
PPD42 Pin i -----vvvvv----- Wemos Dj  -----vvvvv--vvvvv----- GND

where R = 4k7 and (i,j) \in {(2,6),(4,7)}


