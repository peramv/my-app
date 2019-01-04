#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_modify_cot_acct_contract : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_modify_cot_acct_contract() { }
		~CIFast_IFast_ifastdbrkr_err_unable_modify_cot_acct_contract() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_MODIFY_COT_ACCT_CONTRACT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Cot_Acct_Contract record, versions are different.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to modify Cot_Acct_Contract record, versions are different.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cot_Acct_Contract-Eintrag konnte nicht geändert werden, Versionen stimmen nicht überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar el registro Cot-Acct-Contract, los números de versión son diferentes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'enregistrement de contrat du compte x, les versions sont différentes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Cott_Acct_Contract kon niet worden gewijzigd, de versies zijn verschillend")); }

        // Actions
	};
}



