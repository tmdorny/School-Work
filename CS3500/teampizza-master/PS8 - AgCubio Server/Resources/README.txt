﻿PS9- AgCubio Database / Web Server
Tim Dorny u0829896
Tanner Marshall u0840815

Database Description: 
1) We created two tables.  One contains every single game session along with all the scores that go along with it.  Our other table only includes the session and then 
all players that were eaten that session.  The two tables can link up through their session id's.

2) We used inserts and joins.  Every time a player dies we insert their information into the database.  When we get a request from the websever to look at specific session id's we join the two tables and return all the players eaten in a certain id.


Our server still has some seroius issues, but we believe that our database implementation is up to expected standards.
We included hyperlinks on each page. On the overall player stats page (/players), you can click a player's name to bring up all of the games played by that player.

On the page listing all games played by a certain player you can click on the number of players eaten number to pull up the list including the names of players eaten in that game by that player.
There is also a link at the top of the table that returns you to the overall players page.

On the page listen player names that were eaten, there are two links at the top of the page, one brings you back to the overall players page, 
and the other takes to back to all games played by the current player. If no data is returned by the database, the second link will not appear.

All of the data in our database was added before everything was up and running correctly. The 2nd player, Jack, is the only one currently with a working eaten players list.






*****************SERVER NOTES FROM PS8**************************

Unfortunately we were quite pressed for time on this assignment due to holiday plans and conflicting work schedules, so I apologize for the messy state of this project. We unfortunately
did not have a lot of time to polish and refine our implementations as the project went on, leading to some messy solutions and the like. Sorry!


	***Known Issues***

	Our game client does not run with our server for some reason. Our client connects to the demo server without any problems, but completely breaks
	whenever we try to connect our server.

	Getting split by a virus does not initiate the timer for merging, you must send a split request in order for merge to be queued.

	***Implementation Notes***

	View project??? We are unsure what the view project is supposed to contain, the assignment makes it sound like client code? but shouldn't that be seperate??

	When splitting, we give each cube a decaying "momentum" value to allow it to behave as needed.

	With time constraints, we compromised (made a unique feature) in that when cubes split, the fragments kind of 'hover' spaced out rather than shoving up agaisnt each other 
	trying to get to the same exact point. We feel this makes the game more "fun" wink wink.

	Collisions are handled by defining a range of coordinates that constitute a collision and firing off a method each time a cube falls into a player's 'collision range'.

	Our viruses

	We have had issues with memory exceptions and "laggy" game behavior. This was fixed by reducing the number of cubes being sent to the client.



	***Other Notes***
