#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_full_redemption_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_full_redemption_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_full_redemption_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_REDEMPTION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full Redemptions not allowed for Net Redemptions.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Full Redemptions not allowed for Net Redemptions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Volle Tilgung für Netto-Tilgungen nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten rescates totales para rescates netos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Rachats totaux non autorisés pour les rachats nets")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige aflossingen niet toegestaan voor netto aflossingen")); }

        // Actions
	};
}



