#pragma once

#include <commonport.h>
#include <dstringa.hpp>

#define DECNUMDIGITS 34
extern "C" {
   #include "decNumber.h"
}
#define DEC_BUFFER_SZ DECNUMDIGITS+14

#include <iostream>

// standard linkage-specifier macro
#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif



class DICORE_LINKAGE BigDecimalContext {
public:
   ~BigDecimalContext(void);

   friend class BigDecimal;
   friend std::istream& operator>>(std::istream& lhs, BigDecimal& rhs);
#ifdef DST_UNICODE
   friend i_istream& operator>>(i_istream& lhs, BigDecimal& rhs);
#endif

   void setRounding(enum rounding newRound);
   enum rounding getRounding();

   static BigDecimalContext& get();

private:

   BigDecimalContext();

   static BigDecimalContext CTXT;
   decContext ctxt;
};



class BigDecimal {
public:

   friend bool operator==(const BigDecimal& lhs, const BigDecimal& rhs);
   friend bool operator<=(const BigDecimal& lhs, const BigDecimal& rhs);
   friend bool operator<(const BigDecimal& lhs, const BigDecimal& rhs);
   friend std::istream& operator>>(std::istream& lhs, BigDecimal& rhs);
   friend std::ostream& operator<<(std::ostream& lhs, const BigDecimal& rhs);
#ifdef DST_UNICODE
   friend i_istream& operator>>(i_istream& lhs, BigDecimal& rhs);
   friend i_ostream& operator<<(i_ostream& lhs, const BigDecimal& rhs);
#endif

   BigDecimal() {
   }

   BigDecimal(__int32 val) {
      decNumberFromInt32(&decValue, val);
   }

   BigDecimal(unsigned __int32 val) {
      decNumberFromUInt32(&decValue, val);
   }

   BigDecimal(const DString& val) {
      DStringA aVal(val);
      char buffer[1024];
      strncpy(buffer, aVal.c_str(), aVal.size());
      buffer[aVal.size()] = (char)0;
      decNumberFromString(&decValue, buffer, &BigDecimalContext::CTXT.ctxt);
   }

   BigDecimal(const A_STRING& val) {
      char buffer[1024];
      strncpy(buffer, val.c_str(), val.size());
      buffer[val.size()] = (char)0;
      decNumberFromString(&decValue, buffer, &BigDecimalContext::CTXT.ctxt);
   }

   BigDecimal(const char* val) {
      decNumberFromString(&decValue, val, &BigDecimalContext::CTXT.ctxt);
   }

   BigDecimal(const BigDecimal& val) {
      decNumberCopy(&decValue, &val.decValue);
   }

   ~BigDecimal(void) {
   }

   // assignment operators
   BigDecimal& operator=(const BigDecimal& rhs);
   BigDecimal& operator+=(const BigDecimal& rhs);
   BigDecimal& operator-=(const BigDecimal& rhs);
   BigDecimal& operator*=(const BigDecimal& rhs);
   BigDecimal& operator/=(const BigDecimal& rhs);

   // uniary operators
   const BigDecimal operator-() const;
   BigDecimal operator-();

   const BigDecimal abs() const; 
   BigDecimal abs();

   // binary operators
   const BigDecimal operator+(const BigDecimal& rhs) const;
   BigDecimal operator+(const BigDecimal& rhs);

   const BigDecimal operator-(const BigDecimal& rhs) const;
   BigDecimal operator-(const BigDecimal& rhs);

   const BigDecimal operator*(const BigDecimal& rhs) const;
   BigDecimal operator*(const BigDecimal& rhs);

   const BigDecimal operator/(const BigDecimal& rhs) const;
   BigDecimal operator/(const BigDecimal& rhs);

   // increment/decrement operators
   BigDecimal& operator++();
   const BigDecimal operator++(int);

   BigDecimal& operator--();
   const BigDecimal operator--(int);

   BigDecimal scaled(__int32 scale);
   const BigDecimal scaled(__int32 scale) const;

   DStringA asDStringA();
   const DStringA asDStringA() const;
   DStringA asDStringA(__int32 scale);
   const DStringA asDStringA(__int32 scale) const;

   DString asDString();
   const DString asDString() const;
   DString asDString(__int32 scale);
   const DString asDString(__int32 scale) const;

private:

   BigDecimal add(const BigDecimal& rhs) const;
   BigDecimal subtract(const BigDecimal& rhs) const;
   BigDecimal multiply(const BigDecimal& rhs) const;
   BigDecimal divide(const BigDecimal& rhs) const;
   BigDecimal power(const BigDecimal& rhs) const;

