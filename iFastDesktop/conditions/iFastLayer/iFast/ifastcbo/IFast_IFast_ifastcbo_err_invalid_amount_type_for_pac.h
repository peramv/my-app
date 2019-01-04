#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amount_type_for_pac : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amount_type_for_pac() { }
		~CIFast_IFast_ifastcbo_err_invalid_amount_type_for_pac() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMOUNT_TYPE_FOR_PAC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type must be amount for PAC.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart muss Betrag für PAC sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser monto para PAC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être un montant pour PAC.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet bedrag zijn voor VGC")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please select amount.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie einen Betrag aus.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please select amount.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez sélectionner un montant.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("selecteer een bedrag")); }
	};
}



