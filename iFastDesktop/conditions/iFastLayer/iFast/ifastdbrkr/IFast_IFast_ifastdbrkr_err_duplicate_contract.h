#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_duplicate_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_duplicate_contract() { }
		~CIFast_IFast_ifastdbrkr_err_duplicate_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertrag existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El contrato ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Contrat déjà existant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overeenkomst bestaat al")); }

        // Actions
	};
}



