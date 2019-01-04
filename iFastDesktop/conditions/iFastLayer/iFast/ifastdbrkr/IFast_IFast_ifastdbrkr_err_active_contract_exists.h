#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_active_contract_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_active_contract_exists() { }
		~CIFast_IFast_ifastdbrkr_err_active_contract_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACTIVE_CONTRACT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An active contract exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein aktiver Vertrag ist vorhanden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un contrato activo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un contrat actif existe")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat al een actieve overeenkomst")); }

        // Actions
	};
}



