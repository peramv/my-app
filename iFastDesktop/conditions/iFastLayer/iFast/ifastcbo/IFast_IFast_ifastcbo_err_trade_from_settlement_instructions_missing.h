#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_from_settlement_instructions_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_from_settlement_instructions_missing() { }
		~CIFast_IFast_ifastcbo_err_trade_from_settlement_instructions_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_FROM_SETTLEMENT_INSTRUCTIONS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From Settlement Instructions are missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("From Settlement Instructions are missing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("From Settlement Instructions are missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement source sont manquantes.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please enter the Instructions using the Settlement Instructions screen.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please enter the Instructions using the Settlement Instructions screen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please enter the Instructions using the Settlement Instructions screen.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez entrer les instructions en utilisant l'écran des instructions de règlement.")); }
	};
}



