#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_unknown_service : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_unknown_service() { }
		~CIFast_Infrastructure_vision_err_unknown_service() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_SERVICE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No tags were found in the message string.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No tags were found in the message string.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Im Meldungs-String wurde kein Kennzeichen gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron etiquetas en la cadena de mensaje.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun marqueur trouvé dans la chaîne du message")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen tags gevonden in de berichtenstring")); }

        // Actions
	};
}



