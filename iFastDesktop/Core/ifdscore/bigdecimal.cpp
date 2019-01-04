#define DICORE_DLL

#include ".\bigdecimal.hpp"

extern CLASS_EXPORT const BigDecimal BIGDEC_ZERO(0L);
extern CLASS_EXPORT const BigDecimal BIGDEC_ONE(1L);

BigDecimalContext BigDecimalContext::CTXT;

BigDecimalContext::BigDecimalContext() {
   decContextDefault(&ctxt, DEC_INIT_BASE);
   decContextSetRounding(&ctxt, DEC_ROUND_HALF_UP);
   ctxt.traps=0;
   ctxt.digits=DECNUMDIGITS;   
}

BigDecimalContext::~BigDecimalContext(void) {
}

BigDecimalContext& BigDecimalContext::get() {
   return CTXT;
}

void BigDecimalContext::setRounding(enum rounding newRound) {
   decContextSetRounding(&ctxt, newRound);
}

enum rounding BigDecimalContext::getRounding() {
   return decContextGetRounding(&ctxt);
}

