#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_exist_but_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_exist_but_not_effective() { }
		~CIFast_IFast_ifastdbrkr_err_contract_exist_but_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_EXIST_BUT_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A contract exists but is not effective.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Vertrag existiert, ist aber nicht effektiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existe un contrato pero aún no ha entrado en vigencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Contrat existant, mais pas en vigueur")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat een overeenkomst maar deze is niet van kracht")); }

        // Actions
	};
}



