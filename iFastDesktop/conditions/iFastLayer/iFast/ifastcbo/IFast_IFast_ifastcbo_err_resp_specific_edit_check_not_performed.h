#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_specific_edit_check_not_performed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_specific_edit_check_not_performed() { }
		~CIFast_IFast_ifastcbo_err_resp_specific_edit_check_not_performed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_SPECIFIC_EDIT_CHECK_NOT_PERFORMED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP specific edit check is not being performed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le contrôle d'édition spécifique REEE n'est pas en cours d'exécution.")); }

        // Actions
	};
}



