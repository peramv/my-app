#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_update_pdsc_info : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_update_pdsc_info() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_update_pdsc_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_UPDATE_PDSC_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error updating PDSC information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Error updating PDSC information.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors de la mise à jour de l'information sur les FAR perpétuels")); }

        // Actions
	};
}



