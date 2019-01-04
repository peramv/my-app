#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_valid_contract_orig_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_valid_contract_orig_tradedate() { }
		~CIFast_IFast_ifastdbrkr_err_no_valid_contract_orig_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VALID_CONTRACT_ORIG_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No valid contract for the original trade date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No valid contract for the original trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun contrat valide pour la date de transaction d'origine")); }

        // Actions
	};
}



