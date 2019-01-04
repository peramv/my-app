#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amttype_for_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amttype_for_fund_class() { }
		~CIFast_IFast_ifastcbo_err_invalid_amttype_for_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMTTYPE_FOR_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid amount type for fund class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Betragsart für Fonds-Klasse")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de monto no válido para clase de fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour la classe de fonds")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig bedragtype voor fondscategorie")); }

        // Actions
	};
}



