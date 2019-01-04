#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_ex_amt_more_than_holding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_ex_amt_more_than_holding() { }
		~CIFast_IFast_ifastcbo_err_warn_ex_amt_more_than_holding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_EX_AMT_MORE_THAN_HOLDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entered amount for fund %FUNDNAME% %CLASSNAME% exceeds its current holding in this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("entered for fund %FUNDNAME% %CLASSNAME% exceeds its current holding in this account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("entered for fund %FUNDNAME% %CLASSNAME% exceeds its current holding in this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi pour le fonds %FUNDNAME% et la classe %CLASSNAME% excède le portefeuille actuel de ce compte.")); }

        // Actions
	};
}



