#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_negative_guarantee_orig_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_negative_guarantee_orig_tradedate() { }
		~CIFast_IFast_ifastdbrkr_err_negative_guarantee_orig_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEGATIVE_GUARANTEE_ORIG_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There have been Negative Guarantees since the original trade date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There have been Negative Guarantees since the original trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu des garanties négatives depuis la date de transaction d'origine.")); }

        // Actions
	};
}



