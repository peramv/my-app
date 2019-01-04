﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_br_summary : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_br_summary() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_dlr_br_summary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DLR_BR_SUMMARY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid financial institution branch summary.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid financial institution branch summary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Finanzinstitut-Filialen-Zusammenfassung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Resumen de sucursal de institución financiera no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le sommaire de l'unité de service de l'institution financière est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig overzicht filiaal van financiële instelling")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Informationen und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify financial institution information and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'institution financière et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens van de financiële instelling en voer deze opnieuw in")); }
	};
}



