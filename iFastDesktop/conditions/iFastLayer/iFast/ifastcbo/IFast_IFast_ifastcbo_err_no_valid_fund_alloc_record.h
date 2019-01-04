#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_valid_fund_alloc_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_valid_fund_alloc_record() { }
		~CIFast_IFast_ifastcbo_err_no_valid_fund_alloc_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VALID_FUND_ALLOC_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Allocation must exist when Global Level Asset Mix indicates applicable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Allocation must exist when Global Level Asset Mix indicates applicable.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund Allocation must exist when Global Level Asset Mix indicates applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition de fonds existe lorsque la composition d'actif de niveau global indique Applicable.")); }

        // Actions
	};
}



