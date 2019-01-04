#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ensure_pac_is_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ensure_pac_is_allowed() { }
		~CIFast_IFast_ifastcbo_warn_ensure_pac_is_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ENSURE_PAC_IS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Jurisdiction changing.  Ensure PAC is allowed for new tax jurisdiction")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax Jurisdiction changing.  Ensure PAC is allowed for new tax jurisdiction")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changement de juridiction fiscale. Assurez-vous que le PAC est autorisé pour la nouvelle juridiction fiscale.")); }

        // Actions
	};
}



