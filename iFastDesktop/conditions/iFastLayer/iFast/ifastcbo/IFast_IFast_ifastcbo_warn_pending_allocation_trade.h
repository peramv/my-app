﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pending_allocation_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pending_allocation_trade() { }
		~CIFast_IFast_ifastcbo_warn_pending_allocation_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WAR_PENDING_ALLOCATION_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date cannot be modified for pending allocated trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trade date cannot be modified for pending allocated trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction ne peut pas être modifiée pour le commerce alloué en attente")); }

        // Actions
	};
}



