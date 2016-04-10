// $Id: ubigint.cpp,v 1.11 2016-03-24 19:57:29-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <math.h>
using namespace std;

#include "ubigint.h"
#include "debug.h"



//Creates a vector of the digits
ubigint::ubigint (const string& that): ubig_value(0) {
   for (auto itor = that.rbegin(); itor != that.rend(); ++itor){
	   ubig_value.push_back(*itor);
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint result;
   int carry = 0;
   int sum = 0;
   //Gets size of biggest to make sure all digits are added
   if(ubig_value.size() > that.ubig_value.size()){
	   size_t size_of_result = ubig_value.size();
   }else{
	   size_t size_of_result = that.ubig_value.size();
   }
   //Actual implementation for adding
   for(size_t i = 0; i < size_of_result; i++){
	 sum = carry;
	 if(i < ubig_value.size()){
		 sum = sum + ubig_value.at(i)
	 }
	 if(i < that.ubig_value.size()){
		 sum = sum + that.ubig_value.at(i);
	 }
	 if(sum > 10){
		 carry = 1;
		 result.push_back(sum-10);
	 }else{
		 result.push_back(sum);
	 }
   }
   //Add code to get rid of leading zeros
	return result

}

ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   return ubigint (uvalue - that.uvalue);
}

ubigint ubigint::operator* (const ubigint& that) const {
   return ubigint (uvalue * that.uvalue);
}

void ubigint::multiply_by_2() {
   uvalue *= 2;
}

void ubigint::divide_by_2() {
   uvalue /= 2;
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, ubigint divisor) {
   // Note: divisor is modified so pass by value (copy).
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   return uvalue == that.uvalue;
}

bool ubigint::operator< (const ubigint& that) const {
   return uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   return out << "ubigint(" << that.uvalue << ")";
}

