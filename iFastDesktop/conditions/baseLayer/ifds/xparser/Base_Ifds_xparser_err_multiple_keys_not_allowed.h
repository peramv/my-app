#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_multiple_keys_not_allowed : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_multiple_keys_not_allowed() { }
		~CBase_Ifds_xparser_err_multiple_keys_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_KEYS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Only one key can be specified for a CBO.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter existiert nicht. Jetzt erstellen?")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Only one key can be specified for a CBO.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : une seule clé peut être spécifiée pour une optimisation de coûts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Only one key can be specified for a CBO.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



