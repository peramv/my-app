#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_tradedate_fundclass_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_tradedate_fundclass_blank() { }
		~CIFast_IFast_ifastdbrkr_err_tradedate_fundclass_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADEDATE_FUNDCLASS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade Date, Fund or Class cannot be blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Date de transaction, Fonds ou Classe doivent être remplis.")); }

        // Actions
	};
}



