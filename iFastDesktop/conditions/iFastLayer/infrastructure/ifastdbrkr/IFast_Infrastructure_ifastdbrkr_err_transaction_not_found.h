#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_transaction_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_transaction_not_found() { }
		~CIFast_Infrastructure_ifastdbrkr_err_transaction_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareowner Master not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Shareowner Master not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktionärs-Master nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el maestro de titulares de acciones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'actionnaire original est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Hoofdrecord aandeelhouder is niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify shareowner information and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify shareowner information and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Aktionärs-Informationen und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify shareowner information and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'actionnaire et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de aandeelhoudersgegevens en voer deze opnieuw in")); }
	};
}



