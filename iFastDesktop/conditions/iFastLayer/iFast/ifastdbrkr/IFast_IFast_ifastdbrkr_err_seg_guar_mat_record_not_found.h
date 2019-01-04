#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_seg_guar_mat_record_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_seg_guar_mat_record_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_seg_guar_mat_record_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEG_GUAR_MAT_RECORD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Seg-Guar-Mat record not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'échéance de la garantie des fonds distincts est introuvable.")); }

        // Actions
	};
}



