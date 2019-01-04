#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_511_records_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_511_records_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_511_records_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_511_RECORDS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Creation of 511 records not allowed as all transactions are cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La création des enregistrements 511 n'est pas autorisée puisque toutes les transactions sont annulées.")); }

        // Actions
	};
}



