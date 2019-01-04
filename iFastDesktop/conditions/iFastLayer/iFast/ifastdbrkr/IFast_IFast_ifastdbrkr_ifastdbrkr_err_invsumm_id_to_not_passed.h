#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_invsumm_id_to_not_passed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_invsumm_id_to_not_passed() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_invsumm_id_to_not_passed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_INVSUMM_ID_TO_NOT_PASSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("InvSummID of TO is not passed to copy LSIF information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("InvSummID of TO is not passed to copy LSIF information.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de sommaire d'inventaire du transfert sortant n'est pas passé pour la copie de l'information FIT.")); }

        // Actions
	};
}



