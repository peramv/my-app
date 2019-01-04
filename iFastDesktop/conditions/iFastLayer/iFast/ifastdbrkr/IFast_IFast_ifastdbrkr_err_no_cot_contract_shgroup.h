#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_cot_contract_shgroup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_cot_contract_shgroup() { }
		~CIFast_IFast_ifastdbrkr_err_no_cot_contract_shgroup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_COT_CONTRACT_SHGROUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Cot-Contract-ShGroup record found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Cot-Contract-ShGroup record found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Contract-ShGroup-Eintrag nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Cot-Contract-ShGroup")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement du groupe de l'actionnaire du contrat x n'a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Cot-Contract-ShGroup is niet gevonden")); }

        // Actions
	};
}



