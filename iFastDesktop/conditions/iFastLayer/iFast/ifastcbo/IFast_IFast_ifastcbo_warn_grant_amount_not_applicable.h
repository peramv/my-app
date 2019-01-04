#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_grant_amount_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_grant_amount_not_applicable() { }
		~CIFast_IFast_ifastcbo_warn_grant_amount_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GRANT_AMOUNT_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not Sibling Only. Grant amount is not applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas Frère/sœur seulement. Le montant de subvention n'est pas applicable.")); }

        // Actions
	};
}



