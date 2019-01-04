#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_associated_grant_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_associated_grant_trade() { }
		~CIFast_IFast_ifastcbo_warn_associated_grant_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ASSOCIATED_GRANT_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade has %PENDPROC% grant associated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une subvention %PENDPROC% est associée à la transaction.")); }

        // Actions
	};
}



