#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_format_not_recognized : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_format_not_recognized() { }
		~CBase_Infrastructure_dicbocore_err_format_not_recognized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FORMAT_NOT_RECOGNIZED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date format not recognized. Check the enumeration in mfdatetime.hpp for recognized formats.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date format not recognized. Check the enumeration in mfdatetime.hpp for recognized formats.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datumsformat wurde nicht erkannt. Überprüfen Sie die Aufzählung in mfdatetime.hpp nach erkannten Formaten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de fecha no reconocido. Verifique la enumeración en mfdatetime.hpp para formatos reconocidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de date non reconnu. Consultez l'énumération dans mfdatetime.hpp pour les formats reconnus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datumnotatie wordt niet herkend. Controleer de opsomming in mfdatetime.hpp voor toegestane notaties")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



