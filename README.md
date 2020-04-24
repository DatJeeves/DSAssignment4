# DSAssignment4

I had used the following sites for reference:

1. Microsoft Doc Help in VisualStudio in how to throw exceptions
2. http://www.cplusplus.com/forum/
3. https://www.tutorialspoint.com/cplusplus/cpp_pointers.htm
4. https://www.techiedelight.com/queue-implementation-cpp/

Issues:

Initially I just had a tick start and did the processing but I quickly learnt I needed to show
what is the state of play at the start of the tick, then what is at the end of the tick. This is to account
for people that have 1 tick to process. It took a while to think this through.

Second I used a method that will pop a element off the list, do something with it, and then push it back on.
If I used a for loop to iterate this list (queue) I could cycle through the list once and get back to the start.
This is useful to traverse the list to make things quick.

Third I implemented the queue are per most site definitions, however I was not quite sure how to handle the queue
which had no max size specified. I debated if I should have a max limit of a 100 or keep it open. In the end I
decided to use a limit of 100 if one was not specified, however its easy to change to make it infinate by always
returning false to isFull if I wanted to.

Forth the queue was implemented on top of the list function to make it easier to do.

Fith I combined my template classes in the header rather than splitting them into .h and .cpp. I did this more 
to see if this is a better approach since in GenStack I did it the other way. It would be good to 
get some feedback on this.


 
