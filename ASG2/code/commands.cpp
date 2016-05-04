// $Id: commands.cpp,v 1.16 2016-01-14 16:10:40-08 - - $

#include "commands.h"
#include "debug.h"

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}

//Was going to use this to check if the needed directory existed
//However I am not sure how to, so it breaks CD, but allows for
//ls, mkdir, pwd, and mkfile to work
inode_ptr checkDir(inode_state& state, const wordvec path){
   inode_ptr tmp = state.getRoot();
   return tmp;
} 

void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}


void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   
   inode_ptr root = state.getRoot();
   if(words.size() == 1){
      //Set current directory to root directory
      state.setDir(root);
   }else if(words.size() == 2){
      //Set current directory to words[1]
	  //Does not actually work as stated above
	  wordvec path = split(words.at(1), "/");
      inode_ptr newCWD = checkDir(state, path);
	  state.setDir(newCWD);
   }
      
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}


void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr curDir = state.getCurrent();
   if(words.size() == 1){
      //List files in current directory
	  state.printDir(curDir);
   }else if(words.size() == 2){
      //List files in directory words[1]
	  //Not implemented, same as CD
      cout << "printing" << " " << words[1];;
   }
}

//Not Implemented
void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1){
      //Not enough arguments error
      cout << "Not enough arguments needed: > 1";
   }else if(words.size() == 2){
      //Make an empty file named words[1]
	  wordvec fileName = split(words.at(1), "/");
	  inode_ptr newFile = checkDir(state, fileName);
      inode_ptr fileToWrite = newFile->mkfile(fileName.back());
      //Make a file and fill it with the rest of what was typed
   }else if(words.size() > 2){
	  wordvec fileName = split(words.at(1), "/");
	  inode_ptr newFile = checkDir(state, fileName);
      inode_ptr fileToWrite = newFile->mkfile(fileName.back());
	  wordvec data = words;
	  data.erase(words.begin());
	  data.erase(words.begin());
	  fileToWrite->writefile(data);
   }      
}

void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1){
      cout << "Not enough arguments, needed: 2";
   }else if(words.size() == 2){
	  //Separates the second part of the argument(the file name)
	  //And then check if its valid(not working), then creates the directory
	  wordvec path = split(words.at(1), "/");
      inode_ptr newDir = checkDir(state, path);
      newDir->mkdir(path.back()); 
   }else if(words.size() > 2){
      cout << "Too many arguments, needed: 2";
   }
   
}

//This simply iterates through and adds everything passed to update the prompt
void fn_prompt (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   string newPrompt = "";
   if(words.size() == 1){
	   cout << "Not enough arguemnts, needed: > 1" << endl;
   }else{
	   for(size_t i = 1; i < words.size(); i++){
		   newPrompt += words.at(i) + " ";;   
	   }
	state.updatePrompt(newPrompt);
   }
}

//Just prints out the name of the directory
void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode curDir = *state.getCurrent();
   cout << curDir.getName() << endl;
}

//Not implemented
void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1){
	   cout << "Not enough arguments, needed: 2";
   }else if(words.size() == 2){
	   //Remove the directory/file
	   cout << "Removing directory";
   }
}

//Not Implemented
void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}