   bool eq(const BigDecimal& rhs) const;
   bool lt(const BigDecimal& rhs) const;
   bool lteq(const BigDecimal& rhs) const;

   decNumber decValue;

};


extern DICORE_LINKAGE const BigDecimal BIGDEC_ZERO;
extern DICORE_LINKAGE const BigDecimal BIGDEC_ONE;


inline BigDecimal& BigDecimal::operator=(const BigDecimal& rhs) {
   if (this != &rhs) {
      decNumberCopy(&decValue, &rhs.decValue);
   }
   return *this;
}
   
inline BigDecimal& BigDecimal::operator+=(const BigDecimal& rhs) {
   *this = add(rhs);
   return *this;
}

inline BigDecimal& BigDecimal::operator-=(const BigDecimal& rhs) {
   *this = subtract(rhs);
   return *this;
}   

inline BigDecimal& BigDecimal::operator*=(const BigDecimal& rhs) {
   *this = *this*rhs;
   return *this;
}

inline BigDecimal& BigDecimal::operator/=(const BigDecimal& rhs) {
   *this = *this/rhs;
   return *this;
}

inline const BigDecimal BigDecimal::operator-() const {  // negate 
   BigDecimal result;
   // TODO: investigate decNumberCopyNegate instead 
   decNumberCopyNegate(&result.decValue, &decValue);
   return result;
}

inline BigDecimal BigDecimal::operator-() {  // negate 
   BigDecimal result;
   // TODO: investigate decNumberCopyNegate instead 
   decNumberCopyNegate(&result.decValue, &decValue);
   return result;
}

inline const BigDecimal BigDecimal::abs() const {
   BigDecimal result;
   decNumberAbs(&result.decValue, &decValue, &BigDecimalContext::CTXT.ctxt);
   return result;
}

inline BigDecimal BigDecimal::abs() {
   BigDecimal result;
   decNumberAbs(&result.decValue, &decValue, &BigDecimalContext::CTXT.ctxt);
   return result;
}

inline const BigDecimal BigDecimal::operator+(const BigDecimal& rhs) const {
   return add(rhs);
}

inline BigDecimal BigDecimal::operator+(const BigDecimal& rhs) {
   return add(rhs);
}

inline const BigDecimal BigDecimal::operator-(const BigDecimal& rhs) const {
   return subtract(rhs);
}

inline BigDecimal BigDecimal::operator-(const BigDecimal& rhs) {
   return subtract(rhs);
}

inline const BigDecimal BigDecimal::operator*(const BigDecimal& rhs) const {
   return multiply(rhs);
}

inline BigDecimal BigDecimal::operator*(const BigDecimal& rhs) {
   return multiply(rhs);
}

inline const BigDecimal BigDecimal::operator/(const BigDecimal& rhs) const {
   return divide(rhs);
}

inline BigDecimal BigDecimal::operator/(const BigDecimal& rhs) {
   return divide(rhs);
}

inline BigDecimal& BigDecimal::operator++() {
   *this += BIGDEC_ONE;
   return *this;
}

inline const BigDecimal BigDecimal::operator++(int) {
   BigDecimal oldVal = *this;
   ++(*this);
   return oldVal;
}

inline BigDecimal& BigDecimal::operator--() {
   *this -= BIGDEC_ONE;
   return *this;
}

inline const BigDecimal BigDecimal::operator--(int) {
   BigDecimal oldVal = *this;
   --(*this);
   return oldVal;
}

inline BigDecimal BigDecimal::scaled(__int32 scale) {
   BigDecimal roundedValue;
   decNumberRescale(&roundedValue.decValue, 
                    &decValue, 
                    &BigDecimal(scale).decValue, 
                    &BigDecimalContext::CTXT.ctxt);
   return roundedValue;
}

inline const BigDecimal BigDecimal::scaled(__int32 scale) const {
   BigDecimal roundedValue;
   decNumberRescale(&roundedValue.decValue, 
                    &decValue, 
                    &BigDecimal(scale).decValue, 
                    &BigDecimalContext::CTXT.ctxt);
   return roundedValue;
}

inline DStringA BigDecimal::asDStringA() {
   char buffer[DEC_BUFFER_SZ];
   decNumberToString(&decValue, buffer);
   return DStringA(buffer);
}

inline const DStringA BigDecimal::asDStringA() const {
   char buffer[DEC_BUFFER_SZ];
   decNumberToString(&decValue, buffer);
   return DStringA(buffer);
}

