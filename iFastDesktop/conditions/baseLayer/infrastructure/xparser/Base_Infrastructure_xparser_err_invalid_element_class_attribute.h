#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_invalid_element_class_attribute : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_invalid_element_class_attribute() { }
		~CBase_Infrastructure_xparser_err_invalid_element_class_attribute() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ELEMENT_CLASS_ATTRIBUTE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was successful.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war erfolgreich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD fue exitosa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is gelukt")); }

        // Actions
	};
}



