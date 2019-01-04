#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_guar_trans_events_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_guar_trans_events_exist() { }
		~CIFast_IFast_ifastcbo_err_guar_trans_events_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GUAR_TRANS_EVENTS_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Add/Modify/Delete not allowed since transactions/events exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ajouter/Modifier/Supprimer n'est pas autorisé puisque des transactions/des événements existent.")); }

        // Actions
	};
}



