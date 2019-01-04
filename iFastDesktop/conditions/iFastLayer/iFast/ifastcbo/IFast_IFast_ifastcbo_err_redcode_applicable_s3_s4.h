#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redcode_applicable_s3_s4 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redcode_applicable_s3_s4() { }
		~CIFast_IFast_ifastcbo_err_redcode_applicable_s3_s4() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDCODE_APPLICABLE_S3_S4")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redcode 'UP' is applicable for accounts with returned mail.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat UP s'applique aux comptes avec retour de courrier.")); }

        // Actions
	};
}



