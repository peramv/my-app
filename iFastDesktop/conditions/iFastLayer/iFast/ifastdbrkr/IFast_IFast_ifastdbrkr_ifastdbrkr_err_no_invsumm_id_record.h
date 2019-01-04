#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_invsumm_id_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_invsumm_id_record() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_invsumm_id_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_NO_INVSUMM_ID_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Inventory record with InvSummID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Inventory record with InvSummID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'inventaire avec le code de sommaire d'inventaire")); }

        // Actions
	};
}



