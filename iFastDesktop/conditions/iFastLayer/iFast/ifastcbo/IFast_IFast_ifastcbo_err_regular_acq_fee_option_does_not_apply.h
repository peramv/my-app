#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_regular_acq_fee_option_does_not_apply : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_regular_acq_fee_option_does_not_apply() { }
		~CIFast_IFast_ifastcbo_err_regular_acq_fee_option_does_not_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REGULAR_ACQ_FEE_OPTION_DOES_NOT_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Aquisition fee option 'Regular' does not apply for shareholders that have a fee model.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aquisition fee option 'Regular' does not apply for shareholders that have a fee model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option de frais d'acquisition Réguliers n'est pas applicable pour les actionnaires qui ont un modèle de frais.")); }

        // Actions
	};
}



