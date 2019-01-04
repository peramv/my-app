#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_didbrkr_didbrkr_locale_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_didbrkr_didbrkr_locale_not_found() { }
		~CIFast_Infrastructure_didbrkr_didbrkr_locale_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_LOCALE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Requested locale %locale% not found for element %element%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Requested locale %locale% not found for element %element%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gesuchtes Locale %locale% nicht gefunden für Element %element%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el local solicitado %locale% para el elemento %element%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paramètre de lieu demandé %locale% est introuvable pour l'élément %element%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aangevraagde taal- en landcode %locale% is niet gevonden voor element %element%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check data dictionary.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check data dictionary.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Datenlexikon.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check data dictionary.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le dictionnaire de données.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de data dictionary")); }
	};
}



