#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_invalid_root_element_name : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_invalid_root_element_name() { }
		~CBase_Ifds_xparser_err_invalid_root_element_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ROOT_ELEMENT_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Root element name is unknown.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es muss wenigstens ein ID-Typ für jedes Objekt eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Root element name is unknown.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : le nom de l'élément racine est inconnu.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Root element name is unknown.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



