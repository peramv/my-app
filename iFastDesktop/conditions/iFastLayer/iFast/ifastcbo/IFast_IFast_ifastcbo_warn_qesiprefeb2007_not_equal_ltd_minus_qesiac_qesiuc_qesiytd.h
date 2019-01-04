#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_qesiprefeb2007_not_equal_ltd_minus_qesiac_qesiuc_qesiytd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_qesiprefeb2007_not_equal_ltd_minus_qesiac_qesiuc_qesiytd() { }
		~CIFast_IFast_ifastcbo_warn_qesiprefeb2007_not_equal_ltd_minus_qesiac_qesiuc_qesiytd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The QESI Pre Feb 2007 is not equal to LTD - QESI AC - QESI UC - QESI YTD.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'IQEE antérieur à fév. 2007 n'est pas égal aux montants DC - CS IQEE - CNS IQEE.")); }

        // Actions
	};
}



