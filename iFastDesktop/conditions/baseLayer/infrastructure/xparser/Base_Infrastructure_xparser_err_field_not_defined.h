#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_field_not_defined : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_field_not_defined() { }
		~CBase_Infrastructure_xparser_err_field_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Failed to create an AWD Source")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Failed to create an AWD Source")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine AWD-Quelle konnte nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se pudo crear una fuente de AWD")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de création d'une source AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kon geen AWD-bron worden gemaakt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a system administrator")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a system administrator")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Systemadministrator")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un administrador del sistema.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een systeembeheerder")); }
	};
}



