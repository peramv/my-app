#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_fund_class_not_unique : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_fund_class_not_unique() { }
		~CIFast_IFast_ifastcbo_err_acct_fund_class_not_unique() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_FUND_CLASS_NOT_UNIQUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate distribution records are not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Duplicate distribution records are not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte Verteilungseinträge sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten registros de distribución repetidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les copies des enregistrements de distribution ne sont pas autorisées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele distributierecords zijn niet toegestaan")); }

        // Actions
	};
}



