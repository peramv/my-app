#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_element_class_attribute_not_specified : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_element_class_attribute_not_specified() { }
		~CBase_Ifds_xparser_err_element_class_attribute_not_specified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Request: Class attribute expected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungs-Datum muss von einem Eintrag in das Todesdatums-Feld begleitet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid Request: Class attribute expected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : attribut de classe escompté")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invalid Request: Class attribute expected.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



