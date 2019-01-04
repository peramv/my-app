#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_charge_short_term_transfer_fee_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_charge_short_term_transfer_fee_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_charge_short_term_transfer_fee_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CHARGE_SHORT_TERM_TRANSFER_FEE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From fund/class and To fund/class combination does not allow charging short term transfer fees.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("From fund/class and To fund/class combination does not allow charging short term transfer fees.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La combinaison de fonds/de classe source et de fonds/de classe cible n'autorise pas le débit de frais de transfert à court terme.")); }

        // Actions
	};
}



