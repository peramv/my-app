#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_deptype_redcode_not_allowed_in_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_deptype_redcode_not_allowed_in_transfer() { }
		~CIFast_IFast_ifastcbo_warn_deptype_redcode_not_allowed_in_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEPTYPE_REDCODE_NOT_ALLOWED_IN_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DP 20 or RD 61, 83, 84 not allowed in Transfer.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("DP 20 or RD 61, 83, 84 non autorisés pour un transfert.")); }

        // Actions
	};
}



