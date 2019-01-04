#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_a87_rec_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_a87_rec_not_found() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_a87_rec_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_A87_REC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareowner account master information not found (A87).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Shareowner account master information not found (A87).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionär-Konto-Master-Informationen nicht gefunden (A87).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre el maestro de cuenta de titular de acciones (A87).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le compte principal de l'actionnaire est introuvable (A87).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens hoofdaccount aandeelhouder zijn niet gevonden (A87)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify shareowner information and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify shareowner information and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Aktionärs-Informationen und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos del accionista y vuelva a introducirlos.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information de l'actionnaire et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de aandeelhoudersgegevens en voer deze opnieuw in")); }
	};
}



