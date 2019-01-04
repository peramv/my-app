#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_field_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_field_not_found() { }
		~CBase_Infrastructure_bpbase_bp_err_field_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_FIELD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid fund number was entered, or a fund number was not entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("An invalid fund number was entered, or a fund number was not entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine ungültige Fonds-Nummer wurde eingegeben oder keine Fonds-Nummer wurde eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se introdujo un número de fondo no válido o no se introdujo un número de fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un numéro de fonds invalide a été entré ou un numéro de fonds n'a pas été entré.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldig fondsnummer ingevoerd, of er is geen fondsnummer ingevoerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify fund code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify fund code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Fondscode und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código de fondo y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de fonds et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de fondscode en voer deze opnieuw in")); }
	};
}



