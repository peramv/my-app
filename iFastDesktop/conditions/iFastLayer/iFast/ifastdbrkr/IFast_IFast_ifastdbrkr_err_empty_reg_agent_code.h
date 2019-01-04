#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_empty_reg_agent_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_empty_reg_agent_code() { }
		~CIFast_IFast_ifastdbrkr_err_empty_reg_agent_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMPTY_REG_AGENT_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search Criteria field is empty.Please enter registration Agent Code")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du critère de recherche est vide. Veuillez saisir le code code de l'agent d'enregistrement.")); }

        // Actions
	};
}



