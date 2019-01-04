#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams() { }
		~CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading on a global AMS model parent fund class is not allowed, as the account is not linked to any global model.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La négociation sur une catégorie de fonds parent modèle AMS mondiale n'est pas autorisée, le compte n'étant lié à aucun modèle mondial.")); }

        // Actions
	};
}