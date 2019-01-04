#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_no_view_data_repeats : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_no_view_data_repeats() { }
		~CIFast_IFast_dicbocore_err_no_view_data_repeats() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VIEW_DATA_REPEATS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FUNDNAME% fund has %FLAGNAME% stop flag turned on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%FUNDNAME% fund is not available for pat type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FUNDNAME% Fonds ist für Pat-Typ nicht verfügbar..")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo %FUNDNAME% no está disponible para el tipo de pago.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUNDNAME% n'est pas disponible pour le type de paiement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds %FUNDNAME% is niet beschikbaar voor betalingstype")); }

        // Actions
	};
}



