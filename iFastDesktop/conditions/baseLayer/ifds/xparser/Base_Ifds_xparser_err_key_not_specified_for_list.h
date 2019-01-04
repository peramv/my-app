#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_key_not_specified_for_list : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_key_not_specified_for_list() { }
		~CBase_Ifds_xparser_err_key_not_specified_for_list() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_KEY_NOT_SPECIFIED_FOR_LIST")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Key must be specified for list CBO's")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfache Bevollmächtigte Eigentümer (21) nicht erlaubt für Konten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Key must be specified for list CBO's")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une clé doit étre spécifiée pour les optimisations de coûts de la liste.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Key must be specified for list CBO's")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



