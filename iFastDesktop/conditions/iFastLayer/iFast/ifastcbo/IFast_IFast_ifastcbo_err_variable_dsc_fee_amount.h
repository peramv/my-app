#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_variable_dsc_fee_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_variable_dsc_fee_amount() { }
		~CIFast_IFast_ifastcbo_err_variable_dsc_fee_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VARIABLE_DSC_FEE_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption from a Variable Ecoflex contract.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Retrait  sur contrat Ecoflex Variable.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please validate the DSC fees amount before proceeding with the redemption.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez valider les frais DSC avant de procéder au retrait.")); }
	};
}



