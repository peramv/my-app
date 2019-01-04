#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gross_full_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gross_full_redemption() { }
		~CIFast_IFast_ifastcbo_err_gross_full_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GROSS_FULL_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A Full redemption must use a Gross amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für eine Volle Tilgung muss ein Bruttobetrag verwendet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Un rescate total debe utilizar un monto bruto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un rachat total doit utiliser un montant brut.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een volledige aflossing moet gebruikmaken van een bruto bedrag")); }

        // Actions
	};
}



