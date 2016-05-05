// $Id: main.cpp,v 1.8 2015-04-28 19:23:13-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"


using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

//Partially used the catfile.cpp example to implement parsing file content
int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   
   string key;
   string val;
   string line;
   ifstream infile;

   str_str_map test;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
     // str_str_pair pair (*argp, to_string<int> (argp - argv));
      //cout << "Before insert: " << pair << endl;
      //test.insert (pair);
      infile.open(*argp);
      if(infile.fail()){
         cerr << "Could not open file" << endl;

      }else{
         while(getline(infile, line)){
            size_t equalsIndex = line.find_first_of("=");
            //As long a the line is not empty or not a comment.
            if(line.size() > 0 && line.at(0) != '#'){
            	if(equalsIndex == string::npos){
            	   //If no equals sign, print out value at given key
            	   cout << line << endl;
            	} else {
            	
            	   //Need to rearange logic to make printing work.
            	   if(line.size() == 1){
            	   //Only possible argument is the equal, which prints out whole map
            	      cout << "Printing Map" << endl;
            	   }else if(equalsIndex == 0){
            	   //If equal sign is first
            	   //then print out the keys associated with the following value
            	   cout << "printing keys with value:" << " " << line.at(1) << endl;
            	   }else if(equalsIndex == line.size() - 1){
            	   //If equals sign is last, then we are deleting the preceding key
            	   cout << "Deleting key" << endl;
            	   }else{
            	   //If none of the above, then key = to string before =
            	   //and value is equal to strring after =
            	      cout << "Setting key and value" << endl;
            	   }
            	}
            	   
            }
            

         }
      }

   }

   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   test.erase (itor);

   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

