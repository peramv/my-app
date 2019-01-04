#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_locked() { }
		~CIFast_IFast_ifastdbrkr_err_trade_pay_instruct_record_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_PAY_INSTRUCT_RECORD_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade payment instructions record is locked.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des instructions de paiement de transaction est verrouillé.")); }

        // Actions
	};
}



