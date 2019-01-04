#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_payment_method : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_payment_method() { }
		~CIFast_IFast_ifastcbo_err_invalid_payment_method() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PAYMENT_METHOD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Payment Method.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid Payment Method.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Payment Method.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("M�thode de paiement invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Payment Method.")); }

        // Actions
	};
}



