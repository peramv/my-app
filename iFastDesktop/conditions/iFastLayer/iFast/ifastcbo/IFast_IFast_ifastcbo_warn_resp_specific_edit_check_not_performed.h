#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_specific_edit_check_not_performed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_specific_edit_check_not_performed() { }
		~CIFast_IFast_ifastcbo_warn_resp_specific_edit_check_not_performed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_SPECIFIC_EDIT_CHECK_NOT_PERFORMED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP specific edit check is not being performed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP specific edit check is not being performed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("RESP specific edit check is not being performed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le contrôle d'édition spécifique REEE n'est pas en cours d'exécution.")); }

        // Actions
	};
}



