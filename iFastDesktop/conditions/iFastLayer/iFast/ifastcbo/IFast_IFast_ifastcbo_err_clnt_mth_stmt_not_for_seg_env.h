#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clnt_mth_stmt_not_for_seg_env : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clnt_mth_stmt_not_for_seg_env() { }
		~CIFast_IFast_ifastcbo_err_clnt_mth_stmt_not_for_seg_env() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLNT_MTH_STMT_NOT_FOR_SEG_ENV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client Monthly Statement Category is not for SEG environment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de relevé mensuel du client n'est pas pour un environnement de fonds distincts.")); }

        // Actions
	};
}



