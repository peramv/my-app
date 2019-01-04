#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_instructions_expired_as_of : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_instructions_expired_as_of() { }
		~CIFast_IFast_ifastcbo_err_settlement_instructions_expired_as_of() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_INSTRUCTIONS_EXPIRED_AS_OF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default settlement instructions for Account %accountNum% are expired as of: %asofdate%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement par défaut pour le compte %accountNum% sont expirées à partir du %asofdate%.")); }

        // Actions
	};
}



