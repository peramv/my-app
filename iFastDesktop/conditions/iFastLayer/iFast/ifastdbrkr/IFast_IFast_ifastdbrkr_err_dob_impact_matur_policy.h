#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dob_impact_matur_policy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dob_impact_matur_policy() { }
		~CIFast_IFast_ifastdbrkr_err_dob_impact_matur_policy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOB_IMPACT_MATUR_POLICY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DOB change impacts matured/reset policy.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DOB change impacts matured/reset policy.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement de date de naissance touche la police mature/revalorisée.")); }

        // Actions
	};
}



