#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_not_eligible_for_commission : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_not_eligible_for_commission() { }
		~CIFast_IFast_ifastdbrkr_err_fund_not_eligible_for_commission() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_ELIGIBLE_FOR_COMMISSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund not eligible for commission.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds für Provision nicht geeignet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este fondo no es apto para comisión")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'est pas admissible à la commission.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds komt niet in aanmerking voor commissie")); }

        // Actions
	};
}



