#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_deal_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_deal_date() { }
		~CIFast_IFast_ifastcbo_err_future_deal_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DEAL_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Future Deal Date is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zukünftiges Handelsdatum nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite una fecha de operación en el futuro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une date d'opération postérieure à la date actuelle n'est pas autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toekomstige handelsdatum is niet toegestaan")); }

        // Actions
	};
}



