#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_type_scale_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_type_scale_only() { }
		~CIFast_IFast_ifastcbo_err_fee_type_scale_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_TYPE_SCALE_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee type must be scale for based on age of assets.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee type must be scale for based on age of assets.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fee type must be scale for based on age of assets.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de frais doit être établis en fonction de l'échelle d'âge de l'actif.")); }

        // Actions
	};
}



