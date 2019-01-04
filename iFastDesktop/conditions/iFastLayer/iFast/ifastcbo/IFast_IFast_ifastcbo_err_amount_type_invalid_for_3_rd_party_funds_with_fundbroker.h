#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_type_invalid_for_3_rd_party_funds_with_fundbroker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_type_invalid_for_3_rd_party_funds_with_fundbroker() { }
		~CIFast_IFast_ifastcbo_err_amount_type_invalid_for_3_rd_party_funds_with_fundbroker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_TYPE_INVALID_FOR_3_RD_PARTY_FUNDS_WITH_FUNDBROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type invalid for third party funds; allowed only for fund broker with routing type fax and swift.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount type invalid for third party funds; allowed only for fund broker with routing type fax.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour les fonds de tiers; autorisé seulement pour le courtier en fonds dont le type d'acheminement est Télécopieur ou Swift")); }

        // Actions
	};
}



