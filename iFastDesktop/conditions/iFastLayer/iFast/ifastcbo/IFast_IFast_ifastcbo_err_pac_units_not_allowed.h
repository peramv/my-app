#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pac_units_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pac_units_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_pac_units_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAC_UNITS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Type must be Amount for PAC transactions.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Type must be Amount for PAC transactions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Typ muss Betrag für PAC -Transaktionen sein. Bitte wählen Sie neu.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo debe ser Monto para transacciones PAC. Por favor vuelva a seleccionar el tipo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type doit être Montant pour les transactions PAC.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Type moet Bedrag zijn voor VGC-transacties. Selecteer opnieuw")); }

        // Actions
	};
}



