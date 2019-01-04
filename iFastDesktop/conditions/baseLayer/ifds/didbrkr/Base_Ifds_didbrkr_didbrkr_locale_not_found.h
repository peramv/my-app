#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_locale_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_locale_not_found() { }
		~CBase_Ifds_didbrkr_didbrkr_locale_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_LOCALE_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This field (%TAG%) is required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %TAG% est requise.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld ist erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo (%TAG%) es obligatorio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce champ (%TAG%) doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het veld (%TAG%) is vereist.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Required fields cannot be set to blank or null.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Les zones obligatoires ne peuvent pas etre vides ou renseignees avec 0.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Notwendige Felder können nicht auf leer oder null eingestellt werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Los campos obligatorios no pueden configurarse en blanco o en cero.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les champs requis ne peuvent être laissés vides ou réglés à zéro.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Vereiste velden kunnen niet worden ingesteld op leeg of nul.")); }
	};
}



