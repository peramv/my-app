#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_remove_spouse_link_before_delete_owner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_remove_spouse_link_before_delete_owner() { }
		~CIFast_IFast_ifastcbo_err_remove_spouse_link_before_delete_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REMOVE_SPOUSE_LINK_BEFORE_DELETE_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please remove spousal-linkage before deleting account owner or spousal entity.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Please remove spousal-linkage before deleting account owner or spousal entity.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Please remove spousal-linkage before deleting account owner or spousal entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez supprimer le lien conjugal avant de supprimer le titulaire du compte ou l'entité conjointe.")); }

        // Actions
	};
}



