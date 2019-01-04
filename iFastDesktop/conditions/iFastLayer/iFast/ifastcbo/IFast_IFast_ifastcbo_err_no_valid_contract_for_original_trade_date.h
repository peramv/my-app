#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_valid_contract_for_original_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_valid_contract_for_original_trade_date() { }
		~CIFast_IFast_ifastcbo_err_no_valid_contract_for_original_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VALID_CONTRACT_FOR_ORIGINAL_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valid contract for the original trade date")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun contrat valide pour la date de transaction originale.")); }

        // Actions
	};
}



