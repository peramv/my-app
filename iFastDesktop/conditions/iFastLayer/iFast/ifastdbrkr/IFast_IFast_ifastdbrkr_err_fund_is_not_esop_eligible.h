#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_is_not_esop_eligible : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_is_not_esop_eligible() { }
		~CIFast_IFast_ifastdbrkr_err_fund_is_not_esop_eligible() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_IS_NOT_ESOP_ELIGIBLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund is not ESoP Eligible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds ist nicht EsoP-geeignet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este fondo no es apto para ESoP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas admissible au RADE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds komt niet in aanmerking voor ESoP")); }

        // Actions
	};
}



