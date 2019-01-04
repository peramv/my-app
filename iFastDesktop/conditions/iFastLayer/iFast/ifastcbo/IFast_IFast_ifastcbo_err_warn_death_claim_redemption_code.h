#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_death_claim_redemption_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_death_claim_redemption_code() { }
		~CIFast_IFast_ifastcbo_err_warn_death_claim_redemption_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_DEATH_CLAIM_REDEMPTION_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death claim redemption code is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tilgungscode für Sterbegeld-Anspruch erforderlich")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el código de rescate de reclamación por fallecimiento")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat de sinistre-décès est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aflossingscode overlijdensclaim is vereist")); }

        // Actions
	};
}



