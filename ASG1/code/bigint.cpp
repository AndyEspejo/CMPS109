// $Id: bigint.cpp,v 1.73 2015-07-03 14:46:41-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+() const {
   return *this;
}

bigint bigint::operator-() const {
   return {uvalue, not is_negative};
}

//worked on this, checking if its negative then does needed operations
bigint bigint::operator+ (const bigint& that) const {
   ubigint result = 0;
   //If they are the same sign, just add and keep sign
   if(is_negative == that.is_negative){
   	result = uvalue + that.uvalue;
   	return {result, is_negative};

	//else, use sign of the bigger value
	}else if(uvalue > that.uvalue){
   	result = uvalue - that.uvalue;
	return {result, is_negative};
	
	}else{
	result = that.uvalue - uvalue;
	return {result, that.is_negative};
   	}
}
   


bigint bigint::operator- (const bigint& that) const {
   ubigint result = 0;
   //If they are the same sign, check which is bigger
   if (is_negative == that.is_negative){
	   if(uvalue > that.uvalue){
		   result = uvalue - that.uvalue;
		   return {result, !is_negative};
		   
		}else{
			result = that.uvalue - uvalue;
			return{result, that.is_negative};
		}
	//Else just add and make negative
   }else{
		result = uvalue + that.uvalue;
		return{result, is_negative};
   }
	   
	   
	   
}

bigint bigint::operator* (const bigint& that) const {
   bigint result = uvalue * that.uvalue;
   if(is_negative == that.is_negative){
	   result.is_negative = false;
	   return result;
   }else{
	   result.is_negative = true;
	   return result;
   }
}


bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   return result;
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const {
   if(is_negative == that.is_negative && uvalue == that.uvalue){
	   return true;
   }
   return false;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "'-'" : "'+'")
              << that.uvalue << ")";
}

