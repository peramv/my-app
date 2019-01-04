﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_type_invalid_for_depot_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_type_invalid_for_depot_funds() { }
		~CIFast_IFast_ifastcbo_err_amount_type_invalid_for_depot_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_TYPE_INVALID_FOR_DEPOT_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type invalid for depot funds traded via network %ntwk%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount type invalid for depot funds traded via network %ntwk%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de montant invalide pour les fonds de dépôt traités par le réseau %ntwk%")); }

        // Actions
	};
}



