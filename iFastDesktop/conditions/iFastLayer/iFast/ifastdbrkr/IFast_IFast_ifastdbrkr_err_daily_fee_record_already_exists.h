#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_daily_fee_record_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_daily_fee_record_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_daily_fee_record_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DAILY_FEE_RECORD_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee record already exists.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fee record already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de frais existe déjà.")); }

        // Actions
	};
}



