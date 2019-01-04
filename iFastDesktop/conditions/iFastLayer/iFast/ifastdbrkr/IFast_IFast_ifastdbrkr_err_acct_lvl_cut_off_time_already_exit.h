#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_lvl_cut_off_time_already_exit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_lvl_cut_off_time_already_exit() { }
		~CIFast_IFast_ifastdbrkr_err_acct_lvl_cut_off_time_already_exit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_LVL_CUT_OFF_TIME_ALREADY_EXIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Level Cut Off Time already exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account Level Cut Off Time already exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'heure limite au niveau du compte existe déjà.")); }

        // Actions
	};
}



