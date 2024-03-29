// $Id: file_sys.cpp,v 1.5 2016-01-14 16:16:52-08 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>

using namespace std;

#include "debug.h"
#include "file_sys.h"

int inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
      {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}


inode_state::inode_state() {
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
   //First we need to start off with just the root
   //Will also be set to current directory
   inode rootDir(file_type::DIRECTORY_TYPE, "/");
   root = make_shared<inode>(rootDir);
   cwd = root;
   //All directories be defualt should have . and ..
   rootDir.setRoot(root);
   rootDir.setPar(root);
}

const string& inode_state::prompt() { return prompt_; }

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

//I modified this to make make it easier to work with the name of the file
inode::inode(file_type type, string fileName): inode_nr (next_inode_nr++) {
   name = fileName;
   switch (type) {
	   
      case file_type::PLAIN_TYPE:
           contents = make_shared<plain_file>();
           break;
      case file_type::DIRECTORY_TYPE:
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

file_error::file_error (const string& what):
            runtime_error (what) {
}

//Iterates through the ordered map from directory class in the header file
//map has: string,inode_ptr>, so we print out the first part of the pair
void inode_state::printDir(inode_ptr& curDir){
	map<string,inode_ptr> currentMap = curDir->contents->getMap();
	for(auto iter = currentMap.cbegin(); iter != currentMap.cend(); iter++){
		cout << iter->first << endl;
	}
}

//setRoot and setPar just set root and parent to . and .. respectivaly. 
void inode::setRoot(inode_ptr root){
   dynamic_pointer_cast<directory>(contents) -> newDir(string("."), root);
}

void inode::setPar(inode_ptr par){
   dynamic_pointer_cast<directory>(contents) -> newDir(string(".."), par);
}

//mkdir and mkfile as called in commands.cpp, and then these call the functions below
//To actually insert files/directories into the map
inode_ptr inode::mkdir(string dirName){
   inode_ptr newDir = dynamic_pointer_cast<directory>(contents)->mkdir(dirName);
   newDir->setPar(make_shared<inode>(*this));
   return newDir;
}

inode_ptr inode::mkfile(string fileName){
   return dynamic_pointer_cast<directory>(contents)->mkfile(fileName);
}

void inode::writefile(const wordvec& fileContents){
   dynamic_pointer_cast<plain_file>(contents)-> writefile(fileContents);
}


size_t plain_file::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

void plain_file::writefile (const wordvec& words) {
   data = words;
   DEBUGF ('i', words);
}

void plain_file::remove (const string&) {
   throw file_error ("is a plain file");
}

inode_ptr plain_file::mkdir (const string&) {
   throw file_error ("is a plain file");
}

inode_ptr plain_file::mkfile (const string&) {
   throw file_error ("is a plain file");
}

map<string,inode_ptr>& plain_file::getMap(){
	throw file_error ("is a plain file");
}

void directory::newDir(string name, inode_ptr dir){
	dirents.insert(pair<string, inode_ptr>(name, dir));
}
size_t directory::size() const {
   size_t size {0};
   return size = dirents.size();
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& directory::readfile() const {
   throw file_error ("is a directory");
}

void directory::writefile (const wordvec&) {
   throw file_error ("is a directory");
}

void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
}

//Makes a new inode with file type directory, as well as the shared ptr
//Then inserts the directory into the map
inode_ptr directory::mkdir (const string& dirname) {
   DEBUGF ('i', dirname);
   inode newDir (file_type::DIRECTORY_TYPE, dirname);
   inode_ptr dirPtr = make_shared<inode>(newDir);
   
   dirents.insert(pair<string,inode_ptr>("/" + dirname,dirPtr));
   
   
   return dirPtr;
}

//Same as mkdir but with a normal (text) file
inode_ptr directory::mkfile (const string& filename) {
   DEBUGF ('i', filename);
   inode newFile(file_type::PLAIN_TYPE,filename);
   inode_ptr filePtr = make_shared<inode>(newFile);
   
   dirents.insert(pair<string,inode_ptr>(filename,filePtr));
   
   return filePtr;  
}

map<string,inode_ptr>& directory::getMap(){
	return dirents;
}



