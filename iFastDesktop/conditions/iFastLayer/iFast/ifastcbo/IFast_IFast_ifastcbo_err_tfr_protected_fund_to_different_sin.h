#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tfr_protected_fund_to_different_sin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tfr_protected_fund_to_different_sin() { }
		~CIFast_IFast_ifastcbo_err_tfr_protected_fund_to_different_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TFR_PROTECTED_FUND_TO_DIFFERENT_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transferring protected fund to a different beneficial owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer protected fund to different beneficial owner is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transferring protected fund to a different beneficial owner.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert du fonds protégé à un titulaire bénéficiaire différent.")); }

        // Actions
	};
}



