#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_clnt_mth_stmt_should_belong_acct_non_mfda : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_clnt_mth_stmt_should_belong_acct_non_mfda() { }
		~CIFast_IFast_ifastcbo_warn_clnt_mth_stmt_should_belong_acct_non_mfda() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CLNT_MTH_STMT_SHOULD_BELONG_ACCT_NON_MFDA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("\"Client Monthly Statement\" account category should belong to the account for Non-MFDA Broker only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de compte avec relevé mensuel du client devrait appartenir au compte pour les courtiers membres de la MFDA uniquement.")); }

        // Actions
	};
}



