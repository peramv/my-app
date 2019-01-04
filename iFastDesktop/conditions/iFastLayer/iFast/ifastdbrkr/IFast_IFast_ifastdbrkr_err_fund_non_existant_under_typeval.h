#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_non_existant_under_typeval : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_non_existant_under_typeval() { }
		~CIFast_IFast_ifastdbrkr_err_fund_non_existant_under_typeval() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NON_EXISTANT_UNDER_TYPEVAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund does not exist under Fund ID Type and Fund ID Value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund does not exist under Fund ID Type and Fund ID Value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'existe pas pour le type de code de fonds et la valeur de code de fonds.")); }

        // Actions
	};
}



