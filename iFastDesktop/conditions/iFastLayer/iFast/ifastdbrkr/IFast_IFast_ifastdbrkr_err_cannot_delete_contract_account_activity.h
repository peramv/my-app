#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_delete_contract_account_activity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_delete_contract_account_activity() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_delete_contract_account_activity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_DELETE_CONTRACT_ACCOUNT_ACTIVITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot delete a contract on an account that has activity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein aktives Konto oder ein aktiver Vertrag können nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar un contrato de una cuenta que tiene actividad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer un contrat d'un compte actif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overeenkomst kan niet worden gewist voor account waar nog activiteiten zijn")); }

        // Actions
	};
}



