#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pension_juris_is_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pension_juris_is_mandatory() { }
		~CIFast_IFast_ifastcbo_err_pension_juris_is_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENSION_JURIS_IS_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pension Jurisdiction is a mandatory field.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Renten-Rechtssprechung ist ein obligatorisches Feld, bitte auswählen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo Jurisdicción de jubilación es obligatorio, por favor seleccione una opción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction de retraite est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Pensioenrechtsgebied is een verplicht veld, selecteer een waarde")); }

        // Actions
	};
}



