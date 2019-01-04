#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_srvbase_srvbase_cnd_version : public CConditionObject
	{
	public:
		CBase_Infrastructure_srvbase_srvbase_cnd_version() { }
		~CBase_Infrastructure_srvbase_srvbase_cnd_version() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("SRVBASE_CND_VERSION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("srvbase")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid date format. Format must include century.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid date format. Format must include century.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Datumsformat. Jahrhundert muss im Format angegeben sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de fecha no válido. El formato debe incluir el siglo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de date invalide. Le format doit inclure le siècle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige datumnotatie. Notatie moet eeuw bevatten")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Type a date with MMDDCCYY format.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Type a date with MMDDCCYY format.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie ein Datum im Format MMTTJJJJ ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Escriba una fecha con el formato MMDDCCAA.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Taper une date en format JJ/MM/AAAA.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Typ een datum met de indeling MMDDEEJJ")); }
	};
}



