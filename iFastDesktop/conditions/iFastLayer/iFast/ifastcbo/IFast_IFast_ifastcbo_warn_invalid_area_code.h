#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_area_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_area_code() { }
		~CIFast_IFast_ifastcbo_warn_invalid_area_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_AREA_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid area code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Indicatif régional invalide")); }

        // Actions
	};
}



