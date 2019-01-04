#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_settlement_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_settlement_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_net_settlement_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_Net_SETTLEMENT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net Settlement is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto-Abrechnung für diese Abrechnung ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite liquidación neta para esta liquidación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Règlement net non autorisé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto betaling is niet toegestaan voor deze betaling")); }

        // Actions
	};
}



