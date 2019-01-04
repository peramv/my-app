#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_found_resp_earning_grant_redcodes_controls_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_found_resp_earning_grant_redcodes_controls_record() { }
		~CIFast_IFast_ifastdbrkr_err_not_found_resp_earning_grant_redcodes_controls_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_FOUND_RESP_EARNING_GRANT_REDCODES_CONTROLS_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to find RESP Earning&Grant RedCodes controls record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'enregistrement des contrôles des codes de rachat de subvention et de revenu REEE.")); }

        // Actions
	};
}



