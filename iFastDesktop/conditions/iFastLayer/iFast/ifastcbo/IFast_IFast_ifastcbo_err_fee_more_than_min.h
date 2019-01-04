#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_more_than_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_more_than_min() { }
		~CIFast_IFast_ifastcbo_err_fee_more_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MORE_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee less than minimum fee for fund %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provision liegt unter der minimalen Provision für Fonds %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La comisión es inferior a la comisión mínima del fondo %FUNDNAME% %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Frais inférieurs aux frais minimaux pour le fonds %FUNDNAME% et la classe %CLASS%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kosten zijn minder dan minimumkosten voor fonds %FUNDNAME% %CLASS%")); }

        // Actions
	};
}



