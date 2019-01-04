#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amttype_appl_to_bel_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amttype_appl_to_bel_fund() { }
		~CIFast_IFast_ifastcbo_err_amttype_appl_to_bel_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMTTYPE_APPL_TO_BEL_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From-Fund should be back-end load for chosen Amount Type")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("From-Fund should be back-end load for chosen Amount Type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds source devrait comporter des frais de rachat pour le type de montant choisi.")); }

        // Actions
	};
}



