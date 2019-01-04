#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unavailable_resource : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unavailable_resource() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_unavailable_resource() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_UNAVAILABLE_RESOURCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This shareholder has multiple addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cet actionnaire a plusieurs adresses")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Aktionär hat mehrere Adressen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este accionista tiene varias direcciones")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'actionnaire a plusieurs adresses.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze aandeelhouder heeft meerdere adressen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please choose one")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Veuillez choisir un autre actionnaire")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie eines von beiden aus")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please choose one")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez en choisir une.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Kies er een")); }
	};
}



