# le_fish
The world's best* discord bot

What is this repo?: 
Source code for le_fish, a discord bot which limits the vocabulary users of a discord server can send
in thier messages. 

How does it work?:
Uses Orca library for discord API interface: getting information from/sending information to Discord.
Compares the contents of all recieved messages against a wordlist loaded at launch time from a
specified file. After preprocessing a message in order to remove punctuatuion and other "garbage",
each of its words is compared against the wordlist. If a message contains a word not defined in the
wordlist, the message is deleted. Only messages sent in channels registered to the bot via !!register 
are compared against the wordlist,all other messages are ignored. 

Some technical details:
The wordlist loaded at launch is first sorted via a custom generic merge_sort implementation, and then
built into a balanced binary search tree via a custom generic build_bst implementation in order to
vastly improve message checking time(binary search is signifigantly faster than linear search for 
very large lists of words). (The included Makefile was not written by me, just thought it would be useful to include for people who wish to continue development of the bot).

Personal remarks:
This is my first "major" personal project that I intend for other people to be able to see, and use, if 
they wish. Constructive criticism, comments, and other useful communications are welcome and greatly 
appreciated (contanct information should be available via my github profile). I will do my best to 
answer questions and improve the quality of the code, and this repo as the project continues. Thanks 
for your patience and interest in this little project of mine! 
