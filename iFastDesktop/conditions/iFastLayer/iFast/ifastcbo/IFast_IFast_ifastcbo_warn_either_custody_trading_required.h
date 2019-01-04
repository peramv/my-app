#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_either_custody_trading_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_either_custody_trading_required() { }
		~CIFast_IFast_ifastcbo_warn_either_custody_trading_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EITHER_CUSTODY_TRADING_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account should be either Custody Client or Trading Client or Routing Clients")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account should be either a Custody Client or Trading Client")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte devrait être Client du dépôt de titres, Client de l'opération ou Sélection de clients.")); }

        // Actions
	};
}



