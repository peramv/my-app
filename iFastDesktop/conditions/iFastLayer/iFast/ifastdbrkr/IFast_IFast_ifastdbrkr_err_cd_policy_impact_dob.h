#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cd_policy_impact_dob : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cd_policy_impact_dob() { }
		~CIFast_IFast_ifastdbrkr_err_cd_policy_impact_dob() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CD_POLICY_IMPACT_DOB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CD  policy(s) impacted by DOB change.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("CD  policy(s) impacted by DOB change.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les polices de distribution de capital sont touchées par le changement de date de naissance.")); }

        // Actions
	};
}



