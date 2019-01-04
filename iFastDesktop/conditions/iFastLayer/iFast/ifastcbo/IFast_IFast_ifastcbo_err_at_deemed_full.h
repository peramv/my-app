#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_deemed_full : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_deemed_full() { }
		~CIFast_IFast_ifastcbo_err_at_deemed_full() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_DEEMED_FULL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Type must be Amount for full transfers.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Type must be Amount for full transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Typ muss Betrag für volle Transfers sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo debe ser Monto para transacciones totales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type doit être Montant pour les transferts complets.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Type moet Bedrag zijn voor volledige overdrachten")); }

        // Actions
	};
}



