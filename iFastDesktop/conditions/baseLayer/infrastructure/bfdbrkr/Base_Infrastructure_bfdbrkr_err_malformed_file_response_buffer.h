#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_err_malformed_file_response_buffer : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_err_malformed_file_response_buffer() { }
		~CBase_Infrastructure_bfdbrkr_err_malformed_file_response_buffer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MALFORMED_FILE_RESPONSE_BUFFER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
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
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos del accionista y vuelva a introducirlos.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'actionnaire et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de aandeelhoudersgegevens en voer deze opnieuw in")); }
	};
}



