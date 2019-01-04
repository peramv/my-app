#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_adl_fee_percentage_for_default_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_adl_fee_percentage_for_default_record() { }
		~CIFast_IFast_ifastcbo_err_adl_fee_percentage_for_default_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADL_FEE_PERCENTAGE_FOR_DEFAULT_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Percentage cannot be 0 for Default Record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee Percentage cannot be 0 for Default Record.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fee Percentage cannot be 0 for Default Record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage de frais ne peut être 0 pour un enregistrement par défaut.")); }

        // Actions
	};
}



