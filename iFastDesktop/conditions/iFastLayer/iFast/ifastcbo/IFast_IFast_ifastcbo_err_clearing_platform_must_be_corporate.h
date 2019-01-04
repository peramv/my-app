#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearing_platform_must_be_corporate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearing_platform_must_be_corporate() { }
		~CIFast_IFast_ifastcbo_err_clearing_platform_must_be_corporate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARING_PLATFORM_MUST_BE_CORPORATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For Clearing Platform entity type, its category must be corporate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour le type d'entité de plateforme de compensation, la catégorie doit être corporative.")); }

        // Actions
	};
}



