#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_greater_than_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_greater_than_holding() { }
		~CIFast_IFast_ifastcbo_err_amount_greater_than_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_GREATER_THAN_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The amount entered is greater than what is available in the fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der eingegebene Vertrag überschreitet das, was im Fonds verfügbar ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto introducido es mayor que el que hay disponible en el fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi est supérieur au montant disponible dans le fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het ingevulde bedrag is groter dan wat er beschikbaar is in het fonds")); }

        // Actions
	};
}



