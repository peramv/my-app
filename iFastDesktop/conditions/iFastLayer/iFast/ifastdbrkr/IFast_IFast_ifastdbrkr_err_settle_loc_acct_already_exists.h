#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_settle_loc_acct_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_settle_loc_acct_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_settle_loc_acct_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_LOC_ACCT_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account level settlement location record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account level settlement location record already exists.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account level settlement location record already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du lieu de règlement au niveau du compte existe déjà.")); }

        // Actions
	};
}



