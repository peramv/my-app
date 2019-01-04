#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_broker_settlement_instr_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_broker_settlement_instr_missing() { }
		~CIFast_IFast_ifastcbo_err_fund_broker_settlement_instr_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_BROKER_SETTLEMENT_INSTR_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing Settlement Instructions for Fund Broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing Settlement Instructions for Fund Broker.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de règlement du courtier en fonds sont manquantes.")); }

        // Actions
	};
}



