#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_must_be_zero_or_greater : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_must_be_zero_or_greater() { }
		~CIFast_IFast_ifastcbo_err_fee_must_be_zero_or_greater() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MUST_BE_ZERO_OR_GREATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee must be zero or greater.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision muss größer als Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión debe ser cero o mayor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais doivent être de zéro ou plus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten moeten nul zijn of hoger")); }

        // Actions
	};
}



