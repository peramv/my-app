#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_different_reg_agent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_different_reg_agent() { }
		~CIFast_IFast_ifastcbo_err_different_reg_agent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIFFERENT_REG_AGENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account owner has at least one active account with the same tax type (OA, SA or SRS) and the Registration Agent entities are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le propriétaire du compte a au moins un autre compte actif du même type de taxe (OA, SA ou SRS) et les entités du représentant d’inscription sont différentes.")); }

        // Actions
	};
}



