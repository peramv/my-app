#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_non_qesi_env : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_non_qesi_env() { }
		~CIFast_IFast_ifastcbo_err_deptype_redcode_not_allowed_non_qesi_env() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPTYPE_REDCODE_NOT_ALLOWED_NON_QESI_ENV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type or Redemption code not available on non QESI environment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt ou de rachat non disponible dans un environnement non IQEE.")); }

        // Actions
	};
}



