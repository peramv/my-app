﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_contr_mat_date_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_contr_mat_date_missing() { }
		~CIFast_IFast_ifastcbo_err_contr_mat_date_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTR_MAT_DATE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract maturity date is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Contract maturity date is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date d'échéance du contrat manquante.")); }

        // Actions
	};
}



