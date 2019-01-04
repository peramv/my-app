#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amount_greater : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amount_greater() { }
		~CIFast_IFast_ifastdbrkr_err_amount_greater() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_GREATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount entered is greater than that available for Fund.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount entered is greater than that available for Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der eingegebene Betrag ist größer als der für einen Fonds verfügbare Betrag.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto introducido es mayor que el monto disponible para el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi est supérieur au montant disponible pour le fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opgegeven bedrag is groter dan beschikbaar voor het fonds")); }

        // Actions
	};
}



