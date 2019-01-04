#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_more_than_one_record_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_more_than_one_record_found() { }
		~CIFast_IFast_ifastbp_bp_err_more_than_one_record_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_MORE_THAN_ONE_RECORD_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("More than one records found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("More than one records found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plus d'un enregistrement a été trouvé.")); }

        // Actions
	};
}



