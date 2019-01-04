#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_settle_loc_acct_data_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_settle_loc_acct_data_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_settle_loc_acct_data_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_LOC_ACCT_DATA_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account level settlement location data not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account level settlement location data not found.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account level settlement location data not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les données du lieu de règlement au niveau du compte sont introuvables.")); }

        // Actions
	};
}



