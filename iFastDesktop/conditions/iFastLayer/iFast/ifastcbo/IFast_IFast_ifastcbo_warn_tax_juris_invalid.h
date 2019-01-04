#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tax_juris_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tax_juris_invalid() { }
		~CIFast_IFast_ifastcbo_warn_tax_juris_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TAX_JURIS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Jurisdiction not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Juridiction fiscale non trouvée.")); }

        // Actions
	};
}



