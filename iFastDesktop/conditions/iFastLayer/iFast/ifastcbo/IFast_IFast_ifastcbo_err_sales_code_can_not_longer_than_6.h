#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sales_code_can_not_longer_than_6 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sales_code_can_not_longer_than_6() { }
		~CIFast_IFast_ifastcbo_err_sales_code_can_not_longer_than_6() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("sales rep code can only be less than or equal to 6 characters.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("sales rep code can only be less than or equal to 6 characters.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de représentant des ventes doit être composé de 6 caractères ou moins.")); }

        // Actions
	};
}



