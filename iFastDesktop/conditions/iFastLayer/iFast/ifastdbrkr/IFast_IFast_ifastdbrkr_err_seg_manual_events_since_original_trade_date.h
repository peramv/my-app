#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_seg_manual_events_since_original_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_seg_manual_events_since_original_trade_date() { }
		~CIFast_IFast_ifastdbrkr_err_seg_manual_events_since_original_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There have been manual event(s) since the original trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a eu un/des événement(s) manuel(s) depuis la date de transaction d'origine.")); }

        // Actions
	};
}



