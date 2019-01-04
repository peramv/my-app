#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rule_type_record_for_stop_trfer_in_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rule_type_record_for_stop_trfer_in_required() { }
		~CIFast_IFast_ifastcbo_err_rule_type_record_for_stop_trfer_in_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RULE_TYPE_RECORD_FOR_STOP_TRFER_IN_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Transfer In must be set to \"Yes\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop Transfer In must be set to \"Yes\".")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Stop Transfer In must be set to \"Yes\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ d'arrêt du transfert doit être réglé à Oui.")); }

        // Actions
	};
}



