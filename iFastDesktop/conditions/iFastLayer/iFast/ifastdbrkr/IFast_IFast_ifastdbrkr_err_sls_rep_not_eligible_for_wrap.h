#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_sls_rep_not_eligible_for_wrap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_sls_rep_not_eligible_for_wrap() { }
		~CIFast_IFast_ifastdbrkr_err_sls_rep_not_eligible_for_wrap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SLS_REP_NOT_ELIGIBLE_FOR_WRAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Representative is not eligible for Wrap Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sales Representative is not eligible for Wrap Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sales Representative is not eligible for Wrap Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes n'est pas admissible pour un compte intégré.")); }

        // Actions
	};
}



