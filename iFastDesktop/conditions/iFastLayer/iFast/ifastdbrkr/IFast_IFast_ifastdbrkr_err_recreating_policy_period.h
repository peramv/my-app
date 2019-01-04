#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_recreating_policy_period : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_recreating_policy_period() { }
		~CIFast_IFast_ifastdbrkr_err_recreating_policy_period() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RECREATING_POLICY_PERIOD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error in recreating Policy Periods.  Check Contract dates of the account .")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Error in recreating Policy Periods.  Check Contract dates of the account .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de la recréation des périodes de la police. Vérifiez les dates de contrat du compte.")); }

        // Actions
	};
}



