#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_err_user_no_permission_override_ams_alloc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_err_user_no_permission_override_ams_alloc() { }
		~CIFast_IFast_ifastcbo_ams_err_user_no_permission_override_ams_alloc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_ERR_USER_NO_PERMISSION_OVERRIDE_AMS_ALLOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have permission to override AMS Allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User does not have permission to override AMS Allocation.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("User does not have permission to override AMS Allocation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à modifier la répartition de service de gestion de portefeuille.")); }

        // Actions
	};
}



