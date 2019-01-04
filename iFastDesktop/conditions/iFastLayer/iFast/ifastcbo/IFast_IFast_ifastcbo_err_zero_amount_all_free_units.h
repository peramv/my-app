#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_zero_amount_all_free_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_zero_amount_all_free_units() { }
		~CIFast_IFast_ifastcbo_err_zero_amount_all_free_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZERO_AMOUNT_ALL_FREE_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For All Free Units amount should be zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Alle Freien Anteile sollte der Betrag Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de Para todas las unidades gratis debe ser cero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant pour toutes les unités sans frais devrait être de zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor alle vrije eenheden moet het bedrag nul zijn")); }

        // Actions
	};
}



