#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_load_proc_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_load_proc_fail() { }
		~CIFast_IFast_diawdi_diawdi_load_proc_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOAD_PROC_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Some of the characters might not be digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Saisie invalide. Certains caracteres ne sont peut-être pas des chiffres")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Eingabe. Einige der Zeichen sind eventuell keine Ziffern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entrada no válida. Es posible que algunos de los caracteres no sean dígitos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Certains caractères ne devraient pas être des caractères numériques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige invoer. Sommige tekens zijn wellicht geen cijfers")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Reinput the value")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Ressaisissez la valeur")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie den Wert erneut ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Reinput the value")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Saisissez de nouveau la valeur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer de waarde opnieuw in")); }
	};
}



