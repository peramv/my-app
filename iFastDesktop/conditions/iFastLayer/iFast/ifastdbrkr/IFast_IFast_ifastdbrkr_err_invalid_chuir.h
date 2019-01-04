#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_chuir : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_chuir() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_chuir() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CHUIR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid CHUIReln setup.'Function' not found in Company.Meny-Detl.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid CHUIReln setup.'Function' not found in Company.Meny-Detl.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger CHUIReln-Setup. „Funktion“ nicht in Unternehmen gefunden. Meny-Detl")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Configuración de CHUIReln no válida. No se encontró \"'Función\" en Compañía.Meny-Detl")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Réglage de la relation CHUI invalide. Fonction introuvable dans l'entreprise. X")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige CHUIReln-instelling. 'Functie' is niet gevonden in Company.Meny-Detl")); }

        // Actions
	};
}



