#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_reset_occured_since_orig_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_reset_occured_since_orig_tradedate() { }
		~CIFast_IFast_ifastdbrkr_err_reset_occured_since_orig_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESET_OCCURED_SINCE_ORIG_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A reset has occured since the original trade date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("A reset has occured since the original trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une revalorisation a eu lieu depuis la date de transaction d'origine.")); }

        // Actions
	};
}



