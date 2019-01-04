#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_eligable_for_rolloverex : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_eligable_for_rolloverex() { }
		~CIFast_IFast_ifastcbo_err_fund_not_eligable_for_rolloverex() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_ELIGABLE_FOR_ROLLOVEREX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Fund %FUND% Class %CLASS% is not eligible for Rollover Exchange.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% de catégorie %CLASS% n’est pas admissible à un transfert avec report d’impôt.")); }

        // Actions
	};
}



