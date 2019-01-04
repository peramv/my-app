#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_not_applicable_deptype_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_not_applicable_deptype_redcode() { }
		~CIFast_IFast_ifastcbo_err_not_applicable_deptype_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_APPLICABLE_DEPTYPE_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either deposit type or redemption code is not applicable for this trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt ou de rachat n'est pas applicable à cette transaction.")); }

        // Actions
	};
}



