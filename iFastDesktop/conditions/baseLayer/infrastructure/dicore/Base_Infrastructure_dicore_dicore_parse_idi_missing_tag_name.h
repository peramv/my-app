#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_parse_idi_missing_tag_name : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_parse_idi_missing_tag_name() { }
		~CBase_Infrastructure_dicore_dicore_parse_idi_missing_tag_name() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PARSE_IDI_MISSING_TAG_NAME")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

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



