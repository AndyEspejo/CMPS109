.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-109 Spring\~2016 Program\~3 "Templates and Iterators"
.RCS \
"$Id: asg3-listmap-templates.mm,v 1.19 2016-04-19 18:35:37-07 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.H 1 "Overview"
In this assignment,
you will implement template code and not use any template
classes from the STL.
You will also write your own code to handle files.
Refer to the earlier assignment as to how to open and read files.
.P
You may use the following includes,
and if you think anything else is needed,
post a question to the mailing list\(::
.V= <cassert> ,
.V= <cerrno> ,
.V= <cstdlib> ,
.V= <exception> ,
.V= <fstream> ,
.V= <iomanip> ,
.V= <iostream> ,
.V= <stdexcept> ,
.V= <string> ,
.V= <typeinfo> .
.P
Specifically, you may not use any classes that take template
parameters,
such as
.V= <iterator> ,
.V= <list> ,
.V= <map> ,
.V= <pair> ,
.V= <vector> ,
except for those you write yourself.
Do not use
.V= shared_ptr ,
and instead, explicitly manage pointers yourself using
.V= new
and
.V= delete .
.H 1 "Program Specification"
The program is specified in the format of a Unix
.V= man (1)
page.
.SH=BVL
.MANPAGE=LI "NAME"
keyvalue \[em] manage a list of key and value pairs
.MANPAGE=LI "SYNOPSIS"
.V= keyvalue
.=V \|[ -@
.IR flags ]
.RI \|[ filename \|.\|.\|.]
.MANPAGE=LI "DESCRIPTION"
Input is read from each file in turn.
Before any processing,
each input line is echoed to
.V= cout ,
preceded by its filename and line number within the file.
The name of
.V= cin
is printed as a minus sign
.=V ( - ).
.P
Each non-comment line causes some action on the part of the program,
as described below.
Before processing a command,
leading and trailing white space is trimmed off of the key and off of
the value.
White space interior to the key or value is not trimmed.
When a key and value pair is printed,
the equivalent of the format string used is
.V= "\[Dq]%s\0=\0%s\[rs]n\[Dq]" .
Of course, use
.V= <iostream> ,
not
.V= <stdio> .
The newline character is removed from any input line before
processing.
If there is more than one equal sign on the line,
the first separates the key from the value,
and the rest are part of the value.
Input lines are one of the following\(::
.BVL \n[Pi]
.LI \f[CB]#\f[R]
Any input line whose first non-whitespace character is a hash
.=V ( # )
is ignored as a comment.
This means that no key can begin with a hash.
An empty line or a line
consisting of nothing but white space is ignored.
.LI \f[I]key\f[R]
A line consisting of at least one non-whitespace character and no equal
sign causes the key and value pair to be printed.
If not found, the message
.VINDENT* "\f[I]key\f[CB]:\~key\~not\~found\f[R]"
is printed.
Note that the characters in italics are not printed exactly.
The actual key is printed.
This message is printed to
.V= cout .
.LI \f[I]key\f[R]\~\f[CB]=\f[R]
If there is only whitespace after the equal sign,
the key and value pair is deleted from the map.
.LI \f[I]key\f[R]\~\f[CB]=\f[R]\~\f[I]value\f[R]
If the key is found in the map,
its value field is replaced by the new value.
If not found, the key and value are inserted in increasing
lexicographic order, sorted by key.
The new key and value pair is printed.
.LI \f[CB]=\f[R]
All of the key and value pairs in the map are printed in
lexicographic order.
.LI \f[CB]=\f[R]\~\f[I]value\f[R]
All of the key and value pairs with the given value are printed in
lexicographic order sorted by key.
.LE
.MANPAGE=LI "OPTIONS"
The
.V= -@
option is followed by a sequence of flags to enable debugging output,
which is written to the standard error.
The option flags are only meaningful to the programmer.
.MANPAGE=LI "OPERANDS"
Each operand is the name of a file to be read.
If no filenames are specified,
.V= cin
is read.
If filenames are specified,
a filename consisting of a single minus sign
.=V ( - )
causes 
.V= cin
to be read in sequence at that position.
Any file that can not be accessed causes a message in proper format to
be printed to
.V= cerr .
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were found.
.LI 1
There were some problems accessing files,
and error messages were reported to
.V= cerr .
.LE
.LE
.H 1 "Implementation Sequence"
In this assignment,
you will constuct a program from scratch,
using some of the code from previous assignments.
.ALX a ()
.LI
Study the behavior of
.V= misc/pkeyvalue.perl ,
whose behavior your program should emulate.
The Perl version does not support the debug option of your program.
.LI
Copy
.V= Makefile
from your previous assignment,
and edit it so that it will build and submit your new assignment.
.LI
Implement your main program whose name is
.V= main.cpp ,
and handle files in the same way as the sample Perl code.
Instead of trying to use a map,
just print debug statements showing which of the five
kinds of statements are recognized,
printing out the key and value portion of the statement.
.LI
Instead of
.V= <pair>
from the STL,
you will use
.V= xpair .
.LI
You will be using a linear linked list to implement your data
structure.
This is obviously unacceptable in terms of a real data structures
problem,
since unit operations will run in $ O ( n ) $ time instead of
the proper $ O ( log sub 2 n ) $ time for a balanced binary search
tree.
But iteration over a binary search tree is rather complex and
will not contribute to your learning about how to implement templates.
And balancing a BST is part of CMPS-101,
which is not a prerequisite for this course.
.LI
Look at 
.V= xless.h
and
.V= misc/testxless.cpp ,
which show how to create and use an
.V= xless
object to make comparisons.
The 
.V= listmap
class assumes this has already been declared.
.LI
The files
.V= *.tcc
are explicit template instantiations.
Templates are type-safe macros and the source is needed at
the point where they are compiled.
.LE
.H 1 "The main function"
Replace the code in the main function to do options analysis.
Then for each input line, parse the line by splitting it up into
two pieces separated by the first equal
.=V ( = )
sign.
Then trim leading and trailing white space off each end,
and perform the appropriate function.
.ALX a ()
.LI
Use
.V= find_first_of
to locate the first
.V= \&'='
in the string
and then
.V= substr
to pull off the various parts.
.LI
Use
.V= find_first_not_of
and
.V= find_last_not_of
to find the first and last non-whitespace characters in the
string.
Write your own function
.V= trim .
.LI
Use an 
.V= if-else
sequence to determine which command is being parsed.
.LE
.H 1 "Template class \f[CB]listmap\f[P]"
We now examine the class
.V= listmap ,
which is partially implemented for you.
You need not implement functions that are never called.
.de VV
.   VTCODE* 0 \\$@
..
.de LI=VV
.   LI
.   V= \\$@
.   br
..
.ALX a ()
.LI=VV "template <typename Key, typename Value, class Less=xless<Key>>"
.VV "class listmap"
defines the template class with three arguments.
.V= Key
and
.V= Value
are the elements to be kept in the list.
.V= Less
is the class used to determine the ordering of the list and
defaults to
.V= xless<Key> .
.LI=VV "typedef Key key_type;"
.VV "typedef Value mapped_type;"
.VV "typedef xpair<key_type,mapped_type> value_type;"
are some standard names given to usual STL types.
Note that the value type is an
.V= xpair,
not what is normally thought as the value,
which here is called the
mapped type.
.LI=VV "struct link"
represents the list itself and is contained in every node.
The list is kept as a circular doubly linked list with the
list itself being the start and end,
as well as the
.V= end()
result.
In a list with $n$ nodes, 
there are $n + 1$ links,
each node having a link, and the list itself having a link,
but not node values.
.LI=VV "struct node"
is a private node used to hold a value type along with forward
and backword links to form a doubly linked list.
It inherits from
.V= "struct link" .
The private function
.V= anchor()
downcasts from a
.V= link
to a
.V= node.
.LI=VV "listmap();"
.VV "listmap (const listmap&);"
.VV "listmap& operator= (const listmap&);"
.VV "listmap (listmap&&);"
.VV "listmap& operator= (listmap&&);"
.VV "~listmap();"
The usual six members are overriden and explicitly defined.
.LI=VV "iterator insert (const value_type&);"
Note that insertion takes a pair as a single argument.
If the key is already there, the value is replaced,
otherwise there is a new entry inserted into the list.
An iterator pointing at the inserted item is returned.
.LI=VV "iterator find (const key_type&) const;"
Searches and returns an iterator.
If find fails, it returns the
.V= end()
iterator.
.LI=VV "iterator erase (iterator position);"
The item pointed at by the argument iterator is deleted from
the list.
The returned iterator points at the position immediately
following that which was erased.
.LI=VV "iterator begin();"
.VV "iterator end();"
The usual iterator generators.
We don't bother here with a constant iterator.
.LE
.H 1 "Template class \f[CB]listmap::iterator\f[P]
Although the iterator is nested inside the list map,
it is easier to read when specified separately.
.ALX a ()
.LI=VV "class listmap<Key,Value,Less>::iterator"
specifies precisely which class the iterator belongs to.
.LI=VV "friend class listmap<Key,Value>;"
Only a listmap is permitted to construct a valid iterator.
.LI=VV "iterator (listmap* map, node* where);"
The iterator keeps track of both the node and the list as a whole,
so that
.V= end()
can return an iterator ``off the end'',
.LI=VV "value_type& operator*();"
Returns a reference to some value type (key and value pair)
in the list.
Selections are then by dot
.=V ( . ).
.LI=VV "value_type* operator->();"
Returns a pointer to some value type, from which fields can be
selected with an arrow
.=V ( -> ).
.LI=VV "iterator& operator++(); //++itor"
.VV "iterator& operator--(); //--itor"
Move backwards and forwards along the list.
Moving off the end with
.V= ++
and moving from an end iterator to the last element
requires special coding.
.LI=VV "void erase();"
Removes the key and value pair from the list.
.LE
.H 1 "What to Submit"
.V= Makefile ,
.V= README ,
and all necessary C++ header and implementation files.
And don't forget 
.V= checksource .
If you are using pair programming, also submit
.V= PARTNER .
.FINISH
