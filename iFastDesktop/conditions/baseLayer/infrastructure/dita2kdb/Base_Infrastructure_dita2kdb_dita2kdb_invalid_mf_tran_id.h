#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_mf_tran_id : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_mf_tran_id() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_mf_tran_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_MF_TRAN_ID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid mutual fund transaction ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid mutual fund transaction ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Offene-Investmentfonds-Transaktions-ID.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de transacción con fondos mutuos no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de transaction de fonds commun de placement invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig transactie-ID beleggingsfonds")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify data entered. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify data entered. If entry is correct, contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die eingegebenen Daten. Wenn der Eintrag richtig ist, wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos introducidos. Si los datos son correctos, notifique de este mensaje a un supervisor.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les données saisies. Si elles sont exactes, communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de ingevoerde gegevens. Als de invoer juist is, neemt u contact op met een supervisor en meldt u dit bericht")); }
	};
}



