#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_dicore_date_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_dicore_date_invalid() { }
		~CIFast_IFast_dicbocore_dicore_date_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund/class combination %FUNDNAME% %CLASSNAME% is not effective.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FUNDNAME% %CLASSNAME% n'est pas effectif. Veuillez sélectionner une autre combinaison de fonds et de catégorie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUNDNAME% %CLASSNAME% ist nicht wirksam. Bitte wählen Sie eine andere Fonds/Klassen-Kombination.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FUNDNAME% %CLASSNAME% no está vigente. Por favor seleccione otra combinación de fondo/clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La combinaison fonds/classe %FUNDNAME% %CLASSNAME% n'est pas en vigueur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FUNDNAME% %CLASSNAME% is niet van kracht. Selecteer een andere fonds/categoriecombinatie")); }

        // Actions
	};
}



