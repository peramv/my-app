#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rif_spouse_older_than_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rif_spouse_older_than_shareholder() { }
		~CIFast_IFast_ifastcbo_warn_rif_spouse_older_than_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse is older than shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint est plus âgé que l'actionnaire.")); }

        // Actions
	};
}



