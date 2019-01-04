#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_redcode_applicable_to_sttrading : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_redcode_applicable_to_sttrading() { }
		~CIFast_IFast_ifastcbo_warn_redcode_applicable_to_sttrading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REDCODE_APPLICABLE_TO_STTRADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please verify, redemption code is applicable to charge short term transfer and early redemption fees...")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Please verify, redemption code is applicable to charge short term transfer and early redemption fees...")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez vérifier, le code de rachat est applicable pour débiter des frais de transfert à court terme et des frais de rachat anticipé.")); }

        // Actions
	};
}



