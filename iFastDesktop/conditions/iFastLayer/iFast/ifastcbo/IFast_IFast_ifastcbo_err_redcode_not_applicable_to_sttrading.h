#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redcode_not_applicable_to_sttrading : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redcode_not_applicable_to_sttrading() { }
		~CIFast_IFast_ifastcbo_err_redcode_not_applicable_to_sttrading() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDCODE_NOT_APPLICABLE_TO_STTRADING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The redemption code is not applicable to charge short term transfer fees and early redemption fees.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The redemption code is not applicable to charge short term transfer fees and early redemption fees.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat n'est pas applicable pour débiter des frais de transfert à court terme et des frais de rachat anticipé.")); }

        // Actions
	};
}



