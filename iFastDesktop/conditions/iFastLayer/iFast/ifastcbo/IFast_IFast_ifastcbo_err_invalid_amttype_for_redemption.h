#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amttype_for_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amttype_for_redemption() { }
		~CIFast_IFast_ifastcbo_err_invalid_amttype_for_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMTTYPE_FOR_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid amount type for redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Betragsart für Tilgung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de monto no válido para rescate")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour un rachat")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig bedragtype voor aflossing")); }

        // Actions
	};
}



