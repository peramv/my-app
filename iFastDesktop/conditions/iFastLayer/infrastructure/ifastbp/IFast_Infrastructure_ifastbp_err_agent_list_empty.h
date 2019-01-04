#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastbp_err_agent_list_empty : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastbp_err_agent_list_empty() { }
		~CIFast_Infrastructure_ifastbp_err_agent_list_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGENT_LIST_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The zip code is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The zip code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postleitzahl ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code postal invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De postcode is ongeldig")); }

        // Actions
	};
}



