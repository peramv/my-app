#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_invalid_f4_for_selection : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_invalid_f4_for_selection() { }
		~CIFast_IFast_ifastcbo_err_field_invalid_f4_for_selection() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_INVALID_F4_FOR_SELECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELDNAME% is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FIELDNAME% is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELDNAME% ist ungültig. Geben Sie einen gültigen Wert ein oder drücken Sie F4, um eine Auswahlliste anzuzeigen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELDNAME% no es válido. Introduzca un valor válido o presione F4 para ver una lista de opciones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELDNAME% est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELDNAME% is ongeldig. Geef een geldige waarde op of druk op F4 voor een selectielijst")); }

        // Actions
	};
}



