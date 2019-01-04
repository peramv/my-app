#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_contract_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_contract_not_effective() { }
		~CIFast_IFast_ifastcbo_err_contract_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A contract exists but is not effective until %ContractEffect%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A contract exists but is not effective until %ContractEffect%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Vertrag existiert, tritt aber nicht vor dem %ContractEffect%. in Kraft")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe un contrato pero no entrará en  vigencia hasta %ContractEffect%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un contrat existe, mais il n'est pas en vigueur avant le %ContractEffect%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat een overeenkomst maar deze is pas van kracht op %ContractEffect%")); }

        // Actions
	};
}



