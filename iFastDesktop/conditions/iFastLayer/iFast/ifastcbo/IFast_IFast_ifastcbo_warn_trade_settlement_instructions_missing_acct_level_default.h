#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_settlement_instructions_missing_acct_level_default : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_settlement_instructions_missing_acct_level_default() { }
		~CIFast_IFast_ifastcbo_warn_trade_settlement_instructions_missing_acct_level_default() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_SETTLEMENT_INSTRUCTIONS_MISSING_ACCT_LEVEL_DEFAULT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default Settlement Instruction has not been setup at Account Level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Default Settlement Instruction has not been setup at Account Level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Default Settlement Instruction has not been setup at Account Level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement par défaut n'ont pas été réglées au niveau du compte.")); }

        // Actions
	};
}



