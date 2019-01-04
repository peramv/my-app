#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_blank_fundcode_for_indicatie_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_blank_fundcode_for_indicatie_allocation() { }
		~CIFast_IFast_ifastcbo_err_blank_fundcode_for_indicatie_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BLANK_FUNDCODE_FOR_INDICATIE_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Blank Fund Code and Class Code are for indicating allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Leerer Fonds-Code und Klassen-Code zeigen eine Zuweisung an.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de fondo y el código de clase en blanco son para indicar la asignación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Code de fonds et Code de classe laissés vides servent à indiquer la répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Lege fondscode en categoriecode zijn er om de allocatie aan te geven")); }

        // Actions
	};
}



