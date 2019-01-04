#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_jurisdiction_not_same_as_shrhldr_jurisdiction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_jurisdiction_not_same_as_shrhldr_jurisdiction() { }
		~CIFast_IFast_ifastcbo_warn_jurisdiction_not_same_as_shrhldr_jurisdiction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountholder jurisdiction should be the same as the shareholder tax jurisdiction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction devrait être la même que la juridiction fiscale de l’actionnaire.")); }

        // Actions
	};
}



