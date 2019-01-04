#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transfer_track_del_if_outstanding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transfer_track_del_if_outstanding() { }
		~CIFast_IFast_ifastdbrkr_err_transfer_track_del_if_outstanding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TRACK_DEL_IF_OUTSTANDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Can only delete transfer tracking that has status of Outstanding.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Can only delete transfer tracking that has status of Outstanding.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Can only delete transfer tracking that has status of Outstanding.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul un suivi de transfert ayant un statut En cours peut être supprimé.")); }

        // Actions
	};
}



