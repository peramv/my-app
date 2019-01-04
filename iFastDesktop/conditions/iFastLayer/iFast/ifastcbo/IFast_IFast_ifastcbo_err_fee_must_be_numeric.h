#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_must_be_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_must_be_numeric() { }
		~CIFast_IFast_ifastcbo_err_fee_must_be_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MUST_BE_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee must be in numeric value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision muss nummerisch eingegeben werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión debe estar en el valor numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais doivent être une valeur numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten moeten in numerieke waarde worden uitgedrukt")); }

        // Actions
	};
}



