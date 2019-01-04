#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_must_run_modal : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_must_run_modal() { }
		~CBase_Infrastructure_bpbase_bp_err_must_run_modal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_MUST_RUN_MODAL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this bank Magnetic Ink Character Recognition (MICR) ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this bank Magnetic Ink Character Recognition (MICR) ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt die Magnetschrift-Erkennungs-ID nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta identificación de reconocimiento de caracteres de tinta magnética (MICR) del banco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code bancaire de reconnaissance de caractères magnétiques (MICR).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent het MICR-ID (Magnetic Ink Character Recognition) van deze bank niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Daten und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos y vuelva a introducirlos.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens en voer deze opnieuw in")); }
	};
}



