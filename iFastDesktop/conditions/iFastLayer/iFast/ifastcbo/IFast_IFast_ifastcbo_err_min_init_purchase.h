#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_min_init_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_min_init_purchase() { }
		~CIFast_IFast_ifastcbo_err_min_init_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIN_INIT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum initial purchase amount for fund %FUND% and class %CLASS% is %MINIMUM_AMT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimaler anfänglicher Kaufbetrag für Fonds %FUND% und Klasse %CLASS% beträgt %MINIMUM_AMT%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Minimum initial purchase amount for fund %FUND% and class %CLASS% is %MINIMUM_AMT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'achat initial minimal pour le fonds %FUND% et la classe %CLASS% est %MINIMUM_AMT%.")); }

        // Actions
	};
}



