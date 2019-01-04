#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pending_trade_cannot_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pending_trade_cannot_exist() { }
		~CIFast_IFast_ifastdbrkr_err_pending_trade_cannot_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PENDING_TRADE_CANNOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trades cannot exist in old/new closing decade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pending trades cannot exist in old/new closing decade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des transactions en suspens ne peuvent exister dans l'ancienne/la nouvelle décennie de fermeture.")); }

        // Actions
	};
}