inline DStringA BigDecimal::asDStringA(__int32 scale) {
   char buffer[DEC_BUFFER_SZ];
   BigDecimal scaledValue = scaled(scale);

   if(decNumberIsZero(&scaledValue.decValue))
      scaledValue = BIGDEC_ZERO;

   decNumberToString(&scaledValue.decValue, buffer);
   return DStringA(buffer);
}

inline const DStringA BigDecimal::asDStringA(__int32 scale) const {
   char buffer[DEC_BUFFER_SZ];
   BigDecimal scaledValue = scaled(scale);

   if(decNumberIsZero(&scaledValue.decValue))
      scaledValue = BIGDEC_ZERO;

   decNumberToString(&scaledValue.decValue, buffer);
   return DStringA(buffer);
}

inline DString BigDecimal::asDString() {
   return DString(this->asDStringA());
}

inline const DString BigDecimal::asDString() const {
   return DString(this->asDStringA());
}

inline DString BigDecimal::asDString(__int32 scale) {
   return DString(this->asDStringA(scale));
}

inline const DString BigDecimal::asDString(__int32 scale) const {
   return DString(this->asDStringA(scale));
}

inline bool operator==(const BigDecimal& lhs, const BigDecimal& rhs) {
   return lhs.eq(rhs);
}

inline bool operator!=(const BigDecimal& lhs, const BigDecimal& rhs) {
   return !(lhs==rhs);
}

inline bool operator<(const BigDecimal& lhs, const BigDecimal& rhs) {
   return lhs.lt(rhs);
}

inline bool operator>=(const BigDecimal& lhs, const BigDecimal& rhs) {
   return !(lhs<rhs);
}

inline bool operator<=(const BigDecimal& lhs, const BigDecimal& rhs) {
   return lhs.lteq(rhs);
}

inline bool operator>(const BigDecimal& lhs, const BigDecimal& rhs) {
   return !(lhs<=rhs);
}

inline std::istream& operator>>(std::istream& lhs, BigDecimal& rhs) {
   char buffer[1024];
   lhs >> buffer;
   decNumberFromString(&rhs.decValue, buffer, &BigDecimalContext::CTXT.ctxt);
   return lhs;
}

inline std::ostream& operator<<(std::ostream& lhs, const BigDecimal& rhs) {
   char buffer[DEC_BUFFER_SZ];
   decNumberToString(&rhs.decValue, buffer);
   return lhs << buffer;
}

#ifdef DST_UNICODE
inline i_istream& operator>>(i_istream& lhs, BigDecimal& rhs) {
   I_CHAR ibuffer[1024];
   lhs >> ibuffer;
   char buffer[1024];
   
   unsigned i = 0;
   for( i = 0; ibuffer[i]!=(char)0; ++i )
   {
      buffer[i] = (char)ibuffer[i];
   }
   buffer[ i ] = '\0';

   decNumberFromString(&rhs.decValue, buffer, &BigDecimalContext::CTXT.ctxt);
   return lhs;
}

inline i_ostream& operator<<(i_ostream& lhs, const BigDecimal& rhs) {
   char buffer[DEC_BUFFER_SZ];
   decNumberToString(&rhs.decValue, buffer);
   return lhs << buffer;
}
#endif

inline BigDecimal BigDecimal::add(const BigDecimal& rhs) const {
   BigDecimal result;
   decNumberAdd(&result.decValue, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return result;
}

inline BigDecimal BigDecimal::subtract(const BigDecimal& rhs) const {
   BigDecimal result;
   decNumberSubtract(&result.decValue, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return result;
}

inline BigDecimal BigDecimal::multiply(const BigDecimal& rhs) const {
   BigDecimal result;
   decNumberMultiply(&result.decValue, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return result;
}

inline BigDecimal BigDecimal::divide(const BigDecimal& rhs) const {
   BigDecimal result;
   decNumberDivide(&result.decValue, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return result;
}

inline bool BigDecimal::eq(const BigDecimal& rhs) const {
   decNumber result;
   decNumberCompareSignal(&result, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return (decNumberIsZero(&result)!=0);
}

inline bool BigDecimal::lt(const BigDecimal& rhs) const {
   decNumber result;
   decNumberCompareSignal(&result, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return (decNumberIsNegative(&result)!=0);
}

inline bool BigDecimal::lteq(const BigDecimal& rhs) const {
   decNumber result;
   decNumberCompareSignal(&result, &decValue, &rhs.decValue, &BigDecimalContext::CTXT.ctxt);
   // TODO: handle status here
   return (decNumberIsNegative(&result)!=0 || decNumberIsZero(&result)!=0);
}

//BigDecimal BigDecimal::handle_status() const {
//}






