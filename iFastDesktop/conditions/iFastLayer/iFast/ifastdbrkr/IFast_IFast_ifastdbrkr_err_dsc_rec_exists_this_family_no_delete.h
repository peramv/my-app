#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dsc_rec_exists_this_family_no_delete : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dsc_rec_exists_this_family_no_delete() { }
		~CIFast_IFast_ifastdbrkr_err_dsc_rec_exists_this_family_no_delete() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DSC_REC_EXISTS_THIS_FAMILY_NO_DELETE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DSC record exists for this Family - cannot delete.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DSC record exists for this Family - cannot delete.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("DSC record exists for this Family - cannot delete.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement de FAR existe pour cette famille – suppression impossible.")); }

        // Actions
	};
}



