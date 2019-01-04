#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_type_scale_not_supported : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_type_scale_not_supported() { }
		~CIFast_IFast_ifastcbo_err_fee_type_scale_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_TYPE_SCALE_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading not supported for fee type scale.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trading not supported for fee type scale.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'opération n'est pas supportée par l'échelle du type de frais.")); }

        // Actions
	};
}



