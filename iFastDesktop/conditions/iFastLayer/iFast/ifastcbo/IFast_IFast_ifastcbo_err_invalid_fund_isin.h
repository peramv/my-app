#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund_isin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund_isin() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund_isin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_ISIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund does not exist for selected ISIN, please enter a valid ISIN.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund does not exist for selected ISIN, please enter a valid ISIN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds n'existe pas pour le ISIN sélectionné, veuillez entrer un ISIN valide.")); }

        // Actions
	};
}



