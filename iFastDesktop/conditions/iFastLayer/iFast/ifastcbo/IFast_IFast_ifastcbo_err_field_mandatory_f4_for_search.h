﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_mandatory_f4_for_search : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_mandatory_f4_for_search() { }
		~CIFast_IFast_ifastcbo_err_field_mandatory_f4_for_search() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_MANDATORY_F4_FOR_SEARCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% is mandatory.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone %FIELDNAME% doit être renseignee. Renseignea une valeur sur ce champs ou pressez F4 pour rechercher une valeur existante.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% ist obligatorisch. Geben Sie einen gültigen Wert ein oder drücken Sie F4, um nach einem gültigen Wert zu suchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% es obligatorio. Introduzca un valor válido o presione F4 para buscar un valor válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% is verplicht. Geef een geldige waarde op of druk op F4 voor een geldige waarde")); }

        // Actions
	};
}



