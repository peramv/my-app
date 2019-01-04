#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trading_settlement_location_invalid_code_for_clearing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trading_settlement_location_invalid_code_for_clearing_account() { }
		~CIFast_IFast_ifastcbo_err_trading_settlement_location_invalid_code_for_clearing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one Settlement Location Code defined at Acct Level does not exist at Syst Level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("At least one Settlement Location Code defined at Acct Level does not exist at Syst Level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("At least one Settlement Location Code defined at Acct Level does not exist at Syst Level.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un des codes de lieu de règlement définis au niveau du compte n'existe pas au niveau du système.")); }

        // Actions
	};
}



