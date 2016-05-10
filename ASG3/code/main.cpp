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

//Used to trim off the whitespace
//Got this from http://stackoverflow.com/questions/25829143/c-trim-whitespace-from-a-string
string trimWhitespace(string& str){
   size_t first = str.find_first_not_of(' ');
   size_t last = str.find_last_not_of(' ');
   return str.substr(first, (last-first+1));
}

//Partially used the catfile.cpp example to implement parsing file content
int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   
   string key;
   string val;
   bool userInput = true;
   string line;
   ifstream infile;


   str_str_map map;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      userInput = false;
      infile.open(*argp);
      if(infile.fail()){
         cerr << "Could not open file" << endl;
         cout << "EXIT_FAILURE" << endl;
         return EXIT_FAILURE;
      }else{
         while(getline(infile, line)){
            line = trimWhitespace(line);
            size_t equalsIndex = line.find_first_of("=");
            //
            //As long a the line is not empty or not a comment.
            if(line.size() > 0 && line.at(0) != '#'){
            	if(equalsIndex == string::npos){
            	   //If no equals sign, print out value at given key
                  key = line;
                  str_str_map::iterator iter = map.find(key);
                  //If val = iterator then it does not exist
                  if(iter == str_str_map::iterator()){
            	     cout << iter->first << " : Key not found" << endl;
                  }else{
                     cout << iter->first << " = " << iter->second << endl;
                  }
            	} else {
            	   if(line.size() == 1){
            	   //Only possible argument is the equal, which prints out whole map
                     cout << "Here's the whole map!" << endl;
                     for (str_str_map::iterator itor = map.begin();
                        itor != map.end(); ++itor) {
                        cout <<  *itor << endl;
                     }
            	   }else if(equalsIndex == 0 && line.size() > 1){
            	   //If equal sign is first
            	   //then print out the keys associated with the following value
                  val = line.substr(equalsIndex + 1, line.size());
                  //Goes through the whole map until it finds keys that have the given value
            	   for(str_str_map::iterator iter = map.begin();
                        iter != map.end(); ++iter){
                     if(iter->second == val){
                        cout << iter->first << " = " << iter->second << endl;
                     }
                  }
            	   }else if(equalsIndex == line.size() - 1){
            	   //If equals sign is last, then we are deleting the preceding key
                  key = line.substr(0, equalsIndex);
            	   //map.erase(key);
            	   }else{
            	   //If none of the above, then key = to string before =
            	   //and value is equal to strring after =
                     key = line.substr(0, equalsIndex);
                     val = line.substr(equalsIndex + 1, line.size());
                     val = trimWhitespace(val);
                     key = trimWhitespace(key);
                     map.insert(str_str_pair(key, val));

            	      cout << key << ":" << val << endl;
            	   }
            	}	   
            }
         }
      }
   }
   //if we did not have a file, we just do what we did above but with user input
   if(userInput == true){
      while(getline(cin, line)){
            line = trimWhitespace(line);
            size_t equalsIndex = line.find_first_of("=");
            //
            //As long a the line is not empty or not a comment.
            if(line.size() > 0 && line.at(0) != '#'){
              /* if(equalsIndex == string::npos){
                  //If no equals sign, print out value at given key
                  key = line;
                  str_str_map::iterator iter = map.find(key);
                  //If iter = iterator then it does not exist
                  if(iter == str_str_map::iterator()){
                    cout << iter->first << " : Key not found" << endl;
                  }else{
                     cout << iter->first << " = " << iter->second << endl;
                  } */
               } else {
                  if(line.size() == 1){
                  //Only possible argument is the equal, which prints out whole map
                     cout << "Here's the whole map!" << endl;
                     for (str_str_map::iterator itor = map.begin();
                        itor != map.end(); ++itor) {
                        cout <<  *itor << endl;
                     }
                  }else if(equalsIndex == 0 && line.size() > 1){
                  //If equal sign is first
                  //then print out the keys associated with the following value
                  val = line.substr(equalsIndex + 1, line.size());
                  //Goes through the whole map until it finds keys that have the given value
                  for(str_str_map::iterator iter = map.begin();
                        iter != map.end(); ++iter){
                     if(iter->second == val){
                        cout << iter->first << " = " << iter->second << endl;
                     }
                  }
                  }else if(equalsIndex == line.size() - 1){
                  //If equals sign is last, then we are deleting the preceding key
                  key = line.substr(0, equalsIndex);
                  //map.erase(key);
                  }else{
                  //If none of the above, then key = to string before =
                  //and value is equal to strring after =
                     key = line.substr(0, equalsIndex);
                     val = line.substr(equalsIndex + 1, line.size());
                     key = trimWhitespace(key);
                     val = trimWhitespace(val);
                     map.insert(str_str_pair(key, val));

                     cout << key << ":" << val << endl;
                  }
               }     
            }
         }

   }

   cout << "EXIT_SUCCESS" << endl;
   return EXIT_SUCCESS;
}

