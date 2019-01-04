#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unknown_response_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unknown_response_type() { }
		~CIFast_IFast_ifastdbrkr_err_unknown_response_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_RESPONSE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error - Unknown response type returned from host.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler – Unbekannter Antworttyp von Host erhalten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error - El host devolvió un tipo de respuesta desconocido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur – type de réponse inconnu envoyé par l'hôte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout - Onbekende responstypes teruggestuurd door host")); }

        // Actions
	};
}



