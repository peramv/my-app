#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dta_not_allowed_for_this_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dta_not_allowed_for_this_redcode() { }
		~CIFast_IFast_ifastcbo_err_dta_not_allowed_for_this_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DTA_NOT_ALLOWED_FOR_THIS_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct trading not allowed for this red code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Direct trading not allowed for this red code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Direct trading not allowed for this red code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Opération directe non autorisée pour ce code de rachat")); }

        // Actions
	};
}



