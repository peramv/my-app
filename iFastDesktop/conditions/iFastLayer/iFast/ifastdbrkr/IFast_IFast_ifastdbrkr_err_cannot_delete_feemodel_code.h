#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_delete_feemodel_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_delete_feemodel_code() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_delete_feemodel_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_DELETE_FEEMODEL_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FeeModel used in FundSponsorFeeModel - cannot delete")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FeeModel used in FundSponsorFeeModel - cannot delete")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le modèle de frais est utilisé par le modèle de frais du promoteur de fonds – suppression impossible.")); }

        // Actions
	};
}



