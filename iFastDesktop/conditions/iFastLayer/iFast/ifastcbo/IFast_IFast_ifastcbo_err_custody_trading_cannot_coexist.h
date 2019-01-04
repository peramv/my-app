#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_custody_trading_cannot_coexist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_custody_trading_cannot_coexist() { }
		~CIFast_IFast_ifastcbo_err_custody_trading_cannot_coexist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CUSTODY_TRADING_CANNOT_COEXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account can be setup with only one category out of Trading, Custody and Routing Client")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Custody Client and Trading Client cannot coexist")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte ne peut être réglé qu'avec une seule catégorie parmi le client de l'opération, le client du dépôt de titres et la sélection de client.")); }

        // Actions
	};
}



