#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_year_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_year_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_warn_resp_year_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_YEAR_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Year Limit for %BENNAME% is exceeded. Annual Contribution Limit %ANNUALLIMIT% exceeded. Annual Contribution to date is %TODATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La limite annuelle REEE pour %BENNAME% est excédée. Le plafond annuel de cotisation de %ANNUALLIMIT% est excédé. La cotisation annuelle à ce jour est de %TODATE%.")); }

        // Actions
	};
}



