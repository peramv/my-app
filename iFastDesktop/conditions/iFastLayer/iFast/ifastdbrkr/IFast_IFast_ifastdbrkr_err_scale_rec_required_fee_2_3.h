#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_scale_rec_required_fee_2_3 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_scale_rec_required_fee_2_3() { }
		~CIFast_IFast_ifastdbrkr_err_scale_rec_required_fee_2_3() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SCALE_REC_REQUIRED_FEE_2_3")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scale records required for fee type 2 or 3.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Scale records required for fee type 2 or 3.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Scale records required for fee type 2 or 3.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les enregistrements de l'échelle sont requis pour les types de frais 2 ou 3.")); }

        // Actions
	};
}



