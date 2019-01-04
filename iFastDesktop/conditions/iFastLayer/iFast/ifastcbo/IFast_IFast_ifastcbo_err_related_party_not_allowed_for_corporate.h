#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_related_party_not_allowed_for_corporate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_related_party_not_allowed_for_corporate() { }
		~CIFast_IFast_ifastcbo_err_related_party_not_allowed_for_corporate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RELATED_PARTY_NOT_ALLOWED_FOR_CORPORATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Related Party cannot be a Corporate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La partie apparentée ne peut être une société.")); }

        // Actions
	};
}



