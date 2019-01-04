#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund_wkn : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund_wkn() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund_wkn() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_WKN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund does not exist for selected WKN, please enter a valid WKN.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund does not exist for selected WKN, please enter a valid WKN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'existe pas pour le WKN sélectionné, veuillez entrer un WKN valide.")); }

        // Actions
	};
}



