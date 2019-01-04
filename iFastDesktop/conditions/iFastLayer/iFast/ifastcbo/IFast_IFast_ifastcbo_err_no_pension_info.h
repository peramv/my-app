#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_pension_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_pension_info() { }
		~CIFast_IFast_ifastcbo_err_no_pension_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PENSION_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Pension Information for this account, cannot process Cash Redmption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Pension Information for this account, cannot process Cash Redmption.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Pension Information for this account, cannot process Cash Redmption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucune information sur le fonds de pension pour ce compte, impossible de procéder au rachat au comptant.")); }

        // Actions
	};
}



