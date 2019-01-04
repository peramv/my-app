#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_non_int_amt_zero_precision : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_non_int_amt_zero_precision() { }
		~CIFast_IFast_ifastdbrkr_err_non_int_amt_zero_precision() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_INT_AMT_ZERO_PRECISION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Non-integer amount for zero precision currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein ganzzahliger Betrag für ungenaue Währung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Monto no entero para divisa de precisión cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Montant non entier pour l'absence de monnaie de précision")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen geheel getal voor nul-precisievaluta")); }

        // Actions
	};
}



