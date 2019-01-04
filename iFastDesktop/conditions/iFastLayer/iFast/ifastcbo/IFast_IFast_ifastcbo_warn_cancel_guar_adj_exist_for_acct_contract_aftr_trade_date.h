#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cancel_guar_adj_exist_for_acct_contract_aftr_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cancel_guar_adj_exist_for_acct_contract_aftr_trade_date() { }
		~CIFast_IFast_ifastcbo_warn_cancel_guar_adj_exist_for_acct_contract_aftr_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Guarantee adjustment exists for the account contract after trade date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Guarantee adjustment exists for the account contract after trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des ajustements de garantie existent pour le contrat du compte après la date de transaction.")); }

        // Actions
	};
}



