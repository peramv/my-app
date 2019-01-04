#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_assignned_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_assignned_account() { }
		~CIFast_IFast_ifastcbo_err_assignned_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ASSIGNNED_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entire account has been assigned. No redemption available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entire account has been assigned. No redemption available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das gesamte Konto wurde zugewiesen. Keine Tilgung verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha asignado toda la cuenta. No hay rescate disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte a été entièrement mis en garantie. Aucun rachat disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige account is toegewezen. Er is geen aflossing mogelijk")); }

        // Actions
	};
}



