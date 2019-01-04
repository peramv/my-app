#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_load_module_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_load_module_fail() { }
		~CIFast_IFast_diawdi_diawdi_load_module_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOAD_MODULE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Value out of range.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Valeur non comprise dans la plage")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wert liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Valor fuera de rango")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur hors plage")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Waarde ligt buiten het bereik")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Reinput the value")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Ressaisissez la valeur")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie den Wert erneut ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Reinput the value")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Saisissez de nouveau la valeur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer de waarde opnieuw in")); }
	};
}



